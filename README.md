# System-Level Exploration of In-Package Wireless Communication for Multi-Chiplet Platforms

**Author:** Nikhil Suri  
**GitHub:** [nikhil21268](https://github.com/nikhil21268)  
**Email:** nikhil21268@iiitd.ac.in

---

## Table of Contents

- [Introduction](#introduction)
- [Objectives](#objectives)
- [Methodology](#methodology)
  - [Simulation Setup](#simulation-setup)
  - [Wireless Communication Modeling](#wireless-communication-modeling)
  - [Workload Profiles](#workload-profiles)
- [Results and Analysis](#results-and-analysis)
  - [Comparison of Wired and Wireless Interconnects](#comparison-of-wired-and-wireless-interconnects)
  - [Impact of MAC Protocols](#impact-of-mac-protocols)
  - [Granularity of Wireless Interconnects](#granularity-of-wireless-interconnects)
  - [Scalability](#scalability)
- [Challenges Faced](#challenges-faced)
- [Benchmark Details](#benchmark-details)
  - [Selection and Justification](#selection-and-justification)
  - [Environment Setup and Configuration](#environment-setup-and-configuration)
  - [Execution Process](#execution-process)
  - [Analysis of MAC Protocols](#analysis-of-mac-protocols)
- [Plots](#plots)
- [Conclusion](#conclusion)
- [Future Work](#future-work)
- [References](#references)

---

## Introduction

Chiplet-based platforms are emerging as a promising solution for designing highly integrated systems. While they mitigate manufacturing and design challenges associated with monolithic chips, they introduce complexities in interconnects and power delivery. Traditional physical wiring for chiplet communication imposes limitations on bandwidth and flexibility, constraining system performance.

This project explores the feasibility and performance benefits of using **in-package wireless communication** for multi-chiplet architectures. By leveraging wireless solutions, we aim to alleviate inter-chiplet communication constraints and enhance system performance, particularly for workloads like deep neural networks (DNNs) and parallel computing tasks.

## Objectives

1. **Understand System-Level Design**
   - Analyze the interaction between wireless interconnect configurations, chiplet architecture, and application performance.
   - Explore the role of Medium Access Control (MAC) protocols in optimizing communication.
2. **Replicate the Original Study**
   - Recreate the simulation environment using the **gem5-X** simulator.
   - Model wireless communication systems and evaluate their performance under various configurations and workloads.
3. **Evaluate Performance Metrics**
   - Compare wireless and wired interconnects in terms of speedup and efficiency for different application profiles.

## Methodology

### Simulation Setup

- **Simulator:** Utilized the **gem5-X** platform to model multi-chiplet systems and simulate wireless communication using nanoantennas.
- **Architectures:**
  - *Per-core wireless connectivity:* Each processing core equipped with dedicated antennas.
  - *Per-cluster wireless connectivity:* Groups of cores sharing a single antenna.
- **Applications:** Focused on AI workloads and traditional computations from the **Stream** and **Splash2** benchmarks.

### Wireless Communication Modeling

- **Physical Layer:**
  - Implemented data modulation/demodulation and collision detection mechanisms.
- **MAC Protocols:**
  - Tested different protocols, including **token-passing schemes** and **exponential backoff**.
  - Token passing proved most effective due to reduced collision rates and ensured that only one node transmits at a time.

### Workload Profiles

Benchmarked workloads ranged from general-purpose tasks from the **Stream** and **Splash2** benchmarks, including:

- **Ocean (Contiguous and Non-Contiguous Partitions)**
- **Radiosity**
- **Raytrace**

This diversity enabled a comprehensive assessment of the wireless interconnect's performance.

## Results and Analysis

### Comparison of Wired and Wireless Interconnects

Wireless solutions demonstrated notable advantages in flexibility and performance:

- **Speedup:** Best observed for **OceanCP** workloads in a four-cluster configuration.
- **Power Delivery:** Freed microbumps in the package substrate allowed improved power delivery, enhancing system stability.

### Impact of MAC Protocols

- **Token-Passing Schemes:**
  - Consistently outperformed exponential backoff.
  - Offered reduced collision rates and better bandwidth utilization.
- **Exponential Backoff:**
  - Higher penalty due to collision-induced doubling of contention windows.
  - Performed relatively better at higher bandwidths but still lagged behind token passing.

### Granularity of Wireless Interconnects

Per-cluster configurations provided a balanced tradeoff between performance and collision rates, making them ideal for scalable systems.

### Scalability

The wireless interconnect effectively scaled with the increasing number of cores and clusters, demonstrating its viability for future multi-chiplet platforms. At speeds ≥ **500 GBps**, the benefits of using a wireless interconnect outweighed potential overheads.

## Challenges Faced

1. **Simulation Complexity:**
   - Accurate replication of the gem5-X extensions required significant effort due to the complexity of the original simulation environment.
2. **Fine-Tuning Parameters:**
   - Adjusting MAC protocols and workload parameters to replicate results was time-intensive.

## Benchmark Details

### Selection and Justification

Utilized a suite of **Splash2** benchmarks, known for evaluating the performance of parallel applications in multicore environments:

- **Ocean (Contiguous and Non-Contiguous Partitions)**
- **Radiosity**
- **Raytrace**

These applications offer diverse computational and communication patterns for comprehensive assessment.

### Environment Setup and Configuration

1. **Acquisition of Benchmarks:**
   - Downloaded and extracted the Splash2 suite from an online repository.
2. **Building the Benchmarks:**
   - Resolved Makefile errors due to outdated configurations.
   - Adjusted compiler flags and library paths for compatibility.
3. **Integration with gem5X-on-Chip-Wireless:**
   - Configured shared directories to facilitate simulation.
   - Executed simulations using the gem5X-On-Chip-Wireless simulator with consistent procedures.

### Execution Process

- **Mounting Shared Directories:**
  - Used `m5term` and `mount.sh` scripts to prepare the simulation environment.
- **Benchmark Execution:**
  - Executed benchmarks ensuring all necessary data files were appropriately prepared.
  - Commands structured with variations in MAC protocol and L2 cache cluster size.

### Analysis of MAC Protocols

#### Token Passing Protocol

- Achieved lower latencies across all bandwidth scenarios.
- Superior performance at lower bandwidths, maintaining reduced latencies under high congestion.
- Provided higher percentages of ideal interconnect speed in communication-intensive benchmarks.

#### Exponential Backoff Protocol

- Performed poorer in environments with frequent concurrent communication due to high collision rates.
- Slightly outperformed token passing at very high bandwidths in less communication-intensive benchmarks.
- Improvement at higher bandwidths suggests reduced collisions and retransmissions.

### Comparative Insights

- **Raytrace and Radiosity Benchmarks:**
  - Token passing showed clear advantages in latency reduction and overall speedup.
- **OceanCP Benchmark:**
  - Performance of both protocols was closely matched, with exponential backoff marginally better at very high bandwidths.
- **Stream Benchmark:**
  - Token passing consistently delivered higher speedup, handling parallel data streams efficiently.

## Plots

### Raytrace Benchmark

![Raytrace Plot](path_to_raytrace_plot.png)

### Radiosity Benchmark

![Radiosity Plot](path_to_radiosity_plot.png)

### OceanCP Benchmark

![OceanCP Plot](path_to_oceancp_plot.png)

### Stream Benchmark

![Stream Plot](path_to_stream_plot.png)

*(Note: Replace `path_to_*_plot.png` with the actual paths to the plot images.)*

## Conclusion

The project successfully replicated the findings of the original study, validating the potential of in-package wireless communication for multi-chiplet architectures. Wireless interconnects offer a promising path for integrating heterogeneous systems, improving performance, and addressing challenges in power delivery and interconnect bandwidth.

The insights emphasize the need for continued exploration of wireless solutions, particularly for large-scale multi-chiplet systems.

## Future Work

1. **Explore Emerging Technologies:**
   - Investigate the impact of graphene-based nanoantennas on bandwidth and system performance.
2. **Hybrid Interconnect Architectures:**
   - Study combinations of wireless and wired solutions for optimized performance.
3. **MAC Protocol Innovations:**
   - Develop and test new protocols to reduce latency and improve system responsiveness.

## References

1. **Medina, R., Kein, J., Ansaloni, G., Zapater, M., Abadal, S., Alarcón, E., & Atienza, D. (2023).**  
   *System-Level Exploration of In-Package Wireless Communication for Multi-Chiplet Platforms.* ASPDAC '23, ACM, New York. [DOI](https://doi.org/10.1145/3566097.3567952)

---

Feel free to reach out via [email](mailto:nikhil21268@iiitd.ac.in) for any queries or discussions related to this project.
