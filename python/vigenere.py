# implements a vigenere cipher
from cs50 import get_string
from sys import argv, exit
from string import ascii_letters

# validate usage:
# argv[0]: vigenere.py, argv[1]: key
# the key (argv[1]) should be alphabetic only
if len(argv) is not 2 or len(argv) > 2 or argv[1] is None or not argv[1].isalpha():
    print("Usage: python vigenere.py key")
    exit(1)

# now that it is validated, store the key
key = argv[1]

# prompt the user for the plaintext string to be encoded
while True:
    plaintext = get_string("plaintext: ")
    if len(plaintext) > 0:
        break

# encipher
key_counter = 0
ciphertext = ""

for character in plaintext:
    # print(character + " = " + str(ord(character)) + ". Key char " + str(key[key_counter]) + " at pos " + str(key_counter))

    # when the plaintext character is a letter character, encipher it
    if character.isalpha():
        # lowercase values are a-z 97-122, uppercase A-Z 65-90
        if ord(character) < 91:
            # print(f"{character} {ord(character)} =>", end="")
            result = ord(character) - 65
            # offset the ordinal of the key depending on if it is upper or lowercased itself
            # the spec indicated the key would be alphabetic, but not that it would be case insensitive
            if ord(key[key_counter]) < 91:
                offset = 65
            else:
                offset = 97
            result = result + ord(key[key_counter]) - offset
            result = result % 26
            result = result + 65
            ciphertext = ciphertext + chr(result)
            # print(" " + str(result) + " (U)")
        else:
            # print(f"{character} {ord(character)} =>", end="")
            result = ord(character) - 97
            if ord(key[key_counter]) < 91:
                offset = 65
            else:
                offset = 97
            result = result + ord(key[key_counter]) - offset
            result = result % 26
            result = result + 97
            ciphertext = ciphertext + chr(result)
            # print(" " + str(result) + " (L)")
        key_counter = (key_counter + 1) % len(key)
    else:
        # when the plaintext character is a non-letter character (space, period, apostrophe, etc.)
        # copy it directly to the ciphertext and do not increment the key_counter as nothing was enciphered
        ciphertext += character

# print plaintext: plantext\nciphertext: ciphertext
print("ciphertext:", ciphertext)
