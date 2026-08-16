import pandas as pd
import matplotlib.pyplot as plt

try:
    df = pd.read_csv('q6_data.csv')
except FileNotFoundError:
    print("Error: 'q6_data.csv' not found. Please run the C program first.")
    exit()

plt.figure(figsize=(9, 5))

# Plotting the three scenarios and theoretical exact formula
plt.plot(df['N'], df['Random'], marker='o', color='blue', linewidth=3, label='Random Input')
plt.plot(df['N'], df['Reverse'], marker='s', color='red', linestyle='--', linewidth=2, label='Reverse Sorted (Worst)')
plt.plot(df['N'], df['Sorted'], marker='^', color='green', linestyle=':', linewidth=2, label='Sorted (Best)')
plt.plot(df['N'], df['Exact'], color='black', alpha=0.5, label='Exact $n(n-1)/2$')

plt.title("Selection Sort Complexity: Independent of Input Order")
plt.xlabel("Array Size (N)")
plt.ylabel("Number of Comparisons")
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('q6_plot.png', dpi=300)
print("Graph saved!")