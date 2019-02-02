# natural language toolkit, for parsing sentences
from nltk.tokenize import sent_tokenize


# function to compare two strings a and b for lines in common.
# lines are separated by the \n newline character
def lines(a, b):
    """Return lines in both a and b"""
    lines_a = a.split("\n")
    lines_b = b.split("\n")
    matches = []
    for line in lines_a:
        if line in lines_b:
            matches.append(line)
    # return a set so there are no duplicate entries
    return set(matches)


# function to compare two strings a and b for sentences in common.
# sentences are defined by the natural language toolkit (via punctuation).
def sentences(a, b):
    """Return sentences in both a and b"""
    tokens_a = sent_tokenize(a, language='english')
    tokens_b = sent_tokenize(b, language='english')
    matches = []
    for phrase in tokens_a:
        if phrase in tokens_b:
            matches.append(phrase)
    return set(matches)


# function to compare two strings a and b for substrings of length n in common
def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    subs_a = []
    subs_b = []
    # using both character and index requires the user of enumerate per the internet
    for index, character in enumerate(a):
        # Python is smart enough to not seg fault or otherwise break when I attempt to
        # access an index point beyond the end of the string in question
        # But since we only want substrings of length n, validate that before adding it to the subs list
        if len(a[index:index+n]) == n:
            subs_a.append(a[index:index+n])
    for index, character in enumerate(b):
        if len(b[index:index+n]) == n:
            subs_b.append(b[index:index+n])
    matches = []
    for sub in subs_a:
        if sub in subs_b:
            matches.append(sub)
    # print("Matches:",matches)
    return set(matches)
