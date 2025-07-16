# shift alphs
def alphabets(shift):
    alphabet = {}
    for i in range(ord('a'), ord('z') + 1):
        shifted_char = chr((i - ord('a') + shift) % 26 + ord('a'))
        alphabet[chr(i)] = shifted_char
    return alphabet


enc = {f'alphabet_{i}': alphabets(i) for i in range(27)} #27 cause the first one counts as one

def encrypt(text, shift):
    shifted = alphabets(shift)
    result = ''
    for char in text:
        if char in shifted:
            result += (shifted[char]) #encrypt
        else:
            result += (char)
    return result

initial = input(str("enter deciphered text >:"))
i = int(input("shift by >:"))
result = encrypt(initial, i)
print("your secret text is >:", result)