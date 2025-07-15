# shift alphs
def alphabets(shift):
    alphabet = {}
    for i in range(ord('a'), ord('z') + 1):
        shifted_char = chr((i - ord('a') + shift) % 26 + ord('a'))
        alphabet[chr(i)] = shifted_char
    return alphabet

# shifts it 
initial = input(str("enter decyphered text >:"))
i = int(input("shift by >:"))
enc = {f'alphabet_{i}': alphabets(i) for i in range(27)}
def encrypt_decrypt(text, shift):
    shifted = 

print()