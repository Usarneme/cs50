#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    do 
    {        
        height = get_int("How tall should the pyramids be (0-8)? ");
    }
    while (height <= 0 || height > 8);
    
    // for each row: spaces + hashes = height
    for (int row=0; row<height; row++) 
    {
        // left pyramid consists of 0+ spaces + 1+ hashes
        // spaces = height - row
        for (int k=1; k<height-row; k++)
        {
            printf(" ");       
        }
        for (int l=0; l<=row; l++) 
        {
            printf("#");
        }
        // gap
        printf("  ");
        // right pyramid consists only of hashes         
        for (int m=0; m<=row; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// n(1) = 
// "#  #"
    
// n(2) = 
// "*#  #",
// "##  ##"

// n(3) =
// "**#  #",
// "*##  ##",
// "###  ###"
