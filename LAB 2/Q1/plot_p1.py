import csv
import matplotlib.pyplot as plt

operations = ['Time_Insert', 'Time_Search', 'Time_Max', 'Time_Min', 'Time_Pred', 'Time_Succ', 'Time_Delete']
data_structures = ['Unsorted_Array', 'Sorted_Array', 'SLL_Unsorted', 'SLL_Sorted', 'DLL_Unsorted', 'DLL_Sorted']

data = {op: {ds: {"N": [], "Time": []} for ds in data_structures} for op in operations}

try:
    with open('q1_benchmark_data.csv', 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            n_val = int(row['N'])
            ds = row['Data_Structure']
            for op in operations:
                data[op][ds]["N"].append(n_val)
                data[op][ds]["Time"].append(float(row[op]))
except FileNotFoundError:
    print("Error: 'q1_benchmark_data.csv' not found.")
    exit()

styles = {
    'Unsorted_Array': {'color': '#1f77b4', 'marker': 'o', 'ls': '-', 'label': 'Unsorted Array'},
    'Sorted_Array':   {'color': '#2ca02c', 'marker': 's', 'ls': '--', 'label': 'Sorted Array'},
    'SLL_Unsorted':   {'color': '#d62728', 'marker': '^', 'ls': '-.', 'label': 'SLL Unsorted'},
    'SLL_Sorted':     {'color': '#9467bd', 'marker': 'v', 'ls': ':', 'label': 'SLL Sorted'},
    'DLL_Unsorted':   {'color': '#ff7f0e', 'marker': 'D', 'ls': '-', 'label': 'DLL Unsorted'},
    'DLL_Sorted':     {'color': '#8c564b', 'marker': 'X', 'ls': '--', 'label': 'DLL Sorted'}
}

# Create a 4x2 grid of subplots (1 slot will be empty)
fig, axes = plt.subplots(4, 2, figsize=(16, 20))
axes = axes.flatten()

for idx, op in enumerate(operations):
    ax = axes[idx]
    for ds in data_structures:
        x_vals = data[op][ds]["N"]
        y_vals = data[op][ds]["Time"]
        if x_vals:
            ax.plot(x_vals, y_vals, color=styles[ds]['color'], marker=styles[ds]['marker'], 
                    linestyle=styles[ds]['ls'], linewidth=2, label=styles[ds]['label'], alpha=0.8)

    clean_op = op.replace('Time_', '')
    ax.set_title(f'{clean_op} Operation', fontsize=12, fontweight='bold')
    ax.set_xlabel('Input Size (N)')
    ax.set_ylabel('Execution Time (s)')
    ax.grid(True, linestyle='--', alpha=0.6)

# Hide the empty 8th subplot
axes[7].axis('off')

# Add a single common legend in the empty space
handles, labels = axes[0].get_legend_handles_labels()
fig.legend(handles, labels, loc='lower right', bbox_to_anchor=(0.9, 0.1), fontsize=14)

plt.suptitle('Dictionary Operations: Asymptotic Running Time Analysis', fontsize=18, fontweight='bold')
plt.tight_layout(rect=[0, 0, 1, 0.97]) # Adjust layout to fit title

plt.savefig('combined_plots.png', dpi=300)
print("Successfully generated 'combined_plots.png' containing all 7 graphs.")