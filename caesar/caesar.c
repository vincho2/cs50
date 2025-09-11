#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_arg_integer(string argument_value);
void encrypt_and_display_char(int key, string text);
char get_cipher_char_case(int key, char current_char, int case_offset);

const int abc_26 = 26;
const int char_id_A = 65;
const int char_id_a = 97;

int main(int argc, string argv[])
{

    // If the command line is not entered with 1 integer argument and 1 only, then stop the program
    if (argc != 2 || !is_arg_integer(argv[1]))
    {
        // Display error message and return 1
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // Set key variable
        int key = atoi(argv[1]);
        int key_reduced = key % abc_26;

        // Get the plain text input from user
        string plain_text = get_string("plaintext:  ");

        // Display the result and return 0
        printf("ciphertext: ");
        encrypt_and_display_char(key_reduced, plain_text);

        return 0;
    }
}

// -------------------------------------------------------------------------------------------------
// Helper method to encrypt the input text using the provided key
// -------------------------------------------------------------------------------------------------
void encrypt_and_display_char(int key, string text)
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

        // Logic to encrypt upper case letters
        if (isupper(plain_current_char))
        {
            case_offset = char_id_A;
            cipher_current_char = get_cipher_char_case(key, plain_current_char, case_offset);
        }
        // Logic to encrypt lower case letters
        else if (islower(plain_current_char))
        {
            case_offset = char_id_a;
            cipher_current_char = get_cipher_char_case(key, plain_current_char, case_offset);
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
// Helper function to get the cipher character depending on the character case
// -------------------------------------------------------------------------------------------------
char get_cipher_char_case(int key, char current_char, int case_offset)
{

    // Value used to determine how to get the cipher character
    // (depending on the char location in the alphabet)
    int key_offset = abc_26 - key;

    if (current_char < case_offset + key_offset)
    {
        return current_char + key;
    }
    else
    {
        return current_char - key_offset;
    }
}

// -------------------------------------------------------------------------------------------------
// Helper function to check if the input argument is an Integer
// -------------------------------------------------------------------------------------------------
bool is_arg_integer(string argument_value)
{

    int arg_1_length = strlen(argument_value);
    bool is_arg_num = true;
    int i = 0;
    char current_char;

    while (i < arg_1_length && is_arg_num)
    {
        current_char = argument_value[i];
        if (!isdigit(current_char))
        {
            is_arg_num = false;
        }
        i++;
    }
    return is_arg_num;
}
