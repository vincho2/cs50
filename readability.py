

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

# --------------------------------------------------------------------------------------------------
# Define main function to print the grade of an input text
# --------------------------------------------------------------------------------------------------
def main():

    # Ask the user for a text
    text = input("Text: ")

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


# --------------------------------------------------------------------------------------------------
# Function to update the array containing the different character types in a provided text
# --------------------------------------------------------------------------------------------------
def count_text_elements(text):

    # Loop on each text caracter and update counters
    for char in text:

        # Count letters
        if char.isalnum():





# Call main
if __name__ == "__main__":
    main()
