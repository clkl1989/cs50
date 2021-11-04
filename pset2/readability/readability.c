#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letter(string text);
int count_word(string text);
int count_sentence(string text);
float readability_index(int num_of_letter, int num_of_word, int num_of_sentence);

int main(void)
{
    string text = get_string("Text:\n"); //get user to input text

    int num_of_letter = count_letter(text); //count how many letters are there is user's input

    //printf("%i letter(s)\n", num_of_letter); //print out how many letters are there in user's input

    int num_of_word = count_word(text); //count how many words are there in user's input

    //printf("%i word(s)\n", num_of_word); //print out how many words are there in user's input
    
    int num_of_sentence = count_sentence(text); //count how many sentences are there in user's input

    //printf("%i sentence(s)\n", num_of_sentence); //print out how many sentences are there in user's input
    
    int readability_grade = readability_index(num_of_letter, num_of_word, num_of_sentence); //compute readability of given text
    
    //If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number. 
    //If the index number is less than 1, your program should output "Before Grade 1".
    
    if (readability_grade < 1)
    {
        printf("Before Grade 1\n");
    }
    
    else if (readability_grade >= 16)
    {
        printf("Grade 16+\n");
    }
    
    else
    {
        printf("Grade %i\n", readability_grade); //print out the Grade based on Coleman-Liau index
    }
}

int count_letter(string text) //how to count letters in a line of text
{
    int letter_count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letter_count++;
        }
    }

    return letter_count;
}

int count_word(string text) //how to count words in a line of text
{
    int word_count = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            word_count++;
        }
    }

    return word_count;
}

int count_sentence(string text) //how to count sentences in a line of text
{
    int sentence_count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence_count++;
        }
    }

    return sentence_count;
}

float readability_index(int num_of_letter, int num_of_word, int num_of_sentence)
{
    //how to compute readability index (index = 0.0588 * L - 0.296 * S - 15.8), 
    //L is the average number of letters per 100 words in the text, and 
    //S is the average number of sentences per 100 words in the text.
    
    float readability_index = (0.0588 * num_of_letter * 100 / num_of_word) - (0.296 * num_of_sentence * 100 / num_of_word) - 15.8;
    
    int readability_grade;
    
    return readability_grade = round(readability_index);
    
}


