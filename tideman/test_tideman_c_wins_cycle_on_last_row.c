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
int candidate_count = 5;

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

int main(void)
{
    candidates[0] = "a";
    candidates[1] = "b";
    candidates[2] = "c";
    candidates[3] = "d";
    candidates[4] = "e";

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = 10;
    string voters_choices[voter_count][candidate_count];

        string voter0[] = { candidates[2],
                            candidates[0],
                            candidates[1],
                            candidates[4],
                            candidates[3]
        };
        string voter1[] = { candidates[0],
                            candidates[1],
                            candidates[2],
                            candidates[3],
                            candidates[4]
        };

        string voter2[] = { candidates[0],
                            candidates[1],
                            candidates[2],
                            candidates[3],
                            candidates[4]
        };
        string voter3[] = { candidates[1],
                            candidates[2],
                            candidates[0],
                            candidates[4],
                            candidates[3]
        };
        string voter4[] = { candidates[0],
                            candidates[1],
                            candidates[2],
                            candidates[3],
                            candidates[4]
        };
        string voter5[] = { candidates[1],
                            candidates[4],
                            candidates[3],
                            candidates[2],
                            candidates[0]
        };
        string voter6[] = { candidates[2],
                            candidates[4],
                            candidates[3],
                            candidates[1],
                            candidates[0]
        };
        string voter7[] = { candidates[4],
                            candidates[1],
                            candidates[2],
                            candidates[0],
                            candidates[3]
        };
        string voter8[] = { candidates[3],
                            candidates[4],
                            candidates[2],
                            candidates[0],
                            candidates[1]
        };
        string voter9[] = { candidates[3],
                            candidates[4],
                            candidates[2],
                            candidates[0],
                            candidates[1]
        };

    for (int i = 0; i < candidate_count; i++) {voters_choices[0][i] = voter0[i];}
    for (int i = 0; i < candidate_count; i++) {voters_choices[1][i] = voter1[i];}
    for (int i = 0; i < candidate_count; i++) {voters_choices[2][i] = voter2[i];}
    for (int i = 0; i < candidate_count; i++) {voters_choices[3][i] = voter3[i];}
    for (int i = 0; i < candidate_count; i++) {voters_choices[4][i] = voter4[i];}
    for (int i = 0; i < candidate_count; i++) {voters_choices[5][i] = voter5[i];}
    for (int i = 0; i < candidate_count; i++) {voters_choices[6][i] = voter6[i];}
    for (int i = 0; i < candidate_count; i++) {voters_choices[7][i] = voter7[i];}
    for (int i = 0; i < candidate_count; i++) {voters_choices[8][i] = voter8[i];}
    for (int i = 0; i < candidate_count; i++) {voters_choices[9][i] = voter9[i];}

    printf("Voters_choices:\n");        // TBR
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++) {
            printf("%s", voters_choices[i][j]);
        }
        printf("\n");
    }

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = voters_choices[i][j];
            // get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        printf("Display ranks %i\n", i);
        for (int k = 0; k < candidate_count; k++)
        {
            printf("%i ", ranks[k]);
        }
        printf("\n");

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
    // Loop over each pair and define the winner / loser
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Record pair only when there is a winner over a loser
            // (i.e: no tie)
            win_i_over_j = preferences[i][j];
            win_j_over_i = preferences[j][i];

            // Define winner / loser of the pair k when candidate i is winning
            if (win_i_over_j > win_j_over_i)
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                k++;
            }
            // Define winner / loser of the pair k when candidate j is winning
            else if (win_j_over_i > win_i_over_j)
            {
                pairs[k].winner = j;
                pairs[k].loser = i;
                k++;
            }
        }
    }
    // Update pair count when loop is over
    pair_count = k;

    printf("Unsorted pairs:\n");        // TBR
    for (int i = 0; i < pair_count; i++)
    {
        printf("%s-%s = %i\n",
            candidates[pairs[i].winner],
            candidates[pairs[i].loser],
            preferences[pairs[i].winner][pairs[i].loser]);
    }
}

// -------------------------------------------------------------------------------------------------
// Sort pairs in decreasing order by strength of victory
// -------------------------------------------------------------------------------------------------
void sort_pairs(void)
{
    sort_array(pairs, pair_count);

    printf("Sorted Pairs:\n");              // TBR
    for (int i = 0; i < pair_count; i++)
        {
            printf("%s-%s = %i\n",
                candidates[pairs[i].winner],
                candidates[pairs[i].loser],
                preferences[pairs[i].winner][pairs[i].loser]);
        }
}

// -------------------------------------------------------------------------------------------------
// Lock pairs into the candidate graph in order, without creating cycles
// -------------------------------------------------------------------------------------------------
void lock_pairs(void)
{
    printf("Pairs locked\n"); // TBR
    // TODO

}

// -------------------------------------------------------------------------------------------------
// Print the winner of the election
// -------------------------------------------------------------------------------------------------
void print_winner(void)
{
    printf("Winner is printed\n"); // TBR
    // TODO

}

// -------------------------------------------------------------------------------------------------
// Sort array of pairs in decreasing order by strength of victory
// -------------------------------------------------------------------------------------------------
void sort_array(pair pairs_array[], int array_size)
{
    // Sort is only needed when there more than 1 single element in the array
    if (array_size > 1)
    {

        // -- Debug ----------------------------
        printf("Parent array unsorted:\n");
        for (int i = 0; i < array_size; i++)
        {
            printf("%s-%s = %i\n",
                candidates[pairs_array[i].winner],
                candidates[pairs_array[i].loser],
                preferences[pairs_array[i].winner][pairs_array[i].loser]);
        }
        // -- Debug end ---------------------------


        // -----------------------------------------------------------------------------------------
        // Define left array and sort it
        // -----------------------------------------------------------------------------------------
        int left_array_size = array_size / 2;
        pair left_array[left_array_size];
        populate_sub_array(pairs_array, left_array, left_array_size, 0);

        // -- Debug ----------------------------
        printf("Left array unsorted:\n");
        for (int i = 0; i < left_array_size; i++)
        {
            printf("%s-%s = %i\n" ,
                candidates[left_array[i].winner],
                candidates[left_array[i].loser],
                preferences[left_array[i].winner][left_array[i].loser]);
        }
        // -- Debug end ----------------------------

        sort_array(left_array, left_array_size);

        // -- Debug ----------------------------
        printf("Left array sorted:\n");
        for (int i = 0; i < left_array_size; i++)
        {
            printf("%s-%s = %i\n" ,
                candidates[left_array[i].winner],
                candidates[left_array[i].loser],
                preferences[left_array[i].winner][left_array[i].loser]);
        }
        // -- Debug end ----------------------------

        // -----------------------------------------------------------------------------------------
        // Define right array and sort it
        // -----------------------------------------------------------------------------------------
        int right_array_size = array_size - left_array_size;
        pair right_array[right_array_size];
        populate_sub_array(pairs_array, right_array, right_array_size, left_array_size);

        // -- Debug ----------------------------
        printf("Right array unsorted:\n");
        for (int i = 0; i < right_array_size; i++)
        {
            printf("%s-%s = %i\n" ,
                candidates[right_array[i].winner],
                candidates[right_array[i].loser],
                preferences[right_array[i].winner][right_array[i].loser]);
        }
        // -- Debug end ----------------------------

        sort_array(right_array, right_array_size);

        // -- Debug ----------------------------
        printf("Right array sorted:\n");
        for (int i = 0; i < right_array_size; i++)
        {
            printf("%s-%s = %i\n" ,
                candidates[right_array[i].winner],
                candidates[right_array[i].loser],
                preferences[right_array[i].winner][right_array[i].loser]);
        }
        // -- Debug end ----------------------------

        // -----------------------------------------------------------------------------------------
        // Merge left and right arrays into the parent array
        // -----------------------------------------------------------------------------------------

        int array_pair_id = 0;
        int left_counter = 0;
        int right_counter = 0;

        // Compare pairs of both arrays until one has been fully scanned
        while (left_counter < left_array_size && right_counter < right_array_size)
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
                // Add left pair
                pairs_array[array_pair_id] = left_pair;
                left_counter++;
                array_pair_id++;
                // Add right pair
                pairs_array[array_pair_id] = right_pair;
                right_counter++;
                array_pair_id++;
            }
        }
        // At this point, one of the array is fully scanned, so all the remaining pairs of the
        // other array go into the parent array in their current order
        if (left_counter < left_array_size)
        {
            for (int i = left_counter; i < left_array_size; i++)
            {
                pairs_array[array_pair_id] = left_array[i];
                array_pair_id++;
            }
        }
        else if (right_counter < right_array_size)
        {
            for (int i = right_counter; i < right_array_size; i++)
            {
                pairs_array[array_pair_id] = right_array[i];
                array_pair_id++;
            }
        }

        // -- Debug ----------------------------
        printf("Parent array sorted:\n");
        for (int i = 0; i < array_size; i++)
        {
            printf("%s-%s = %i\n" ,
                candidates[pairs_array[i].winner],
                candidates[pairs_array[i].loser],
                preferences[pairs_array[i].winner][pairs_array[i].loser]);
        }
        // -- Debug end ----------------------------
    }
}

// -------------------------------------------------------------------------------------------------
// Helper method to populate the intermediaries arrays
// -------------------------------------------------------------------------------------------------
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

// -------------------------------------------------------------------------------------------------
// Helper method to get the number of votes of a pair's winner
// -------------------------------------------------------------------------------------------------
int get_pair_winner_votes(pair pair)
{
    return preferences[pair.winner][pair.loser];
}
