import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

print("Plotting...")
final_v_array = np.reshape(np.load("final_v.npy", "r"), (100, 100))
final_p_array = np.reshape(np.load("final_p.npy", "r"), (100, 100))

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(18, 6))

ax1.imshow(final_v_array, cmap="coolwarm")
ax1.set_title("Final V Array")

ax2.imshow(final_p_array, cmap="coolwarm")
ax2.set_title("Final P Array")

plt.tight_layout()
plt.show()
