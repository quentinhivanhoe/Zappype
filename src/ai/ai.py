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

ELAPSED_SLEEP = 0.25
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

    def read(self, bufferSize=1):
        try:
            data = ""
            while True:
                chunk = self.clientSocket.recv(bufferSize).decode()
                if not chunk:
                    break
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
        self.lookInventory = []

    def receive_loop(self):
        while self.running:
            try:
                data = self.client.read()
                if data:
                    print(f"[SERVER] {data.strip()}")
                else:
                    print("[INFO] Serveur fermé la connexion.")
                    self.running = False
            except Exception as e:
                print(f"[ERROR] Réception: {e}")
                self.running = False

    def send_loop(self):
        while self.running:
            try:
                msg = input()
                if msg.lower() in ["exit", "quit"]:
                    self.running = False
                    break
                self.client.write(msg + "\n")
            except Exception as e:
                print(f"[ERROR] Envoi: {e}")
                self.running = False

    def parse_response(self):
        for res in self.resArray:
            print(f"Parse => {res}")
            if res == "dead\n":
                self.isDead = True
            if res in ["ok\n", "ko\n"]:
                continue
            if res.count(',') == 6:
                fillInventory(res)
                continue
            if res[0] == '[' and res[-2] == ']':
                self.lookInventory = formatLook(res)

    def wait_all_resp(self):
        self.resArray = []
        while len(self.resArray) <= (self.nbResToWait - 1):
            res = self.client.read()
            if res == None:
                raise("Error server")
            self.resArray.append(res)
            print(res.strip())
        self.parse_response()
        self.nbResToWait = 0
        print("Fini")

    def simulation(self):
        welcome = self.client.read()
        if welcome.strip() != "WELCOME":
            print("Erreur protocole de connexion")
            return

        self.client.write(f"{self.client.teamName}\n")
        print(f"[INFO] Connecté : {self.client.read().strip()}")
        print(f"[INFO] Message serveur : {self.client.read().strip()}")

        while self.isDead != True:
            pprint.pprint(self.inventory)
            self.client.write("Inventory\n")
            self.nbResToWait += 1
            self.wait_all_resp()
            if checkElevationCondition(ai.inventory, ai.level) == True:
                print("You can level up!")
            elif ai.food < 3:
                self.client.write("Look\n")
                self.nbResToWait += 1
                time.sleep(ELAPSED_SLEEP)
                self.wait_all_resp()
                idx = detNearRessources(self.lookInventory, "food")
                respArray = detPath(idx)
                for res in respArray:
                    self.client.write(res)
                    self.nbResToWait += 1
                    time.sleep(ELAPSED_SLEEP)
                self.client.write("Take food\n")
                self.nbResToWait += 1
                time.sleep(ELAPSED_SLEEP)
                self.wait_all_resp()
            else:
                for resource, required in elevationCondition[str(ai.level)]["ressources"].items():
                    if self.inventory[resource] < required:
                        self.client.write("Look\n")
                        self.nbResToWait += 1
                        time.sleep(ELAPSED_SLEEP)
                        self.wait_all_resp()

                        idx = detNearRessources(self.lookInventory, resource)
                        if idx == -1:
                            print(f"[WARN] {resource} not found nearby.")
                            continue
                        respArray = detPath(idx)
                        for res in respArray:
                            self.client.write(res)
                            self.nbResToWait += 1
                            time.sleep(ELAPSED_SLEEP)
                        self.client.write(f"Take {resource}\n")
                        self.nbResToWait += 1
                        time.sleep(ELAPSED_SLEEP)
                        self.wait_all_resp()
                    if random.randint(0, 1):
                        self.client.write("Right\n")
                        self.nbResToWait += 1
                        time.sleep(ELAPSED_SLEEP)
                        self.wait_all_resp()
                    else:
                        self.client.write("Right\n")
                        self.nbResToWait += 1
                        time.sleep(ELAPSED_SLEEP)
                        self.wait_all_resp()
                    break

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

# example = "player linemate, linemate player player, food deraumere , mendiane phiras,food linemate player player, deraumere , mendiane phiras, sibur"
# tile_tab = formatLook(example)
# index = detNearRessources(tile_tab, "player")
# index = detNearRessources(tile_tab, "player")

# fillInventory("[linemate 1, deraumere 2, food 5, sibur 0, mendiane 0, phiras 1, thystame 0]")

# from pprint import pprint
# pprint(tile_tab)
# print(detNearRessources(tile_tab, "sibur"))
# print(detNearRessources(tile_tab, "food"))
# print(detNearRessources(tile_tab, "phiras"))
# # print(detNearRessources(tile_tab, "food"))
# print(detPath(detNearRessources(tile_tab, "sibur")))
# print(detPath(detNearRessources(tile_tab, "food")))
# print(detPath(detNearRessources(tile_tab, "phiras")))
# print(detPath(detNearRessources(tile_tab, "toot")))

