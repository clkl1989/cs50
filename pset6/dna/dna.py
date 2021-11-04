import csv
import sys

def main():
    #command line argument should contain the sample dna sequence to check
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")


    else:
        #open the dataset
        #read the CSV as a dictionary, r = read
        dataset = csv.DictReader(open(sys.argv[1], 'r'))

        #record the STR headers
        STR = dataset.fieldnames[1:]

        #open and read the sequence that needs to be checked for dna match
        sequence = open(sys.argv[2], 'r').read()

        result_list = []
        
        #check for max consecutive repeats of each STR
        for x in STR:
            #this function shall return the longest consecutive str in the sequence
            result = find_longest_consec_str(x, sequence)
            #append the result of each x in a list
            result_list.append(str(result))
            
        
        
        #check if the result list can match any of the value in the nested_list and return the key (name) of the matched value
        match_found = 0
        
        for row in dataset:
            match_count = 0
            for i in STR:
                if result_list[match_count] == row[str(i)]:
                    match_count += 1
                else:
                    break
                
            if match_count == len(STR):
                print(row["name"])
                match_found = 1
                return
        
        #if no match if found after iterating through the entire dataset, print "No Match"     
      
        if match_found == 0:
            print("No Match")
            

def find_longest_consec_str(DNA_STR , DNA_substring):
    result_count = 0
    #define an empty list to store the repeat counts of each set of consecutive STR
    result = []
    #to find the first set of the specific DNA STR in the DNA substring
    for i in range(len(DNA_substring)):
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

    if len(result) > 0:
        max_count = max(result)
        return max_count

main()