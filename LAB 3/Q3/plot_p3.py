import pandas as pd
import matplotlib.pyplot as plt

try:
    df = pd.read_csv('q3_data.csv')
except FileNotFoundError:
    print("Error: 'q3_data.csv' not found. Run the C program first.")
    exit()

plt.figure(figsize=(9, 5))

plt.plot(df['N'], df['Naive_Comps'], marker='o', label='Naive Linear Scan', color='red')
plt.plot(df['N'], df['DC_Comps'], marker='s', label='Divide & Conquer', color='blue')
plt.plot(df['N'], df['Theoretical'], marker='^', linestyle='--', color='black', label='Theoretical 3N/2 - 2')

plt.title('Min-Max Algorithm: Divide & Conquer vs Naive Scan')
plt.xlabel('Array Size (N)')
plt.ylabel('Number of Comparisons')
plt.legend()
plt.grid(True, linestyle='--', alpha=0.6)

plt.tight_layout()
plt.savefig('q3_plot.png')
print("Graph saved!")