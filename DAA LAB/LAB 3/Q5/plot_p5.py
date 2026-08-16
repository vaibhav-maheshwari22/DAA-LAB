import pandas as pd
import matplotlib.pyplot as plt

try:
    df = pd.read_csv('q5_data.csv')
except FileNotFoundError:
    print("Error: 'q5_data.csv' not found. Please run the C program first.")
    exit()

plt.figure(figsize=(9, 5))

plt.plot(df['N'], df['NaiveMuls'], marker='o', color='red', label='Naive $O(n^3)$')
plt.plot(df['N'], df['DCMuls'], marker='s', color='blue', label='Divide & Conquer $O(n^2)$')

plt.title("Special Matrix Multiplication Complexity")
plt.xlabel("Matrix Dimension (N x N)")
plt.ylabel("Number of Scalar Multiplications")
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)
plt.ticklabel_format(style='plain', axis='y')

plt.tight_layout()
plt.savefig('q5_plot.png', dpi=300)
print("Graph saved !")