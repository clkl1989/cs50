#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool validate(string key);


int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];

        if (validate(key) == true)
        {
            string plaintext = get_string("plaintext:");

            string original_alpha = "abcdefghijklmnopqrstuvwxyz";

            int plaintext_length = strlen(plaintext);

            char ciphertext[plaintext_length];

            int x, y, z;
            
            printf("ciphertext:  ");

            for (x = 0; x < plaintext_length; x++) //go through each character in the plaintext
            {
                char plainchar = tolower(plaintext[x]);
                if (plainchar >= 'a' && plainchar <= 'z') //if the character in plaintext is an alphabet between a to z
                {
                    //determine if letter is upper or lowercase
                    int is_it_uppercase = isupper(plaintext[x]);
                    if (isupper(plaintext[x]) > 0)  //if letter is uppercase
                    {
                        plaintext[x] = tolower(plaintext[x]); //convert letter to lowercase

                        for (y = 0; y < 26; y++) //determine which letter is in plaintext
                        {
                            if (plaintext[x] == original_alpha[y]) //find the corresponding letter in the key
                            {
                                ciphertext[x] = toupper(key[y]); //substitute each uppercase character
                                printf("%c", ciphertext[x]);
                            }
                        }

                    }

                    else  //if letter is lowercase
                    {
                        for (z = 0; z < 26; z++) //determine which letter is in plaintext
                        {
                            if (plaintext[x] == original_alpha[z]) //find the corresponding letter in the key
                            {
                                ciphertext[x] = tolower(key[z]); //substitute each lowercase character
                                printf("%c", ciphertext[x]);
                            }
                        }
                    }




                }
                else
                {
                    ciphertext[x] = plaintext[x];
                    printf("%c", ciphertext[x]);
                }

            }
            printf("\n");
        }

        else
        {
            printf("Key must contain 26 characters.\n"); //ask user to put in the key properly
            return 1;
        }

    }
    else
    {
        printf("Key must contain 26 characters.\n"); //ask user to put in the key properly
        return 1;
    }
}


bool validate(string key)
{
    int i, j;

    if (strlen(key) == 26)
    {
        for (i = 0; i < 26; i++)
        {
            if (isalpha(key[i]) == 0)
            {
                return false;
            }
            else
            {
                for (j = 0; j < i; j++)
                {
                    if (tolower(key[i]) == tolower(key[j]))
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}