#ifndef SENTIMENT_ANALYSIS_H
#define SENTIMENT_ANALYSIS_H

typedef struct {
    char *word;
    float score;
    float sd;
    int intensity[10];
} WordScore;

// Function prototypes
WordScore *read_dictionary(const char *filename, int *size);
float calculate_sentence_score(WordScore *lexicon, int lexicon_size, const char *sentence);
void print_sentiment_analysis(const char *filename, WordScore *lexicon, int lexicon_size);

#endif // SENTIMENT_ANALYSIS_H