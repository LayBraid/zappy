import selectors
import socket

from ai.src.Algorithm_Ventura import AlgorithmVentura
from ai.src.Inventory import Inventory


class ClientSupra:
	def __init__(self, address, port, team_name) -> None:
		self.alive = True

		self.address = address
		self.port = int(port)
		self.team_name = team_name

		self.algorithm = AlgorithmVentura(self)
		self.algorithm_available = False

		self.level = 1

		self.login_step = 0

		self.available_slots = 0
		self.map_width = None
		self.map_height = None

		self.socket = None
		self.selectors = selectors.DefaultSelector()

		self.circular_buffer = ""
		self.sender = ""

		self.inventory = Inventory()

		self.sending = False
		self.waiting_player = False
		self.waiting_player_nb = 0
		self.command = ""

		self.launch()

	def left(self):
		self.command = "left"
		self.sender += "Left\n"

	def right(self):
		self.command = "right"
		self.sender += "Right\n"

	def forward(self):
		self.command = "forward"
		self.sender += "Forward\n"

	def look(self):
		self.command = "look"
		self.sender += "Look\n"

	def incantation(self):
		self.command = "incantation"
		self.sender += "Incantation\n"

	def fork(self):
		self.command = "fork"
		self.sender += "Fork\n"

	def connect_nbr(self):
		self.command = "connect_nbr"
		self.sender += "Connect_nbr\n"

	def take(self, resource):
		self.command = "take"
		self.sender += "Take " + resource + "\n"

	def set_item(self, resource):
		self.command = "set"
		self.sender += "Set " + resource + "\n"

	def inventory_command(self):
		self.command = "inventory"
		self.sender += "Inventory\n"

	def broadcast(self, message):
		self.command = "broadcast"
		self.sender += "Broadcast " + message + "\n"

	def team_name_send(self):
		self.sender += self.team_name + "\n"

	def launch(self):
		print(f"[+] Connecting to {self.address}:{self.port}")
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.socket.connect_ex((self.address, self.port))
		events = selectors.EVENT_READ | selectors.EVENT_WRITE
		self.selectors.register(self.socket, events)

		while self.alive:
			from_select = self.selectors.select(timeout=None)

			for key, mask in from_select:

				if mask & selectors.EVENT_READ:
					data = self.socket.recv(4096).decode("utf-8")
					if data:
						self.circular_buffer += data
						if "\n" in self.circular_buffer:
							self.compute_circular_buffer()

				if mask & selectors.EVENT_WRITE:

					if self.login_step < 2:
						self.socket.send(self.sender.encode("utf-8"))
						self.sender = ""
						continue

					if self.algorithm_available:
						self.algorithm.retrieve_action_from_algorithm()

					if self.algorithm_available and self.sender:
						print(f"[+] Sending: {self.sender}")
						self.socket.send(self.sender.encode("utf-8"))
						self.algorithm_available = False

	def compute_circular_buffer(self):
		data = self.circular_buffer.split("\n")[0]
		self.circular_buffer = self.circular_buffer[len(data) + 1:]
		if self.login_step > 1:
			print(f"[+] Received: {data}")

		self.handle_death(data)
		if self.login_step == 0 and "WELCOME" in data:
			print("[+] Server accepted connection, sending team name")
			self.login_step = 1
			self.sender += f"{self.team_name}\n"
			return

		elif self.login_step == 1 and "ko" in data:
			print("[-] Server refused team name or no available slot, exiting")
			exit(1)

		elif self.login_step == 1:
			print("[+] Server accepted team name, receiving slot number")
			self.available_slots = int(data)
			self.login_step = 2

		elif self.login_step == 2 and "ko" in data:
			print("[-] Server refused and crash at login step 2, exiting")
			exit(1)

		elif self.login_step == 2:
			self.map_width = int(data.split(" ")[0])
			self.map_height = int(data.split(" ")[1])
			self.algorithm.set_map_size(self.map_width, self.map_height)
			print("[+] Receiving map size, width: " + str(self.map_width) + ", height: " + str(self.map_height))
			self.login_step = 3
			self.algorithm_available = True
			return

		elif "message" in data:
			print("[!] Message received: " + data)

		elif "Inventory" in self.sender:
			try:
				self.inventory.update_inventory(data)
			except Exception as e:
				print("[-] Error while computing inventory abstraction: " + str(e))

		elif "Look" in self.sender:
			self.algorithm.last_look = data

		if self.algorithm_available is False:
			self.sender = ""
			self.algorithm_available = True

		if "\n" in self.circular_buffer:
			self.compute_circular_buffer()

	def handle_death(self, message):
		if "dead" in message:
			print("Received death message from server, exiting")
			print("My level was: " + str(self.level))
			print("My inventory was: " + str(self.inventory))
			self.login_step = 0
			exit(1)
