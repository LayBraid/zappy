import string
from typing import Union

class Ciphers:
    charsList = string.digits + string.ascii_letters + string.punctuation
    # Magic string to verif message's validity
    magic = "5Up3rA1"

    def __init__(self, teamName: str) -> None:
        self.teamName = teamName

    def encryption(self, message: str) -> str:
        message = Ciphers.magic + message
        result=""
        for i, e in enumerate(message):
            position = Ciphers.charsList.index(e)
            decal = Ciphers.charsList.index(self.teamName[i % len(self.teamName)])
            result += Ciphers.charsList[(position + decal) % len(Ciphers.charsList)]
        return result

    def understand(self, message:str) -> bool:
        if (len(message) < len(Ciphers.magic)):
            return False
        for i in range(len(Ciphers.magic)):
            position = Ciphers.charsList.index(message[i])
            decal = Ciphers.charsList.index(self.teamName[i % len(self.teamName)])
            if Ciphers.charsList[(position - decal) % len(Ciphers.charsList)] != Ciphers.magic[i]:
                return False
        return True

    def decryption(self, message: str) -> str:
        result=""
        for i, e in enumerate(message):
            position = Ciphers.charsList.index(e)
            decal = Ciphers.charsList.index(self.teamName[i % len(self.teamName)])
            result += Ciphers.charsList[(position - decal) % len(Ciphers.charsList)]
        return result[len(Ciphers.magic):]

    def verifyAndDecrypt(self, message:str) -> Union[bool, str]:
        if not self.understand(message):
            return False
        return self.decryption(message)



if __name__ == "__main__":

    basic = Ciphers("1")
    simple = Ciphers("12")
    team1 = Ciphers("Team1")
    team2 = Ciphers("Team2")
    one = Ciphers("one")
    two = Ciphers("two")

    # Begin with the encoded magic
    print(basic.encryption("abc"))
    print(simple.encryption("abc"))
    print(team1.encryption("Hello_World"))

    if team2.understand(team1.encryption("Hello_World")):
        print("Error test 1")
    if not team1.understand(team1.encryption("Hello_World")):
        print("Error test 2")

    print(team1.decryption(team1.encryption("Hello_World")))

    # This case should not append thanks to understandable
    print(team2.decryption(team1.encryption("Hello_World")))

    print(one.verifyDecryption(one.encryption("I_need_2_to_level_up")))

    print(one.verifyDecryption(two.encryption("I_need_2_to_level_up")))
