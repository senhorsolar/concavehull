import numpy as np
import time

from concavehull import concavehull
    
n = 500
pts = np.random.randn(n,2)

s = time.time()
chi_factor = 0.05
ch = concavehull(pts, chi_factor=chi_factor)

print(f"found concave hull in {time.time() - s:0.5f}s")

try:
    import matplotlib.pyplot as plt

    plt.scatter(pts[:,0], pts[:,1])
    plt.plot(ch[:,0], ch[:,1])
    plt.title(f"Concave Hull\nChi Factor: {chi_factor}")
    plt.show()

except ImportError:
    print("Tried plotting, but matplotlib not found")
