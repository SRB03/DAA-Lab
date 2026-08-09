import os
import pandas as pd
import matplotlib.pyplot as plt

def generate_plots(csv_filename):
    # Ensure the plots directory exists
    output_dir = "plots"
    os.makedirs(output_dir, exist_ok=True)

    try:
        df = pd.read_csv(csv_filename)
    except FileNotFoundError:
        print(f"Error: '{csv_filename}' not found. Please run the C code first.")
        return

    N = df['N']
    
    # Consistent color and marker scheme across all plots
    colors = {
        'UA': '#1f77b4', 'SA': '#ff7f0e', 'SLU': '#2ca02c',
        'SLS': '#d62728', 'DLU': '#9467bd', 'DLS': '#8c564b'
    }
    labels = {
        'UA': 'Unsorted Array', 'SA': 'Sorted Array',
        'SLU': 'SLL Unsorted', 'SLS': 'SLL Sorted',
        'DLU': 'DLL Unsorted', 'DLS': 'DLL Sorted'
    }
    markers = ['o', 's', '^', 'D', 'v', 'X']

    def style_ax(ax, title):
        ax.set_title(title, fontsize=14, fontweight='bold')
        ax.set_xlabel('Number of Elements (N)', fontsize=12)
        ax.set_ylabel('Execution Time (seconds)', fontsize=12)
        ax.grid(True, linestyle='--', linewidth=0.7, alpha=0.7)

    def plot_metric(ax, metric_suffix):
        for i, (key, color) in enumerate(colors.items()):
            col_name = f"{key}_{metric_suffix}"
            if col_name in df.columns:
                ax.plot(N, df[col_name], color=color, marker=markers[i], 
                        markersize=6, linewidth=2, label=labels[key])
        ax.legend(fontsize=9, loc='upper left')

    # ---------------------------------------------------------
    # 1. Insertion and Deletion (Side by Side)
    # ---------------------------------------------------------
    fig1, axs1 = plt.subplots(1, 2, figsize=(16, 6))
    
    plot_metric(axs1[0], 'Ins')
    style_ax(axs1[0], 'Order of Growth: Insertion Time')
    
    plot_metric(axs1[1], 'Del')
    style_ax(axs1[1], 'Order of Growth: Deletion Time')
    
    plt.tight_layout()
    fig1.savefig(os.path.join(output_dir, 'insertion_deletion.png'), dpi=300)
    plt.close(fig1)

    # ---------------------------------------------------------
    # 2. Search (Single Graph)
    # ---------------------------------------------------------
    fig2, ax2 = plt.subplots(figsize=(8, 6))
    
    plot_metric(ax2, 'Src')
    style_ax(ax2, 'Order of Growth: Search Time')
    
    plt.tight_layout()
    fig2.savefig(os.path.join(output_dir, 'search.png'), dpi=300)
    plt.close(fig2)

    # ---------------------------------------------------------
    # 3. Minimum and Maximum (Side by Side)
    # ---------------------------------------------------------
    fig3, axs3 = plt.subplots(1, 2, figsize=(16, 6))
    
    plot_metric(axs3[0], 'Min')
    style_ax(axs3[0], 'Order of Growth: Minimum Time')
    
    plot_metric(axs3[1], 'Max')
    style_ax(axs3[1], 'Order of Growth: Maximum Time')
    
    plt.tight_layout()
    fig3.savefig(os.path.join(output_dir, 'min_max.png'), dpi=300)
    plt.close(fig3)

    # ---------------------------------------------------------
    # 4. Predecessor and Successor (Side by Side)
    # ---------------------------------------------------------
    fig4, axs4 = plt.subplots(1, 2, figsize=(16, 6))
    
    plot_metric(axs4[0], 'Prd')
    style_ax(axs4[0], 'Order of Growth: Predecessor Time')
    
    plot_metric(axs4[1], 'Suc')
    style_ax(axs4[1], 'Order of Growth: Successor Time')
    
    plt.tight_layout()
    fig4.savefig(os.path.join(output_dir, 'pred_succ.png'), dpi=300)
    plt.close(fig4)

    print(f"Success! All plots have been generated and saved inside the '{output_dir}/' folder.")

if __name__ == "__main__":
    generate_plots("benchmark_full.csv")