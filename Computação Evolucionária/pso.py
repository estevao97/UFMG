import json
import math

import matplotlib.pyplot as plt
import numpy as np
import pyswarms as ps

MEDIAN_RADIUS = 45  # Increase as number of medians decreases (to highlight them)
'''
Client format:

{
  "name": "Buritis",
  "population": "29374",
  "area": "3823",
  "radius": 34.88407508994085,
  "coordinates": "-19.981873247174203, -43.98007179914421"
}
'''


def get_distance_between_points(point_a, point_b):
    y_dist = point_b[0] - point_a[0]
    x_dist = point_b[1] - point_a[1]
    return math.sqrt(x_dist * x_dist + y_dist * y_dist)


def get_median_distance_to_point(point, medians):
    min_distance = float('inf')
    for median in medians:
        dist = get_distance_between_points(point, median)
        if dist < min_distance:
            min_distance = dist
    return min_distance


def concat_floating_and_fixed_medians(floating_medians, fixed_medians):
    # Inicializa a lista de resultados com as medianas fixas
    result = list(fixed_medians)

    # Concatena as medianas flutuantes com as medianas fixas
    for i in range(0, len(floating_medians), 2):
        result.append((floating_medians[i], floating_medians[i + 1]))

    return result


def fitness(floating_medians, clients, fixed_medians):
    total_cost = 0
    all_medians = concat_floating_and_fixed_medians(floating_medians,
                                                    fixed_medians)

    for client in clients:
        y, x = parse_client_coordinates(client)
        total_cost += get_median_distance_to_point(
            [x, y], all_medians) * client["population"]

    return total_cost


def read_clients_from_file(filename):
    with open(filename, 'r', encoding='utf-8') as file:
        content = file.read()
        return json.loads(content)


def filter_clients_with_coordinates(clients):
    return [client for client in clients if 'coordinates' in client]


def parse_client_coordinates(client):
    latitude, longitude = client['coordinates'].split(",")
    return float(latitude), float(longitude)


def zip_client_coordinates(clients):
    zipped = [[], []]
    for client in clients:
        coordinates = parse_client_coordinates(client)
        zipped[0].append(coordinates[1])  # Longitude as X
        zipped[1].append(coordinates[0])  # Latitude as Y
    return zipped


def get_client_opacity(client, clients_list):
    max_opacity = 1
    min_opacity = 0.3

    max_population = max(client['population'] for client in clients_list)
    min_population = min(client['population'] for client in clients_list)
    client_population = client['population']
    opacity = (client_population - min_population) / (max_population -
                                                      min_population)
    return max(min_opacity, min(max_opacity, opacity))


def plot_map(clients,
             fixed_medians,
             optimized_medians,
             x_bounds,
             y_bounds,
             filename='mapa_pmedians.png'):
    plt.figure(figsize=(10, 10))
    client_x, client_y = zip_client_coordinates(clients)

    if fixed_medians:
        fixed_median_x, fixed_median_y = zip(*fixed_medians)
        plt.scatter(fixed_median_x,
                    fixed_median_y,
                    c='blue',
                    s=MEDIAN_RADIUS,
                    label='Fixed Medians')

    if optimized_medians:
        optimized_median_x, optimized_median_y = zip(*optimized_medians)
        plt.scatter(optimized_median_x,
                    optimized_median_y,
                    c='red',
                    s=MEDIAN_RADIUS,
                    label='Optimized Medians')

    # Plot regions with low opacity as circles
    for client in clients:
        y_center, x_center = parse_client_coordinates(client)
        plt.scatter(x_center,
                    y_center,
                    s=client["radius"] * 400,
                    alpha=get_client_opacity(client, clients),
                    c="grey")

    plt.title('Mapa de Clientes e Medians')
    plt.xlabel('Longitude')
    plt.ylabel('Latitude')
    plt.xlim(x_bounds)
    plt.ylim(y_bounds)
    plt.legend()
    plt.grid(True)
    plt.savefig(filename)
    plt.close()


def pso_pmedian(clients,
                num_medians,
                x_bounds,
                y_bounds,
                options,
                fixed_medians=[],
                num_particles=100,
                iters=100):
    num_free_medians = num_medians - len(fixed_medians)

    if num_free_medians < 0:
        raise ValueError(
            "Number of fixed medians cannot exceed the total number of medians."
        )

    # Set up the bounds for the medians
    bounds = (np.array([x_bounds[0], y_bounds[0]] * num_free_medians),
              np.array([x_bounds[1], y_bounds[1]] * num_free_medians))

    # Define the fitness function wrapper for PSO
    def fitness_wrapper(x):
        n_particles = x.shape[0]
        fitness_values = [
            fitness(x[i], clients, fixed_medians) for i in range(n_particles)
        ]
        return np.array(fitness_values)

    # Initialize the optimizer
    optimizer = ps.single.GlobalBestPSO(n_particles=num_particles,
                                        dimensions=num_free_medians * 2,
                                        options=options,
                                        bounds=bounds)

    # Perform optimization
    best_cost, best_pos = optimizer.optimize(fitness_wrapper, iters=iters)

    # Combine fixed medians with optimized medians
    best_medians = [(best_pos[i * 2], best_pos[i * 2 + 1])
                    for i in range(num_free_medians)]
    return fixed_medians, best_medians, best_cost


# Example usage
# File with clients data
filename = "bairros_bh_v2.json"
clients = filter_clients_with_coordinates(read_clients_from_file(filename))

num_medians = 10
x_bounds = (-44.15, -43.80)  # Longitude bounds
y_bounds = (-20.05, -19.75)  # Latitude bounds
c1 = 0.3
c2 = 0.7
w = 0.2
iters=200
options = {"c1": c1, "c2": c2, "w": w}


# Define fixed medians (longitude, latitude)
fixed_medians2 = [
    (-43.92692909130526, -19.935822934244335),  # Araújo Funcionários
    (-44.02467943241981, -19.976970685295015),  # Araújo Barreiro
    (-43.97656281607443, -19.976770270056527),  # Araujo Buritis
    (-43.94409945257786, -19.922809344453064),  # Araujo Raul Soares
    (-43.95029194142025, -19.863253586759335)  # Araújo Jaraguá
]

# Define fixed medians (longitude, latitude)
fixed_medians = [

]

fixed_medians, optimized_medians, best_cost = pso_pmedian(clients,
                                                          num_medians,
                                                          x_bounds,
                                                          y_bounds,
                                                          options,
                                                          fixed_medians,
                                                          num_particles=100,
                                                          iters=iters)

print("Best Cost:", best_cost)

# Plot graph
map_filename = f"./imgs/mapa_pmedians_f{len(fixed_medians)}_t{num_medians}_c1{c1}_c2{c2}_w{w}_i{iters}.png"
plot_map(clients, fixed_medians, optimized_medians, x_bounds, y_bounds,
         map_filename)
