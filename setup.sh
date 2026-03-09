#!/bin/bash

set -e

echo "Updating system..."
sudo apt update

echo "Installing build dependencies for Hyprland..."

sudo apt install -y \
build-essential \
cmake \
meson \
ninja-build \
git \
pkg-config \
libwayland-dev \
libxkbcommon-dev \
libpixman-1-dev \
libinput-dev \
libseat-dev \
libdrm-dev \
libgbm-dev \
libegl-dev \
libgles2-mesa-dev \
libvulkan-dev \
libdisplay-info-dev \
libliftoff-dev \
libpango1.0-dev \
libcairo2-dev \
libglib2.0-dev \
libxcb-composite0-dev \
libxcb-xfixes0-dev \
libxcb-render0-dev \
libxcb-shape0-dev \
libxcb-xinput-dev \
libxcb1-dev \
pipewire \
wireplumber \
xwayland \
xdg-desktop-portal \
network-manager-gnome \
blueman \
grim \
slurp \
wl-clipboard \
brightnessctl \
playerctl \
thunar

echo "Cloning Hyprland source..."

git clone --recursive https://github.com/hyprwm/Hyprland ~/Hyprland
cd ~/Hyprland

echo "Building Hyprland..."

make all

echo "Installing Hyprland..."

sudo make install

echo "Installing Hyprland ecosystem tools..."

sudo apt install -y \
waybar \
wofi \
kitty \
fonts-font-awesome

echo "Creating Wayland session..."

sudo mkdir -p /usr/share/wayland-sessions

sudo bash -c 'cat <<EOF > /usr/share/wayland-sessions/hyprland.desktop
[Desktop Entry]
Name=Hyprland
Comment=Hyprland Wayland compositor
Exec=Hyprland
Type=Application
EOF'

echo "Creating config directories..."

mkdir -p ~/.config/hypr
mkdir -p ~/.config/waybar
mkdir -p ~/.config/wofi

echo "Creating Hyprland config..."

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

bind = , Print, exec, grim -g "\$(slurp)" ~/Pictures/screenshot.png

general {
    gaps_in = 6
    gaps_out = 12
    border_size = 2
    col.active_border = rgba(8aadf4ff)
    col.inactive_border = rgba(313244aa)
    layout = dwindle
}

decoration {
    rounding = 10

    blur {
        enabled = true
        size = 8
        passes = 2
    }

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

    touchpad {
        natural_scroll = true
    }

    sensitivity = 0
}

windowrulev2 = float,class:^(pavucontrol)$
windowrulev2 = float,class:^(nm-connection-editor)$

exec-once = waybar
exec-once = nm-applet
exec-once = blueman-applet
exec-once = swww init

EOF

echo "Creating Waybar config..."

cat <<EOF > ~/.config/waybar/config
{
"layer": "top",
"position": "top",
"modules-left": ["hyprland/workspaces"],
"modules-center": ["clock"],
"modules-right": ["network", "battery", "pulseaudio"]
}
EOF

echo "Creating Waybar style..."

cat <<EOF > ~/.config/waybar/style.css
* {
  font-family: "Font Awesome 6 Free";
  font-size: 13px;
}

window#waybar {
background: rgba(20,20,20,0.7);
border-radius: 10px;
}
EOF

echo "Creating Wofi config..."

cat <<EOF > ~/.config/wofi/config
show=drun
prompt=Search
EOF

echo ""
echo "Installation complete."
echo "Log out and select 'Hyprland' from the login screen."
echo ""
echo "Keybinds:"
echo "SUPER + ENTER = Terminal"
echo "SUPER + SPACE = App Launcher"
echo "SUPER + Q = Close Window"
echo "SUPER + 1-5 = Workspaces"
