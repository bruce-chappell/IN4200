import matplotlib.pyplot as plt
import numpy as np

# PARALLEL implementation
threads = np.arange(1,9)
matrix_count = [5.138, 2.713, 1.699, 1.316, 1.312, 1.299, 1.241, 1.205]
crs_count = [0.000806, 0.000664, 0.000582, 0.000527, 0.000557, 0.000658, 0.000723, 0.000740]
top_n = [0.00065, 0.00499, 0.000417, 0.000428, 0.000366, 0.000357, 0.000260, 0.000360]

#CONSTANTS
base = np.ones(8)
matrix_const = 4.408*base
crs_const = 0.000688*base
top_const = 0.000639*base

fig, ax = plt.subplots(figsize = (6.86906, 6.86906 / 1.618))
ax.plot(threads, matrix_count, label = "Full Matrix: Parallel")
ax.plot(threads, matrix_const, label = "Full Matrix: Serial")
ax.set_ylabel("Time [s]")
ax.set_xlabel("Number of Threads")
ax.grid()
legend = fig.legend()
fig.tight_layout()
frame = legend.get_frame()
frame.set_facecolor("white")
fig.savefig("../figures/full_mat.jpg", dpi=1000)
plt.close()

fig, ax = plt.subplots(figsize = (6.86906, 6.86906 / 1.618))
ax.plot(threads, crs_count, label = "CRS: Parallel")
ax.plot(threads, crs_const, label = "CRS: Serial")
ax.set_ylabel("Time [s]")
ax.set_xlabel("Number of Threads")
ax.grid()
legend = fig.legend()
fig.tight_layout()
frame = legend.get_frame()
frame.set_facecolor("white")
fig.savefig("../figures/crs.jpg", dpi=1000)
plt.close()

fig, ax = plt.subplots(figsize = (6.86906, 6.86906 / 1.618))
ax.plot(threads, top_n, label = "Top_N: Parallel")
ax.plot(threads, top_const, label = "Top_N: Serial")
ax.set_ylabel("Time [s]")
ax.set_xlabel("Number of Threads")
ax.grid()
legend = fig.legend()
fig.tight_layout()
frame = legend.get_frame()
frame.set_facecolor("white")
fig.savefig("../figures/top_N.jpg", dpi=1000)
plt.close()
