# prints out the least number of coins that can be returned equal to the change owed
# use the get_float method from cs50 library
from cs50 import get_float

# expects input to be 9.00, 0.45, .2, but not 912 or $9.12. range is more than 0 and less than $10
while True:
    pennies = get_float("Change owed: ")
    if pennies > 0 and pennies < 1000:
        break

# easier to deal with whole numbers 192 cents rather than $1.92 or 1.92 float dollars
pennies = int(pennies * 100)
# keep track of the total coins dispensed
coins = 0

while True:
    if (pennies - 25) >= 0:
        coins += 1
        pennies -= 25
    else:
        break

while True:
    if (pennies - 10) >= 0:
        coins += 1
        pennies -= 10
    else:
        break

while True:
    if (pennies - 5) >= 0:
        coins += 1
        pennies -= 5
    else:
        break

coins = coins + pennies
print(coins)
