import csv
import requests

AVG_DAYS = 7


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct day lists of new cases for each states
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

    # Print out n-day averages for this week vs last week
    comparative_averages(new_cases, states)


# Create a dictionary to store the most recent days of new cases by state
def calculate(reader):

    cumulative_cases = {}       # {State name: total nb of cases}
    result = {}                 # {State name: list of new cases}

    for row in reader:

        state = row['state']
        current_cases = int(row['cases'])

        # Initialize previous cases count
        previous_cases = cumulative_cases.get(state, 0)

        # Count new cases compared to previous day for this state
        new_cases = current_cases - previous_cases

        # Append the new cases value to the result or initialize the key and value if not present
        result.setdefault(state, []).append(new_cases)

        # Maintain a window of twice the number of the number of days used for average
        if len(result[state]) > AVG_DAYS * 2:
            result[state].pop(0)

        # Update cumulative state for the current row
        cumulative_cases[state] = current_cases

    return result

# Calculate and print out seven day average for given state


def comparative_averages(new_cases, states):

    # Loop on each state
    for state in states:

        # Define the list of cases for the doubled average day
        cases = new_cases[state]

        # Compute average (previous and latest)
        prev_avg = round(sum(cases[0:AVG_DAYS]) / AVG_DAYS)
        recent_avg = round(sum(cases[AVG_DAYS:AVG_DAYS * 2]) / AVG_DAYS)

        # Compute trend
        trend = round((recent_avg / prev_avg - 1) * 100) if prev_avg != 0 else 0
        trend_abs = abs(trend)
        trend_type = 'an increase' if trend > 0 else 'a decrease'

        # Print result
        print(f'{state} had a {AVG_DAYS}-day average of {recent_avg} and {trend_type} of {trend_abs}%')


# Call Main
main()
