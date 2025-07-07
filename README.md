# Zappy Project Documentation - Epitech

## Project Overview

Zappy is a second-year Epitech project consisting of a multi-component system including a game server, artificial intelligence, and graphical interface. The project follows a client-server architecture with network communication.

## Development Team

- **Quentin Hivanhoe** - [@quentinhivanhoe](https://github.com/quentinhivanhoe)
- **Loic Rabearivelo** - [@LoicRabearivelo](https://github.com/LoicRabearivelo)
- **Nzoctopus** - [@Nzoctopus](https://github.com/Nzoctopus)
- **Yardaven** - [@Yardaven](https://github.com/Yardaven)
- **SNicolas974** - [@SNicolas974](https://github.com/SNicolas974)
- **Adent974** - [@Adent974](https://github.com/Adent974)

## Project Architecture

The Zappy project consists of three main modules:

### Directory Structure

```
zappy/
├── CMakeLists.txt          # CMake configuration
├── Makefile               # Main Makefile
├── README.md              # Main documentation
├── RFC-ZAPPYPE.md         # Protocol specifications
└── src/                   # Source code
    ├── server/            # Game server
    │   └── README.md      # Server documentation
    ├── ai/                # Artificial intelligence
    │   └── README.md      # AI documentation
    └── gui/               # Graphical interface
        └── README.md      # GUI documentation
```

### Components

1. **Server (zappy_server)** - Manages game logic and communications
2. **Artificial Intelligence (zappy_ai)** - Automated clients for gameplay
3. **Graphical Interface (zappy_gui)** - Real-time game visualization

## Installation and Setup

### System Requirements

- **Python 3** (minimum)
- **C Compiler** (GCC recommended)
- **CMake 3.26** or higher
- **C++20** (compiler support required)
- **SFML 2** (Simple and Fast Multimedia Library)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/quentinhivanhoe/Zappype.git
   cd Zappype
   ```

2. **Compilation**
   ```bash
   make
   ```

### Execution

After compilation, three binaries are generated:

```bash
./zappy_server [options]
./zappy_ai [options]
./zappy_gui [options]
```

## Technical Documentation

### RFC and Specifications

The `RFC-ZAPPYPE.md` file contains complete specifications of the communication protocol and game rules.

### Detailed Modules

Each module has its own documentation in its respective `src/` directory:

- `src/server/README.md` - Server configuration and usage
- `src/ai/README.md` - Artificial intelligence implementation
- `src/gui/README.md` - Graphical interface and controls

## Development

### Build Tools

- **CMake**: Configuration and Makefile generation
- **Automation script**: `run-cmakes.sh` to facilitate configuration
- **Main Makefile**: Unified compilation of all components

### Languages Used

- **C**: Game server
- **Python 2**: Artificial intelligence
- **C++20**: Graphical interface (with SFML)

## Usage

1. **Start the server** first
2. **Launch the graphical interface** for visualization
3. **Connect the AI** to begin the game

## Support

For any questions or issues:
- Consult the specific README.md files in each module
- Reference the RFC for protocol specifications
- Contact the development team via GitHub

## Educational Objectives

This Epitech project aims to develop:
- Network programming and communication protocols
- Multi-component software architecture
- Artificial intelligence and game algorithms
- Graphics programming with SFML
- Teamwork and project management

---

*Documentation generated for the Zappy project - Epitech 2nd year*