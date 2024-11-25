# Python script to compute Average Latency and Speedup over Ideal Interconnect

def compute_average_latency(sim_ticks, sim_insts, sim_freq, clock_period):
    """
    Computes the average latency in clock cycles per 64 bytes.

    Parameters:
    - sim_ticks: Total number of ticks simulated.
    - sim_insts: Total number of simulated instructions.
    - sim_freq: Simulation frequency in Hz.
    - clock_period: Clock period in ticks.

    Returns:
    - latency_per_64B: Average latency in clock cycles per 64 bytes.
    """
    # Compute ticks per instruction
    tpi = sim_ticks / sim_insts

    # Convert ticks to clock cycles per instruction
    cpi = tpi / clock_period

    # Assuming each instruction processes 64 bytes
    latency_per_64B = cpi * 64

    return latency_per_64B

def compute_speedup(sim_ticks_simulated, sim_ticks_ideal):
    """
    Computes the speedup over an ideal interconnect.

    Parameters:
    - sim_ticks_simulated: Total ticks from the simulated interconnect.
    - sim_ticks_ideal: Total ticks from the ideal interconnect.

    Returns:
    - speedup: The speedup factor over the ideal interconnect.
    """
    # Compute speedup
    speedup = sim_ticks_ideal / sim_ticks_simulated

    return speedup

# Example usage:
radiosity=6261681300458000,12099868535135000, 1935977863922500,14882837826256000, 23594743976028500,35634113990508500, 4174454477710000,25954218523269500
8132779763,8613578450,6898648294,8848760795, 9568409489, 10570324301,7947847113,9771509618
# Input your simulation data here
sim_ticks = [4144490051566000,23776241761816000,-1,8590906549813500,4144504662099500,16849066587757000,-1,-1, 6261681300458000,12099868535135000, 1935977863922500,14882837826256000, 23594743976028500,35634113990508500, 4174454477710000,25954218523269500,   2238475182882500,5443700267886500,84941079908226496,-1 , -1,-1,-1,-1]       # Total ticks from your simulation data
sim_insts = [14523923045,16537587259,-1,15267996127,14548978004 ,15940478596,-1,-1, 8132779763,8613578450,6898648294,8848760795, 9568409489, 10570324301,7947847113,9771509618,   12413065760, 13543407729,21025654672,-1, -1,-1,-1,-1]        # Total instructions simulated
sim_freq = 1000000000000              # Simulation frequency (e.g., 1 THz)
clock_period = 625           # Clock period in ticks
simul_order=['raytrace','radiosity','oceancp']
names=['tokenPass_100GBPS_16cluster', 'tokenPass_500GBPS_16cluster', 'expBackoff_100GBPS_16cluster', 'expBackoff_500GBPS_16cluster', 'tokenPass_100GBPS_4cluster', 'tokenPass_500GBPS_4cluster', 'expBackoff_100GBPS_4cluster', 'expBackoff_500GBPS_4cluster']

# For speedup calculation, provide sim_ticks for both simulated and ideal interconnects
# Replace the following with your actual data for the ideal interconnect
sim_ticks_ideal = 3906197250  # Example: sim_ticks for ideal interconnect (adjust accordingly)

# Compute Average Latency
average_latency = compute_average_latency(sim_ticks, sim_insts, sim_freq, clock_period)
print(f"Average Latency (clk/64B): {average_latency:.4f}")

# Compute Speedup over Ideal Interconnect
speedup = compute_speedup(sim_ticks, sim_ticks_ideal)
print(f"Speedup over Ideal Interconnect: {speedup:.4f}")