import numpy as np

size = 10000  # 100x100 matrix
density = 0.05  # 5% of connections will be 1s

# Generate random floats between 0 and 1, then convert to 0 or 1
matrix = (np.random.rand(size, size) < density).astype(int)

# Optional: Remove self-loops (zeros on the diagonal)
np.fill_diagonal(matrix, 0)

# Save it
np.savetxt("random_2.txt", matrix, delimiter=" ", fmt='%d')