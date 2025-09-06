#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask for the person's name and store the value in the name variable
    string name = get_string("What's your name?\n");

    // Display the answer in the terminal
    printf("hello, %s\n", name);
}
