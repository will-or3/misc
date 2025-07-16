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
def input_enc():
    initial = input(str("enter unencoded text >:"))
    i = int(input("shift by >:"))
    result = encrypt(initial, i)
    print("your secret text is >:", result)
def input_dec():
    initial = input(str("enter encrypted text >:"))
    for i in range (1, 27):
         result = encrypt(initial, i)  
         print(f"shift {i}: {result}\n")
def main():
    want = input("encrypt(1) or decrypt(2) >:")
    if want == '1':
        input_enc()
    if want == '2':
        input_dec()

if __name__ == "__main__":
    main()