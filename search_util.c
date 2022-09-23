#include "search_util.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// This function should loop over the vocabulary (which contains num_words
// entries) and return the number of words in which that particular letter
// occurs. So if there are 15 words containing the letter 'x' for the particular
// vocabulary, then this function will return 15.
int score_letter(char letter, char **vocabulary, size_t num_words) {

  // TODO(you): implement this function!
	bool letter_in_word = false;
	int counter = 0;
	for (int i = 0; i < (int)num_words; i++) { //looping through the dictionary
		if (vocabulary[i] != NULL) {
			for (int j = 0; j < 5; j++) { //looping through the word
				if (vocabulary[i][j] == letter) {
					letter_in_word = true;
				}
			}
			// if the letter is in the word, plus 1, go onto next word
			if (letter_in_word == true) {
				counter = counter + 1;
			}
			letter_in_word = false;
		}
	} 
//printf("number of words with that contain this letter: %d", counter); 
return counter;
	
}


// Calculate the score for a given word, where the letter_scores array has
// already been filled out for you and is guaranteed to be of length 26. Slot 0
// contains the score for 'a', and slot 25 contains the score for 'z'.
// The score for a word is the sum of all of the letter scores, *for unique
// letters*. So if the letter 'e' occurs three times, it only contributes to the
// score once.
int score_word(char *word, int *letter_scores) {

  // TODO(you): implement this function!
	int sum = 0;
	bool dupe_letter = false;
	//size_t size_of_array = sizeof(letter_scores) / sizeof(char);
	for (int i = 0; i < 5; i++) { //looping through the letter of each word

		char current_letter = word[i];

		for (int j = i + 1; j < 5; j++) {//making sure we don't add dupes
			if (word[i] == word[j]) {
				dupe_letter = true;
			}
		}

		if (dupe_letter == false) { //if it is not a dupe letter, then add to sum
			sum = sum + letter_scores[current_letter - 'a'];
		}

		dupe_letter = false;
		
	}
  return sum;

}

// Returns the optimum guess, based on our heuristic.
// This one works, you don't have to change it.
// Note that this function allocates a new string every time it runs, and those
// strings will need to be freed!
char *get_guess(char **vocabulary, size_t num_words) {
  int letter_scores[26];

  for (int i = 0; i < 26; i++) {
    letter_scores[i] = score_letter('a' + i, vocabulary, num_words);
  }

  char *best_guess = NULL;
  int best_score = 0;
  int score = 0;
  for (size_t i = 0; i < num_words; i++) {
    if (vocabulary[i] == NULL) {
      continue;
    }
    score = score_word(vocabulary[i], letter_scores);
    if (score > best_score) {
      best_guess = vocabulary[i];
      best_score = score;
    }
  }
  return best_guess ? strdup(best_guess) : NULL;
}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter *does not occur* in the secret word. So for any of the words
// in the vocabulary that do contain that letter, free their pointers and set
// the corresponding slot to NULL.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_gray(char letter, char **vocabulary, size_t num_words) {

  // TODO(you): implement this function!
	int counter = 0;
	for (int i = 0; i < (int)num_words; i++) { //looping through number of words in dict
		for (int j = 0; j < 5; j++) { //looping through each letter in word
			if (vocabulary[i] != NULL) { //if it's already null skip
				if (vocabulary[i][j] == letter) { //if letter of word in vocab == letter
					free(vocabulary[i]); //free word
					vocabulary[i] = NULL; //set word to null
					counter = counter + 1; // add to counter
				}
			}
		}
	}
//printf("counter for gray: %d", counter);  
return counter;

}

// This function will filter down the vocabulary based on the knowledge that the
// specified letter occurs in the word, *but not at this particular position*.
// So remove any words that either don't contain the letter at all, or do
// contain it, but at the specified position.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_yellow(char letter, int position, char **vocabulary, size_t num_words) {

  // TODO(you): implement this function!
/*	int counter = 0;
	for (int i = 0; i < (int)num_words; i++) {
		for (int j = 0; j < 5; j++) {
			if (vocabulary[i] != NULL) {
				if (vocabulary	
*/
	int counter = 0;
	for (int i = 0; i < (int)num_words; i++) {
		if (vocabulary[i] != NULL) {
			for (int j = 0; j < 5; j++) {
/*				for (int k = j; k < 5; k++) {
					if (vocabulary[i][k] != letter) {
						free(vocabulary[i]);
						vocabulary[i] = NULL;
						counter = counter + 1;
					}
				}
*/
				if (position == j) {
					if (vocabulary[i][j] == letter) {
						free(vocabulary[i]);
						vocabulary[i] = NULL;
						counter = counter + 1;
					}
				}
			}
		}
	}
return counter;

}


// This function will filter down the vocabulary based on the knowledge that the
// specified letter *definitely* occurs as the specified position. So remove any
// word that does not contain, for the specified position, the specified letter.
// Returns the number of words that have been filtered from the vocabulary.
size_t filter_vocabulary_green(char letter, int position, char **vocabulary, size_t num_words) {

  // TODO(you): implement this function!
	int counter = 0;
	for (int i = 0; i < (int)num_words; i++) { //loop through dictionary
		if (vocabulary[i] != NULL) { //if word is not null already
			for (int j = 0; j < 5; j++) { //loop through word
				if (position == j) { //once the position of the letter is equal to the looped letter
					if (vocabulary[i][j] != letter) {
						free(vocabulary[i]);
						vocabulary[i] = NULL;
						counter = counter + 1;
					}
				}
			}
		}
	}	
  return counter;

}

// Free each of the strings in the vocabulary, as well as the pointer vocabulary
// itself (which points to an array of char *).
void free_vocabulary(char **vocabulary, size_t num_words) {
  for (size_t i = 0; i < num_words; i++) {
    free(vocabulary[i]);
  }
  free(vocabulary);
}
