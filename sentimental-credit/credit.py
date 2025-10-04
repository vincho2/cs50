from cs50 import get_int
import re

AMEX = "AMEX"
MASTERCARD = "MASTERCARD"
VISA = "VISA"
INVALID = "INVALID"

patterns = {
    AMEX: r"^(34|37)\d{13}",
    MASTERCARD: r"^5[1-5]\d{14}",
    VISA: r"^4(\d{12}|\d{15})"
}

# ---------------------------------------------------------------------------------------------------
# Define main function that gets the card number and returns the card type
# ---------------------------------------------------------------------------------------------------


def main():

    # Get card number from user input
    card_nb = input("Number: ")

    for card, pattern in patterns.items():
        if re.match(pattern, card_nb) and check_luhn(card_nb):
            print(card)
            break
    else:
        print(INVALID)

# ---------------------------------------------------------------------------------------------------
# Function to check card validity according to Luhn's algorithm
# ---------------------------------------------------------------------------------------------------


def check_luhn(card_nb):

    # Initialize the checksum to 0
    checksum = 0

    # Loop on each number's digit starting by the last one and update checksum
    for i in range(len(card_nb), 0, - 1):

        # Define digit i and convert it to an integer
        digit = int(card_nb[i - 1])

        # For the last digit and every other digits before that, simply add it to the checksum
        if (len(card_nb) - i) % 2 == 0:
            checksum += digit

        # For the second-to-last digit and every other digits before that,
        # double the digit and add the sum of the doubled digit to the checksum
        else:
            checksum += (digit * 2) // 10 + (digit * 2) % 10

    # Return True if the checksum finishes by 0
    return True if checksum % 10 == 0 else False


# ---------------------------------------------------------------------------------------------------
# Call main
# ---------------------------------------------------------------------------------------------------
if __name__ == '__main__':
    main()
