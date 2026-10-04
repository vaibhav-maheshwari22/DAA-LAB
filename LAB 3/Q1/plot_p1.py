import pandas as pd
import matplotlib.pyplot as plt

# Read CSV naturally
df = pd.read_csv('q1_search_data.csv')

plt.figure(figsize=(10, 4))

# Plot 1: Average Comparisons
plt.subplot(1, 2, 1)
plt.plot(df['N'], df['BinAvg'], marker='o', label='Binary')
plt.plot(df['N'], df['TerAvg'], marker='s', label='Ternary')
plt.title('Average Comparisons')
plt.xlabel('N')
plt.ylabel('Comparisons')
plt.legend()
plt.grid(True)

# Plot 2: Worst Case Comparisons
plt.subplot(1, 2, 2)
plt.plot(df['N'], df['BinWC'], marker='o', label='Binary WC')
plt.plot(df['N'], df['TerWC'], marker='s', label='Ternary WC')
plt.title('Worst Case Comparisons')
plt.xlabel('N')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.savefig('q1_plot.png')
print("Graph saved!")