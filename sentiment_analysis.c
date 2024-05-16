#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sentiment_analysis.h"

// Function implementations
WordScore *read_dictionary(const char *filename, int *size)
{
    // Implementation...
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open the file");
        return NULL;
    }

    WordScore *lexicon = NULL;
    char line[256];
    *size = 0;

    while (fgets(line, sizeof(line), file))
    {
        lexicon = realloc(lexicon, (*size + 1) * sizeof(WordScore));
        lexicon[*size].word = malloc(256 * sizeof(char));

        sscanf(line, "%s %f %f", lexicon[*size].word, &lexicon[*size].score, &lexicon[*size].sd);
        (*size)++;
    }

    fclose(file);
    return lexicon;
}
int is_intensifier(const char *word)
{
    const char *intensifiers[] = {"very", "really", "extremely"};
    int num_intensifiers = sizeof(intensifiers) / sizeof(intensifiers[0]);

    for (int i = 0; i < num_intensifiers; i++)
    {
        if (strcmp(word, intensifiers[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

float calculate_sentence_score(WordScore *lexicon, int lexicon_size, const char *sentence)
{
    char *sentence_copy = strdup(sentence);
    for (int i = 0; sentence_copy[i]; i++)
    {
        sentence_copy[i] = tolower(sentence_copy[i]);
    }
    char *word = strtok(sentence_copy, " .,;:!?\"\'\n");
    float total_score = 0;
    int word_count = 0;
    int intensifier = 0;

    while (word != NULL)
    {
        if (is_intensifier(word))
        {
            intensifier = 1;
        }
        else
        {
            for (int i = 0; i < lexicon_size; i++)
            {
                if (strcmp(word, lexicon[i].word) == 0)
                {
                    total_score += (intensifier ? 2 : 1) * lexicon[i].score;
                    break;
                }
            }
            intensifier = 0;
        }
        word = strtok(NULL, " .,;:!?\"\'\n");
        word_count++;
    }
    int negation = 0; // Flag to track negation

    while (word != NULL)
    {
        if (strcmp(word, "not") == 0 || strcmp(word, "n't") == 0)
        {
            negation = !negation; // Toggle negation flag
        }
        else
        {
            for (int i = 0; i < lexicon_size; i++)
            {
                if (strcmp(word, lexicon[i].word) == 0)
                {
                    total_score += (intensifier ? 2 : 1) * (negation ? -lexicon[i].score : lexicon[i].score);
                    break;
                }
            }
            negation = 0; // Reset negation after processing a word
        }
        word = strtok(NULL, " .,;:!?\"\'\n");
        word_count++;
    }

    free(sentence_copy);
    return total_score / word_count;
}

void print_sentiment_analysis(const char *filename, WordScore *lexicon, int lexicon_size)
{
    // Implementation...
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open the file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        float score = calculate_sentence_score(lexicon, lexicon_size, line);
        printf("%s: %.2f\n", line, score);
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <lexicon_file> <validation_file>\n", argv[0]);
        return 1;
    }

    int lexicon_size;
    WordScore *lexicon = read_dictionary(argv[1], &lexicon_size);
    if (lexicon == NULL)
    {
        fprintf(stderr, "Failed to read the lexicon\n");
        return 1;
    }

    print_sentiment_analysis(argv[2], lexicon, lexicon_size);

    for (int i = 0; i < lexicon_size; i++)
    {
        free(lexicon[i].word);
    }
    free(lexicon);

    return 0;
}