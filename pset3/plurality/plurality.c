#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name)) // if (vote(name) == false)
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote


//vote takes a single argument, a string called name, representing the name of the candidate who was voted for.
//If name matches one of the names of the candidates in the election, then update that candidate’s vote total to account for the new vote. The vote function in this case should return true to indicate a successful ballot.
//If name does not match the name of any of the candidates in the election, no vote totals should change, and the vote function should return false to indicate an invalid ballot.
//You may assume that no two candidates will have the same name.
bool vote(string name) // vote should + 1 if name in vote matches candidate name
{
    for (int j = 0; j < candidate_count; j++)
    {
        int comp = strcmp(name, candidates[j].name);
        if (comp == 0)
        
        {
            candidates[j].votes++;
            
            return true;
            
        }
        
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void) //print candidate name with highest vote count if only 1 candidate has max votes, otherwise print all candidate names with highest vote on new lines (\n)
{
    //find the candidate with maximum votes
    int maximum = candidates[0].votes;
    int locations[candidate_count]; //array that captures winning candidate whether it is candidate #0, #1, #2 and so on...
    int index = 0;
    
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes > maximum) //only identify 1 winner with highest vote
        {
           locations[candidate_count] = -1;
           maximum = candidates[c].votes;
           locations[0] = c;
        }
        
        else if (candidates[c].votes == maximum) //identify other winners with a tie
        {
            locations[index++] = c;
        }

    }
    
    if (index == 0) //only 1 winner
    {
        printf("%s\n", candidates[locations[0]].name);
    }
    else
    {
        for (int w = 0; w < index; w++)
        {
            printf("%s\n", candidates[locations[w]].name);
        }
    }
    return;
}

