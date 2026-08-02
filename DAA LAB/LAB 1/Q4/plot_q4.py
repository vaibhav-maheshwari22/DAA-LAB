import csv
import matplotlib.pyplot as plt

# Initialize lists
n_vals = []
total_moves = []

# Read the data
with open('q4_data.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        n_vals.append(int(row['n']))
        total_moves.append(int(row['total_moves']))

plt.figure(figsize=(10, 6))

# Plot the growth curve
plt.plot(n_vals, total_moves, marker='o', color='purple')

# Add labels, title, and styling
plt.title('Towers of Hanoi: Moves vs Number of Discs')
plt.xlabel('Number of Discs (n)')
plt.ylabel('Total Moves Required')
plt.grid(True, linestyle='--', alpha=0.7)
plt.tight_layout()

plt.savefig('q4_graph.png')

print("Graph saved as q4_graph.png successfully!")
