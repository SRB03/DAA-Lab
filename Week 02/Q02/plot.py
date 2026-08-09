import pandas as pd
import matplotlib.pyplot as plt

# 1. Read the CSV output from the C program
df = pd.read_csv('merge_sort_results.csv', skipinitialspace=True)

# Retrieve column names for easy access
col_x = df.columns[0]
col_y1 = df.columns[1]
col_y2 = df.columns[2]

# 2. Set up the plot figure size
plt.figure(figsize=(10, 6))

# 3. Plot both lines 
plt.plot(df[col_x], df[col_y1], marker='o', linewidth=2, color='blue', label='2-Way Merge Sort')
plt.plot(df[col_x], df[col_y2], marker='s', linewidth=2, color='red', label='3-Way Merge Sort')

# 4. Customize titles, labels, and visual grid
plt.title('Time Complexity Comparison: 2-Way vs 3-Way Merge Sort', fontsize=14, fontweight='bold')
plt.xlabel('Array Size (N)', fontsize=12)
plt.ylabel('Time (Seconds)', fontsize=12)

# Add a grid for easier reading
plt.grid(True, linestyle='--', alpha=0.7)

# Add the legend
plt.legend(fontsize=12)

# Adjust layout to prevent clipping
plt.tight_layout()

# 5. Save the output to a PNG file
plt.savefig('merge_sort_plot.png', dpi=300)
print("Plot successfully saved to merge_sort_plot.png")