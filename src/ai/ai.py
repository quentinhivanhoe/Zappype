##
## EPITECH PROJECT, 2025
## Zappype
## File description:
## ai
##

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
    def __init__(self, port, teamName, ip):
        self.port = int(port)
        self.teamName = teamName
        self.ip = "127.0.0.1" if ip == "localhost" else ip
        self.clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def read(self, bufferSize=1024):
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
        try:
            return self.clientSocket.send(msg.encode())
        except:
            return 0

    def closeConnection(self):
        self.clientSocket.close()

    def processConnection(self):
        self.clientSocket.connect((self.ip, self.port))

class AI:
    def __init__(self, args):
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
        # if not command.endswith('\n'):
        #     command += '\n'
        print(f"[SEND] {command.strip()}")
        self.client.write(command)
        self.nbResToWait += 1
        time.sleep(ELAPSED_SLEEP)
        self.cmd_resp_queue.append([command.strip(), None])



    def send_loop(self):
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
        for resource, quantity in self.inventory.items():
            if quantity > 0:
                for _ in range(quantity):
                    self.send_command(f"Set {resource}\n")

    def collect_food(self):
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
    required = elevationCondition[str(level)]["ressources"]
    if ai.debug:
        print(f"Level {level}")
    for res, qty in required.items():
        if inventory.get(res, 0) < qty:
            return False
    return True

def formatLook(inventoryString):
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
