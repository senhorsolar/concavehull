import matplotlib.pyplot as plt
import numpy as np

convexhull = np.loadtxt("convexhull.txt", dtype=float, delimiter="\n").reshape(-1,2)
concavehull = np.loadtxt("concavehull.txt", dtype=float, delimiter="\n").reshape(-1,2)
pts = np.loadtxt("coords.txt", dtype=float, delimiter="\n").reshape(-1,2)

plt.scatter(pts[:,0], pts[:,1], alpha=0.3)
plt.plot(convexhull[:,0], convexhull[:,1])
plt.plot(concavehull[:,0], concavehull[:,1])

for i, (x, y) in enumerate(concavehull):
    plt.annotate(f"{i}", (x, y))

plt.show()
