# PhysXCustomEngine

## Desription

PhysXCustomEngine is a collaborative project trying to adapt the engine from my earlier Boston Simulator project for use in a 3D physics simulation. It features 2 scenes under different git branches.

<img width="724" height="340" alt="image" src="https://github.com/user-attachments/assets/b57a624a-db53-4bd4-9eaa-076b9841e762" />

<img width="734" height="342" alt="image" src="https://github.com/user-attachments/assets/890ee43b-31bc-466e-9edb-3169cc53b9d1" />

## Dependencies

- Nvidia PhysX 3.4.2
- Nupengl installed via nuget

## Build

To build and use the project you must be on Windows and using Visual Studio.

1. Clone this repository (switch branches to change the scene you want)
2. Install Nvidia PhysX 3.4.2 from https://github.com/NVIDIAGameWorks/PhysX-3.4/releases and unzip in the following directory:
   
```
C:\Program Files (x86)\NVIDIA Corporation\PhysX SDK\PhysX-3.4.2
```

3. Open this project's VS solution and (re)install nupengl nuget package. (even it shows to be installed, it will not work without a reinstall)

## Controls

- WASD for camera movement, ZX for up/down
- Mouse to rotate camera

### D-Game

- UHJK to control the crane

### B-Game

- UHJK to control the cannon
- Space to fire the cannon

## Gameplay

The player's objective is to destroy the structure using the tool provided. Once the game detects the structure is sufficiently destroyed, then it will print a victory message in the console.
