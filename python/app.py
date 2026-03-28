import os 
import time

def sticks(frames, repeat=1, delay=0.05):
    for _ in range(repeat):
        for frame in frames:
            os.system("cls" if os.name == "nt" else "clear")
            print(frame)
            time.sleep(delay)
logging_in_frames = [
    "login in",
    "login in.",
    "login in..",
    "login in..."
]
welcome = [
    "",
    "w",
    "we",
    "wel",
    "welc",
    "welco",
    "welcom",
    "welcome",
    "welcom",
    "welco",
    "welc",
    "wel",
    "we",
    "w",
    ""
]
stick_1 = [
    "/",
    "/",
    "_",
    "_",
    "\\",
    "\\",
    "|"
]
stick_2 = [
    " 0\n\\|/\n |\n/ \\",
    " 0\n\\|/                  o\n |\n/ \\",
    " 0\n\\|/                 o\n |\n/ \\",
    " 0\n\\|/                o\n |\n/ \\",
    " 0\n\\|/               o\n |\n/ \\",
    " 0\n\\|/              o\n |\n/ \\",
    " 0\n\\|/             o\n |\n/ \\",
    " 0\n\\|/            o\n |\n/ \\",
    " 0\n\\|/           o\n |\n/ \\",
    " 0\n\\|/          o\n |\n/ \\",
    " 0\n\\|/         o\n |\n/ \\",
    " 0\n\\|/        o\n |\n/ \\",
    " 0\n\\|/       o\n |\n/ \\",
    " 0\n\\|/      o\n |\n/ \\",
    " 0\n\\|/     o\n |\n/ \\",
    " 0\n\\|/    o\n |\n/ \\",
    " 0\n\\|/   o\n |\n/ \\",
    " 0\n\\|/  o\n |\n/ \\",
    " 0\n\\|/ o\n |\n/ \\",
    " 0\n\\|/o\n |\n/ \\",
    " 0\n\\|/o\n |\n/ \\",
    " 0\n\\|/o\n |\n/ \\",
    " 0\n\\|/o\n |\n/ \\",
    " 0\n\\|/o\n |\n/ \\",
    " 0\n\\|/o\n |\n/ \\",
    " 0\n\\|--\n | o\n/ \\",
    " 0\n\\|--\n | o\n/ \\",
    " 0\n\\|--\n | o\n/ \\",
    " 0\n\\|\\\n | \\\n/ \o",
    " 0\n\\|\\\n | \\\n/ \o",
    " 0\n\\|\\\n | \\\n/ \o",
    " 0\n\\|\\\n | \\\n/ \o",
    " 0\n\\|--\n | o\n/ \\",
    " 0\n\\|--\n | o\n/ \\",
    " 0\n\\|--\n | o\n/ \\",
    " 0\n\\|/o\n |\n/ \\",
    " 0\n\\||o\n |\n/ \\",
    " 0\n\\||o\n |\n/ \\",
    " 0\n\\||o\n |\n/ \\",
    " 0\n\\||o\n |\n/ \\",
    " 0\n\\|/ o\n |\n/ \\",
    " 0\n\\|-- o\n |\n/ \\",
    " 0\n\\|--   o\n |\n/ \\",
    " 0\n\\|--   o\n |\n/ \\",
    " 0\n\\|-    o\n |\n/ \\",
    " 0\n\\|       o\n |\\\n/ \\",
    " 0\n\\|-       o\n |\n/ \\",
    " 0\n\\|--       o\n |\n/ \\",
    " 0\n\\|--        o\n |\n/ \\",
    " 0\n\\|/          o\n |\n/ \\",
    " 0\n\\|/           o\n |\n/ \\",
    " 0\n\\|/            o\n |\n/ \\",
    " 0\n\\|/\n |             o\n/ \\",
    " 0\n\\|/\n |\n/ \\              o",
    " 0\n\\|/\n |\n/ \\ \n               o",
    " 0\n\\|/\n |\n/ \\ \n\n                o",
    " 0\n\\|/\n |\n/ \\ \n\n\n                 o",
]

print("welcome to your very own password manager")
print("Login :1")
print("generate passwords :2")
print("stick :stick")
print("Exit :4\n")
#print(" 0\n\\|/\n |\n/ \\")
choice = input(">:")      

if choice == "1":
    while True:
        for frame in logging_in_frames:
            os.system("cls" if os.name == "nt" else "clear")
            print(frame)
            time.sleep(0.3)

if choice == "welcome":   
    while True:
        for frame in welcome:
            os.system("cls" if os.name == "nt" else "clear")
            print(frame)
            time.sleep(0.1)

if choice == "stick":   
    sticks(stick_1, repeat=5)
    sticks(stick_2, repeat=1)
