import csv
import sys

# Initialize subsequences to match
AGATC = 'AGATC'
AATG = 'AATG'
TATC = 'TATC'


# --------------------------------------------------------------------------------------------------
# Define Main function
# --------------------------------------------------------------------------------------------------
def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print('Usage: python dna.py database.csv sample.txt')
        return 1

    # Get files path from input arguments
    db_name = sys.argv[1]
    sample_name = sys.argv[2]

    # Read database file into rows variable (list of dictionaries)
    rows = []
    with open(db_name, newline='') as dbf:
        db_content = csv.DictReader(dbf)
        headers = db_content.fieldnames
        for row in db_content:
            rows.append(row)

    # Read DNA sequence file into a variable
    with open(sample_name) as seqf:
        sample_content = seqf.read()

    # Initialize Sample STR count
    sample_str = {
        AGATC: 0,
        AATG: 0,
        TATC: 0
    }

    # Find longest match of each STR in DNA sequence
    for s in sample_str:
        sample_str[s] = longest_match(sample_content, s)

    # Check database for matching profiles

    # Loop on each row of the db
    for row in rows:

        # For each row, loop on each STR to check if they match with sample
        for s in sample_str:

            # As soon as a non-match is found, process with next row
            if sample_str[s] != int(row[s]):
                break
        # If all STRs matches, then print the name of the person matched and stop the program
        else:
            print(row['name'])
            return 0

    # If no match is found, print that no match is found
    else:
        print('No match')


# --------------------------------------------------------------------------------------------------
# Longest match function
# --------------------------------------------------------------------------------------------------
def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


# --------------------------------------------------------------------------------------------------
# Call main
# --------------------------------------------------------------------------------------------------
if __name__ == '__main__':
    main()
