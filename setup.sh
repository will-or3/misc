#!/bin/bash
set -e

echo "=== Updating system ==="
sudo apt update && sudo apt upgrade -y

echo "=== Installing KDE Plasma and essential apps ==="
sudo apt install -y kde-plasma-desktop plasma-workspace \
plank wofi kitty thunar network-manager-gnome blueman \
grim slurp wl-clipboard fonts-font-awesome rofi

echo "=== Configuring Plasma appearance ==="
# Enable rounded corners and blur (via KWin effects)
kwriteconfig5 --file kwinrc --group Compositing --key BlurEnabled true
kwriteconfig5 --file kwinrc --group Compositing --key ShadowEnabled true
kwriteconfig5 --file kwinrc --group Windows --key BorderRadius 12

echo "=== Setting up Plank dock ==="
mkdir -p ~/.config/plank/dock1/
cat <<EOF > ~/.config/plank/dock1/settings
[PlankDockPreferences]
Position=Bottom
ZoomEnabled=true
IconSize=48
BackgroundAlpha=0.8
Roundness=12
EOF

echo "=== Creating Wofi config ==="
mkdir -p ~/.config/wofi
cat <<EOF > ~/.config/wofi/config
show=drun
prompt=Search
EOF

echo "=== Creating KDE keybindings for macOS-style shortcuts ==="
kwriteconfig5 --file kglobalshortcutsrc --group "KDE Component Shortcuts" \
--key "Run Command" "Meta+Space,Meta+Space,rofi -show drun"

kwriteconfig5 --file kglobalshortcutsrc --group "KDE Component Shortcuts" \
--key "Konsole" "Meta+Return,Meta+Return,kitty"

kwriteconfig5 --file kglobalshortcutsrc --group "KWin" \
--key "Close Window" "Meta+Q,Meta+Q,Close"

echo "=== Setup complete ==="
echo "Log out and select 'Plasma' session."
echo "SUPER+Enter = Terminal"
echo "SUPER+Space = App Launcher"
echo "SUPER+Q = Close Window"
echo "Plank dock will appear at the bottom."
