import matplotlib.pyplot as plt
import numpy as np


final_array = np.load('final_array.npy', 'r')
initial_array = np.load('initial_array.npy', 'r')

plt.plot(final_array, label='Final', color='red', linestyle='dashed')
plt.plot(initial_array, label='Initial', color='black')
plt.legend()
plt.show()