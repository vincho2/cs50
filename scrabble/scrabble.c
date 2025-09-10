#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int compute_score(string word);
string get_player_word(int player_id);

// Define the table containing the scores (in alphabetic order)
const int letter_scores[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                             1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

const int ascii_A = 65;
const int ascii_Z = 90;

int main(void)
{
    // Get player's words
    string player_1_word = get_player_word(1);
    string player_2_word = get_player_word(2);

    // Compute each score
    int score1 = compute_score(player_1_word);
    int score2 = compute_score(player_2_word);

    // Compare scores and return the result accordingly
    if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Compute the score of a given word
int compute_score(string word)
{
    // Declare and initialize the current character of the string
    char current_char = 'A';
    int i = 0;
    int total_score = 0;

    while (current_char != '\0')
    {
        // Get current character
        current_char = word[i];
        // Convert it to upper case
        char current_char_up = toupper(current_char);

        // For characters that are letters, add it score to the total score
        if (current_char_up >= ascii_A && current_char_up <= ascii_Z)
        {
            // Initialize score
            int letter_score = 0;
            // Get the score from the score table by converting the char to upper case
            letter_score = letter_scores[current_char_up - ascii_A];
            // Update the overal score
            total_score += letter_score;
        }
        // Increment i
        i++;
    }
    return total_score;
}

// Return the input word provided by user
string get_player_word(int player_id)
{
    return get_string("Player %i: ", player_id);
}
