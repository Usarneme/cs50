from cs50 import get_string
from sys import argv, exit


def main():
    # 1. validate program command -> a single command line argument should be passed: a valid dictionary file
    if not argv or argv[1] is None or len(argv) is not 2:
        print("Usage: python bleep.py dictionary")
        exit(1)

    # 2. open and read the dictionary of bad words, placing them into a python set for later comparison
    bad_word_set = set()
    with open(argv[1]) as file:
        for line in file:
            # add the bad word to the set, stripping off the trailing newline
            bad_word_set.add(line.rstrip("\n"))

    # print("bad_word_set created: ", bad_word_set)

    # 3. get a user phrase
    while True:
        input_phrase = get_string("What message would you like to censor?\n")
        if len(input_phrase) > 0:
            break

    # 4. compare each word (case insensitive) in the user phrase to the bad_word_list, replacing bad words with *s
    # attempting to do this the pythonic way using a python ternary condition statement. returns:
    # condition_if_true if condition else condition_if_false for word in set
    output_phrase = ["*" * len(word) if word.lower() in bad_word_set else word for word in input_phrase.split(" ")]

    # 5. print the final, bleeped phrase
    print(" ".join(output_phrase))


if __name__ == "__main__":
    main()
