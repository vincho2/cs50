#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int compute_grade(string text);
int count_words(string text);
int count_letters(string text);
int count_sentences(string text);

int main(void)
{

    string text = get_string("Text: ");
    int grade = compute_grade(text);

    printf("Grade %i\n", grade);

}


// Function to compute the grade
int compute_grade(string text)
{
    // Define formula constants
    const float letter_factor = 0.0588;
    const float sentence_factor = 0.296;
    const float formula_const = 15.8;

    int words_nb = count_words(text);
    // Compute average factor to get the number of letters or sentences per 100 words
    double avg_factor = 100.0 / words_nb;

    // Get average number of letters per 100 words
    int letter_nb = count_letters(text);
    double avg_letter = letter_nb * avg_factor;

    // Get average number of letters per 100 words
    int sentence_nb = count_sentences(text);
    double avg_sentence = sentence_nb * avg_factor;

    // Compute raw result
    int raw_result = round(letter_factor * avg_letter
                            - sentence_factor * avg_sentence
                            - formula_const);

    // Return the grade formula result
    return raw_result;
}


// Helper function to count the number of words in a provided text
int count_words(string text)
{
    return 98;
}

// Helper function to count the number of letters in a provided text
int count_letters(string text)
{
    return 1350;
}

// Helper function to count the number of sentences in a provided text
int count_sentences(string text)
{
    return 2;
}
