import csv
import matplotlib.pyplot as plt

sizes, time_2way, time_3way = [], [], []

try:
    with open('q2_merge_comparison.csv', 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            sizes.append(int(row['Size']))
            time_2way.append(float(row['Time_2Way']))
            time_3way.append(float(row['Time_3Way']))
except FileNotFoundError:
    print("Error: 'q2_merge_comparison.csv' not found. Please run the C program first.")
    exit()

plt.figure(figsize=(10, 6))
plt.plot(sizes, time_2way, marker='o', color='#1f77b4', linewidth=2.5, markersize=8, label='2-Way Merge Sort $O(n \\log_2 n)$')
plt.plot(sizes, time_3way, marker='s', color='#ff7f0e', linewidth=2.5, markersize=8, label='3-Way Merge Sort $O(n \\log_3 n)$')

plt.title('Performance Validation: 2-Way vs 3-Way Merge Sort', fontsize=14, fontweight='bold')
plt.xlabel('Number of Elements (N)', fontsize=12)
plt.ylabel('Execution Time (Seconds)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(fontsize=12)
plt.tight_layout()

plt.savefig('q2_plot.png', dpi=300)
print("Successfully generated!")