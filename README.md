# Simple Particle Simulation with SDL2

This program is a simple particle simulation using the SDL2 library. It initializes a screen using SDL, creates a swarm of particles, and updates their positions and colors in a game loop until the user decides to quit.

## Prerequisites

- A C++ compiler supporting C++11 or later.
- SDL2 library installed on your system.

## Building and Running

To build and run the program, follow the steps below:

1. Navigate to the project directory.
2. Run the build command (this may vary depending on your build system and platform).
3. Execute the resulting binary.

### Example with g++ on Linux

```sh
g++ -std=c++11 -o ParticleSimulation main.cpp Screen.cpp Swarm.cpp Particle.cpp -lSDL2
./ParticleSimulation
```

## Code Structure

- `main.cpp`: Contains the `main` function where the program starts. It initializes the screen, handles the game loop, updates particles, and draws them to the screen.
- `Screen.cpp`: Manages the screen initialization, updating, and event processing using SDL2.
- `Swarm.cpp`: Manages the swarm of particles, including their updating.
- `Particle.cpp`: Represents an individual particle and manages its properties and behavior.

### Headers

- `Screen.h`: Header file for the `Screen` class.
- `Swarm.h`: Header file for the `Swarm` class.
- `Particle.h`: Header file for the `Particle` class.

## Usage

Once the program is running, it will display a swarm of particles on the screen with changing colors. The user can quit the program by closing the window.
