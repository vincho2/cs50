#include <cs50.h>
#include <stdio.h>

int compute_quotient(int dividend, int divisor);
int compute_remainder(int dividend, int divisor);

// --- Display on screen the minimum number of coins to provide for a given change amount ---
int main(void)
{
    // --- Ask for the change amount until you get a positive integer ---
    int change_amount;

    do
    {
        change_amount = get_int("Change owed: ");
    }
    while (change_amount <= 0);

    // --- Go over each coin value and update the number of coins as well as the remaining amount --

    // I am aware that there is code repetition here that could be overcome by a loop
    // with an array containing the coin values but since we did not cover it yet
    // during the course, I stick to this method

    // Define coin's face values
    const int coin25 = 25;
    const int coin10 = 10;
    const int coin5 = 5;
    const int coin1 = 1;

    // Initialize the number of coins
    int coin_nb = 0;
    int coin_value;

    coin_value = coin25;
    if (change_amount >= coin_value)
    {
        coin_nb = coin_nb + compute_quotient(change_amount, coin_value);
        change_amount = compute_remainder(change_amount, coin_value);
    }

    coin_value = coin10;
    if (change_amount >= coin_value)
    {
        coin_nb = coin_nb + compute_quotient(change_amount, coin_value);
        change_amount = compute_remainder(change_amount, coin_value);
    }

    coin_value = coin5;
    if (change_amount >= coin_value)
    {
        coin_nb = coin_nb + compute_quotient(change_amount, coin_value);
        change_amount = compute_remainder(change_amount, coin_value);
    }

    coin_value = coin1;
    if (change_amount >= coin_value)
    {
        coin_nb = coin_nb + compute_quotient(change_amount, coin_value);
        change_amount = compute_remainder(change_amount, coin_value);
    }

    // Display the number of coins computed
    printf("%i\n", coin_nb);
}

// --- Helper function to return the quotient of an euclidian division ---
int compute_quotient(int dividend, int divisor)
{
    return (dividend / divisor);
}

// --- Helper function to return the remainder of an euclidian division ---
int compute_remainder(int dividend, int divisor)
{
    return (dividend % divisor);
}
