from cs50 import get_int

# pythonic do-while loop, do forever then break out when a condition has been met setting a global variable (hoisted?)
while True:
    # cast the string input to an integer
    height = int(get_int("How tall (1-8)? "))
    if height > 0 and height < 9:
        break

# for each row: spaces + hashes = height
for row in range(height):
    # left side leading spaces (spaces = height - row), -1 to account for input being 1-8 but index counting 0-N
    print(" " * (height - row - 1), end="")

    # left side hashes of the pyramid
    print("#" * (row + 1), end="")

    # gap
    print("  ", end="")

    # right side of the pyramid consists only of hashes (no need for trailing spaces)
    print("#" * (row + 1))
