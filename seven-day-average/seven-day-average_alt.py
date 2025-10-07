import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):

    # Key = State name, value = [total nb of cases, counter]
    cumulative_cases = {}
    # Key = State name, value = [case day 0, case day 1, etc]
    result = {}

    # Loop on each row of the csv file
    for row in reader:

        # Define state and current cases variables with the row values
        state = row['state']
        current_cases = row['cases']

        # Initialize cumulative cases dictionary with 0 values if the state key is absent
        if state not in cumulative_cases.keys():
            cumulative_cases[state] = [0]
            cumulative_cases[state].append(0)

        # Inistialize previous cases count and result array counter
        previous_cases = int(cumulative_cases[state][0])
        counter = int(cumulative_cases[state][1])

        # Count new cases compared to previous day for this state
        new_cases = int(current_cases) - previous_cases

        # Initialize the key in the result dictionary if not present
        if state not in result.keys():
            result[state] = [new_cases]

        # Else fill the result list with cases until there are 14 values
        elif len(result[state]) < 14:
            result[state].append(new_cases)

        # After the max of 14 values is reached, start replacing oldest values by newest ones
        else:
            result[state][counter % 14] = new_cases
            cumulative_cases[state][1] += 1

        # Update cumulative state for the current row
        cumulative_cases[state][0] = int(current_cases)

    # Reorder case values in the correct order with the oldest ones at the beginning of the list
    formatted_result = {}
    for state, cases in result.items():
        counter = cumulative_cases[state][1]
        formatted_result[state] = [cases[(counter + i + 1) % 14] for i in range(14)]

    # Return the result
    return formatted_result


# Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):

    # Loop on each state
    for state in states:

        # Define the list of cases for the last 14 days (old to new)
        new_cases_state = new_cases[state]

        # Compute average (previous and latest)
        prev_seven_day_avg = round(sum(new_cases_state[0:7]) / 7)
        seven_day_avg = round(sum(new_cases_state[7:14]) / 7)

        # Compute trend
        trend = round((seven_day_avg / prev_seven_day_avg - 1) * 100)
        trend_abs = abs(trend)
        trend_type = 'an increase' if trend > 0 else 'a decrease'

        # Print result
        print(f'{state} had a 7-day average of {seven_day_avg} and {trend_type} of {trend_abs}%')


# Call Main
main()
