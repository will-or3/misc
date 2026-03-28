import random 

key={1: "rock", 2: "paper", 3: "scissors"}
robot = random.randint(1,3)
play = (int(input("rock(1), paper(2), scissors(3) Shoot! >:")))
rps = play - robot
print("robot chose\n" + key[robot])
if rps > 0 and rps != -2: print("you win")
elif rps == -2: print("you win")
elif rps == -1: print("you lose")
elif rps == 0: print("tie")
else:
    print("pick one of the numbers")