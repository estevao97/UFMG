import math

import matplotlib.pyplot as plt
import pyswarms as ps
from matplotlib.patches import Circle
from numpy import array, random


def create_random_point(x_bounds, y_bounds):
    x = random.randint(x_bounds[0], x_bounds[1])
    y = random.randint(y_bounds[0], y_bounds[1])
    return x, y


def generate_random_region(x_bounds, y_bounds):
    radius = random.randint(10, 12)  # Define a radius between 10 and 20
    x_center = random.randint(x_bounds[0] + radius, x_bounds[1] - radius)
    y_center = random.randint(y_bounds[0] + radius, y_bounds[1] - radius)

    return (x_center, y_center, radius)


def create_random_clients_in_regions(num_clients, regions):
    clients = []
    for region in regions:
        x_center, y_center, radius = region
        region_clients = num_clients // len(regions)
        for _ in range(region_clients):
            while True:
                point = create_random_point(
                    (x_center - radius, x_center + radius),
                    (y_center - radius, y_center + radius))
                if get_distance_between_points((x_center, y_center),
                                               point) <= radius:
                    clients.append(point)
                    break
    return clients


def get_distance_between_points(point_a, point_b):
    x_dist = point_b[0] - point_a[0]
    y_dist = point_b[1] - point_a[1]
    return math.sqrt(x_dist * x_dist + y_dist * y_dist)


def calculate_total_distances_one_to_many(reference_point, other_points):
    total_dist = 0
    for current_point in other_points:
        total_dist += get_distance_between_points(reference_point,
                                                  current_point)
    return total_dist


def fitness(x, clients):
    total_dist = 0
    num_medians = len(x) // 2
    for client in clients:
        min_dist = float('inf')
        for i in range(num_medians):
            median = (x[i * 2], x[i * 2 + 1])
            dist = get_distance_between_points(client, median)
            if dist < min_dist:
                min_dist = dist
        total_dist += min_dist
    return total_dist


def pso_pmedian(num_medians,
                num_clients,
                regions,
                x_bounds,
                y_bounds,
                num_particles=100,
                iters=100):
    # Generate random clients
    clients = create_random_clients_in_regions(num_clients, regions)

    bounds = (array([x_bounds[0], y_bounds[0]] * num_medians),
              array([x_bounds[1], y_bounds[1]] * num_medians))

    # Define the fitness function wrapper for PSO
    def fitness_wrapper(x):
        n_particles = x.shape[0]
        fitness_values = [fitness(x[i], clients) for i in range(n_particles)]
        return array(fitness_values)

    # Initialize the optimizer
    options = {'c1': 0.5, 'c2': 0.3, 'w': 0.9}
    optimizer = ps.single.GlobalBestPSO(n_particles=num_particles,
                                        dimensions=num_medians * 2,
                                        options=options,
                                        bounds=bounds)

    # Perform optimization
    best_cost, best_pos = optimizer.optimize(fitness_wrapper, iters=iters)

    # Return the results
    best_medians = [(best_pos[i * 2], best_pos[i * 2 + 1])
                    for i in range(num_medians)]
    return clients, best_medians, best_cost


def plot_map(clients,
             medians,
             regions,
             x_bounds,
             y_bounds,
             filename='mapa_pmedians.png'):
    plt.figure(figsize=(10, 10))
    client_x, client_y = zip(*clients)
    median_x, median_y = zip(*medians)

    # Plot regions with low opacity as circles
    for region in regions:
        x_center, y_center, radius = region
        circle = Circle((x_center, y_center), radius, color='green', alpha=0.3)
        plt.gca().add_patch(circle)

    plt.scatter(client_x, client_y, c='blue', label='Clientes')
    plt.scatter(median_x,
                median_y,
                c='red',
                marker='x',
                s=100,
                label='Medians')
    plt.title('Mapa de Clientes e Medians')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.xlim(x_bounds)
    plt.ylim(y_bounds)
    plt.legend()
    plt.grid(True)
    plt.savefig(filename)
    plt.close()


# Example usage
num_medians = 3
num_clients = 30
# Set up the bounds for the medians
x_bounds = [0, 100]
y_bounds = [0, 100]
regions = [generate_random_region((0, 100), (0, 100)) for _ in range(4)]
clients, best_medians, best_cost = pso_pmedian(num_medians, num_clients,
                                               regions, x_bounds, y_bounds)
print("Best Medians:", best_medians)
print("Best Cost:", best_cost)

# Plot the results and save the image
plot_map(clients, best_medians, regions, x_bounds, y_bounds)
