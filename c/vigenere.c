#include <cs50.h>
#include <stdio.h>
#include <string.h>

// function prototype declaration
int shift(char inp_char);

int main(int argc, string argv[])
{
    // hold the user-provided key
    char * key = argv[1];
//     printf("key set to %s\n",key);
    
    // BEGIN KEY VALIDATION
    // If there is no key or word provided, explain how to run the program and exit
    if (!key || argc > 3)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    // Ensure that the key provided is entirely alphabetical
    for (int i=0, keylen=strlen(key); i<keylen; i++) 
    {
//         printf("checking key[%i]: %c|%i\n",i,key[i],key[i]);
        // Uppercase A = 65-90. Lowercase a = 97-122
        if (key[i] < 65 || key[i] > 122)
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;            
        }
        if (key[i] > 90 && key[i] < 97)
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }
    // END KEY VALIDATION - key is valid
     
    // Get the plaintext string from the user
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
    
    // increment index i is used to go through each individual char in the plaintext string
    // increment index j is used to go through each individual char in key string
    // i is always incremented so the entire plaintext string is traversed
    // j is not incremened on whitespace as that would effectively skip a key from modifying the cipher text
    for (int i=0, j=0; i<l; i++)
    {
        if (plaintext[i] == ' ')
        {
            printf(" ");
        }
        else 
        {
            // Uppercase A = 65-90. Lowercase a = 97-122.
            // Subtract A as the minimum value, add the key...
            char char_code = plaintext[i];
            char uppercase = 0;

            // Key var after being shifted from letter to number
            // modulo keeps cycling 0-keylength 
            // in case the plaintext is longer, thus repeating key values
            // key index counter j is used as i increments on spaces but j does not
            int key_shifted = shift(key[j%strlen(key)]);
    //         printf("key shifted to %i\n",key_shifted);

    //         printf("\nlooping %c : %i\n",char_code,char_code);
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
            char enc = char_code+key_shifted;
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
            // only increment j, the key index counter, when the key is used on a valid, non-space plaintext character
            j++;
        //         printf("Letter %c. Value %i. Encrypted letter %c. Encrypted value %i\n",plaintext[i],plaintext[i],enc,enc);
        }
    }
    printf("\n");
}

// shift function definition
// input char @inp_char is the key we'll use to en/decipher
// this key was already validated above and is in 
// the range of either the upper or lowercase alphabet
int shift(char inp_char)
{
//     printf("shift func. checking inp_char : %c - ",inp_char);
    // Uppercase A = 65-90. Lowercase a = 97-122
    if (inp_char < 91)
    {
//         printf("uppercase. downshifting by 65\n");
        return inp_char-65;
    }
    else
    {
//         printf("lowercase. downshifting by 97\n");
        return inp_char-97;
    }
}
