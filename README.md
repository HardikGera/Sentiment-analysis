This is a C program for performing sentiment analysis on text data. The program reads a lexicon
of words with associated sentiment scores from a file, and then uses this lexicon to calculate
the sentiment score of sentences in another file.
The program defines several functions:
1) read dictionary: This function reads the lexicon file, which should contain one word per
line, followed by its sentiment score and standard deviation. The function returns an array of
WordScore structures, each representing a word and its associated score.
2) is intensifier: This function checks if a given word is an intensifier (e.g., "very", "really",
"extremely"). Intensifiers are used to increase the sentiment score of the following word.
3) calculate sentence score: This function calculates the sentiment score of a given sentence.
It tokenizes the sentence into words, and for each word, it checks if it is an intensifier or
a negation word (e.g., "not"). If the word is in the lexicon, its score is added to the total score of
the sentence, possibly modified by an intensifier or negation.
4) print sentiment analysis: This function reads sentences from a file and prints their sentiment
scores.
The main function of the program takes two command-line arguments: the name of the
lexicon file and the name of the file containing sentences to analyze. It reads the lexicon into
memory, performs sentiment analysis on the sentences, and then frees the memory used by
the lexicon.
