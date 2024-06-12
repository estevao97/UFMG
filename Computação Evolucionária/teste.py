import json

import matplotlib.pyplot as plt
import numpy as np


# Exemplo de função de fitness
def fitness(item):
    # Calcule a aptidão com base na população e na área, por exemplo
    return max(item["population"], 0)


# Função para criar o mapa 3D
def create_3d_relief_map(data):
    # Extrair as coordenadas, população, área e calcular o fitness
    lats = []
    lons = []
    radii = []
    fitness_values = []
    names = []

    for item in data:
        coords = item["coordinates"].split(", ")
        lats.append(float(coords[0]))
        lons.append(float(coords[1]))
        radii.append(item["radius"])
        fitness_values.append(fitness(item))
        names.append(item["name"])

    # Convertendo listas para arrays numpy
    lats = np.array(lats)
    lons = np.array(lons)
    radii = np.array(radii)
    fitness_values = np.array(fitness_values)

    # Criar uma grade de longitude e latitude
    lon_grid, lat_grid = np.meshgrid(np.linspace(lons.min(), lons.max(), 100),
                                     np.linspace(lats.min(), lats.max(), 100))

    # Interpolar os valores de fitness para a grade
    from scipy.interpolate import griddata
    fitness_grid = griddata((lons, lats),
                            fitness_values, (lon_grid, lat_grid),
                            method='linear')

    # Criar a figura e o eixo 3D
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Plotar os dados como uma superfície
    surf = ax.plot_surface(lon_grid, lat_grid, fitness_grid, cmap='viridis')

    # Adicionar barra de cores
    colorbar = fig.colorbar(surf, ax=ax, pad=0.1)
    colorbar.set_label('Fitness')

    # Adicionar títulos e rótulos
    ax.set_title('Mapa 3D do Problema de PSO (Relevo)')
    ax.set_xlabel('Longitude')
    ax.set_ylabel('Latitude')
    ax.set_zlabel('Fitness')

    # Mostrar o gráfico
    # plt.show()
    plt.savefig("graficao3D.png")
    plt.close()


# Função para ler clientes de um arquivo JSON
def read_clients_from_file(filename):
    with open(filename, 'r', encoding='utf-8') as file:
        content = file.read()
        return json.loads(content)


# Filtrar clientes que possuem coordenadas
def filter_clients_with_corrdinates(clients):
    return [client for client in clients if 'coordinates' in client]


# Ler e filtrar clientes do arquivo
clients = filter_clients_with_corrdinates(
    read_clients_from_file("bairros_bh_v2.json"))

# Criar o mapa 3D
create_3d_relief_map(clients)
