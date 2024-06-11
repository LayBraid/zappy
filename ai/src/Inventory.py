class Inventory:
	def __init__(self) -> None:
		self.food = 0
		self.linemate = 0
		self.deraumere = 0
		self.sibur = 0
		self.mendiane = 0
		self.phiras = 0
		self.thystame = 0

	def __str__(self) -> str:
		return "food: " + str(self.food) + ", linemate: " + str(self.linemate) + ", deraumere: " + str(
			self.deraumere) + ", sibur: " + str(self.sibur) + ", mendiane: " + str(self.mendiane) + ", phiras: " + str(
			self.phiras) + ", thystame: " + str(self.thystame)

	def update_inventory(self, message: str):
		try:
			items = message[1:-1].strip().split(",")
			items = list(map(lambda x: x.strip().split(" ")[1], items))
			self.food = int(items[0])
			self.linemate = int(items[1])
			self.deraumere = int(items[2])
			self.sibur = int(items[3])
			self.mendiane = int(items[4])
			self.phiras = int(items[5])
			self.thystame = int(items[6])

		except Exception as e:
			print(e)
			print("Error while updating inventory, message: " + message)

	def add(self, item):
		if item == "food":
			self.food += 1
		elif item == "linemate":
			self.linemate += 1
		elif item == "deraumere":
			self.deraumere += 1
		elif item == "sibur":
			self.sibur += 1
		elif item == "mendiane":
			self.mendiane += 1
		elif item == "phiras":
			self.phiras += 1
		elif item == "thystame":
			self.thystame += 1
