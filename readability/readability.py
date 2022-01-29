from cs50 import get_string


def main():
    # Get user text input
    text = get_string("Text: ")
    # Calculate Coleman-Liau index
    count = count_letters(text)
    words = count_words(text)
    sentence = count_sentences(text)
    index = round(calculate_index(count, words, sentence))
    
    # Print Grade Level
    print_grade_level(index)
    
    
def count_letters(text):
    count = 0
    # Count each letter in the text
    for c in text:
        if c.isalpha():
            count += 1
    return count
    
    
def count_words(text):
    word = 0
    # Count the number of words
    for i in text:
        if i.isspace():
            word += 1
    word += 1
    return word
    

def count_sentences(text):
    sentence = 0
    # Count the number of sentences
    for c in text:
        # Check for . or ! or ?
        if c == '.' or c == '!' or c == '?':
            sentence += 1
    
    return sentence
    

def calculate_index(c, w, s):
    # Calculate the L and S values for the Coleman-Liau index
    L = c / w * 100.00
    S = s / w * 100.00

    # Compute the index
    index = 0.0588 * L - 0.296 * S - 15.8
    return index
    

def print_grade_level(index):
    if index < 1:
        print("Before Grade 1")
    if index >= 16:
        print("Grade 16+")
    if index > 1 and index < 16:
        print(f"Grade {index}")
        
        
main()