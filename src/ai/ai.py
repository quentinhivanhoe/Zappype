##
## EPITECH PROJECT, 2025
## Zappype
## File description:
## ai
##

import socket
import sys
import getopt
import threading
import time
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

ai = None

class Client:
    def __init__(self, port, teamName, ip):
        self.port = int(port)
        self.teamName = teamName
        self.ip = "127.0.0.1" if ip == "localhost" else ip
        self.clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def read(self, bufferSize=2048):
        try:
            return self.clientSocket.recv(bufferSize).decode()
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

# class AI:
#     def __init__(self, args):
#         self.client = Client(args["port"], args["team"], args["host"])
#         self.debug = args.get("debug", False)
#         self.level = 1
#         self.food = 0
#         self.isDead = False
#         self.nbResToWait = 0
#         self.resArray = []

#     def waitResponse(self):
#         while len(self.resArray) < self.nbResToWait:
#             response = self.client.read()
#             if response:
#                 responses = response.strip().split('\n')
#                 self.resArray.extend(responses)
#                 for msg in responses:
#                     print(f"[RECEIVED] {msg}")

#     def simulation(self):


#     def send_commands(self):
#         commands = []

#         commands.append("Connect_nbr\n")
#         for _ in range(5):
#             commands.append("Forward\n")
#             commands.append("Right\n")
#             commands.append("Left\n")

#         self.nbResToWait = len(commands)

#         for cmd in commands:
#             print(f"[SENT] {cmd.strip()}")
#             self.client.write(cmd)

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

    def wait_all_resp(self):
        self.resArray = []
        while len(self.resArray) <= (self.nbResToWait - 1):
            res = self.client.read()
            if res == None:
                raise("Error server")
            self.resArray.append(res)
            print(res.strip())
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
            self.nbResToWait = 0
            self.client.write("Forward\n")
            time.sleep(0.5)
            self.nbResToWait += 1
            self.client.write("Right\n")
            time.sleep(0.5)
            self.nbResToWait += 1
            self.client.write("Left\n")
            time.sleep(0.5)
            self.nbResToWait += 1
            self.client.write("Forward\n")
            time.sleep(0.5)
            self.nbResToWait += 1
            self.wait_all_resp()
            # self.nbResToWait = 0

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

if __name__ == "__main__":
    process_ai()
