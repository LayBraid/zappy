#!/usr/bin/python3
import selectors
import socket
import subprocess

from ai.src.Algorithm_Ventura import AlgorithmVentura
from ai.src.Algorithm_Sonoma import AlgorithmSonoma
from ai.src.Inventory import Inventory
from ai.src.Utils import get_food_min_incantation


class ClementZappy:
	def __init__(self, address, port, team_name):
		self.address = address
		self.port = int(port)
		self.team_name = team_name
		self.selectors = selectors.DefaultSelector()
		self.socket = None
		self.log_step = 0
		self.level = 1
		self.buffer = ""
		self.sending = False
		self.slot = None
		self.map_width = None
		self.map_height = None
		self.algorithm_ventura = AlgorithmVentura(self)
		self.algorithm_ventura.set_standby(True)
		self.algorithm_sonoma = AlgorithmSonoma(self)
		self.requests = []
		self.command = None
		self.inventory = Inventory()
		self.shared_inventory = Inventory()
		self.last_take = None
		self.waiting_player = None
		self.waiting_player_nb = 0
		self.circular_buffer = ""
		self.last_broadcast = None
		self.child = []
		self.id = None
		self.algorithm_chosen = "ventura"

	def __del__(self):
		# close socket
		pass

	def left(self):
		self.command = "left"
		self.buffer += "Left\n"

	def right(self):
		self.command = "right"
		self.buffer += "Right\n"

	def forward(self):
		self.command = "forward"
		self.buffer += "Forward\n"

	def look(self):
		self.command = "look"
		self.buffer += "Look\n"

	def incantation(self):
		self.command = "incantation"
		self.buffer += "Incantation\n"

	def fork(self):
		self.command = "fork"
		self.buffer += "Fork\n"

	def connect_nbr(self):
		self.command = "connect_nbr"
		self.buffer += "Connect_nbr\n"

	def take(self, resource):
		self.command = "take"
		self.buffer += "Take " + resource + "\n"

	def set_item(self, resource):
		self.command = "set"
		self.buffer += "Set " + resource + "\n"

	def inventory_command(self):
		self.command = "inventory"
		self.buffer += "Inventory\n"

	def broadcast(self, message):
		self.command = "broadcast"
		self.buffer += "Broadcast " + message + "\n"

	def team_name_send(self):
		self.buffer += self.team_name + "\n"

	def send(self, force):
		if self.command is not None and not force and self.sending is False and self.buffer.endswith('\n'):
			tmp = self.buffer.replace('\n', '')
			print(f"{str(self.command).ljust(15)}\tSending message to server: '{tmp}'")
			self.socket.send(self.buffer.encode())
			self.requests.append(self.buffer)
			self.buffer = ""
			self.sending = True
		elif force:
			self.socket.send(self.buffer.encode())
			self.buffer = ""

	def run(self):
		print(f"Connecting to {self.address}:{self.port}")
		self.socket_connect()

		while True:
			from_select = self.selectors.select(timeout=None)
			for key, mask in from_select:
				if mask & selectors.EVENT_READ:
					data = self.socket.recv(4096).decode("utf-8")
					if data:
						self.circular_buffer += data
						if "\n" in self.circular_buffer:
							self.handle_messages()

				if mask & selectors.EVENT_WRITE:
					if self.log_step == 3:
						if self.algorithm_chosen == "ventura":
							self.algorithm_ventura.retrieve_action_from_algorithm()
						elif self.algorithm_chosen == "sonoma":
							self.algorithm_sonoma.retrieve_action_from_algorithm()
					self.send(False)

	def handle_messages(self):
		data = self.circular_buffer.split("\n")[0]
		self.circular_buffer = self.circular_buffer[len(data) + 1:]

		self.last_broadcast = None
		self.handle_death(data)
		if "WELCOME" in data:
			print("Received welcome message from server, sending team name")
			self.team_name_send()
			self.log_step = 1
			self.send(True)
			return
		elif self.log_step == 1 and "message" not in data:
			print(f"Received slot number from server: '{data}'")
			try:
				self.slot = int(data)
				self.id = self.slot
			except ValueError:
				print("Received invalid slot number from server, exiting")
				exit(1)
			self.log_step = 2
			self.command = None
		elif self.log_step == 2 and "message" not in data:
			print(f"Received map size from server: '{data}'")
			self.map_width = int(data.split(" ")[0])
			self.map_height = int(data.split(" ")[1])
			self.algorithm_ventura.set_map_size(self.map_width, self.map_height)
			self.command = None
			if self.slot > 2:
				self.log_step = 3
		elif "ko" in data:
			print("Received ko message from server, command: " + str(self.command))
			self.command = None
		elif "message" in data:
			# print(f"BROADCAST: '{data}'")
			if self.inventory.food >= get_food_min_incantation():
				self.last_broadcast = data
				self.algorithm_chosen = "sonoma"
			return
		elif self.command == "fork":
			print("JE FORK")
			subprocess.Popen(["python", "zappy_ai", "-p", self.port, "-n", self.team_name, ])
			self.log_step = 3
			self.command = None
		elif self.command == "connect_nbr":
			print(f"Received connect_nbr message from server: '{data}'")
			self.command = None
		elif self.command == "team_name":
			print("Received team name message from server, sending team name")
			self.command = None
		elif self.command == "inventory":
			self.inventory.update_inventory(data)
			self.command = None
		elif self.command == "look":
			print("Received look message from server, updating map")
			self.algorithm_ventura.parse_look(data)
			self.command = None
		elif self.command == "take":
			self.inventory.add(self.last_take)
			self.last_take = None
			self.command = None
		elif self.command == "incantation":
			self.algorithm_ventura.standby = True
			self.command = "in_incantation"
		elif self.command == "in_incantation":
			if "Current level" in data:
				self.algorithm_ventura.standby = False
				self.command = None
				next_level = int(data.split(" ")[2])
				print(f"Level up! {self.level} -> {next_level}")
				self.level = next_level
				self.algorithm_ventura.step = 1
			elif "ko" in data:
				self.algorithm_ventura.standby = False
				self.command = None
			elif "Elevation underway" in data:
				self.algorithm_ventura.standby = True
				self.command = "in_incantation"
		elif self.command == "forward":
			self.command = None
		elif self.command == "right":
			self.command = None
		elif self.command == "left":
			self.command = None
		elif self.command == "broadcast":
			self.command = None
		elif self.command == "set":
			self.command = None
		else:
			print(f"Received unknown message from server: '{data}' (command: '{self.command}')")

		self.sending = False

		if "\n" in self.circular_buffer:
			self.handle_messages()

	def handle_death(self, message):
		if "dead" in message:
			print("Received death message from server, exiting")
			print("My level was: " + str(self.level))
			print("My inventory was: " + str(self.inventory))
			self.log_step = 0
			exit(1)

	def socket_connect(self):
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.socket.connect_ex((self.address, self.port))
		events = selectors.EVENT_READ | selectors.EVENT_WRITE
		self.selectors.register(self.socket, events)


def run(hostname, port, team_name):
	client = ClementZappy(hostname, port, team_name)
	client.run()
