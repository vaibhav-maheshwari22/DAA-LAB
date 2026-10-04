import csv
import matplotlib.pyplot as plt

# Initialize data structures
n_vals = []
columns = ["log2n", "12sqrtn", "50sqrtn", "n051", "nlog2n", "n2_minus324", "100n2_6n", "2n3", "nlog2n_pow", "pow3n"]
data = {col: [] for col in columns}

with open('q1_data.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        n_vals.append(float(row['n']))
        for col in columns:
            data[col].append(float(row[col]))

plt.figure(figsize=(12, 8))

# Plot each function's growth curve
for col in columns:
    plt.plot(n_vals, data[col], label=col)

# Apply logarithmic scale
plt.yscale('log')
plt.ylim(1, 10**12)

# Apply professional styling and labels
plt.title('Growth Rate Comparison of Functions (Log Scale)')
plt.xlabel('Input Size (n)')
plt.ylabel('Operations (Log Scale)')
plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()

plt.savefig('q1_graph.png')

print("Graph saved as q1_graph.png successfully without Pandas!")
