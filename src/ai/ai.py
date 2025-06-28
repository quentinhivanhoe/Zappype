##
## EPITECH PROJECT, 2025
## Zappype
## File description:
## ai
##
"""
Zappy AI Bot

EPITECH PROJECT 2025

This module implements an autonomous AI agent that connects to a Zappy server
and performs resource collection, leveling up, and breeding new processes
to populate the server with AI-controlled clients.

Classes:
    Client
        Manages the network socket communication with the server.

    AI
        Encapsulates the main AI logic, including state management,
        resource collection, elevation (level up), and spawning new AI processes.

Functions:
    fillInventory(inventoryString)
        Parses an inventory response string and updates the AI's inventory state.

    checkElevationCondition(inventory, level)
        Checks if the current inventory meets the requirements to level up.

    formatLook(inventoryString)
        Parses the response from the "Look" command into structured data.

    detNearRessources(tile_tab, element)
        Identifies the index of the nearest tile containing the desired element.

    detPath(idx)
        Generates a sequence of movement commands to reach a given tile index.

    process_ai()
        Entry point for launching the AI, parsing command-line arguments, and running the simulation loop.

Constants:
    ELAPSED_SLEEP (float)
        Sleep duration between commands to avoid flooding the server.

    INVENTORY_ITEM (int)
        Number of resource types tracked in the inventory.

    elevationCondition (dict)
        Contains the leveling requirements for each level (resources and players).

Usage Example:
    python3 ai.py -p <port> -n <team> -h <host> [-d]

Author:
    Your Name <loic.rabearivelo@epitech.eu>
"""


import socket
import sys
import getopt
import time
import pprint
import random
import subprocess
import os

ELAPSED_SLEEP = 0.2
INVENTORY_ITEM = 6
ai = None

elevationCondition = {
    "1" : {
        "food": 3,
        "nb_player" : 1,
        "ressources": {
            "linemate": 1,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
    },
    "2" : {
        "food": 3,
        "nb_player" : 2,
        "ressources": {
            "linemate": 1,
            "deraumere": 1,
            "sibur": 1,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
    },
    "3" : {
        "food": 3,
        "nb_player" : 2,
        "ressources": {
            "linemate": 2,
            "deraumere": 2,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 2,
            "thystame": 0
        }
    },
    "4" : {
        "food": 3,
        "nb_player" : 2,
        "ressources": {
            "linemate": 2,
            "deraumere": 0,
            "sibur": 1,
            "mendiane": 0,
            "phiras": 2,
            "thystame": 0
        }
    },
    "5" : {
        "food": 3,
        "nb_player" : 4,
        "ressources": {
            "linemate": 1,
            "deraumere": 1,
            "sibur": 2,
            "mendiane": 0,
            "phiras": 1,
            "thystame": 0
        }
    },
    "6" : {
        "food": 3,
        "nb_player" : 4,
        "ressources": {
            "linemate": 1,
            "deraumere": 2,
            "sibur": 1,
            "mendiane": 3,
            "phiras": 0,
            "thystame": 0
        }
    },
    "7" : {
        "food": 3,
        "nb_player" : 6,
        "ressources": {
            "linemate": 1,
            "deraumere": 2,
            "sibur": 3,
            "mendiane": 0,
            "phiras": 1,
            "thystame": 0
        }
    },
    "8" : {
        "food": 3,
        "nb_player" : 6,
        "ressources": {
            "linemate": 2,
            "deraumere": 2,
            "sibur": 2,
            "mendiane": 2,
            "phiras": 2,
            "thystame": 1
        }
    },
}

class Client:
    """
    Handles the network connection and communication with the Zappy server.

    Attributes:
        port (int): Server port.
        teamName (str): Team name for authentication.
        ip (str): Server IP address.
        clientSocket (socket.socket): TCP socket for communication.
    """

    def __init__(self, port, teamName, ip):
        """
        Initializes the Client with connection parameters.

        Args:
            port (int): Server port.
            teamName (str): Team name.
            ip (str): Server IP or hostname.
        """
        self.port = int(port)
        self.teamName = teamName
        self.ip = "127.0.0.1" if ip == "localhost" else ip
        self.clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def read(self, bufferSize=1):
        """
        Reads data from the server socket until a newline is encountered.

        Args:
            bufferSize (int): Number of bytes to read per chunk.

        Returns:
            str or None: The received data or None if the connection is closed.
        """
        try:
            data = ""
            while True:
                chunk = self.clientSocket.recv(bufferSize).decode()
                if not chunk:
                    return None
                data += chunk
                if '\n' in chunk:
                    break
            return data
        except:
            return None

    def write(self, msg):
        """
        Sends a message to the server.

        Args:
            msg (str): Message to send.

        Returns:
            int: Number of bytes sent, or 0 on failure.
        """
        try:
            return self.clientSocket.send(msg.encode())
        except:
            return 0

    def closeConnection(self):
        """
        Closes the connection to the server.
        """
        self.clientSocket.close()

    def processConnection(self):
        """
        Establishes a connection to the server.
        """
        self.clientSocket.connect((self.ip, self.port))

class AI:
    """
    Implements the main AI logic for the Zappy bot, including state management,
    resource collection, leveling up, and breeding new AI processes.

    Attributes:
        client (Client): Network client for server communication.
        debug (bool): Enables debug output.
        running (bool): Main loop control flag.
        level (int): Current AI level.
        food (int): Amount of food in inventory.
        isDead (bool): Death state flag.
        nbResToWait (int): Number of responses to wait for.
        resArray (list): Stores responses from the server.
        inventory (dict): Resource inventory.
        takeFailed (bool): Indicates if the last take command failed.
        cmd_resp_queue (list): Queue of commands and their responses.
        isLeveling (bool): Indicates if the AI is currently leveling up.
        lookInventory (list): Parsed result of the last "Look" command.
        freeSlots (int): Number of available breeding slots.
    """

    def __init__(self, args):
        """
        Initializes the AI with command-line arguments.

        Args:
            args (dict): Dictionary of arguments (port, team, host, debug).
        """
        self.client = Client(args["port"], args["team"], args["host"])
        self.debug = args.get("debug", False)
        self.running = True
        self.level = 1
        self.food = 0
        self.isDead = False
        self.nbResToWait = 0
        self.resArray = []
        self.inventory = {
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.takeFailed = False
        self.cmd_resp_queue = []
        self.isLeveling = False
        self.lookInventory = []
        self.freeSlots = 0

    def receive_loop(self):
        """
        Continuously reads and prints messages from the server.
        """
        while self.running:
            try:
                data = self.client.read()
                if data:
                    print(f"[SERVER] {data.strip()}")
                else:
                    print("[INFO] Connection closed by the host.")
                    self.running = False
            except Exception as e:
                print(f"[ERROR] Receive: {e}")
                self.running = False

    # def send_command(self, command):
    #     self.client.write(command)
    #     self.nbResToWait += 1
    #     self.cmd_resp_queue.append([command.strip(), None])
    def send_command(self, command):
        """
        Sends a command to the server and queues it for response tracking.

        Args:
            command (str): Command to send.
        """
        self.client.write(command)
        self.nbResToWait += 1
        time.sleep(ELAPSED_SLEEP)
        self.cmd_resp_queue.append([command.strip(), None])



    def send_loop(self):
        """
        Reads user input from stdin and sends it to the server.
        """
        while self.running:
            try:
                msg = input()
                if msg.lower() in ["exit", "quit"]:
                    self.running = False
                    break
                self.client.write(msg + "\n")
            except Exception as e:
                print(f"[ERROR] Send: {e}")
                self.running = False
    def parse_response(self):
        """
        Parses and processes responses for all queued commands.
        """
        for cmd, res in self.cmd_resp_queue:
            cmd = cmd.strip().lower()
            res = res.strip()

            if res == "dead":
                self.isDead = True
                print(f"[INFO] Mort détectée suite à la commande : {cmd}")
                break
            elif res.startswith("eject"):
                break
            elif cmd == "connect_nbr":
                self.freeSlots = int(res)
            elif cmd == "fork" and res == "ok":
                self.fork_new_ai()
            elif cmd == "incantation" and res == "ko":
                self.isLeveling == False
                break
            elif cmd == "incantation" and res == "Elevation underway":
                self.isLeveling == True
                break
            elif cmd.startswith("take") and res == "ko":
                self.takeFailed = True
            elif cmd == "inventory":
                fillInventory(res)
                print(f"[DEBUG] Inventory : {cmd}")
            elif cmd == "look":
                self.lookInventory = formatLook(res)
                print(f"[DEBUG] Update look : {cmd}")
            elif res in ["ok", "ko"]:
                print(f"[DEBUG] Command: '{cmd}' => Res: '{res}'")
            else:
                print(f"[WARN] Unknown response '{cmd}' => {res}")
    def wait_all_resp(self):
        """
        Waits for all expected responses from the server and processes them.

        Returns:
            list: List of [command, response] pairs.
        """
        self.resArray = []
        idx = 0
        while len(self.resArray) <= (self.nbResToWait - 1):
            res = self.client.read()
            if res is None:
                raise Exception("Error server")
            self.resArray.append(res)
            print(res.strip())
            if idx < len(self.cmd_resp_queue):
                self.cmd_resp_queue[idx][1] = res.strip()
                idx += 1
        self.parse_response()
        self.nbResToWait = 0

        if self.debug:
            print("[DEBUG] Command / Response :")
            for cmd, resp in self.cmd_resp_queue:
                print(f"  > {cmd} => {resp}")

        result = self.cmd_resp_queue.copy()
        self.cmd_resp_queue = []
        self.nbResToWait = 0
        return result

    def setAllObjects(self):
        """
        Drops all resources from the inventory onto the current tile.
        """
        for resource, quantity in self.inventory.items():
            if quantity > 0:
                for _ in range(quantity):
                    self.send_command(f"Set {resource}\n")

    def collect_food(self):
        """
        Searches for and collects food from the nearest tile.
        """
        self.send_command("Look\n")
        self.wait_all_resp()
        idx = detNearRessources(self.lookInventory, "food")
        if idx == -1:
            direction = random.choice(["Left\n", "Right\n", "Forward\n"])
            self.send_command(direction)
            self.wait_all_resp()
            return
        steps = detPath(idx)
        for step in steps:
            self.send_command(step)
            self.wait_all_resp()
        self.send_command("Take food\n")
        self.wait_all_resp()

    def try_level_up(self):
        """
        Attempts to level up by performing an incantation if requirements are met.
        """
        print(f"[INFO] Attempting Level Up (Level {self.level})")
        self.setAllObjects()
        self.wait_all_resp()
        self.send_command("Incantation\n")
        responses = self.wait_all_resp()
        _, last_resp = responses[-1]
        last_resp = last_resp.strip()

        if last_resp == "Elevation underway":
            if self.debug:
                print("[DEBUG] Elevating...")
            while True:
                buffer = self.client.read()
                if buffer:
                    buffer = buffer.strip()
                    if buffer.startswith("Current level"):
                        try:
                            self.level = int(buffer.split()[-1])
                            print(f"[INFO] New Level: {self.level}")
                        except ValueError:
                            print(f"[WARN] Bad format: {buffer}")
                        break
                    else:
                        if self.debug:
                            print(f"[INFO] Incantation feedback: {buffer}")
                        if "ko" in buffer:
                            print("[INFO] Incantation failed.")
                            break
        else:
            print("[INFO] Incantation failed or not ready.")

    def collect_resources(self):
        """
        Searches for and collects required resources for the next level.
        """
        required = elevationCondition[str(self.level)]["ressources"]
        for res, qty in required.items():
            if self.inventory.get(res, 0) < qty:
                if self.debug:
                    print(f"[DEBUG] Searching {res}")
                self.send_command("Look\n")
                self.wait_all_resp()
                idx = detNearRessources(self.lookInventory, res)
                if idx == -1:
                    direction = random.choice(["Left\n", "Right\n", "Forward\n"])
                    self.send_command(direction)
                    self.wait_all_resp()
                    return
                steps = detPath(idx)
                for step in steps:
                    self.send_command(step)
                    self.wait_all_resp()
                self.send_command(f"Take {res}\n")
                self.wait_all_resp()
                return

    def breed(self):
        """
        Attempts to breed (fork) a new AI process if slots are available.
        """
        self.send_command("Connect_nbr\n")
        self.wait_all_resp()
        if self.freeSlots <= 0:
            print("[INFO] No free slots to breed.")
            return
        self.send_command("Fork\n")
        self.wait_all_resp()
        print("[INFO] Breeding initiated.")
        self.freeSlots -= 1
        if self.debug:
            print(f"[DEBUG] Free slots after breeding: {self.freeSlots}")

    def fork_new_ai(self):
        """
        Launches a new AI process in detached mode.
        """
        cmd = [
            "./zappy_ai",
            "-h", self.client.ip,
            "-n", self.client.teamName,
            "-p", str(self.client.port)
        ]
        if self.debug:
            print(f"[DEBUG] Forking new AI with command: {' '.join(cmd)}")
        try:
            subprocess.Popen(
                cmd,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
                stdin=subprocess.DEVNULL,
                close_fds=True,
                start_new_session=True
            )
            print("[INFO] New AI process started in detached mode.")
        except Exception as e:
            print(f"[ERROR] Failed to fork new AI: {e}")


    def simulation(self):
        """
        Main simulation loop for the AI, handling state transitions and actions.
        """
        welcome = self.client.read()
        if welcome.strip() != "WELCOME":
            print("[ERROR] Wrong connection's protocole.")
            return
        self.client.write(f"{self.client.teamName}\n")
        self.freeSlots = int(self.client.read().strip())
        print(f"[INFO] Connected : {self.freeSlots}")
        print(f"[INFO] Servor message : {self.client.read().strip()}")

        state = "IDLE"

        while not self.isDead:
            self.send_command("Inventory\n")
            self.wait_all_resp()
            breed_chance = random.random()
            if breed_chance < 0.2 and self.freeSlots > 0 and self.food >= 10:
                state = "BREED"
            else:
                if self.food < 10:
                    state = "COLLECT_FOOD"
                elif checkElevationCondition(self.inventory, self.level):
                    state = "LEVEL_UP"
                else:
                    state = "COLLECT_RESOURCES"

            if self.debug:
                print(f"[DEBUG] Current State: {state}")

            if state == "COLLECT_FOOD":
                self.collect_food()
            elif state == "LEVEL_UP":
                self.try_level_up()
            elif state == "COLLECT_RESOURCES":
                self.collect_resources()
            elif state == "BREED":
                self.breed()
            else:
                time.sleep(ELAPSED_SLEEP)

def fillInventory(inventoryString):
    """
    Parses the inventory response string and updates the AI's inventory.

    Args:
        inventoryString (str): Inventory response from the server.
    """
    cleaned = inventoryString.strip().replace('[', '').replace(']', '').replace('\n', '')
    slots = cleaned.split(',')

    for slot in slots:
        elements = slot.strip().split()
        for i in range(0, len(elements), 2):
            name = elements[i]
            try:
                qty = int(elements[i + 1])
            except (IndexError, ValueError):
                continue
            if name == "food":
                ai.food = qty
            elif name in ai.inventory:
                ai.inventory[name] = qty

def checkElevationCondition(inventory, level):
    """
    Checks if the current inventory meets the requirements to level up.

    Args:
        inventory (dict): Current inventory.
        level (int): Current AI level.

    Returns:
        bool: True if requirements are met, False otherwise.
    """
    required = elevationCondition[str(level)]["ressources"]
    if ai.debug:
        print(f"Level {level}")
    for res, qty in required.items():
        if inventory.get(res, 0) < qty:
            return False
    return True

def formatLook(inventoryString):
    """
    Parses the response from the "Look" command into structured data.

    Args:
        inventoryString (str): Look response from the server.

    Returns:
        list: List of dictionaries representing each tile's contents.
    """
    cleaned = inventoryString.strip().replace('[', '').replace(']', '').replace('\n', '')
    tiles = cleaned.split(',')

    result = []

    for tile in tiles:
        elements = tile.strip().split()
        tile_dict = {
            "player": 0,
            "food": 0,
            "ressources": {}
        }
        for elem in elements:
            if elem == "player":
                tile_dict["player"] += 1
            elif elem == "food":
                tile_dict["food"] += 1
            else:
                if elem in tile_dict["ressources"]:
                    tile_dict["ressources"][elem] += 1
                else:
                    tile_dict["ressources"][elem] = 1
        result.append(tile_dict)
    return result

def detNearRessources(tile_tab, element):
    """
    Identifies the index of the nearest tile containing the desired element.

    Args:
        tile_tab (list): List of tile dictionaries.
        element (str): Resource or entity to search for.

    Returns:
        int: Index of the nearest tile, or -1 if not found.
    """
    print(f"Looking for {element}")
    for i, tile in enumerate(tile_tab):
        if element in ["player", "food"]:
            if tile.get(element, 0) > 0:
                print(f"Find {element} at {i}")
                return i
        elif tile.get("ressources", {}).get(element, 0) > 0:
            return i
    return -1

def detPath(idx):
    """
    Generates a sequence of movement commands to reach a given tile index.

    Args:
        idx (int): Index of the target tile.

    Returns:
        list: List of movement commands as strings.
    """
    path = []
    max_level = len(elevationCondition)
    for i in range(1, max_level + 1):
        if idx >= (i**2) and idx < ((i+1)**2):
            for _ in range(i):
                path.append("Forward\n")
            mid = i + i**2
            val = idx - mid
            if val < 0:
                path.append("Left\n")
            elif val > 0:
                path.append("Right\n")
            for _ in range(abs(val)):
                path.append("Forward\n")
            break
    return path

def process_ai():
    """
    Entry point for launching the AI, parsing command-line arguments,
    and running the simulation loop.
    """
    global ai
    argsTab = {}
    argv = sys.argv[1:]
    opts, _ = getopt.getopt(argv, "p:n:h:d")

    for opt, arg in opts:
        if opt == "-p":
            argsTab["port"] = arg
        elif opt == "-n":
            argsTab["team"] = arg
        elif opt == "-h":
            argsTab["host"] = arg
        elif opt == "-d":
            argsTab["debug"] = True

    if not all(k in argsTab for k in ("port", "team", "host")):
        raise Exception("Usage: -p <port> -n <team> -h <host> [-d]")
    ai = AI(argsTab)
    if ai.debug:
        print(f"Connexion au serveur {ai.client.ip}:{ai.client.port}")

    ai.client.processConnection()
    ai.simulation()
    ai.client.closeConnection()
    print("You are dead\n")
