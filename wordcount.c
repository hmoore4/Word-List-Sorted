/* Hunter Moore
 * 10/11/19
 * CPSC275 F
 * This program takes a text file as input and prints the unique words followed by their occurence. 
 * It also sorts the occurences so the most frequent word is at the top and the least frequent at the bottom.
 */
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 30
#define MAX_WORD_AMOUNT 1000

int getInput(char array1[MAX_WORD_AMOUNT][MAX_WORD_LENGTH], int array2[]);
void sort(char array1[][MAX_WORD_LENGTH], int array2[], int size);
void setToNull(char array[], int n);

void main(void){
	int i;
	int j;
	char wordArray[MAX_WORD_AMOUNT][MAX_WORD_LENGTH];

	int occurenceArray[MAX_WORD_AMOUNT];
	int size = getInput(wordArray, occurenceArray);
	sort(wordArray, occurenceArray, size);
	

	
		for(i = 0; i < size; i++){								//Go through each word in word array
			for(j = 0; j < MAX_WORD_LENGTH; j++){			
				printf("%c", wordArray[i][j]);			//Print them out

			}	

			printf(": \t%d \t", occurenceArray[i]);
			printf("\n");
		}
}



int getInput(char array1[MAX_WORD_AMOUNT][MAX_WORD_LENGTH], int array2[]){

	int c;
	int i;
	int j;
	int k;
	int wordCounter = 0;
	int letterCounter = 0;
	int occurenceCounter = 0;
	c = getchar();
	array2[0] += 1;									
	array2[1] += 1;
	
	while(c != EOF){
		if(c != ' '  || c != '\n'){	
			c = tolower(c);																	//convert all chars to lower case
			if(isalpha(c)){																	//only add to array if a letter
				array1[wordCounter][letterCounter] = c;
			}
			c = getchar();
			letterCounter++;
		}
		
		if(c == ' ' || c == '\n'){
			array1[wordCounter][letterCounter] = '\0';		//end word with terminating character
			wordCounter++;
			c = getchar();
			letterCounter = 0;
			for(i = 0; i < wordCounter - 1; i++){														
					if(strcmp(array1[i], array1[wordCounter-1])==0){							//if word is in array1 already						
						setToNull(array1[wordCounter-1], strlen(array1[wordCounter-1]));		//set the entry to null
						array2[i] += 1;																											//increment occurence array
						wordCounter--;
						letterCounter = 0;
					}
					else{
						array2[wordCounter] = 1;
					}
			}															
		}
	}
	if(c == EOF && isalpha(c)){																						//handles last word
		array1[wordCounter][letterCounter] = c;
		array1[wordCounter][letterCounter + 1] = '\0';
	}

	
return wordCounter;																									//returns this to keep track of array size
}


void setToNull(char array[], int n){						//Sets entry of array to null
	int i;																				//I do this when a non-unique word is found and I want to reset the array entry
	for(i = 0; i < n; i++){
		array[i] = '\0';
	}
}


void sort(char array1[][MAX_WORD_LENGTH], int array2[], int size){
  int j = 0;
	int key;			
	char tempChar[MAX_WORD_LENGTH];
	int i = 0;
	for(j = 1; j < size; j++){	
		 key = array2[j];																	
		 setToNull(tempChar, strlen(tempChar));					//Reset temp array
		 strcpy(tempChar, array1[j]);										//Put word array info in temp array
		 i = j - 1;
		 while(i >= 0 && array2[i] < key){		//If the lower index(toward 0) is lower than the one higher then switch then. If I change < to > if i want smaller values at the top
			 	array2[i+1] = array2[i];
			 	setToNull(array1[i+1], strlen(array1[i+1]));
			 	strcpy(array1[i+1], array1[i]);
			 	i = i - 1;

		 }
		 
		 array2[i+1] = key;																	//Set temp var to next entry
		 setToNull(array1[i+1], strlen(array1[i+1]));
		 strcpy(array1[i+1], tempChar);		

	}
}
