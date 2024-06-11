import copy
import random
from collections import namedtuple

from ai.src import Client
from ai.src.Inventory import Inventory
from ai.src.Utils import retrieve_levels, Direction, Orientation, get_food_min, get_food_step, get_food_min_incantation

Point = namedtuple('Point', ['x', 'y'])

FOOD_MIN = 45
FOOD_PALER = 30
FOOD_MIN_INCANTATION = 15


def rotate_character(origin, direction):
	if direction == Direction.LEFT:
		if origin == Orientation.NORTH:
			return Orientation.WEST
		elif origin == Orientation.SOUTH:
			return Orientation.EAST
		elif origin == Orientation.EAST:
			return Orientation.NORTH
		elif origin == Orientation.WEST:
			return Orientation.SOUTH
	elif direction == Direction.RIGHT:
		if origin == Orientation.NORTH:
			return Orientation.EAST
		elif origin == Orientation.SOUTH:
			return Orientation.WEST
		elif origin == Orientation.EAST:
			return Orientation.SOUTH
		elif origin == Orientation.WEST:
			return Orientation.NORTH


def compute_position(origin, orientation, direction):
	x = origin.x
	y = origin.y
	if direction == Direction.FORWARD:
		if orientation == Orientation.NORTH:
			return Point(x, y - 1)
		elif orientation == Orientation.SOUTH:
			return Point(x, y + 1)
		elif orientation == Orientation.EAST:
			return Point(x + 1, y)
		elif orientation == Orientation.WEST:
			return Point(x - 1, y)


class AlgorithmVentura:
	def __init__(self, client: Client):
		self.standby = False
		self.second_standby = False
		self.step = 0
		self.map_width = None
		self.map_height = None
		self.client = client
		self.levels = retrieve_levels()
		self.current_objects_same_cell = []
		self.take_needed = []
		self.vector_to_target = (0, 0)
		self.target = None
		self.target_cell = []
		self.target_cell_needs = []
		self.look_drop = []

	def set_standby(self, standby):
		self.standby = standby

	def set_map_size(self, width, height):
		self.map_width = width
		self.map_height = height

	def up(self):
		self.step += 1

	def down(self):
		self.step -= 1

	def can_elevate(self) -> bool:
		inventory = self.client.inventory
		if self.client.level == 1:
			if inventory.linemate >= 1:
				return True
		elif self.client.level == 2:
			if inventory.linemate >= 1 \
					and inventory.deraumere >= 1 \
					and inventory.sibur >= 1:
				return True
		elif self.client.level == 3:
			if inventory.linemate >= 2 \
					and inventory.sibur >= 1 \
					and inventory.phiras >= 2:
				return True
		elif self.client.level == 4:
			if inventory.linemate >= 1 \
					and inventory.deraumere >= 1 \
					and inventory.sibur >= 2 \
					and inventory.phiras >= 1:
				return True
		elif self.client.level == 5:
			if inventory.linemate >= 1 \
					and inventory.deraumere >= 2 \
					and inventory.sibur >= 1 \
					and inventory.mendiane >= 3:
				return True
		elif self.client.level == 6:
			if inventory.linemate >= 1 \
					and inventory.deraumere >= 2 \
					and inventory.sibur >= 3 \
					and inventory.phiras >= 1:
				return True
		elif self.client.level == 7:
			if inventory.linemate >= 2 \
					and inventory.deraumere >= 2 \
					and inventory.sibur >= 2 \
					and inventory.mendiane >= 2 \
					and inventory.phiras >= 2 \
					and inventory.thystame >= 1:
				return True
		return False

	def can_elevate_with(self, inventory: Inventory) -> bool:
		if self.client.level == 1:
			if inventory.linemate >= 1:
				return True
		elif self.client.level == 2:
			if inventory.linemate >= 1 \
					and inventory.deraumere >= 1 \
					and inventory.sibur >= 1:
				return True
		elif self.client.level == 3:
			if inventory.linemate >= 2 \
					and inventory.sibur >= 1 \
					and inventory.phiras >= 2:
				return True
		elif self.client.level == 4:
			if inventory.linemate >= 1 \
					and inventory.deraumere >= 1 \
					and inventory.sibur >= 2 \
					and inventory.phiras >= 1:
				return True
		elif self.client.level == 5:
			if inventory.linemate >= 1 \
					and inventory.deraumere >= 2 \
					and inventory.sibur >= 1 \
					and inventory.mendiane >= 3:
				return True
		elif self.client.level == 6:
			if inventory.linemate >= 1 \
					and inventory.deraumere >= 2 \
					and inventory.sibur >= 3 \
					and inventory.phiras >= 1:
				return True
		elif self.client.level == 7:
			if inventory.linemate >= 2 \
					and inventory.deraumere >= 2 \
					and inventory.sibur >= 2 \
					and inventory.mendiane >= 2 \
					and inventory.phiras >= 2 \
					and inventory.thystame >= 1:
				return True
		return False

	def can_group_elevate(self) -> bool:
		shared_inventory = self.client.shared_inventory
		if self.client.level == 1:
			return False
		elif self.client.level == 2:
			if shared_inventory.linemate >= 1 \
					and shared_inventory.deraumere >= 1 \
					and shared_inventory.sibur >= 1:
				return True
		elif self.client.level == 3:
			if shared_inventory.linemate >= 2 \
					and shared_inventory.sibur >= 1 \
					and shared_inventory.phiras >= 2:
				return True
		elif self.client.level == 4:
			if shared_inventory.linemate >= 1 \
					and shared_inventory.deraumere >= 1 \
					and shared_inventory.sibur >= 2 \
					and shared_inventory.phiras >= 1:
				return True
		elif self.client.level == 5:
			if shared_inventory.linemate >= 1 \
					and shared_inventory.deraumere >= 2 \
					and shared_inventory.sibur >= 1 \
					and shared_inventory.mendiane >= 3:
				return True
		elif self.client.level == 6:
			if shared_inventory.linemate >= 1 \
					and shared_inventory.deraumere >= 2 \
					and shared_inventory.sibur >= 3 \
					and shared_inventory.phiras >= 1:
				return True
		elif self.client.level == 7:
			if shared_inventory.linemate >= 2 \
					and shared_inventory.deraumere >= 2 \
					and shared_inventory.sibur >= 2 \
					and shared_inventory.mendiane >= 2 \
					and shared_inventory.phiras >= 2 \
					and shared_inventory.thystame >= 1:
				return True
		return False

	def what_you_need(self) -> str:
		if self.client.inventory.food < FOOD_MIN:
			return 'food'
		if self.client.level == 1:
			if self.client.inventory.linemate < 1:
				return 'linemate'
			return 'food'
		elif self.client.level == 2:
			if self.client.inventory.linemate < 1:
				return 'linemate'
			elif self.client.inventory.deraumere < 1:
				return 'deraumere'
			elif self.client.inventory.sibur < 1:
				return 'sibur'
			return 'food'
		elif self.client.level == 3:
			if self.client.inventory.linemate < 2:
				return 'linemate'
			elif self.client.inventory.sibur < 1:
				return 'sibur'
			elif self.client.inventory.phiras < 2:
				return 'phiras'
			return 'food'
		elif self.client.level == 4:
			if self.client.inventory.linemate < 1:
				return 'linemate'
			elif self.client.inventory.deraumere < 1:
				return 'deraumere'
			elif self.client.inventory.sibur < 2:
				return 'sibur'
			elif self.client.inventory.phiras < 1:
				return 'phiras'
			return 'food'
		elif self.client.level == 5:
			if self.client.inventory.linemate < 1:
				return 'linemate'
			elif self.client.inventory.deraumere < 2:
				return 'deraumere'
			elif self.client.inventory.sibur < 1:
				return 'sibur'
			elif self.client.inventory.mendiane < 3:
				return 'mendiane'
			return 'food'
		elif self.client.level == 6:
			if self.client.inventory.linemate < 1:
				return 'linemate'
			elif self.client.inventory.deraumere < 2:
				return 'deraumere'
			elif self.client.inventory.sibur < 3:
				return 'sibur'
			elif self.client.inventory.phiras < 1:
				return 'phiras'
			return 'food'
		elif self.client.level == 7:
			if self.client.inventory.linemate < 2:
				return 'linemate'
			elif self.client.inventory.deraumere < 2:
				return 'deraumere'
			elif self.client.inventory.sibur < 2:
				return 'sibur'
			elif self.client.inventory.mendiane < 2:
				return 'mendiane'
			elif self.client.inventory.phiras < 2:
				return 'phiras'
			elif self.client.inventory.thystame < 1:
				return 'thystame'
			return 'food'
		return 'food'

	def what_you_need_custom(self, inventory: Inventory):
		if self.client.inventory.food < get_food_step():
			return 'food'

		if self.client.level == 1:
			if inventory.linemate < 1:
				return 'linemate'
			return 'food'
		elif self.client.level == 2:
			if inventory.linemate < 1:
				return 'linemate'
			elif inventory.deraumere < 1:
				return 'deraumere'
			elif inventory.sibur < 1:
				return 'sibur'
			return 'food'
		elif self.client.level == 3:
			if inventory.linemate < 2:
				return 'linemate'
			elif inventory.sibur < 1:
				return 'sibur'
			elif inventory.phiras < 2:
				return 'phiras'
			return 'food'
		elif self.client.level == 4:
			if inventory.linemate < 1:
				return 'linemate'
			elif inventory.deraumere < 1:
				return 'deraumere'
			elif inventory.sibur < 2:
				return 'sibur'
			elif inventory.phiras < 1:
				return 'phiras'
			return 'food'
		elif self.client.level == 5:
			if inventory.linemate < 1:
				return 'linemate'
			elif inventory.deraumere < 2:
				return 'deraumere'
			elif inventory.sibur < 1:
				return 'sibur'
			elif inventory.mendiane < 3:
				return 'mendiane'
			return 'food'
		elif self.client.level == 6:
			if inventory.linemate < 1:
				return 'linemate'
			elif inventory.deraumere < 2:
				return 'deraumere'
			elif inventory.sibur < 3:
				return 'sibur'
			elif inventory.phiras < 1:
				return 'phiras'
			return 'food'
		elif self.client.level == 7:
			if inventory.linemate < 2:
				return 'linemate'
			elif inventory.deraumere < 2:
				return 'deraumere'
			elif inventory.sibur < 2:
				return 'sibur'
			elif inventory.mendiane < 2:
				return 'mendiane'
			elif inventory.phiras < 2:
				return 'phiras'
			elif inventory.thystame < 1:
				return 'thystame'
			return 'food'
		return 'food'

	def player_need_to_level_up(self):
		if self.client.level == 1:
			return 1
		elif self.client.level == 2:
			return 2
		elif self.client.level == 3:
			return 2
		elif self.client.level == 4:
			return 4
		elif self.client.level == 5:
			return 4
		elif self.client.level == 6:
			return 6
		elif self.client.level == 7:
			return 6
		return 0

	def what_want_to_next_level(self):
		if self.client.level == 1:
			if self.client.inventory.linemate < 1:
				return 'linemate'
			if self.client.inventory.deraumere < 1:
				return 'deraumere'
			if self.client.inventory.sibur < 1:
				return 'sibur'
			return 'food'
		elif self.client.level == 2:
			if self.client.inventory.linemate < 2:
				return 'linemate'
			if self.client.inventory.sibur < 1:
				return 'sibur'
			if self.client.inventory.phiras < 2:
				return 'phiras'
			return 'food'
		elif self.client.level == 3:
			if self.client.inventory.linemate < 1:
				return 'linemate'
			if self.client.inventory.deraumere < 1:
				return 'deraumere'
			if self.client.inventory.sibur < 2:
				return 'sibur'
			if self.client.inventory.phiras < 1:
				return 'phiras'
			return 'food'
		elif self.client.level == 4:
			if self.client.inventory.linemate < 1:
				return 'linemate'
			if self.client.inventory.deraumere < 2:
				return 'deraumere'
			if self.client.inventory.sibur < 1:
				return 'sibur'
			if self.client.inventory.mendiane < 3:
				return 'mendiane'
			return 'food'
		elif self.client.level == 5:
			if self.client.inventory.linemate < 1:
				return 'linemate'
			if self.client.inventory.deraumere < 2:
				return 'deraumere'
			if self.client.inventory.sibur < 3:
				return 'sibur'
			if self.client.inventory.phiras < 1:
				return 'phiras'
			return 'food'
		elif self.client.level == 6:
			if self.client.inventory.linemate < 2:
				return 'linemate'
			if self.client.inventory.deraumere < 2:
				return 'deraumere'
			if self.client.inventory.sibur < 2:
				return 'sibur'
			if self.client.inventory.mendiane < 2:
				return 'mendiane'
			if self.client.inventory.phiras < 2:
				return 'phiras'
			if self.client.inventory.thystame < 1:
				return 'thystame'
			return 'food'
		elif self.client.level == 7:
			if self.client.inventory.linemate < 2:
				return 'linemate'
			if self.client.inventory.deraumere < 2:
				return 'deraumere'
			if self.client.inventory.sibur < 2:
				return 'sibur'
			if self.client.inventory.mendiane < 2:
				return 'mendiane'
			if self.client.inventory.phiras < 2:
				return 'phiras'
			if self.client.inventory.thystame < 1:
				return 'thystame'
			return 'food'
		return 'food'

	def simulate_whats_needed(self):
		copy_inventory = copy.deepcopy(self.client.inventory)

		for index, obj in enumerate(self.current_objects_same_cell):
			need = self.what_you_need_custom(copy_inventory)
			if need == obj:
				self.take_needed.append(obj)
				if need == 'linemate':
					copy_inventory.linemate += 1
				elif need == 'deraumere':
					copy_inventory.deraumere += 1
				elif need == 'sibur':
					copy_inventory.sibur += 1
				elif need == 'mendiane':
					copy_inventory.mendiane += 1
				elif need == 'phiras':
					copy_inventory.phiras += 1
				elif need == 'thystame':
					copy_inventory.thystame += 1
				elif need == 'food':
					copy_inventory.food += 1
			self.current_objects_same_cell.remove(obj)

	def simulate_whats_needed_custom(self, cell, index) -> bool:
		copy_inventory = copy.deepcopy(self.client.inventory)
		target_cell = cell.split(' ')
		self.target_cell_needs = []

		for index, obj in enumerate(target_cell):
			need = self.what_you_need_custom(copy_inventory)
			if need == obj:
				self.target_cell_needs.append(obj)
				if need == 'linemate':
					copy_inventory.linemate += 1
				elif need == 'deraumere':
					copy_inventory.deraumere += 1
				elif need == 'sibur':
					copy_inventory.sibur += 1
				elif need == 'mendiane':
					copy_inventory.mendiane += 1
				elif need == 'phiras':
					copy_inventory.phiras += 1
				elif need == 'thystame':
					copy_inventory.thystame += 1
				elif need == 'food':
					copy_inventory.food += 1
			target_cell.remove(obj)

		if len(self.target_cell_needs) > 0:
			self.vector_to_target = [0, index]
			return True
		return False

	def retrieve_target_coordinates(self, index):
		if index == 0:
			self.vector_to_target = [0, 0]
			return [0, 0]
		elif index == 1:
			self.vector_to_target = [1, -1]
			return [1, -1]
		elif index == 2:
			self.vector_to_target = [1, 0]
			return [1, 0]
		elif index == 3:
			self.vector_to_target = [1, 1]
			return [1, 1]
		elif index == 4:
			self.vector_to_target = [2, -2]
			return [2, -2]
		elif index == 5:
			self.vector_to_target = [2, -1]
			return [2, -1]
		elif index == 6:
			self.vector_to_target = [2, 0]
			return [2, 0]
		elif index == 7:
			self.vector_to_target = [2, 1]
			return [2, 1]
		elif index == 8:
			self.vector_to_target = [2, 2]
			return [2, 2]
		elif index == 9:
			self.vector_to_target = [3, -3]
			return [3, -3]
		elif index == 10:
			self.vector_to_target = [3, -2]
			return [3, -2]
		elif index == 11:
			self.vector_to_target = [3, -1]
			return [3, -1]
		elif index == 12:
			self.vector_to_target = [3, 0]
			return [3, 0]
		elif index == 13:
			self.vector_to_target = [3, 1]
			return [3, 1]
		elif index == 14:
			self.vector_to_target = [3, 2]
			return [3, 2]
		elif index == 15:
			self.vector_to_target = [3, 3]
			return [3, 3]
		else:
			self.vector_to_target = [0, 0]
			return [0, 0]

	def parse_look(self, look):
		print("\n\t\t\t------ PARSE LOOK ------")
		# print("\t\t\tInitial look: " + str(look) + "")
		my_look = look
		self.current_objects_same_cell = []
		my_look = my_look.replace('[ ', '')
		my_look = my_look.replace(', ]', '')
		my_look = my_look.replace(' ]', '')
		my_look = my_look.replace('"', '')
		my_look = my_look.replace('\n', '')
		my_look = my_look.replace(', ', ',')
		cells = my_look.split(',')
		# print("\t\t\tCells: " + str(cells) + "")
		for obj in cells[0].split(' '):
			if obj != '':
				self.current_objects_same_cell.append(obj)

		if self.step == 102:
			self.down()
			return

		if self.client.waiting_player is True:
			player_on_cell = 0
			for obj in cells[0].split(' '):
				if obj == 'player':
					player_on_cell += 1
			if player_on_cell >= self.client.waiting_player_nb:
				self.client.waiting_player = False
				self.client.waiting_player_nb = 0

		want = self.what_you_need()
		# print("\t\t\t----- ON CELL -----")
		# print("\t\t\tI need: " + want + "")
		# print("\t\t\tI see: " + str(self.current_objects_same_cell) + "")
		all_need = self.what_all_need()
		if self.client.inventory.food >= FOOD_PALER:
			self.take_needed = []
			for obj in self.current_objects_same_cell:
				if obj in all_need and obj != want:
					self.take_needed.append(obj)
					self.current_objects_same_cell.remove(obj)
		if want in self.current_objects_same_cell:
			for obj in self.current_objects_same_cell:
				if obj == want:
					# print("\t\t\tFound what I need on my cell: " + obj)
					self.take_needed.append(obj)
					self.current_objects_same_cell.remove(obj)
			# print("\t\t\tNow, I need to take: " + str(self.take_needed) + "")
			return
		# else:
		# print("\t\t\tI don't need what I see")

		if self.client.inventory.food <= FOOD_PALER:
			return
		# print("\t\t\t--- ANOTHER LEVEL ---")
		want_next = self.what_want_to_next_level()
		if want_next == want:
			return
		# print("\t\t\tI want to level next: " + want_next + "")

		if want_next in self.current_objects_same_cell:
			# print("\t\t\tFound what I need in for another level: " + want_next)
			for obj in self.current_objects_same_cell:
				if obj == want_next:
					self.take_needed.append(obj)
					self.current_objects_same_cell.remove(obj)

		# print("\t\t\t--- ANOTHER CELL ---")
		# self.simulate_whats_needed()

		for index, cell in enumerate(cells):
			if index != 0:
				if self.simulate_whats_needed_custom(cell, index) is True:
					# print(
					#	"\t\t\tFound what I need in target cell: " + str(self.target_cell_needs) + " at index: " + str(
					#		index) + "")
					self.retrieve_target_coordinates(index)
					self.target = True
					# print("\t\t\tset Target cell: " + str(self.target_cell))
					break

	def what_all_need(self):
		need = []
		if self.client.level == 0:
			need.append('linemate')
		elif self.client.level == 1:
			need.append('linemate')
			need.append('deraumere')
			need.append('sibur')
		elif self.client.level == 2:
			need.append('linemate')
			need.append('linemate')
			need.append('sibur')
			need.append('phiras')
		elif self.client.level == 3:
			need.append('linemate')
			need.append('deraumere')
			need.append('sibur')
			need.append('phiras')
		elif self.client.level == 4:
			need.append('linemate')
			need.append('deraumere')
			need.append('sibur')
			need.append('mendiane')
			need.append('phiras')
		elif self.client.level == 5:
			need.append('linemate')
			need.append('deraumere')
			need.append('deraumere')
			need.append('sibur')
			need.append('phiras')
			need.append('phiras')
		elif self.client.level == 6:
			need.append('linemate')
			need.append('deraumere')
			need.append('deraumere')
			need.append('sibur')
			need.append('sibur')
			need.append('phiras')
			need.append('phiras')
		elif self.client.level == 7:
			need.append('linemate')
			need.append('deraumere')
			need.append('deraumere')
			need.append('sibur')
			need.append('sibur')
			need.append('mendiane')
			need.append('phiras')
			need.append('phiras')
			need.append('thystame')
		return need

	def drop_for_incantation(self):
		print("\t\t\t--- DROP FOR INCANTATION ---")
		need = self.what_all_need()

		if len(need) == 0:
			self.step = 100
			print("\t\t\tI don't need anything")
			return

		for obj in self.current_objects_same_cell:
			if obj in need:
				need.remove(obj)

		if len(need) == 0:
			self.step = 100
			print("\t\t\tI have everything I need two")
			return

		for obj in need:
			if obj == "linemate" and self.client.inventory.linemate > 0:
				self.look_drop.append("linemate")
				self.client.inventory.linemate -= 1
			elif obj == "deraumere" and self.client.inventory.deraumere > 0:
				self.look_drop.append("deraumere")
				self.client.inventory.deraumere -= 1
			elif obj == "sibur" and self.client.inventory.sibur > 0:
				self.look_drop.append("sibur")
				self.client.inventory.sibur -= 1
			elif obj == "mendiane" and self.client.inventory.mendiane > 0:
				self.look_drop.append("mendiane")
				self.client.inventory.mendiane -= 1
			elif obj == "phiras" and self.client.inventory.phiras > 0:
				self.look_drop.append("phiras")
				self.client.inventory.phiras -= 1
			elif obj == "thystame" and self.client.inventory.thystame > 0:
				self.look_drop.append("thystame")
				self.client.inventory.thystame -= 1

		print("\t\t\tI need: " + str(self.look_drop))

	def rotate_coordinates(self, orientation: Orientation):
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
		inventory_action = random.choice(["Inventory", "None"])
		if inventory_action == "Inventory":
			self.client.inventory_command()
			print("\t\t\t Cancel by inventory check")
			return
		if self.client.inventory.food <= FOOD_MIN_INCANTATION:
			self.second_standby = False
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
			if level != self.client.level:
				self.step = 2
				self.client.last_broadcast = None
				return
			self.step = 103
			print("\t\t\tBroadcast for me")

			position = int(split_message[1])
			print("\t\t\tPosition: " + str(position))
			if position in [1]:
				self.client.last_broadcast = None
				self.client.forward()
				print("\t\t\tForward for broadcast")
			elif position in [2, 3, 4, 5]:
				self.client.last_broadcast = None
				self.client.left()
				print("\t\t\tLeft for broadcast")
			elif position in [6, 7, 8]:
				self.client.last_broadcast = None
				self.client.right()
				print("\t\t\tRight for broadcast")
			elif position == 0:
				print("\t\t\tI'm on the right position")
				self.step = 102
				self.client.last_broadcast = None
				self.second_standby = False

			self.client.last_broadcast = None
			return

	def player_on_cell(self):
		players = 0

		for obj in self.current_objects_same_cell:
			if obj.startswith("player"):
				players += 1

		return players

	def retrieve_action_from_algorithm(self):
		# reference = Point(0, 0)
		# distance_to_corner = 1
		# orientation = Orientation.NORTH
		# last_position = reference

		if self.client.sending is True:
			return

		if self.client.waiting_player is True:
			#print("\t\t\t--- WAITING PLAYER ---")
			self.client.look()
			return

		if len(self.look_drop) > 0:
			print("\t\t\t--- LOOK DROP ---")
			self.client.set_item(self.look_drop[0])
			self.look_drop.pop(0)
			return

		if self.step == 102:
			print("\t\t\t--- INCANTATION LOOK ---")
			self.client.look()
			return

		if self.step == 101:
			print("\t\t\t--- INCANTATION INVENTORY ---")
			self.client.inventory_command()
			self.step = 105
			return

		if self.step == 105:
			self.client.incantation()
			return

		if self.second_standby is True:
			self.handle_broadcast_incantation()

		if len(self.take_needed) > 0:
			fake_inventory = copy.deepcopy(self.client.inventory)
			cell_inventory = Inventory()
			for index, obj in enumerate(self.take_needed):
				if obj == 'linemate':
					fake_inventory.linemate += 1
					cell_inventory.linemate += 1
				elif obj == 'deraumere':
					fake_inventory.deraumere += 1
					cell_inventory.deraumere += 1
				elif obj == 'sibur':
					fake_inventory.sibur += 1
					cell_inventory.sibur += 1
				elif obj == 'mendiane':
					fake_inventory.mendiane += 1
					cell_inventory.mendiane += 1
				elif obj == 'phiras':
					fake_inventory.phiras += 1
					cell_inventory.phiras += 1
				elif obj == 'thystame':
					fake_inventory.thystame += 1
					cell_inventory.thystame += 1
				elif obj == 'food':
					fake_inventory.food += 1
					cell_inventory.food += 1
			if self.can_elevate_with(fake_inventory) is True:
				if 1 < self.player_need_to_level_up() != self.player_on_cell():
					if self.client.inventory.food < FOOD_MIN_INCANTATION:
						self.client.waiting_player = False
						self.client.waiting_player_nb = 0
					else:
						inventory_action = random.choice(["Inventory", "None"])
						if inventory_action == "Inventory":
							self.client.inventory_command()
							return
						print("I can elevate with what I have, and what is on my cell, but I need more player")
						self.client.waiting_player = True
						self.client.waiting_player_nb = self.levels[str(self.client.level)]['player'] - 1
						self.client.broadcast("ELEVATE " + str(self.client.level))
						return
				else:
					if self.can_elevate_with(cell_inventory) is False:
						self.drop_for_incantation()
						return
					print("I can elevate with what I have, and what is on my cell")
					self.take_needed = []
					self.client.last_take = None
					self.client.incantation()
					self.step = 100
					return
			else:
				#print("I take: " + str(self.take_needed[0]) + " because I need it")
				self.client.last_take = self.take_needed[0]
				self.client.take(self.take_needed[0])
				self.take_needed.pop(0)
				return

		if self.target is not None and self.step != 100:
			if self.vector_to_target[0] > 0:
				#print("Forward to target cell: " + str(self.vector_to_target))
				self.vector_to_target[0] -= 1
				self.rotate_coordinates(Orientation.NORTH)
				self.client.forward()
				return
			elif self.vector_to_target[1] > 0:
				#print("Right to target cell: " + str(self.vector_to_target))
				self.vector_to_target[1] -= 1
				self.rotate_coordinates(Orientation.EAST)
				self.client.right()
				return
			elif self.vector_to_target[1] < 0:
				#print("Left to target cell: " + str(self.vector_to_target))
				self.vector_to_target[1] += 1
				self.rotate_coordinates(Orientation.WEST)
				self.client.left()
				return
			else:
				self.target = None
				self.target_cell_needs = []
				self.target_cell = [0, 0]
				self.vector_to_target = [0, 0]
				#print("Reset target cell: " + str(self.vector_to_target) + " and look")
				self.vector_to_target = None
				self.step = 1
				return

		can_elevate = self.can_elevate()
		if can_elevate is True and self.step != 100:
			print("I can elevate")
			self.client.incantation()
			self.step = 100
			return

		if self.step == 0:
			self.client.inventory_command()
			return self.up()
		elif self.step == 1:
			self.client.look()
			return self.up()
		elif self.step == 2:
			action = random.choice(["Forward", "Forward", "Right", "Left"])
			if action == "Forward":
				self.client.forward()
			elif action == "Right":
				self.client.right()
			elif action == "Left":
				self.client.left()
			#action_inventory = random.choice(["Inventory", "None", "None", "None", "None"])
			#if action_inventory == "Inventory":
			#	self.down()
			return self.down()

# for a in range(self.map_width):
#
# 	for avc in range(2):
# 		for jmp in range(distance_to_corner):
# 			new_position = compute_position(last_position, orientation, Direction.FORWARD)
# 			last_position = new_position
# 			self.client.forward()
# 		orientation = rotate_character(orientation, Direction.RIGHT)
# 		self.client.right()
# 	distance_to_corner += 1
