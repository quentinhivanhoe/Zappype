# Zappy GUI

Welcome to the graphical interface for **Zappy**, a network-based multiplayer game where teams compete for dominance on the world of Trantor. This README provides comprehensive instructions for building, running, and using the GUI, as well as an overview of the game mechanics and controls.

---

## 🌍 Project Overview

Zappy is a network game set on a toroidal (wrap-around) tile map, where teams of Trantorians gather resources, perform elevation rituals, and strive to be the first with six players at the maximum level. The GUI connects to the game server, visualizing the world, players, and resources in real-time.

---

## 🛠️ Building the Project

### Prerequisites

- A C++20 compatible compiler (e.g., `g++` 10+ or `clang++` 11+)
- [SFML 2.5+](https://www.sfml-dev.org/) libraries (`libsfml-graphics`, `libsfml-window`, `libsfml-system`, `libsfml-network`)
- `make` **or** `cmake` (for alternative build)
- Any additional dependencies (see project-specific requirements)

### Build Instructions

1. Clone the repository and navigate to the `src/gui` directory.
2. Run the following command to build the project:

    ```sh
    make
    ```

### Makefile Rules

| Rule      | Description                                 |
|-----------|---------------------------------------------|
| `make`    | Builds the GUI executable (`zappy_gui`)     |
| `make all`| Same as `make`                              |
| `make clean` | Removes object files and temporary files |
| `make fclean`| Removes all build artifacts, including the executable |
| `make re` | Cleans and rebuilds the project             |

---

## 🚀 Launching the GUI

To start the graphical interface, use:

```sh
./zappy_gui [-d]
```

- `-d` : Enables debug mode for additional output.

---

## 🎮 In-Game Controls

| Key   | Action                        |
|-------|-------------------------------|
| `TAB` | Deselect current selection    |
| `Q`   | Return to main menu           |
| `Mouse Scroll`   | Zoom           |
| `Arrows`   | Navigate           |

---

## 🕹️ Game Mechanics (Summary)

### The World

- **Map**: Flat, wrap-around (toroidal) grid.
- **Resources**: Food and six types of stones (linemate, deraumere, sibur, mendiane, phiras, thystame) spawn at regular intervals and are evenly distributed.
- **Players**: Bodiless, peaceful, and occupy entire tiles. They collect resources and perform elevation rituals.

### Elevation Ritual

- Players gather on a tile with required resources and teammates of the same level.
- If conditions are met, all involved players level up.
- Stones are consumed upon successful elevation.

### Vision

- Players' field of view increases with level.
- The `look` command returns visible objects per tile.

### Sound

- Broadcasts are heard by all, with direction indicated by tile numbering.

---

## 🔗 GUI-Server Communication Initialisation

The GUI communicates with the server using a set protocol:

| Direction | Command         | Description/Response Example                |
|-----------|----------------|---------------------------------------------|
| `<-`      | `WELCOME\n`    | Server greeting                             |
| `->`      | `GRAPHIC\n`    | GUI identifies itself                       |
| `<-`      | `ok\n`         | Server acknowledges                         |
| `->`      | `msz\n`        | Request map size                            |
| `<-`      | `msz x y\n`    | Map size response                           |
| `->`      | `pnu\n`        | Request number of players                   |
| `<-`      | `pnu nb\n`     | Number of players                           |
| `->`      | `enu\n`        | Request number of eggs                      |
| `<-`      | `enu nb\n`     | Number of eggs                              |
| `->`      | `mct\n`        | Request map content                         |
| `<-`      | `bct X Y q0 q1 q2 q3 q4 q5 q6\n * tile_nb` | All Tile content             |
| `->`      | `pls\n`        | Request player list                         |
| `<-`      | `pls #n x y o s t l\n * player_nb` | All Player info                        |
| `->`      | `els\n`        | Request egg list                            |
| `<-`      | `els #e x y T\n * egg_nb` | All Egg info                                 |

---



## 📚 Additional Information

- For detailed protocol and gameplay mechanics, refer to the project documentation and RFC.
- The GUI is designed to provide a clear, interactive visualization of the game state, supporting both standard and debug modes.

---

Enjoy playing and visualizing Zappy!