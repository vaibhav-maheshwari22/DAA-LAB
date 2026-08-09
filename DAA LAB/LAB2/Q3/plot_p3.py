import csv
import matplotlib.pyplot as plt

k_vals, time_seq, time_dc = [], [], []

try:
    with open('q3_benchmark.csv', 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            k_vals.append(int(row['K']))
            time_seq.append(float(row['Time_Sequential']))
            time_dc.append(float(row['Time_DivideConquer']))
except FileNotFoundError:
    print("Error: 'q3_benchmark.csv' not found. Please run the C program first.")
    exit()

plt.figure(figsize=(10, 6))

# Sequential Merge represents O(n * k^2)
plt.plot(k_vals, time_seq, marker='o', color='#d62728', linewidth=2.5, markersize=8, label='Sequential Merge $O(n \\cdot k^2)$')
# Divide & Conquer represents O(n * k * log k)
plt.plot(k_vals, time_dc, marker='s', color='#2ca02c', linewidth=2.5, markersize=8, label='Divide & Conquer $O(n \\cdot k \\log_2 k)$')

plt.title('Performance Validation: Merging K Sorted Arrays', fontsize=14, fontweight='bold')
plt.xlabel('Number of Arrays (K) [Fixed N = 1000]', fontsize=12)
plt.ylabel('Execution Time (Seconds)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(fontsize=12, loc='upper left')
plt.tight_layout()

plt.savefig('q3_plot.png', dpi=300)
print("Successfully generated 'q3_plot.png'")