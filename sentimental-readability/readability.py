# Define sentences separators
separators = ['.', '?', '!']

# Ask the user for a text
text = input("Text: ")

# Initialize counters as global variables
words = 0
letters = 0
sentences = 0

# Loop on each text caracter and update counters
for char in text:

    # Count letters
    if char.isalnum():
        letters += 1
    elif char.isspace():
        words += 1
    elif char in separators:
        sentences += 1

# L = average number of letters per 100 words in the text
L = letters * 100 / words
# S = average number of sentences per 100 words in the text
S = sentences * 100 / words

# Return Coleman-Liau index
grade = 0.0588 * L - 0.296 * S - 15.8

# Display result
if grade < 1:
    print('Before Grade 1')
elif grade > 16:
    print('Grade 16+')
else:
    print(f'Grade {grade}')
