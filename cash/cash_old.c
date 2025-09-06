#include <cs50.h>
#include <stdio.h>


int compute_quotient(int dividend, int divisor);
int compute_remainder(int dividend, int divisor);

// Display on screen the minimum number of coins to provide for a given change amount
int main(void)
{
    int change_amount;
    // -- Ask for the change amount until you get a positive integer
    do {
        change_amount = get_int("Change owed: ");
    }
    while (change_amount <= 0);

    // Define coin's face values
    const int coin25 = 25;
    const int coin10 = 10;
    const int coin5 = 5;
    const int coin1 = 1;

    // Initialize the number of coins
    int coin_nb = 0;

    int counter = 0;

    while (change_amount > 0)
    {
        counter++;
        printf("Loop nb: %i\n", counter);

        if (change_amount > coin25)
        {
            coin_nb = coin_nb + compute_quotient(change_amount, coin25);
            printf("quotient = %i\n", coin_nb);
            change_amount = compute_remainder(change_amount, coin25);
            printf("remainder = %i\n", change_amount);

            if (change_amount == 0)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    // Display the number of coins computed
    printf("%i\n", coin_nb);
}

// Helper function to return the quotient of an euclidian division
int compute_quotient(int dividend, int divisor)
{
    return (dividend / divisor);
}

// Helper function to return the remainder of an euclidian division
int compute_remainder(int dividend, int divisor)
{
    return (dividend % divisor);
}

int add_coin(int amount, int coin_value, int )
{
     if (amount > coin_value)
     {
        coin_nb = coin_nb + compute_quotient(change_amount, coin25);
        printf("quotient = %i\n", coin_nb);
        change_amount = compute_remainder(change_amount, coin25);
        printf("remainder = %i\n", change_amount);

            if (change_amount == 0)
            {
                break;
            }
        }
}
