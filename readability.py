

# Define counters
C_WORDS = 'word count'
C_LETTERS = 'letter count'
C_SENTENCES = 'sentence count'

# Define counter dictionary
counters = {
    C_WORDS: 0,
    C_LETTERS: 0,
    C_SENTENCES: 0
}


# Initialize counters as global variables
words = 0
letters = 0
sentences = 0

# Define sentences separators
separators = ['.', '?', '!']


# --------------------------------------------------------------------------------------------------
# Define main function to print the grade of an input text
# --------------------------------------------------------------------------------------------------
def main():

    # Ask the user for a text
    text = input("Text: ")

    # Count text elements and store them in the dedicated global variables
    count_text_elements(text)

    # Compute the grade of the input text
    grade = compute_grade(text)

    # Display result
    if grade < 1:
        print('Before Grade 1')
    elif grade > 16:
        print('Grade 16+')
    else:
        print(f'Grade {grade}')


# --------------------------------------------------------------------------------------------------
# Function to compute the grade
# --------------------------------------------------------------------------------------------------
def compute_grade(text):

    # L = average number of letters per 100 words in the text
    L = letters * 100 / words
    # S = average number of sentences per 100 words in the text
    S = sentences * 100 / words

    # Return Coleman-Liau index
    return 0.0588 * L - 0.296 * S - 15.8


# --------------------------------------------------------------------------------------------------
# Function to update the array containing the different character types in a provided text
# --------------------------------------------------------------------------------------------------
def count_text_elements(text):

    # Loop on each text caracter and update counters
    for char in text:

        # Count letters
        if char.isalnum():
            letters += 1
        elif char.isspace():
            words += 1
        elif char in separators:
            sentences += 1


# --------------------------------------------------------------------------------------------------
# Call main
# --------------------------------------------------------------------------------------------------
if __name__ == "__main__":
    main()
