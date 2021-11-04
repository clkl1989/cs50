import csv
import sys

def main():
    #command line argument should contain the sample dna sequence to check
    #print(len(sys.argv))
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")


    else:
        #open the dataset
        #read the CSV as a dictionary, rb = read binary
        dataset = csv.DictReader(open(sys.argv[1], 'r'))

        #create an empty list:
        dict_list = []

        #put dataset into a dictionary of SRTs
        for line in dataset:
            dict_list.append(line)

        #record the STR headers
        STR = dataset.fieldnames[1:]
        #print(STR)

        #open and read the sequence that needs to be checked for dna match
        sequence = open(sys.argv[2], 'r').read()

        sequence_list = []
        #check for max consecutive repeats of each STR
        for str in STR:
            #print(str)
            #print(sequence)
            #this function shall return the longest consecutive str in the sequence
            result = find_longest_consec_str(str, sequence)
            #append the result of each str in a list
            sequence_list.append({str : result})
        
        #print(sequence_list)
        #this function shall check if the sequence list can match any of the value in the dict_list and return the key (name) of the matched va
        find_name(dict_list, sequence_list)
        for key, value in dict_list:
            #if yes, return the key (name)
            if dict_list.get(key) == sequence_list:
                print(name)
                return
        #if no, return "No Match"    
        print("No Match")

        # ____
        # # list out keys and values separately
        # key_list = list(my_dict.keys())
        # val_list = list(my_dict.values())
         
        # # print key with val 100
        # position = val_list.index(100)
        # print(key_list[position])
         
        # # print key with val 112
        # position = val_list.index(112)
        # print(key_list[position])
        # ____



def find_longest_consec_str(DNA_STR , DNA_substring):
    result_count = 0
    #define an empty list to store the repeat counts of each set of consecutive STR
    result = []
    #to find the first set of the specific DNA STR in the DNA substring
    for i in range(len(DNA_substring)):
        #left = DNA_substring[i:i+len(DNA_STR)]
        #right = DNA_STR

        if DNA_substring[i:i+len(DNA_STR)] == DNA_STR:
            result_count += 1
            current_repeat_count = 1

            #only if the first sequence is found to match, then find how many consecutive STRs follow
            for j in range(i + len(DNA_STR), len(DNA_substring), len(DNA_STR)):
                if DNA_substring[j:j+len(DNA_STR)] == DNA_STR:
                    current_repeat_count += 1
                    
                else:
                    #append the latest repeat count to the result list
                    result.append(current_repeat_count)
                    #stop iteration
                    break
        else:
            current_repeat_count = 0

    #print(result)
    #print(result_count)
    max_count = max(result)
    #print(max_count)
    return max_count


main()

#     #find the SRT[1], SRT[2] and so on, starting with every letter in the sequence
#     for i in sequence:
#         dna_substring = s[i:]
#         for j in range(len(STR) - 1):
#             dna_match(STR[j+1] , dna_substring)