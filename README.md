# cub3D

A 3D raycasting engine inspired by the legendary Wolfenstein 3D game, developed in C with the MLX library.

![cub3D](https://img.shields.io/badge/École-42-000000?style=flat-square&logo=42&logoColor=white)
![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)

## 📋 Table of Contents

- [Description](#description)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [.cub File Format](#cub-file-format)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Raycasting Algorithm](#raycasting-algorithm)
- [Authors](#authors)

## 📝 Description

cub3D is a 42 school project that involves creating a simple 3D rendering engine using the raycasting technique. The program displays a first-person view of a maze defined in a configuration file, with wall textures, floor and ceiling colors.

This project allows you to learn:
- Mathematics applied to video games
- The raycasting algorithm
- Event and graphical window management
- Real-time performance optimization

## ✨ Features

- **Real-time 3D rendering** with raycasting algorithm
- **Wall textures** with XPM file support
- **Customizable colors** for floor and ceiling
- **Smooth navigation** with WASD keys and directional arrows
- **Complete error handling** for configuration files
- **Map validation** to ensure maze consistency
- **Graphical interface** with MLX (MiniLibX)

## 🔧 Prerequisites

- **Operating System**: macOS or Linux
- **Compiler**: GCC or Clang
- **Libraries**:
  - MLX (MiniLibX)
  - Mathematics (libm)
  - System (libc)

## 🚀 Installation

1. **Clone the repository**
   ```bash
   git clone [your-repo-url] cub3D
   cd cub3D
   ```

2. **Compile the project**
   ```bash
   make
   ```

3. **Clean object files (optional)**
   ```bash
   make clean    # Removes .o files
   make fclean   # Removes .o files and executable
   make re       # Recompiles entirely
   ```

## 🎮 Usage

```bash
./cub3D [path_to_file.cub]
```

**Example:**
```bash
./cub3D maps/map.cub
```

## 📁 .cub File Format

Configuration `.cub` files define:

### Wall textures
```
NO ./textures/path_to_the_north_texture.xpm
SO ./textures/path_to_the_south_texture.xpm  
WE ./textures/path_to_the_west_texture.xpm
EA ./textures/path_to_the_east_texture.xpm
```

### Floor and ceiling colors
```
F 225,30,0      # Floor (RGB)
C 0,200,200     # Ceiling (RGB)
```

### Maze map
```
111111111111
100000000001
100N00000001  # N = starting position (North)
100000000001
111111111111
```

**Legend:**
- `0`: Empty space
- `1`: Wall
- `N/S/E/W`: Player's initial position and orientation

## 🎹 Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `←` | Turn left |
| `→` | Turn right |
| `ESC` | Quit game |

## 📂 Project Structure

```
cub3D/
├── Makefile                    # Compilation
├── README.md                   # Documentation
├── includes/
│   └── library.h              # Headers and definitions
├── src/
│   ├── main.c                 # Entry point
│   ├── utils.c                # General utilities
│   ├── parsing/               # .cub file analysis
│   │   ├── main_parsing.c
│   │   ├── parsing_map.c
│   │   ├── parsing_textures.c
│   │   └── ...
│   └── raycasting/            # Rendering engine
│       ├── init_mlx.c
│       ├── raycasting.c
│       └── utils.c
├── libft/                     # Personal library
├── maps/                      # Example map files
└── textures/                  # Wall textures
```

## 🧮 Raycasting Algorithm

Raycasting is a 3D rendering technique that consists of:

1. **Projecting rays** from the player's position
2. **Calculating intersections** with walls
3. **Determining distance** to obstacles
4. **Drawing vertical columns** proportional to distance
5. **Applying textures** according to wall orientation

### Key mathematical formulas:

```c
// Ray direction
ray_dir_x = dir_x + plane_x * camera_x;
ray_dir_y = dir_y + plane_y * camera_x;

// Distance to wall
wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;

// Line height to draw
line_height = (int)(HEIGHT / wall_dist);
```

## 🔍 Validation and error handling

The program checks:
- ✅ `.cub` file extension
- ✅ Presence of all required elements
- ✅ Validity of texture paths
- ✅ RGB color format (0-255)
- ✅ Closed and consistent map
- ✅ Unique player presence

## 🏆 Technical features

- **Performance optimization** with aggressive compilation flags
- **Memory management** without leaks
- **Modular architecture** for maintenance
- **Robust parsing** with complete validation
- **Smooth rendering** at 60 FPS

## 👥 Authors

- **yohanafi** - Main development and raycasting
- **rdendonc** - Parsing and error handling

## 📄 License

This project is developed as part of the 42 School curriculum.

---

### 🎯 Educational objectives

This project allows you to master:
- Vector and trigonometric mathematics
- 3D rendering algorithms
- Graphics programming with MLX
- Complex C project management
- Optimization and performance

**Note:** This README presents a complete implementation of the cub3D project compliant with 42 School requirements.
