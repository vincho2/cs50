#include <cs50.h>
#include <stdio.h>

// Define constants
const string invalid = "INVALID";

// Card number size
const int size_13 = 13;     // Visa
const int size_15 = 15;     // Amex
const int size_16 = 16;     // Visa & Mastercard

// Card number digit starter
const int amex_digit1 = 34;
const int amex_digit2 = 37;

const int mast_digit1 = 51;
const int mast_digit2 = 52;
const int mast_digit3 = 53;
const int mast_digit4 = 54;
const int mast_digit5 = 55;

const int visa_digit = 4;

bool check_amex(long card_nb);
bool check_mastercard(long card_nb);
bool check_visa(int long);
bool check_luhn(long card_nb);
int starting_digits(long number, int length, int n);
long get_number_size(long long_nb);
int get_digit(long long_nb, int digit_nb);
int get_last_digit(long long_nb);
long power10(int n);

// -------------------------------------------------------------------------------------------------
// --- Main: Return card type and validity based on the card number input
// -------------------------------------------------------------------------------------------------
int main(void)
{
    // Ask for the credit card number until a valid positive long integer is displayed
    long card_nb;
    int digit_requested;                                                // to be removed
    do
    {
        card_nb = get_long("What's your credit card number?\n");
        digit_requested = get_int("What digit do you want?\n");         // to be removed
    }
    while (card_nb <= 0);

    int card_nb_size = get_number_size(card_nb);
    printf("Card number size: %i\n", card_nb_size);

    int nb_digit = get_digit(card_nb, digit_requested);
    printf("Digit value: %i\n", nb_digit);

    // Check Amex card validity and return AMEX if true
    if (check_amex(card_nb))
    {
        printf("AMEX\n");
    }

    // Check MasterCard validity and return MASTERCARD if true
    else if (check_mastercard(card_nb))
    {
        printf("MASTERCARD\n");
    }

    // Check Visa validity and return VISA if true
    else if (check_visa(card_nb))
    {
        printf("VISA\n");
    }
    else
    {
        printf("%s\n", invalid);
    }
}

// -------------------------------------------------------------------------------------------------
// Helper function: Check American Express card validity
// -------------------------------------------------------------------------------------------------
bool check_amex(long card_nb)
{
    // Extract the first 2 digits of the card number
    int starting_2_digits = starting_digits(card_nb, size_15, 2);

    // Check that the starting digits of the card number are valid for this card type
    bool check_starting_digits =
        (starting_2_digits == amex_digit1 || starting_2_digits == amex_digit2);

    // Check overall validity by checking the firt digits and then Luhn algorithm
    if (check_starting_digits && check_luhn(card_nb))
    {
        return true;
    }
    else
    {
        printf("Not an Amex !!!!!\n");
        return false;
    }
}

// -------------------------------------------------------------------------------------------------
// Helper function: Check Mastercard card validity
// -------------------------------------------------------------------------------------------------
bool check_mastercard(long card_nb)
{
    // Extract the first 2 digits of the card number
    int starting_2_digits = starting_digits(card_nb, size_16, 2);

    // Check that the starting digits of the card number are valid for this card type
    bool check_starting_digits =
        (starting_2_digits == mast_digit1 || starting_2_digits == mast_digit2 ||
         starting_2_digits == mast_digit3 || starting_2_digits == mast_digit4 ||
         starting_2_digits == mast_digit5);

    // Check overall validity by checking the firt digits and then Luhn algorithm
    if (check_starting_digits && check_luhn(card_nb))
    {
        return true;
    }
    else
    {
        printf("Not a Mastercard !!!!!!\n");
        return false;
    }
}

// -------------------------------------------------------------------------------------------------
// Helper function: Check Visa card validity
// -------------------------------------------------------------------------------------------------
bool check_visa(long card_nb)
{
    // Extract the first digit of the card number
    int check_starting_digit_low = starting_digits(card_nb, size_13, 1);
    int check_starting_digit_high = starting_digits(card_nb, size_16, 1);

    // Check that the starting digit of the card number is valid for this card type
    bool check_starting_digits =
        (check_starting_digit_low == visa_digit || check_starting_digit_high == visa_digit);

    // Check overall validity by checking the firt digits and then Luhn algorithm
    if (check_starting_digits && check_luhn(card_nb))
    {
        return true;
    }
    else
    {
        printf("Not a Visa !!!!!!\n");
        return false;
    }
}

// -------------------------------------------------------------------------------------------------
// Helper function: Check Luhn's algorithm
// -------------------------------------------------------------------------------------------------
bool check_luhn(long card_nb)
{
    int card_nb_size = get_number_size(card_nb);

    int check_digit_sum = O;
    int j = 1;

    for (int i = card_nb_size; i--; i = 1)
    {
        // Declare the number to add to the sum
        int nb_to_add;
        int digit_i = get_digit(i);

        // For the last digit and every other digits before that, simply add it to the sum
        if ((j / 2) * 2 == j)
        {
            nb_to_add = digit_i;
        }
        // For the second-to-last digit and every other digits before that, check further
        else
        {
            // Double the digit
            nb_to_add = digit_i * 2;

            // If the doubled digit is higer than 10, number to add is the sum of the digits of the
            // doubled digit
            if (nb_to_add > 10)
            {
                // Replace the number to add by the sum of both digits of the doubled digit
                nb_to_add = get_digit(nb_to_add, 1) + get_digit(nb_to_add, 2);
            }
        }

        // Add the number obtained to the overal sum
        check_digit_sum += nb_to_add;
        printf("check digit sum: %i, digit checked: %i, nb added: %i\n", check_digit_sum, i, nb_to_add);

        // Increment j
        j++;
    }

    // After looping on all digits, return true if the final sum modulo 10 is congruent to 0
    if ((check_digit_sum % 10) == 0)
    {
        printf("Luhn's check ok\n");
        return true;
    }
    else
    {
        printf("Result of modulo = %i\n", check_digit_sum % 10);
        return false
    }
}

// -------------------------------------------------------------------------------------------------
// Helper function: Returns the n first digit of a number, providing its length and n
// -------------------------------------------------------------------------------------------------
int starting_digits(long number, int length, int n)
{
    int starting_digits = number / power10(length - n);
    printf("starting digits: %i\n", starting_digits);

    return starting_digits;
}


// -------------------------------------------------------------------------------------------------
// Helper function: Get number size
// -------------------------------------------------------------------------------------------------
long get_number_size(long long_nb)
{
    int result = 0;
    while (long_nb > 0)
    {
        long_nb /= 10;
        result++;
    }
    return result;
}

// -------------------------------------------------------------------------------------------------
// Helper function: Get number digit i of number
// -------------------------------------------------------------------------------------------------
int get_digit(long long_nb, int digit_nb)
{
    int nb_size = get_number_size(long_nb);
    return get_last_digit(long_nb / power10(nb_size - digit_nb));
}

// -------------------------------------------------------------------------------------------------
// Helper function: Get number last
// -------------------------------------------------------------------------------------------------
int get_last_digit(long long_nb)
{
    return long_nb - (long_nb / 10) * 10;
}

// -------------------------------------------------------------------------------------------------
// Helper function: Returns 10^n, n being the argument provided
// -------------------------------------------------------------------------------------------------
long power10(int n)
{
    long result = 1;
    for (int i = 0; i < n; i++)
    {
        result *= 10;
    }
    return result;
}
