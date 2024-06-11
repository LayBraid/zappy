from enum import Enum


def retrieve_levels():
	return {
		'1': {'player': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
		'2': {'player': 2, 'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0},
		'3': {'player': 2, 'linemate': 2, 'deraumere': 0, 'sibur': 1, 'mendiane': 0, 'phiras': 2, 'thystame': 0},
		'4': {'player': 4, 'linemate': 1, 'deraumere': 1, 'sibur': 2, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
		'5': {'player': 4, 'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3, 'phiras': 0, 'thystame': 0},
		'6': {'player': 6, 'linemate': 1, 'deraumere': 2, 'sibur': 3, 'mendiane': 0, 'phiras': 1, 'thystame': 0},
		'7': {'player': 6, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1},
	}


def levels():
	return {
		1: {"linemate": 1},
		2: {"linemate": 1, "deraumere": 1, "sibur": 1},
		3: {"linemate": 2, "sibur": 1, "phiras": 2},
		4: {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
		5: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
		6: {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
		7: {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
	}


class Orientation(Enum):
	NORTH = 1
	SOUTH = 2
	EAST = 3
	WEST = 4


class Direction(Enum):
	FORWARD = 1
	LEFT = 2
	RIGHT = 3


def get_food_min():
	return 40


def get_food_step():
	return 20


def get_food_min_incantation():
	return 10
