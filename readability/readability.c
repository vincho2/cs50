#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int compute_grade(string text);
void count_text_elements(string text);

// Initialize the array which stores the number letters, words and sentences
int nb_by_char_type[] = {0, 0, 0};

int main(void)
{
    // Get the text input from the user
    string text = get_string("Text: ");
    // Compute the grade
    int grade = compute_grade(text);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// -------------------------------------------------------------------------------------------------
// Function to compute the grade
// -------------------------------------------------------------------------------------------------
int compute_grade(string text)
{
    // Define formula constants to compute the Coleman-Liau index
    // index = 0.0588 * L - 0.296 * S - 15.8

    // Factor to apply to the average number of letters per 100 words in the text
    const float letter_factor = 0.0588;
    // Factor to apply to the average number of letters per 100 words in the text
    const float sentence_factor = 0.296;
    // Number to substract to compute the Coleman-Liau index
    const float formula_const = 15.8;

    const float percent_factor = 100.0;

    // Update the number of letters, words and sentence in the dedicated array
    count_text_elements(text);

    int words_nb = nb_by_char_type[1];
    // Compute average factor to get the number of letters or sentences per 100 words
    double avg_factor = percent_factor / words_nb;

    // Get average number of letters per 100 words
    int letter_nb = nb_by_char_type[0];
    double avg_letter = letter_nb * avg_factor;

    // Get average number of letters per 100 words
    int sentence_nb = nb_by_char_type[2];
    double avg_sentence = sentence_nb * avg_factor;

    // Compute raw result
    int raw_result =
        round(letter_factor * avg_letter - sentence_factor * avg_sentence - formula_const);

    // Return the grade formula result
    return raw_result;
}

// -------------------------------------------------------------------------------------------------
// Function to update the array containing the different character types in a provided text
// -------------------------------------------------------------------------------------------------
void count_text_elements(string text)
{
    // Get the total number of characters in the input text
    int text_length = strlen(text);

    // Declare and initialize variables
    char current_char;
    int letter_nb = 0;
    int word_nb = 0;
    int sentence_nb = 0;

    for (int i = 0; i < text_length; i++)
    {
        current_char = text[i];

        if (isalnum(current_char))
        {
            letter_nb++;
        }
        else if (isspace(current_char))
        {
            word_nb++;
        }
        else if (current_char == '.' || current_char == '?' || current_char == '!')
        {
            sentence_nb++;
        }
    }

    nb_by_char_type[0] = letter_nb;
    nb_by_char_type[1] = word_nb + 1;
    nb_by_char_type[2] = sentence_nb;
}
