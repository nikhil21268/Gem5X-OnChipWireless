import matplotlib.pyplot as plt

# Example bandwidths (in GB/s)
bandwidths = [100, 500]
speedups = []
names=['tokenPass_100GBPS_16cluster', 'tokenPass_500GBPS_16cluster', 'expBackoff_100GBPS_16cluster', 'expBackoff_500GBPS_16cluster', 'tokenPass_100GBPS_4cluster', 'tokenPass_500GBPS_4cluster', 'expBackoff_100GBPS_4cluster', 'expBackoff_500GBPS_4cluster']
average_latency = []