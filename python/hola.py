import random, string

def random_colors():
    r = random.randint(0, 255)
    g = random.randint(0, 255)
    b = random.randint(0, 255)
    return f"\033[38;2;{r};{g};{b}m"

def generate_random_password(length=30):
    return ''.join(random.choices(string.ascii_letters + string.digits + string.punctuation, k=length))

while True:
    color_code = random_colors()
    password = generate_random_password()
    print(f"{color_code}{password}\033[0m")  # resets and stuff