import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.fftpack import fftn, ifftn
from noise import pnoise2
from matplotlib.colors import LinearSegmentedColormap

alphabet = 'abcdefghijklmnopqrstuvwxyz'

def generate_terrain(size, octaves=10, scale_factor=100, max_height=1000):
    terrain = np.zeros((size, size))

    # Create base terrain using Perlin noise
    scale = scale_factor
    for x in range(size):
        for y in range(size):
            terrain[x, y] += pnoise2(x/scale, y/scale, octaves=octaves) * max_height

    # Define peaks
    peaks = [(300, 300), (500, 700), (700, 450), (800, 300), (800, 700), (900, 600), (500, 900)]
    for peak in peaks:
        x_peak, y_peak = peak
        for x in range(size):
            for y in range(size):
                distance = np.sqrt((x - x_peak)**2 + (y - y_peak)**2)
                height = max_height * np.exp(-distance**2 / (2 * (70)**2))
                terrain[x, y] += height

    # Add random noise for sharpness
    terrain += np.random.normal(scale=70, size=(size, size))

    save_data(terrain, 'terrain.txt')

    return terrain

def reduce_fourier_descriptor(descriptor, num_coefficients):
    flattened_descriptor = np.abs(descriptor.flatten())
    threshold = np.sort(flattened_descriptor)[-num_coefficients]
    reduced_descriptor = np.where(np.abs(descriptor) >= threshold, descriptor, 0)
    return reduced_descriptor

def plot_3d_terrain(terrain, index, title, filename):
    fig = plt.figure(figsize=(10, 10))
    ax = fig.add_subplot(111, projection='3d')
    size = terrain.shape[0]
    x, y = np.meshgrid(range(size), range(size))

    # Define custom colormap
    custom_colors = {
        'red': [(0, 0.05, 0.05), (0.7, 0.6, 0.6), (0.85, 0.3, 0.3), (0.9, 0, 0), (1, 1, 1)],
        'green': [(0, 0.25, 0.25), (0.7, 0.5, 0.5), (0.85, 0.2, 0.2), (0.9, 0, 0), (1, 1, 1)],
        'blue': [(0, 0, 0), (0.7, 0, 0), (0.85, 0, 0), (0.9, 0, 0), (1, 1, 1)]
    }
    custom_cmap = LinearSegmentedColormap('custom_cmap', custom_colors)

    ax.plot_surface(x, y, terrain, cmap=custom_cmap)
    plt.title(alphabet[index] + ')    ' + title, fontweight='bold', fontsize=15)
    ax.set_xlim([0, 1000])
    ax.set_ylim([0, 1000])
    ax.set_zlim([0, 1000])
    ax.set_xlabel('X', labelpad=25)
    ax.set_ylabel('Y', labelpad=25)
    ax.set_zlabel('Z', labelpad=25)
    ax.tick_params(axis='x', length=25, which='major', pad=25)
    ax.tick_params(axis='y', length=25, which='major', pad=25)
    ax.tick_params(axis='z', length=25, which='major', pad=15)
    plt.savefig(filename, dpi=600)
    plt.close()

def plot_fourier_descriptor(descriptor, title, filename):
    plt.imshow(np.log(np.abs(descriptor)))
    plt.title(title, fontsize=15)
    plt.colorbar()
    plt.savefig(filename, dpi=600)
    plt.close()

def save_data(data, filename):
    file = open(filename, 'w')
    count = 0
    for element in data:
        for item in element:
            if not item == 0:
                count += 1

#    	print(str(element), file=file)
    print(str(count), file=file)

# Terrain parameters
size = 1000

# Generate original terrain
terrain = generate_terrain(size)

# Perform Fourier transform
fourier_descriptor = fftn(terrain)

# Reduce coefficients
coefficients_to_reduce = [10000, 5000, 2000, 1000, 500, 200, 100, 50]
reduced_fourier_descriptors = [reduce_fourier_descriptor(fourier_descriptor, coef) for coef in coefficients_to_reduce]

# Reconstruct terrains
reconstructed_terrains = [np.real(ifftn(reduced_fd)) for reduced_fd in reduced_fourier_descriptors]

index = 0
# Save plots

plot_3d_terrain(terrain, index, 'Plot of 1,000,000 generated points in 3D Euclidean space representing terrain', 'original.png')

for coef, recon_terrain, reduced_fd in zip(coefficients_to_reduce, reconstructed_terrains, reduced_fourier_descriptors):
    index += 1
    plot_3d_terrain(recon_terrain, index, f'Mesh reconstructed from Fourier Descriptor with {coef} coefficients', f'reconstructed_{coef}.png')
    save_data(reduced_fd, 'fourier_descriptor_' + str(coef) + '.txt')
#    plot_fourier_descriptor(reduced_fd, f'Fourier Descriptor with {coef} coefficients', f'fourier_{coef}.png')
