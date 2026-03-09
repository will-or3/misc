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

echo "=== Writing Hyprland config ==="
cat <<EOF > ~/.config/hypr/hyprland.conf
monitor=,preferred,auto,1

\$terminal = kitty
\$fileManager = thunar
\$menu = wofi --show drun

env = XCURSOR_SIZE,24
env = HYPRCURSOR_SIZE,24

\$mainMod = SUPER

bind = \$mainMod, RETURN, exec, \$terminal
bind = \$mainMod, SPACE, exec, \$menu
bind = \$mainMod, Q, killactive
bind = \$mainMod, E, exec, \$fileManager
bind = \$mainMod, R, exec, hyprctl reload

bind = \$mainMod, 1, workspace, 1
bind = \$mainMod, 2, workspace, 2
bind = \$mainMod, 3, workspace, 3
bind = \$mainMod, 4, workspace, 4
bind = \$mainMod, 5, workspace, 5

bind = \$mainMod SHIFT, 1, movetoworkspace, 1
bind = \$mainMod SHIFT, 2, movetoworkspace, 2

general {
    gaps_in = 6
    gaps_out = 12
    border_size = 2
    col.active_border = rgba(8aadf4ff)
    col.inactive_border = rgba(313244aa)
    layout = dwindle
}

decoration {
    rounding = 15
    blur { enabled = true; size = 12; passes = 3 }
    drop_shadow = true
}

animations {
    enabled = yes
    animation = windows,1,6,default
    animation = fade,1,5,default
    animation = workspaces,1,5,default
}

input {
    kb_layout = us
    follow_mouse = 1
    touchpad { natural_scroll = true }
    sensitivity = 0
}

windowrulev2 = float,class:^(pavucontrol)$
windowrulev2 = float,class:^(nm-connection-editor)$

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

echo "=== Writing NWG Dock config for macOS-style dock ==="
cat <<EOF > ~/.config/nwg-dock/dock.conf
[dock]
position = bottom
icon_size = 48
background_opacity = 0.8
blur = true
rounding = 12
EOF

echo ""
echo "=== Setup complete! ==="
echo "Log out and select 'Hyprland' from the login screen."
echo "SUPER + ENTER = Terminal"
echo "SUPER + SPACE = App Launcher"
echo "SUPER + Q = Close Window"
echo "SUPER + 1-5 = Workspaces"
echo "Your macOS-style dock will appear at the bottom."
