import math
a = []
while (n := input(">:")) != "":
    try: a.append(float(n))
    except: pass
print(math.sqrt(sum(x*x for x in a)) if a else "no numbers dumbass")