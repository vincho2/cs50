#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt_and_display_text(string key, string text);
bool is_arg_valid_key(string key);

const int ALPHABET_LENGTH = 26;
const int ASCII_A = 65;

// -------------------------------------------------------------------------------------------------
// Main  - Takes a text as argument and encrypt it according to provided key
// -------------------------------------------------------------------------------------------------

int main(int argc, string argv[])
{

    // Stop the program with an error if the argument is not a text combining all alphabet letters
    if (argc != 2 || !is_arg_valid_key(argv[1]))
    {
        // Display error message and return 1
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // Get the plain text input from user
        string plain_text = get_string("plaintext:  ");

        // Display the result and return 0
        printf("ciphertext: ");
        // Display the encrypted text
        encrypt_and_display_text(argv[1], plain_text);

        return 0;
    }
}

// -------------------------------------------------------------------------------------------------
// Helper function to encrypt the input text using the provided key
// -------------------------------------------------------------------------------------------------
void encrypt_and_display_text(string key, string text)
{

    // Get plain text length
    int text_length = strlen(text);
    char plain_current_char;
    char cipher_current_char;

    // Value used to determine the cipher character depending on the character case
    int case_offset;

    // Loop on each plain text character, encrypt it and display it
    for (int i = 0; i < text_length; i++)
    {

        plain_current_char = text[i];
        int index = toupper(plain_current_char) - ASCII_A;

        // Logic to encrypt upper case letters
        if (isupper(plain_current_char))
        {
            cipher_current_char = toupper(key[index]);
        }
        // Logic to encrypt lower case letters
        else if (islower(plain_current_char))
        {
            cipher_current_char = tolower(key[index]);
        }
        // Else, non alphabetical characters should remain unchanged
        else
        {
            cipher_current_char = plain_current_char;
        }

        // Display resulting character
        printf("%c", cipher_current_char);
    }
    printf("\n");
}

// -------------------------------------------------------------------------------------------------
// Helper function to check if the input argument is a valid 26 char containing the entire alphabet
// -------------------------------------------------------------------------------------------------
bool is_arg_valid_key(string key)
{

    // Key is not valid if it is not 26 characters long
    if (strlen(key) != ALPHABET_LENGTH)
    {
        return false;
    }
    // If key is the correct size, it should contain all 26 letters of the alphabet
    else
    {
        bool are_all_char_included_in_key = true;
        bool is_current_char_included_in_key;

        int i = 0;
        while (i < ALPHABET_LENGTH && are_all_char_included_in_key)
        {
            int j = 0;
            is_current_char_included_in_key = false;
            while (j < ALPHABET_LENGTH && !is_current_char_included_in_key)
            {
                // Compare
                if (toupper(key[j]) == ASCII_A + i)
                {
                    is_current_char_included_in_key = true;
                }
                j++;
            }
            if (!is_current_char_included_in_key)
            {
                are_all_char_included_in_key = false;
            }
            i++;
        }
        return are_all_char_included_in_key;
    }
}
