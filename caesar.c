#include <cs50.h>
#include <stdio.h>
#include <string.h>
#import <ctype.h>

int main(int argc, string argv[])
{
    // If there is no key or word provided, explain how to run the program and exit
    if (argc == 1 || !argv[1] || argc > 2 || strlen(argv[1]) <= 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int a=0; a<strlen(argv[1]); a++)
    {
        // only numeric keys allowed
        // any letter will return 1024 ie not 1 from isalpha, this will exclude only letters but not exclude special characters eg ;,./><
        // isalnum returns 0 if the input is a letter or number, otherwise is returns 8 to indicate a special character
        // combinging isalpha and isalnum ensures only numbers can be set as the key
        if (isalpha(argv[1][a]) != 0 || isalnum(argv[1][a] == 0))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    // mod 26 the key to keep it within the bounds 0-26 exclusive
    const int key = atoi(argv[1])%26;
    printf("key set to %i\n",key);
    string plaintext;
    do
    {
        plaintext = get_string("Enter a word or phrase to encrypt: ");
    }
    while (!plaintext || strlen(plaintext) <= 0);

    // length of the provided plaintext
    int l = strlen(plaintext);
//     printf("Plaintext set to %s of length %i\n",plaintext,l);
    printf("plaintext: %s\nciphertext: ",plaintext);
    
    for (int i=0; i<l; i++)
    {
        // Uppercase A = 65-90. Lowercase a = 97-122.
        // Subtract A as the minimum value, add the key...
        if (plaintext[i] != ' ')
        {        
            char char_code = plaintext[i];
//             printf("\nlooping %c : %i",char_code,char_code);
            char uppercase = 0;

            if (char_code < 91) 
            {
                char_code = char_code - 65;
                uppercase = 1;
    //             printf(" adj UPP %i",char_code);
            }
            else 
            {
                char_code = char_code - 97;
    //             printf(" adj LOW %i",char_code);
            }
            // add the key, mod by 26 (len of the alphabet to loop/rotate)
            char enc = char_code+key;
    //         printf(" key added %i",enc);
            enc = enc%26;
    //         printf(" mod %i",enc);

            if (uppercase)
            {
                enc = enc + 65;
    //             printf(" adj UPP %i : %c",enc,enc);
            }
            else
            {
                enc = enc + 97;
    //             printf(" adj LOW %i : %c",enc,enc);
            }
            printf("%c",enc);
    //         printf("Letter %c. Value %i. Encrypted letter %c. Encrypted value %i\n",plaintext[i],plaintext[i],enc,enc);
        }
        else
        {
            printf(" ");
        }
    }
    printf("\n");
}
