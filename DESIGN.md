# Design Document for hw6

### Pseudocode

### Pseudocode for Score_letter()
	* loop through each word in vocabulary
		if not null,
		the set a letter in that to true
		add up the counters if it is true
		remember to reset letter to false
	*add up total values in vocabulary
	*return that counter

### psuedocode for score_word()
	*we do not use score_letter() in our code
	*same thing as score_letter() except that we check for dupe letters
	*we add up sum of letter_scores[current_letter - a]
	*return the sum

### psuedocode for filter_vocabulary
	*all of these are going to have the same layout
	*gray
		*if the vocabulary letter equals to the desired letter, free it
	*yellow
		*if it does not contain the letter at all
		*if it contains it but at a different position
		*free it
	*green
		*if the vocabulary letter does not contain it, free it
