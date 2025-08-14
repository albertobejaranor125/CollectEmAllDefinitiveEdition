# CollectEmAllDefinitiveEdition

A 2D game developed in **C++** with **SDL2** where your goal is to collect items, avoid enemies, and survive progressively harder waves.

## 🎮 Features

- Wave system with increasing difficulty.
- Player and item animations.
- Visual effects such as *fade-in*, *blinking text*, and *damage flash*.
- Sound effects and background music.
- Temporary invulnerability mechanic.
- HUD displaying score, lives, level, and timer.

## 🕹️ Controls

- **Arrow keys / WASD** → Move the player.
- **P** → Pause the game.
- **ESC** (while paused) → Return to main menu.
- Click **PLAY** or **RESTART** → Start or restart the game.

## 📦 Folder Structure

bin/
  CollectEmAll.exe
  SDL2.dll
  SDL2_image.dll
  SDL2_ttf.dll
  SDL2_mixer.dll
assets/
spritesheet.png
heart.png
coin.png
font.ttf
music.ogg
correct.wav
wrong.wav
victory.wav
gameover.wav


## 🚀 How to Run

1. Download and unzip the `.zip` file.
2. Make sure the `assets/` folder is in the same directory as the executable.
3. Run `CollectEmAll.exe` from the `bin/` folder.

## ⚙️ Dependencies

- [SDL2](https://libsdl.org/)
- [SDL2_image](https://github.com/libsdl-org/SDL_image)
- [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf)
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer)

These libraries are already included in the `bin/` directory for distribution.
