#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];
int r, p;
int ranker = 0;

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

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

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    for (int u = 0; u < candidate_count; u++)
    {
        if (strcmp(name, candidates[u].name) == 0)
        {
            for (int v = 0; v < voter_count; v++)
            {
                for (int c = 0; c < candidate_count; c++)
                {

                    preferences[voter][rank] = u;
                    printf("Voter: %i\n", voter);
                    printf("Rank: %i\n", rank);
                    //printf("Candidate: %s\n", candidates[u].name);
                    return true;

                }
            }
        }
    }


    // TODO
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        int u = 0;
        {
            int number = preferences[i][u];

            if (candidates[number].eliminated == false)
            {
                candidates[number].votes += 1;
                printf("Candidates number vote: %i %s\n", candidates[number].votes, candidates[number].name);
            }
            
            else if (candidates[number].eliminated == true)
            {
                for (u = 1; u < candidate_count; u++)
                {
                    int number2 = preferences[i][u];
                    if (candidates[number].eliminated == false)
                    {
                        candidates[number2].votes += 1;
                        printf("Candidates number vote: %i %s\n", candidates[number2].votes, candidates[number2].name);
                    }
                    else if (candidates[number].eliminated == true)
                    {
                        for (u = 2; u < candidate_count; u++)
                        {
                            if (candidates[number].eliminated == false)
                            {
                                candidates[number2].votes += 1;
                                printf("Candidates number vote: %i %s\n", candidates[number2].votes, candidates[number2].name);
                            }
                        }
                    }
                }
            }

        }
    }

}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // do it by modulo
    if (candidate_count % 2 == 0)
    {
        int half = (voter_count / 2) + 1;
        printf("Even half: %i\n", half);

        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes >= half)
            {
                printf("Winner is: %s\n", candidates[i].name);
                return true;
            }
        }
    }
    else if (candidate_count % 2 == 1)
    {
        int half = ((voter_count - 1) / 2) + 1;
        printf("Odd half %i\n", half);

        for (int i = 0; i < candidate_count; i++)
        {
            if (candidates[i].votes >= half)
            {
                printf("Winner is: %s\n", candidates[i].name);
                return true;
            }
        }
    }
    printf("Half not reached.\n");
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;
    printf("Min is: %i\n", min);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            for (int u = 0; u < candidate_count; u++)
            {
                if (min > candidates[u].votes)
                {
                    min = candidates[u].votes;
                    printf("Min is: %i\n", min);
                }
            }
            return min;
            /* for (int c = 0; c < candidate_count; c++)
            {
               // printf("Candidate %s votes are: %i.\n", candidates[c].name, candidates[c].votes);
               // printf("Min second loop is: %i\n", min);
                
                if(candidates[c].votes == min && candidates[c].eliminated == false)
                {
                    printf("Eliminated is: %s\n", candidates[c].name);
                    candidates[c].eliminated = true;
                    return 0;
                }
            } */
            
        }
    }
    return 5;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    printf("Min isssss: %i\n", min);
    int counter = 0;
    int ingame = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min &&  candidates[i].eliminated == false) // calculate how many people are still in game    
        {
            printf("Minimal scores: %s \n", candidates[i].name);
            counter++;
        }
        
    }
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].eliminated == false)
        {
            ingame++;
        }
    }
    printf("In game is %i and min num has %i.\n", ingame, counter);
    if (counter == ingame)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min && candidates[i].eliminated == false)
        {
            printf("Eliminated: %s\n", candidates[i].name);
            candidates[i].eliminated = true;
              
        }
    }
    return;
}
