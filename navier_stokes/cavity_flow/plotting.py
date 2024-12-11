import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

print("Plotting...")
final_vx_array = np.reshape(np.load("final_vx.npy", "r"), (100, 100))
final_vy_array = np.reshape(np.load("final_vy.npy", "r"), (100, 100))
final_p_array = np.reshape(np.load("final_p.npy", "r"), (100, 100))

fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(18, 6))

ax1.imshow(final_vx_array, cmap="coolwarm")
ax1.set_title("Final Vx Array")

ax2.imshow(final_vy_array, cmap="coolwarm")
ax2.set_title("Final Vy Array")

ax3.imshow(final_p_array, cmap="coolwarm")
ax3.set_title("Final P Array")

plt.tight_layout()
plt.show()
