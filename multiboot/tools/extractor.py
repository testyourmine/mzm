from array import array
from io import BufferedReader
import shutil
import os

DATA_PATH = "data/"
subDirs: array = [
    "sprites/",
    "hud/",
    "weapons/",
    "common/",
    "intro/",
    "tourian_escape/",
    "animated_tiles/",
    "close_up/",
    "fusion_gallery/",
    "ending/",
    "chozodia_escape/",
    "tilesets/",
    "tilesets/animated_palettes",
    "cutscenes/",
    "cutscenes/KraidRising/",
    "cutscenes/StoryText/",
    "cutscenes/MotherBrainCloseUp/",
    "cutscenes/RidleyInSpace/",
    "cutscenes/RidleyLanding/",
    "cutscenes/RidleySpawn/",
    "cutscenes/MechaSeesSamus/",
    "cutscenes/GettingFullyPoweredSuit/",
    "cutscenes/BeforeCharlie/",
    "cutscenes/StatueOpening/",
    "cutscenes/EnterTourian/",
    "cutscenes/SamusInBlueShip/",
    "menus/",
    "menus/TitleScreen/",
    "menus/GameOver/",
    "menus/EraseSram/",
    "menus/PauseScreen/",
    "menus/FileSelect/",
    "rooms/",
    "rooms/debug/",
    "rooms/brinstar/",
    "rooms/kraid/",
    "rooms/norfair/",
    "rooms/ridley/",
    "rooms/tourian/",
    "rooms/crateria/",
    "rooms/chozodia/",
    "samus/",
    "samus/palettes/",
    "samus/graphics/",
    "samus/graphics/power_suit/",
    "samus/graphics/full_suit/",
    "samus/graphics/suitless/",
    "samus/graphics/effects/",
    "samus/graphics/arm_cannon/",
    "io/",
]

try:
    shutil.rmtree(DATA_PATH, ignore_errors=False, onerror=None)
except:
    pass

# Create directories
os.mkdir(DATA_PATH)
for dir in subDirs:
    os.mkdir(DATA_PATH.__add__(dir))


rom: BufferedReader = open("mzm_us_baserom.gba", "rb")
db: BufferedReader = open("database.txt", "r")

line: str = db.readline()
while line != '':
    # Formatted as follows : name;length;address;size
    # The symbol # can be used as the first character of a line to make the extractor ignore it
    if line[0] != '\n' and line[0] != '#':
        info: array = line.split(";")

        name: str = info[0]
        print("Extracting", name)
        rom.seek(int(info[2], 16))

        size: int = int(info[3])
        output: BufferedReader = open(DATA_PATH.__add__(name), "ab")
        for x in range(0, int(info[1])):
            output.write(int.from_bytes(rom.read(size), "little").to_bytes(size, "little"))

        output.close()
    line = db.readline()

rom.close()