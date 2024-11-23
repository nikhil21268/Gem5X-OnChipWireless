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

# Input your simulation data here
sim_ticks = [7812394500,,,,,,,,]       # Total ticks from your simulation data
sim_insts = [590195683,,,,,,]        # Total instructions simulated
sim_freq = [1e12,,,,,,]              # Simulation frequency (e.g., 1 THz)
clock_period = [625,,,,,,]           # Clock period in ticks

# For speedup calculation, provide sim_ticks for both simulated and ideal interconnects
# Replace the following with your actual data for the ideal interconnect
sim_ticks_ideal = 3906197250  # Example: sim_ticks for ideal interconnect (adjust accordingly)

# Compute Average Latency
average_latency = compute_average_latency(sim_ticks, sim_insts, sim_freq, clock_period)
print(f"Average Latency (clk/64B): {average_latency:.4f}")

# Compute Speedup over Ideal Interconnect
speedup = compute_speedup(sim_ticks, sim_ticks_ideal)
print(f"Speedup over Ideal Interconnect: {speedup:.4f}")
