#import <stdio.h>
#import <cs50.h>

int main(void)
{
    float cash = 0;
    do
    {
        cash = get_float("How much change we talking (0.01-1000)? ");
    }
    while (cash <= 0 || cash > 1000); // reasonable boundary 0 < x < 1000
    // multiply by 100 so I can divide below by whole numbers
    // i.e.: $1.52 => 152. 152 - 25 cents instead of 1.52 - 0.25 cents
    // no real reason to do this other than I think it reads easier
    cash = cash*100;
        
    // track how many coins have been dispensed
    int coins = 0;
       
    // while able to remove 25 cents from the current cash total...
    while (cash - 25 >= 0)
    {
        // lower the total by 25 cents
        cash -= 25;
        // increment the coin counter by +1 coin
        coins++;
    }
    // repease for dimes and nickels
    while (cash - 10 >= 0) 
    {
        cash -= 10;
        coins++;
    }
    while (cash - 5 >= 0)
    {
        cash -= 5;
        coins++;
    }
    
    // all that is left at this point is pennies (total is under 5c)
    // convert the float to an int (removing all decimals) leaving whole pennies
    int int_cash = cash;
    // add the pennies to the coins counter
    coins += int_cash;
    // simple print function returns the coin counter value    
    printf("%i\n", coins);
}
