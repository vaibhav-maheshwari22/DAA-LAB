import csv
import matplotlib.pyplot as plt

# Initialize lists
n_vals = []
opt_comps = []
strict_comps = []


with open('q3_data.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        n_vals.append(int(row['n']))
        opt_comps.append(int(row['optimized_comparisons']))
        strict_comps.append(int(row['strict_comparisons']))

plt.figure(figsize=(10, 6))

# Plot both variants
plt.plot(n_vals, opt_comps, label='Optimized (Early Exit)', marker='o', color='green')
plt.plot(n_vals, strict_comps, label='Strict (Full Passes)', marker='x', color='red')


# Configure labels, title, and grid
plt.title('Bubble Sort Performance Analysis')
plt.xlabel('Array Size (n)')
plt.ylabel('Number of Comparisons')
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()
plt.tight_layout()

plt.savefig('q3_graph.png')

print("Graph saved as q3_graph.png successfully!")
