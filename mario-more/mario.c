#include <cs50.h>
#include <stdio.h>

// Helper function to display a single character as many times as requested
void print_char(char char_symbol, int nb_char);

// Build single stairs for Mario
int main(void)
{
    // --- Ask for a number of steps and store it ---
    int step_nb;
    do
    {
        step_nb = get_int("How many steps should the Mario's double stairs should include? ");
    }
    while (step_nb <= 0);

    // --- Build the double stairs and display it ---

    // Define caracters symbol used by the stairs
    const char char_space = ' ';
    const char char_block = '#';

    // Loop to display each step
    for (int i = 1; i <= step_nb; i++)
    {
        print_char(char_space, step_nb - i);
        print_char(char_block, i);
        print_char(char_space, 2);
        print_char(char_block, i);
        printf("\n");
    }
}

// Helper function to display a single character as many times as requested
void print_char(char char_symbol, int nb_char)
{
    for (int i = 0; i < nb_char; i++)
    {
        printf("%c", char_symbol);
    }
}
