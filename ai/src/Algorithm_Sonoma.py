import random

from ai.src.Utils import retrieve_levels, Direction, Orientation, get_food_min, get_food_step, get_food_min_incantation


class AlgorithmSonoma:
	def __init__(self, client):
		self.map_width = None
		self.map_height = None
		self.levels = retrieve_levels()
		self.client = client
		self.vector_to_target = [0, 0]
		self.step = 0

	def set_map_size(self, width, height):
		self.map_width = width
		self.map_height = height

	def rotate_coordinates(self, orientation):
		[x, y] = self.vector_to_target
		if orientation == Orientation.NORTH:
			self.vector_to_target = [x, y]
			return
		elif orientation == Orientation.EAST:
			self.vector_to_target = [y, -x]
			return
		elif orientation == Orientation.WEST:
			self.vector_to_target = [-y, x]
			return

	def handle_broadcast_incantation(self):
		inventory_action = random.choice(["Inventory", "None", "None", "None", "None"])
		if inventory_action == "Inventory":
			self.client.inventory_command()
			print("\t\t\t Cancel by inventory check")
			return
		if self.client.inventory.food <= get_food_min_incantation():
			self.client.last_broadcast = None
			self.step = 1
			print("\t\t\t Cancel by food check")
			return

		print("\t\t\t------ Message broadcast ------")
		print("\t\t\tBroadcast message: " + str(self.client.last_broadcast))
		message = self.client.last_broadcast
		if message is None:
			print("\t\t\tNo message")
			self.step = 2
			self.client.last_broadcast = None
			return
		message = message.replace("'", "")
		message = message.replace(",", "")

		split_message = message.split(" ")
		if split_message[2].startswith("ELEVATE"):
			level = int(split_message[3])
			print("\t\t\tLevel: " + str(level))
			print("\t\t\tMy level: " + str(self.client.level))
			if level != self.client.level:
				self.step = 2
				self.client.last_broadcast = None
				self.client.algorithm_chosen = "ventura"
				self.client.algorithm_ventura.retrieve_action_from_algorithm()
				return
			self.step = 103
			print("\t\t\tBroadcast for me")

			position = int(split_message[1])
			print("\t\t\tPosition: " + str(position))
			if position in [1, 2, 8]:
				self.client.last_broadcast = None
				self.client.forward()
				print("\t\t\tForward for broadcast")
			elif position in [3, 4, 5]:
				self.client.last_broadcast = None
				self.client.left()
				print("\t\t\tLeft for broadcast")
			elif position in [6, 7]:
				self.client.last_broadcast = None
				self.client.right()
				print("\t\t\tRight for broadcast")
			elif position == 0:
				print("\t\t\tI'm on the right position")
				self.step = 102
				self.client.last_broadcast = None

			self.client.last_broadcast = None
			return

	def retrieve_action_from_algorithm(self):
		# print("\t\t\t------ Algorithm SONOMA ------")
		if self.client.last_broadcast is not None:
			self.handle_broadcast_incantation()
			return
		pass
