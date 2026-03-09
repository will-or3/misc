#!/bin/bash
set -e

echo "=== Updating system ==="
sudo apt update

echo "=== Installing essential packages ==="
sudo apt install -y git build-essential pkg-config libx11-dev libxinerama-dev libxrandr-dev \
libxft-dev libxkbcommon-dev waybar wofi kitty thunar network-manager-gnome blueman \
grim slurp wl-clipboard fonts-font-awesome

# Install Rust (needed for swww)
if ! command -v cargo &> /dev/null; then
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
    source $HOME/.cargo/env
fi

echo "=== Building swww (wallpaper manager) ==="
cd ~
if [ ! -d "swww" ]; then
    git clone https://github.com/Hyprland/swww
fi
cd swww
cargo build --release
sudo cp target/release/swww /usr/local/bin/

echo "=== Cloning and building Hyprland ==="
cd ~
if [ ! -d "Hyprland" ]; then
    git clone --recursive https://github.com/hyprwm/Hyprland
fi
cd Hyprland
make all
sudo make install

echo "=== Creating Wayland session ==="
sudo mkdir -p /usr/share/wayland-sessions
sudo bash -c 'cat <<EOF > /usr/share/wayland-sessions/hyprland.desktop
[Desktop Entry]
Name=Hyprland
Comment=Hyprland Wayland compositor
Exec=Hyprland
Type=Application
EOF'

echo "=== Creating config directories ==="
mkdir -p ~/.config/hypr ~/.config/waybar ~/.config/wofi ~/.config/nwg-dock

echo "=== Writing minimal Hyprland config ==="
cat <<EOF > ~/.config/hypr/hyprland.conf
\$terminal = kitty
\$fileManager = thunar
\$menu = wofi --show drun
\$mainMod = SUPER

bind = \$mainMod, RETURN, exec, \$terminal
bind = \$mainMod, SPACE, exec, \$menu
bind = \$mainMod, Q, killactive
bind = \$mainMod, E, exec, \$fileManager
bind = \$mainMod, R, exec, hyprctl reload
bind = \$mainMod, 1, workspace, 1
bind = \$mainMod, 2, workspace, 2

exec-once = waybar
exec-once = nm-applet
exec-once = blueman-applet
exec-once = swww init
exec-once = nwg-dock
EOF

echo "=== Writing Waybar config ==="
cat <<EOF > ~/.config/waybar/config
{
"layer": "top",
"position": "top",
"modules-left": ["hyprland/workspaces"],
"modules-center": ["clock"],
"modules-right": ["network", "battery", "pulseaudio"]
}
EOF

echo "=== Writing Waybar style ==="
cat <<EOF > ~/.config/waybar/style.css
* { font-family: "Font Awesome 6 Free"; font-size: 13px; }
window#waybar { background: rgba(20,20,20,0.7); border-radius: 12px; }
EOF

echo "=== Writing Wofi config ==="
cat <<EOF > ~/.config/wofi/config
show=drun
prompt=Search
EOF

echo "=== Writing NWG Dock config ==="
cat <<EOF > ~/.config/nwg-dock/dock.conf
[dock]
position = bottom
icon_size = 48
background_opacity = 0.8
blur = true
rounding = 12
EOF

echo ""
echo "=== Minimal Hyprland setup complete ==="
echo "Log out and select 'Hyprland' from the login screen."
echo "SUPER + ENTER = Terminal"
echo "SUPER + SPACE = App Launcher"
echo "SUPER + Q = Close Window"
echo "SUPER + 1-5 = Workspaces"
