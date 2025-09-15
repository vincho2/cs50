#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    printf("\n");


    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// -------------------------------------------------------------------------------------------------
// VOTE - Record preference if vote is valid
// -------------------------------------------------------------------------------------------------
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// -------------------------------------------------------------------------------------------------
// TABULATE - Tabulate votes for non-eliminated candidates
// -------------------------------------------------------------------------------------------------
void tabulate(void)
{

    // Loop on each voter
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        bool vote_done = false;
        // Loop on each rank until best non-eliminated candidate's vote is done
        while (j < candidate_count && !vote_done)
        {
            int candidate_index = preferences[i][j];
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                vote_done = true;
            }
            j++;
        }
    }
}


// -------------------------------------------------------------------------------------------------
// PRINT WINNER - Print the winner of the election, if there is one
// -------------------------------------------------------------------------------------------------
bool print_winner(void)
{
    // Inistialize the number of votes of the winner
    int max_vote = 0;
    float fifty_percent_factor = 0.5;

    string winner_name;

    // Loop once on each candidate and check if it hase more than 50% of the votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            // Identify the candidate with the most votes
            if (candidates[i].votes > max_vote)
            {
                max_vote = candidates[i].votes;
                winner_name = candidates[i].name;
            }
        }
    }

    // Display winner's name if there is one and return true
    if (max_vote > (voter_count * fifty_percent_factor))
    {
        printf("%s\n", winner_name);
        return true;
    }
    // Else, there is no winner return false
    else
    {
        return false;
    }
}

// -------------------------------------------------------------------------------------------------
// FIND MIN - Return the minimum number of votes any remaining candidate has
// -------------------------------------------------------------------------------------------------
int find_min(void)
{
    // Inistialize the number of votes of the eliminated candidate
    int min_vote = voter_count;

    // Loop once on each candidate and check their votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            // Identify the nb of votes of candidate with the least votes
            if (candidates[i].votes < min_vote)
            {
                min_vote = candidates[i].votes;
            }
        }
    }
    return min_vote;
}

// -------------------------------------------------------------------------------------------------
// IS TIE - Return true if the election is tied between all candidates, false otherwise
// -------------------------------------------------------------------------------------------------
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes != min)
            {
                return false;
            }
        }
    }
    return true;
}

// -------------------------------------------------------------------------------------------------
// ELIMINATE - Eliminate the candidate (or candidates) in last place
// -------------------------------------------------------------------------------------------------
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
