#include <cs50.h>
#include <stdio.h>

// Define constants
const string invalid = "INVALID";

// Card number size
const int size_amex = 15;
const int size_matercard = 16;
const int size_visa_low = 13;
const int size_visa_high = 16;

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
long power10(int n);

// -------------------------------------------------------------------------------------------------
// --- Main: Return card type and validity based on the card number input
// -------------------------------------------------------------------------------------------------
int main(void)
{
    // Ask for the credit card number until a valid positive long integer is displayed
    long card_nb;
    do
    {
        card_nb = get_long("What's your credit card number?\n");
    }
    while (card_nb <= 0);

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
    int starting_2_digits = starting_digits(card_nb, size_amex, 2);

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
    int starting_2_digits = starting_digits(card_nb, size_matercard, 2);

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
    int check_starting_digit_low = starting_digits(card_nb, size_visa_low, 1);
    int check_starting_digit_high = starting_digits(card_nb, size_visa_high, 1);

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
    printf("Luhn's check ok\n");
    return true;
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
