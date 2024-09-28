# Tilemap Editor

## Overview

Tilemap Editor is an OpenGL-based tool designed to help users create, edit, and manage 2D tilemaps. The editor allows users to define layers, load textures, and render tilemaps efficiently for use in game development or other graphical applications.

This project is built using the following key libraries:
- **FLTK**: Provides the GUI components.
- **OpenGL**: Handles the rendering of tilemaps and textures.
- **nlohmann/json**: Used for managing tilemap configuration and data in JSON format.
- **stb_image**: A lightweight image loading library used for reading textures in various formats (e.g., PNG, JPEG).

## Features

- **Tilemap Editing**: Create and edit 2D tilemaps.
- **Layer Management**: Manage multiple layers of tiles for complex scenes.
- **Texture Loading**: Load and render tile textures from external files using stb_image.
- **OpenGL Rendering**: Utilize OpenGL for efficient real-time rendering of the tilemaps.
- **JSON Configuration**: Save and load tilemap data using JSON files.

## Requirements

Before building the project, ensure the following dependencies are installed:

- **FLTK** (Fast Light Toolkit)
- **OpenGL** (Open Graphics Library)
- **nlohmann/json** (JSON library for C++)
- **stb_image** (Header-only image loading library)
- **CMake** (version 3.10 or above)

Optional (for future features):
- **SDL2** and **SDL2_image** for advanced input handling and image loading.

### Installing Dependencies

#### Linux (Fedora example using `dnf`):

```bash
sudo dnf install fltk fltk-devel nlohmann-json-devel opengl stb_image-devel
```
#### Linux (Debian example using `apt`):
```bash
sudo apt install libfltk1.3-dev libfltk1.3 libnlohmann-json-dev libgl1-mesa-dev libglu1-mesa-dev libstb-dev
```
### Build
```bash
mkdir build
cd build
cmake ..
make
```
### Run
```bash
./editor
```

