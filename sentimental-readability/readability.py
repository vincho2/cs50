# Define sentences separators
separators = ['.', '?', '!']

# Define counters key
C_LETTERS = 'Letters counter'
C_WORDS = 'Word counter'
C_SENTENCES = 'Sentences counter'


# --------------------------------------------------------------------------------------------------
# Define main function to print the grade of an input text
# --------------------------------------------------------------------------------------------------
def main():

    while True:

        # Define counters dictionary
        counters = {
            C_LETTERS: 0,
            C_WORDS: 0,
            C_SENTENCES: 0
        }

        # Ask the user for a text
        text = input("Text: ")

        # Count text elements and store them in the dedicated global variables
        counters = get_text_elements_counters(text, counters)

        if counters[C_WORDS] > 0:
            break

    # Compute the grade of the input text based on the counters
    grade = compute_grade(counters)

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
def compute_grade(counters):

    # L = average number of letters per 100 words in the text
    L = counters[C_LETTERS] * 100 / counters[C_WORDS]
    # S = average number of sentences per 100 words in the text
    S = counters[C_SENTENCES] * 100 / counters[C_WORDS]

    # Return Coleman-Liau index
    return 0.0588 * L - 0.296 * S - 15.8


# --------------------------------------------------------------------------------------------------
# Function to update the array containing the different character types in a provided text
# --------------------------------------------------------------------------------------------------
def get_text_elements_counters(text, counters):

    # Loop on each text caracter and update counters
    for char in text:

        # Count letters
        if char.isalnum():
            counters[C_LETTERS] += 1
        elif char.isspace():
            counters[C_WORDS] += 1
        elif char in separators:
            counters[C_SENTENCES] += 1

    return counters

# --------------------------------------------------------------------------------------------------
# Call main
# --------------------------------------------------------------------------------------------------
if __name__ == "__main__":
    main()
