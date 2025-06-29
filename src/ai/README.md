# Zappy AI

## Description

The Zappy AI is an autonomous Python client for the EPITECH Zappy game. This AI implements intelligent behavior allowing players to survive, collect resources, and evolve in the Zappy universe.

## Objectives

- **Survival**: Maintain sufficient food levels
- **Evolution**: Progress through levels (1 to 8)
- **Reproduction**: Create new players for the team
- **Collection**: Gather resources necessary for incantations

## Prerequisites

- Python 3.x
- Running Zappy server
- Network access to the server

## Installation and Launch

### Project structure
```
src/ai/
├── ai.py          # Main AI logic
├── __init__.py    # Python module
├── main.py        # Entry point
├── Makefile       # Compilation script
└── README.md      # This documentation
```

### Compilation
```bash
# From project root
make
```

### Launching the AI
```bash
./zappy_ai -h <hostname> -p <port> -n <team_name> [-d]
```

#### Required parameters:
- `-h <hostname>`: Server IP address (or "localhost")
- `-p <port>`: Server connection port
- `-n <team_name>`: Team name

#### Optional parameters:
- `-d`: Enable debug mode (detailed output)

### Usage examples
```bash
# Basic connection
./zappy_ai -h localhost -p 4242 -n team1

# With debug enabled
./zappy_ai -h 127.0.0.1 -p 4242 -n myteam -d

# Connection to remote server
./zappy_ai -h 192.168.1.100 -p 4242 -n warriors
```

## Architecture

### Main classes

#### `Client`
Manages network communication with the Zappy server.
- **Connection**: Establishes and maintains TCP connection
- **Communication**: Sends and receives messages
- **Protocol**: Respects Zappy protocol

#### `AI`
Core of the artificial intelligence.
- **State**: Manages level, inventory, food
- **Decisions**: Implements behavior logic
- **Strategy**: Determines actions to perform

## Game mechanics

### Level system
The AI can evolve from level 1 to level 8. Each level requires:

| Level | Players | Food | Linemate | Deraumere | Sibur | Mendiane | Phiras | Thystame |
|-------|---------|------|----------|-----------|-------|----------|--------|----------|
| 1→2   | 1       | 3    | 1        | 0         | 0     | 0        | 0      | 0        |
| 2→3   | 2       | 3    | 1        | 1         | 1     | 0        | 0      | 0        |
| 3→4   | 2       | 3    | 2        | 2         | 0     | 0        | 2      | 0        |
| 4→5   | 2       | 3    | 2        | 0         | 1     | 0        | 2      | 0        |
| 5→6   | 4       | 3    | 1        | 1         | 2     | 0        | 1      | 0        |
| 6→7   | 4       | 3    | 1        | 2         | 1     | 3        | 0      | 0        |
| 7→8   | 6       | 3    | 1        | 2         | 3     | 0        | 1      | 0        |
| 8→Max   | 6       | 3    | 2        | 2         | 2     | 2        | 2      | 1        |

### Behavioral states

#### COLLECT_FOOD
- **Condition**: Food < 10
- **Action**: Search and collect food
- **Priority**: Maximum (survival)

#### LEVEL_UP
- **Condition**: Sufficient resources for incantation
- **Action**: Place objects and start incantation
- **Result**: Level increase

#### COLLECT_RESOURCES
- **Condition**: Missing resources for evolution
- **Action**: Search for specific resources
- **Strategy**: Intelligent targeting based on level

#### BREED
- **Condition**: 20% chance + food ≥ 10 + free slots
- **Action**: Reproduce a new player
- **Benefit**: Strengthens the team

## Advanced features

### Vision system
- **Look**: Analyzes environment in spiral
- **Detection**: Locates resources and players
- **Navigation**: Optimal pathfinding

### Inventory management
- **Tracking**: Real-time resource monitoring
- **Optimization**: Intelligent object storage
- **Prioritization**: Focus on current needs

### Server communication
- **Queue**: Command queue system
- **Synchronization**: Wait for server responses
- **Error handling**: Recovery in case of problems

### Autonomous reproduction
- **Fork**: Automatic creation of new AI processes
- **Detachment**: Independent processes
- **Growth**: Natural team expansion

## Debug and monitoring

### Debug mode (`-d`)
Enables detailed output:
- Internal AI states
- Server communications
- Decisions made
- Inventory and resources

### Informational logs
```
[INFO] Connected : 5
[INFO] Attempting Level Up (Level 2)
[INFO] New Level: 3
[INFO] Breeding initiated.
```

### Debug logs
```
[DEBUG] Current State: COLLECT_RESOURCES
[DEBUG] Searching linemate
[DEBUG] Inventory : inventory
[DEBUG] Command: 'take food' => Res: 'ok'
```

## Configuration

### Modifiable constants
```python
ELAPSED_SLEEP = 0.2    # Delay between commands (seconds)
INVENTORY_ITEM = 6     # Number of different objects
```

### Elevation conditions
The `elevationCondition` dictionary defines prerequisites for each level.

## Optimization strategies

### Movement efficiency
- Random movement if resource not found
- Spiral pathfinding for vision
- Rotation optimization

### Resource management
- Food prioritization
- Targeted collection based on level
- Avoidance of useless resources

### Team collaboration
- Strategic reproduction
- Respect for player quotas
- Indirect communication via environment

## Error handling

### Network connection
- Automatic reconnection on disconnection
- Timeout management
- Server response validation

### Player death
- Detection of "dead" status
- Clean process termination
- Resource cleanup
