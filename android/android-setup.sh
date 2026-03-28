#!/bin/bash
#setup or something

# Configs
vm_dir="$HOME/android/vm1/"
vm_img="$HOME/android.qcow2"
vm_size="16G"
ram="4G"
cpus=4
spice_port=5930
iso_path="$HOME/Downloads/android.iso"

mkdir -p "$vm_dir"
chmod 700 "$vm_dir"

#create qcow2 if it doesn't exit
if [ ! -f "$vm_img" ]; then
  echo ">>> Creating qcow2 disk"
  qemu-img create -f qcow2 "$vm_img" "$vm_size"
fi

# Gen random mac addr
mac_addr=$(printf '52:54:%02x:%02x:%02x:%02x\n' $((RANDOM%256)) $((RANDOM%256)) $((RANDOM%256)) $((RANDOM%256)))

echo ">>> setting everything up"
qemu-system-x86_64 \
  -m "$ram" \
  -smp "$cpus" \
  -machine q35,accel=kvm \
  -drive file="$vm_img",if=virtio,cache=none,aio=threads \
  -cdrom "$iso_path" \
  -boot d \
  -netdev user,id=net0,restrict=on,ipv6=off \
  -device virtio-net-pci,netdev=net0,mac="$mac_addr" \
  -vga qxl \
  -spice port="$spice_port",disable-ticketing=on \
  -rtc base=localtime,clock=host \
  -no-shutdown \
  -display gtk,gl=on \
  -uuid $(uuidgen)
