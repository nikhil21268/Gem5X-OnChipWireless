import matplotlib.pyplot as plt

# Input your data here

# Wireless Channel Bandwidths in Gbps
bandwidths = [100, 500]

# Execution times in seconds for each bandwidth configuration
# Replace these values with the 'sim_seconds' extracted from your stats.txt files
execution_times = []  # Replace with your data

# Average latencies in cycles (or appropriate units)
# Replace these values with the average latency extracted from your stats.txt files
average_latencies = [0.0] * len(bandwidths)  # Replace with your data

# Ideal execution time in seconds (from the ideal interconnect simulation)
# Replace this value with the 'sim_seconds' from the ideal interconnect stats.txt
ideal_execution_time = 0.0  # Replace with your data

# Calculate speedup over ideal interconnect
speedups = [ideal_execution_time / exec_time for exec_time in execution_times]

# Plot Speedup over Ideal Interconnect vs. Wireless Channel Bandwidth
plt.figure(figsize=(8,6))
plt.plot(bandwidths, speedups, marker='o', linestyle='-', color='b')
plt.title('Speedup over Ideal Interconnect vs. Wireless Channel Bandwidth')
plt.xlabel('Wireless Channel Bandwidth (Gbps)')
plt.ylabel('Speedup over Ideal Interconnect')
plt.grid(True)
plt.xticks(bandwidths)
plt.savefig('speedup_vs_bandwidth.png')
plt.show()

# Plot Average Latency vs. Wireless Channel Bandwidth
plt.figure(figsize=(8,6))
plt.plot(bandwidths, average_latencies, marker='o', linestyle='-', color='r')
plt.title('Average Latency vs. Wireless Channel Bandwidth')
plt.xlabel('Wireless Channel Bandwidth (Gbps)')
plt.ylabel('Average Latency (units)')  # Replace 'units' with the actual units, e.g., 'cycles' or 'ns'
plt.grid(True)
plt.xticks(bandwidths)
plt.savefig('latency_vs_bandwidth.png')
plt.show()
