#!/bin/bash
# start it

# Configs
vm_dir="~/android/vm1/"
vm_img="~/android.qcow2"
vm_size="16G"
ram="4G"
cpus=4
spice_port=5930

# Gen random mac addr
mac_addr=$(printf '52:54:%02x:%02x:%02x:%02x\n' $((RANDOM%256)) $((RANDOM%256)) $((RANDOM%256)) $((RANDOM%256)))

echo ">>> setting everything up"
qemu-system-x86_64 \
  -m "$ram" \
  -smp "$cpus" \
  -machine q35,accel=kvm \
  -drive file="$vm_img",if=virtio,cache=none,aio=threads \
  -netdev user,id=net0,restrict=on,ipv6=off \
  -device virtio-net-pci,netdev=net0,mac="$mac_addr" \
  -vga qxl \
  -spice port="$spice_port",disable-ticketing \
  -rtc base=localtime,clock=host \
  -no-shutdown \
  -display gtk,gl=on \
  -boot menu=off \
  -uuid $(uuidgen)
