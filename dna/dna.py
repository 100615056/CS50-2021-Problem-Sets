# Import libraries
import sys
import csv
import re


def main():
    # Validate command-line arguments
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read Database into Memory
    with open(sys.argv[1]) as file:
        # Create file object and store STR types in memory
        reader = csv.reader(file)
        # Skip first column by slicing string
        STR = next(reader)[1:]
        data = [row for row in reader]

    # Read DNA Sequence into memory
    with open(sys.argv[2]) as dna_file:
        sequence = dna_file.read()

    # For each STR compute the longest run of consecutive STRs from DNA sequence and store in a list
    longest_STR = []
    for i in STR:
        longest_STR.append(repeat_count(i, sequence))

    # Iterate through the database and compare each STR count with each row in CSV file
    # Use enumerate function to keep track of index
    for i, person in enumerate(data):
        # Reset counter for each row
        count = 0
        # Iterate over each entry skipping the first entry (the name)
        for j, entry in enumerate(person[1:]):
            # Check if value matches with STR count
            if int(entry) == longest_STR[j]:
                count += 1
                # Check to make sure matches all instances of the STR counts
                if count == len(STR):
                    print(person[0])
                    exit()

    print("no match")


# Calculate the maximum number of STR occurrences given a DNA sequence
def repeat_count(STR, sequence):
    length = int(len(STR))
    # Credit from GeeksforGeeks https://www.geeksforgeeks.org/python-maximum-consecutive-substring-occurrence/
    # Using the findall and escape functions from re library to find consecutive STRs
    # Then use the max function to find the maximum occurrence
    # key = len, find longest item based on length
    sub = max(re.findall('((?:' + re.escape(STR) + ')*)', sequence), key=len)
    # Determine the maximum number of consecutive STR repeats
    # Divide length of repeated consecutive STR substring by individual length of STR
    count = len(sub)
    longest = count / length
    return int(longest)


main()
