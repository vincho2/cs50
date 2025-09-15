#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void populate_sub_array(pair source_array[],
    pair target_array[],
    int target_array_size,
    int source_array_starting_point);
void sort_array(pair pairs_array[], int array_size);
int get_pair_winner_votes(pair pair);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// -------------------------------------------------------------------------------------------------
// Update ranks given a new vote
// -------------------------------------------------------------------------------------------------
bool vote(int rank, string name, int ranks[])
{
    // Loop on each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If the name of the candidate corresponds to the one given by the voter...
        if (strcmp(candidates[i], name) == 0)
        {
            // Then store the candidate id at the current rank of the ranks array and return true
            ranks[rank] = i;
            return true;
        }
    }
    // Return false in case the name provided does not correspond to any candidate
    return false;
}

// -------------------------------------------------------------------------------------------------
// Update preferences given one voter's ranks
// -------------------------------------------------------------------------------------------------
void record_preferences(int ranks[])
{
    int candidate_id_pair_winner;
    int candidate_id_pair_loser;
    // Loop on each rank
    for (int i = 0; i < candidate_count; i++)
    {
        candidate_id_pair_winner = ranks[i];
        for (int j = i + 1; j < candidate_count; j++)
        {
            candidate_id_pair_loser = ranks[j];
            // Update preference table
            preferences[candidate_id_pair_winner][candidate_id_pair_loser]++;
        }
    }


    // ---------------------------------------------------------------------------------------------
    // TBR - display preferences
    // ---------------------------------------------------------------------------------------------
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i", preferences[i][j]);
        }
        printf("\n");
    }
    // ---------------------------------------------------------------------------------------------
    // TBR - end
    // ---------------------------------------------------------------------------------------------
}

// -------------------------------------------------------------------------------------------------
// Record pairs of candidates where one is preferred over the other
// -------------------------------------------------------------------------------------------------
void add_pairs(void)
{
    int win_i_over_j;
    int win_j_over_i;
    int k = 0;
    // Loop over pair and define the winner / loser
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Define a pair only when there is a winner over a loser
            // (i.e: 2 different candidates, no tie)
            if(i != j)
            {
                win_i_over_j = preferences[i][j];
                win_j_over_i = preferences[j][i];

                // Define winner / loser of the pair k when candidate i is winning
                if (win_i_over_j > win_j_over_i)
                {
                    pairs[k].winner = i;
                    pairs[k].loser = j;
                }
                // Define winner / loser of the pair k when candidate j is winning
                else if (win_j_over_i < win_i_over_j)
                {
                    pairs[k].winner = j;
                    pairs[k].loser = i;
                }
                // Don't define any pair if i=j (same candidate) or when there is a tie
                // increment k to analyze next pair
                k++;
            }
        }
    }
    // Update pair count when loop is over
    pair_count = k + 1;
}

// -------------------------------------------------------------------------------------------------
// Sort pairs in decreasing order by strength of victory
// -------------------------------------------------------------------------------------------------
void sort_pairs(void)
{
    sort_array(pairs, pair_count);
}

// -------------------------------------------------------------------------------------------------
// Lock pairs into the candidate graph in order, without creating cycles
// -------------------------------------------------------------------------------------------------
void lock_pairs(void)
{
    // TODO

}

// -------------------------------------------------------------------------------------------------
// Print the winner of the election
// -------------------------------------------------------------------------------------------------
void print_winner(void)
{
    // TODO

}

// -------------------------------------------------------------------------------------------------
// Sort array of pairs in decreasing order by strength of victory
// -------------------------------------------------------------------------------------------------
void sort_array(pair pairs_array[], int array_size)
{
    printf("Array size: %i\n", array_size); // TBR
    if (array_size == 1)
    {
        printf("Array sorted"); // TBR
    }
    else
    {
        // Define left array and sort it
        int left_array_size = array_size / 2;
        pair left_array[left_array_size];
        populate_sub_array(pairs_array, left_array, left_array_size, 0);
        sort_array(left_array, left_array_size);

        // Define right array and sort it
        int right_array_size = array_size - left_array_size;
        pair right_array[right_array_size];
        populate_sub_array(pairs_array, right_array, right_array_size, left_array_size);
        sort_array(right_array, right_array_size);

        // Merge left and right arrays into the parent array
        int array_pair_id = 0;
        while (array_pair_id < array_size)
        {

            int left_counter = 0;
            int right_counter = 0;

            // Compare pairs of both arrays until one has been fully scanned
            while (left_counter < left_array_size || right_counter < right_array_size)
            {
                // Define left and right pairs to compare
                pair left_pair = left_array[left_counter];
                pair right_pair = right_array[right_counter];

                // Define pairs scores
                int left_winner_votes = get_pair_winner_votes(left_pair);
                int right_winner_votes = get_pair_winner_votes(right_pair);

                // If left pair has the higher edge, then update the array with this pair
                if (left_winner_votes > right_winner_votes)
                {
                    pairs_array[array_pair_id] = left_pair;
                    left_counter++;
                    array_pair_id++;
                }
                // If right pair has the higher edge, then update the array with this pair
                else if (right_winner_votes > left_winner_votes)
                {
                    pairs_array[array_pair_id] = right_pair;
                    right_counter++;
                    array_pair_id++;
                }
                // In case both are equal, then update the array with both (starting with left one)
                else
                {
                    pairs_array[array_pair_id] = left_pair;
                    left_counter++;
                    array_pair_id++;
                    pairs_array[array_pair_id] = right_pair;
                    right_counter++;
                    array_pair_id++;
                }
            }
            // At this point, one of the array is fully scanned, so all the remaining pairs goes
            // into the parent array
            if (left_counter < left_array_size)
            {
                for (int i = left_counter; i < left_array_size; i++)
                {
                    pairs_array[]
                }
            }
        }
    }
}

void populate_sub_array(pair source_array[],
    pair target_array[],
    int target_array_size,
    int source_array_starting_point)
{
    for (int i = 0; i < target_array_size; i++)
    {
        target_array[i] = source_array[source_array_starting_point + i];
    }
}

int get_pair_winner_votes(pair pair)
{
    return preferences[pair.winner, pair.loser];
}
