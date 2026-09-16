Requirements:
ffmpeg
meson
gcc

git clone https://github.com/RegalityBreach/sway-bg-editor
cd sway-bg-editor
meson setup build
meson compile -C build
./build/app
