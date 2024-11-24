import re
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

def compute_average_latency(sim_ticks, sim_insts, sim_freq, clock_period):
    """
    Computes the average latency in clock cycles per 64 bytes.
    """
    # Compute ticks per instruction
    tpi = sim_ticks / sim_insts

    # Convert ticks to clock cycles per instruction
    cpi = tpi / clock_period

    # Assuming each instruction processes 64 bytes
    latency_per_64B = cpi * 64

    return latency_per_64B / clock_period # Convert to clock cycles per 64 bytes

def compute_speedup(sim_ticks_simulated, sim_ticks_ideal):
    """
    Computes the speedup over an ideal interconnect.
    """
    # Compute speedup
    if(sim_ticks_simulated>sim_ticks_ideal):
        speedup = sim_ticks_ideal / sim_ticks_simulated
    else:
        speedup = sim_ticks_simulated / sim_ticks_ideal
    return speedup

def extract_bandwidth(name):
    """
    Extracts the bandwidth from the configuration name.
    """
    match = re.search(r'(\d+)GBPS', name)
    if match:
        bandwidth = int(match.group(1))
        return bandwidth
    else:
        return None
    
def extract_bandwidth2(name):
    """
    Extracts the bandwidth from the configuration name.
    Swaps the bandwidth values to correct possible mislabeling.
    """
    match = re.search(r'(\d+)GBPS', name)
    if match:
        bandwidth = int(match.group(1))
        # Swap bandwidth values since there is a mislabeling for the radiosity and raytrace workloads; my bad :)
        # So instead of messing with the global data, i'm fixing this locally
        if bandwidth == 100:
            bandwidth = 500
        elif bandwidth == 500:
            bandwidth = 100
        return bandwidth
    else:
        return None


def extract_protocol(name):
    """
    Extracts the protocol from the configuration name.
    """
    return name.split('_')[0]

def extract_protocol2(name):
    """
    Extracts the protocol from the configuration name.
    """
    # Swap protocol values since there is a mislabeling for the radiosity and raytrace workloads; my bad :)
    # So instead of messing with the global data, i'm fixing this locally
    strs= name.split('_')[0]
    if(strs=='tokenPass'):
        return 'expBackoff'
    else:
        return 'tokenPass'

# Input your simulation data here
sim_ticks = [
    4144490051566000, 23776241761816000, -1, 8590906549813500,
    4144504662099500, 16849066587757000, -1, -1,
    6261681300458000, 12099868535135000, 1935977863922500, 14882837826256000,
    23594743976028500, 35634113990508500, 4174454477710000, 25954218523269500,
    2238475182882500, 5443700267886500, 84941079908226496, 44890513856577504,
    4144494892190500, -1, 2843468712956000, 4386201336479500,
    7815588000, 8721612500, 6229241000, 7811841000,
    7813308000, 7812307500, 7804790000, 5784618000
]

sim_insts = [
    14523923045, 16537587259, -1, 15267996127,
    14548978004, 15940478596, -1, -1,
    8132779763, 8613578450, 6898648294, 8848760795,
    9568409489, 10570324301, 7947847113, 9771509618,
    12413065760, 13543407729, 21025654672, 16836164062,
    13069088701, -1, 12464641593, 13456283917,
    627990173, 649345711, 537954181, 509459373,
    694973738, 581316727, 601820008, 356821299
]

# Define a color palette for the protocols
protocol_palette = {
    'tokenPass': 'blue',
    'expBackoff': 'orange'
}

sim_freq = 1e12  # Simulation frequency (e.g., 1 THz)
clock_period = 625  # Clock period in ticks

# Workloads and configurations
simul_order = ['raytrace', 'radiosity', 'oceancp', 'stream']
names = [
    'tokenPass_100GBPS_16cluster', 'tokenPass_500GBPS_16cluster',
    'expBackoff_100GBPS_16cluster', 'expBackoff_500GBPS_16cluster',
    'tokenPass_100GBPS_4cluster', 'tokenPass_500GBPS_4cluster',
    'expBackoff_100GBPS_4cluster', 'expBackoff_500GBPS_4cluster'
]

# Initialize an empty list to store the results
data = []

# Process each data point
for i in range(len(sim_ticks)):
    if sim_ticks[i] == -1 or sim_insts[i] == -1:
        continue  # Skip incomplete simulations
    else:
        # Compute metrics
        avg_latency = compute_average_latency(sim_ticks[i], sim_insts[i], sim_freq, clock_period)
        sim_ticks_ideal = sim_insts[i] * clock_period  # Assuming CPI = 1 in the ideal interconnect
        speedup = compute_speedup(sim_ticks[i], sim_ticks_ideal)
        print("speedup ",speedup)
        # Determine configuration and workload
        config_index = i % len(names)
        config_name = names[config_index]
        workload_index = i // len(names)
        workload = simul_order[workload_index]
        
        # Extract bandwidth and protocol

        if(workload=='radiosity' or workload=='raytrace'):
            bandwidth = extract_bandwidth2(config_name)
            protocol = extract_protocol2(config_name)
            # print("hhelloofdsf ",workload)
        elif(workload=='stream'):
            bandwidth = extract_bandwidth2(config_name)
            protocol = extract_protocol(config_name)
        else:
            bandwidth = extract_bandwidth(config_name)
            # print("hello ",workload)
            protocol = extract_protocol(config_name)
        
        if bandwidth is not None:
            data.append({
                'average_latency': avg_latency,
                'speedup': speedup,
                'bandwidth': bandwidth,
                'config_name': config_name,
                'protocol': protocol,
                'workload': workload,
                'sim_ticks': sim_ticks[i],
                'sim_insts': sim_insts[i]
            })
        else:
            continue  # Skip if bandwidth could not be extracted

# Convert data to a pandas DataFrame
df = pd.DataFrame(data)

# Display the DataFrame (optional)
# print(df)

# Save the DataFrame to a CSV file (optional)
# df.to_csv('simulation_results.csv', index=False)

# Unique workloads and protocols
workloads = df['workload'].unique()
protocols = df['protocol'].unique()

# Plotting per workload
for workload in workloads:
    df_workload = df[df['workload'] == workload]
    
    # Plotting Average Latency vs. Bandwidth
    plt.figure(figsize=(8, 6))
    sns.lineplot(
        x='bandwidth', y='average_latency', hue='protocol', style='protocol',
        markers=True, dashes=False, data=df_workload, linewidth=2, markersize=8, palette=protocol_palette  # Apply the fixed color palette here
    )
    plt.xlabel('Bandwidth (GBPS)')
    plt.ylabel('Average Latency (clk/64B)')
    plt.title(f'Average Latency vs. Bandwidth for {workload}')
    plt.grid(True)
    plt.legend(title='Protocol')
    plt.tight_layout()
    plt.show()
    
    # Plotting Speedup vs. Bandwidth
    plt.figure(figsize=(8, 6))
    sns.lineplot(
        x='bandwidth', y='speedup', hue='protocol', style='protocol',
        markers=True, dashes=False, data=df_workload, linewidth=2, markersize=8, palette=protocol_palette  # Apply the fixed color palette here
    )
    plt.xlabel('Bandwidth (GBPS)')
    plt.ylabel('Speedup over Ideal Interconnect')
    plt.title(f'Speedup vs. Bandwidth for {workload}')
    plt.grid(True)
    plt.legend(title='Protocol')
    plt.tight_layout()
    plt.show()
