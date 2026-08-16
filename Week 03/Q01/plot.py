import numpy as np
import matplotlib.pyplot as plt

# Generate a dense, continuous array of N values for a perfectly smooth curve
N = np.linspace(100, 1000000, 1000)

# Theoretical continuous formulas for maximum comparisons
bin_theory = 2 * np.log2(N)
ter_theory = 4 * (np.log(N) / np.log(3))

plt.figure(figsize=(10, 6))

# Plotting
plt.plot(N, bin_theory, label=r'Binary Search ($2 \log_2 N$)', color='blue', linewidth=2.5)
plt.plot(N, ter_theory, label=r'Ternary Search ($4 \log_3 N$)', color='red', linewidth=2.5)

# Formatting the graph
plt.title('Theoretical Comparison Count vs Array Size (N)', fontsize=14, fontweight='bold')
plt.xlabel('Array Size (N)', fontsize=12)
plt.ylabel('Max Number of Comparisons', fontsize=12)
plt.legend(fontsize=12)

plt.grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('search_comps.png', dpi=300)
