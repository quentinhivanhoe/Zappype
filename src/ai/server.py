import socket

HOST = "127.0.0.1"
PORT = 4242

def start_manual_response_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen(1)
        print(f"[INFO] Serveur en attente sur {HOST}:{PORT}...")

        conn, addr = s.accept()
        print(f"[INFO] Client connecté depuis {addr}")
        conn.sendall(b"WELCOME\n")  # Envoie le message de bienvenue

        try:
            while True:
                data = b''
                while not data.endswith(b'\n'):
                    chunk = conn.recv(1024)
                    if not chunk:
                        print("[INFO] Client déconnecté.")
                        return
                    data += chunk

                msg = data.decode().strip()
                print(f"[CLIENT] {msg}")

                # Tu tapes ici la réponse manuellement
                response = input("Répondre : ").strip()
                if response == "":
                    continue
                conn.sendall((response + "\n").encode())

        except KeyboardInterrupt:
            print("\n[INFO] Fermeture serveur.")
        finally:
            conn.close()

if __name__ == "__main__":
    start_manual_response_server()
