# the Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8,
# where L is the average number of letters per 100 words in the text,
# and S is the average number of sentences per 100 words in the text.

from cs50 import get_string

# get user to input text
def main():
    text = get_string("Text:")
    # compute readability of given text
    # Coleman-Liau index = 0.0588 * L - 0.296 * S - 15.8
    # where L is the average number of letters per 100 words in the text
    # S is the average number of sentences per 100 words in the text
    L = count_letter(text) * 100 / count_word(text)
    S = count_sentence(text) * 100 / count_word(text)
    CL_index = (0.0588 * L) - (0.296 * S) - 15.8

    # print(f"letter + {count_letter(text)}")
    # print(f"word + {count_word(text)}")
    # print(f"sentence + {count_sentence(text)}")
    # print(f"index + {round(CL_index)}")

    # If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number.
    # If the index number is less than 1, your program should output "Before Grade 1".
    # Otherwise, print out the grade based on Coleman-Liau index

    if CL_index >= 16:
        print("Grade 16+")

    elif CL_index < 1:
        print("Before Grade 1")

    else:
        print(f"Grade {round(CL_index)}")

# count how many letters are there is user's input
# letters can be any uppercase or lowercase alphabetic characters, but shouldn’t include any punctuation, digits, or other symbols.
def count_letter(string):
    alphabets = 0
    for i in range(len(string)):
        if(string[i].isalpha()):
            alphabets = alphabets + 1
    return alphabets


# count how many words are there in user's input
def count_word(string):
    word_count = 1 + string.count(' ')
    return word_count


# count how many sentences are there in user's input
def count_sentence(string):
    # a sentence is anything that ends with . or ! or ?
    sentence_count = 0
    for i in string:
        if i == '.' or i == '!' or i == '?':
            sentence_count += 1
    return sentence_count

main()