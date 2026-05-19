# CollectEmAll: Definitive Edition

A 2D arcade survival game developed from scratch in native **C++** utilizing the **SDL2** framework. The core gameplay loop challenges players to gather dynamic items, evade procedural enemy scaling, and survive escalating combat waves.

## 🎮 Key Features
* **Progressive Wave Manager**: An automated system that tracks levels and dynamically scales enemy spawns.
* **Sprite Animation Engine**: Frame-by-frame sprite sheet rendering for smooth character and item visuals.
* **Visual Presentation Polish**: Implements screen fade-ins, blinking text UI, and hit-flash damage feedback.
* **Invulnerability Frames (i-Frames)**: A state-based temporary invulnerability mechanic upon taking damage.
* **Real-Time HUD**: On-screen rendering tracking player scores, remaining lives, active wave levels, and a countdown clock.

## 🕹️ Controls
* **Arrow Keys / WASD** : Entity navigation
* **P** : Trigger Pause runtime state
* **ESC** (While Paused) : Revert the execution loop back to the Main Menu
* **Mouse Input** : UI buttons feature mouse bounding-box collision detection for menus

## 📦 Directory Structure
* `bin/` : Production binaries containing `CollectEmAll.exe` and native library link mappings (`SDL2.dll`, `SDL2_image.dll`, `SDL2_ttf.dll`, `SDL2_mixer.dll`).
* `assets/` : Media directory holding texture sheets, custom TTF typography, and compressed audio assets (.ogg / .wav).

## 🚀 Execution Guide
1. Download and extract the production compilation archive.
2. Ensure the `assets/` directory remains adjacent to the executable binary.
3. Run `CollectEmAll.exe` located within the `bin/` folder.
- [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf)
- [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer)
