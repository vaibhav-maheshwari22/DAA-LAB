import pandas as pd
import matplotlib.pyplot as plt

try:
    # Read the CSV file 
    df = pd.read_csv('q4_data.csv')
except FileNotFoundError:
    print("Error: 'q4_data.csv' not found. Please run the C program first.")
    exit()

plt.figure(figsize=(9, 5))

# Plotting the number of multiplications
plt.plot(df['N'], df['NaiveMuls'], marker='o', color='red', label='Naive ($O(n^3)$)')
plt.plot(df['N'], df['StrassenMuls'], marker='s', color='blue', label='Strassen ($O(n^{2.81})$)')

plt.title("Matrix Multiplication: Strassen's Method vs Naive")
plt.xlabel("Matrix Dimension (N x N)")
plt.ylabel("Number of Scalar Multiplications")
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)

# Formatting the Y-axis to show large numbers clearly without scientific notation
plt.ticklabel_format(style='plain', axis='y')

plt.tight_layout()
plt.savefig('q4_plot.png', dpi=300)
print("Graph saved!")