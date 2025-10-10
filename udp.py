# use on quiet network or raise threshold
# must run with sudo

import subprocess
import time
import socket
from collections import Counter

INTERFACE = "wlo1"
THRESHOLD = 100
INTERVAL = 2 # seconds 

def get_local_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(("10.255.255.255", 1))
    ip = s.getsockname()[0]
    s.close()
    return ip

def parse_line(line, local_ip):
    parts = line.strip().split()
    ips = []
    if len(parts) >= 2:
        src = parts[0]
        dst = parts[1]
        if src != local_ip:
            ips.append(src)
        if dst != local_ip:
            ips.append(dst)
    return ips

# main monitoring
local_ip = get_local_ip()
print("local ip:", local_ip)

process = subprocess.Popen(["tshark", "-i", INTERFACE, 
"-l", "-T", "fields", "-e", "ip.src", "-e", "ip.dst", "udp"],
stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

buffer = []

try:
    while True:
        end_time = time.time() + INTERVAL
        while time.time() < end_time:
            line = process.stdout.readline()
            if line:
                buffer.append(line)
                if len(buffer) >= THRESHOLD:
                    break
    
        if len(buffer) >= THRESHOLD:
            remote_ips = []
            for line in buffer:
                parsed = parse_line(line, local_ip)
                for ip in parsed:
                    remote_ips.append(ip)
            
            if remote_ips:
                counts = Counter(remote_ips)
                most_common_ip, count = counts.most_common(1)[0]

                print("\n====================")
                print("Identified :\033[1m\033[92m", most_common_ip, "\033[0m")
                print("\nPacket count in burst :\033[1m\033[91m", count, "\033[0m")
            else:
                print("threshold reached but no ip's found")
            buffer = []

except KeyboardInterrupt:
    print("\nStopped")

process.terminate()
process.wait()
print("tshark process terminated")
