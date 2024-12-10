import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D


intial_array = np.reshape(np.load("initial_array.npy", "r"), (100, 100))
final_array = np.reshape(np.load("final_array.npy", "r"), (100, 100))

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))

ax1.imshow(intial_array, cmap="viridis")
ax1.set_title("Initial Array")

ax2.imshow(final_array, cmap="viridis")
ax2.set_title("Final Array")

plt.show()
