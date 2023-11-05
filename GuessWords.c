#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants
#define MAX_WORDS 6
#define MAX_WORD_LENGTH 20

void initializeGame(char words[MAX_WORDS][MAX_WORD_LENGTH], char wordToGuess[], char guessedWord[], int *wordIndex) {
    srand(time(NULL));
    int randomIndex;

    do {
        randomIndex = rand() % MAX_WORDS;
    } while (strlen(words[randomIndex]) == 0); // Check the length of the word

    strcpy(wordToGuess, words[randomIndex]);
    strcpy(words[randomIndex], ""); // Remove the guessed word from the array
    int wordLength = strlen(wordToGuess);
    int i;
    for (i = 0; i < wordLength; ++i) {
        guessedWord[i] = '_';
    }
    guessedWord[wordLength] = '\0';
    *wordIndex = randomIndex;
}

char getUserGuess() {
    char guess;
    printf("Enter your guess: ");
    scanf(" %c", &guess);
    return guess;
}

void updateGuessedWord(char wordToGuess[], char guessedWord[], char guess) {
    int wordLength = strlen(wordToGuess);
    int i;
    for (i = 0; i < wordLength; ++i) {
        if (wordToGuess[i] == guess) {
            guessedWord[i] = guess;
        }
    }
}

int isWordGuessed(char guessedWord[], char wordToGuess[]) {
    return strcmp(guessedWord, wordToGuess) == 0;
}

void playGame() {
    char words[MAX_WORDS][MAX_WORD_LENGTH] = {
        "hardware",
        "software",
        "screen",
        "cpu",
        "app",
        "mouse"
    };

    int score = 0;
    int totalAttempts = 0;
    int wordIndex;
    for (wordIndex = 0; wordIndex < MAX_WORDS; wordIndex++) {
        char wordToGuess[MAX_WORD_LENGTH];
        char guessedWord[MAX_WORD_LENGTH];
        int attempts = 0;

        initializeGame(words, wordToGuess, guessedWord, &wordIndex);

        printf("Welcome to the Guess the Word Game!\n");
        printf("Guess the word (%d letters): %s\n", (int)strlen(wordToGuess), guessedWord);

        while (!isWordGuessed(guessedWord, wordToGuess)) {
            char guess = getUserGuess();
            attempts++;
            totalAttempts++;

            updateGuessedWord(wordToGuess, guessedWord, guess);

            printf("Feedback: %s\n", guessedWord);

            if (isWordGuessed(guessedWord, wordToGuess)) {
                printf("Congratulations! You guessed the word '%s' correctly in %d attempts!\n", wordToGuess, attempts);
                break;
            } else {
                printf("Keep trying!\n");
            }
        }

        // Add attempts to score after guessing each word
        score += attempts;
	attempts = 0 ;
    }

    printf("Thanks for playing! Total score: %d\n", score);
    printf("press ENTER  to exit the game : ");
    getchar();
}

int main() {
    playGame();
    getchar();
    return 0;
}
