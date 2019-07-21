#include <stdio.h>
#include <unistd.h>
#include <cs50.h>

bool isValid(long cardNumber);

int main(void){
  long cardNumber; // this will be the credit card number
  cardNumber = get_long("CARD NUMBER: "); // waits for user input

  if(isValid(cardNumber)){
    printf("VALID\n");
  } else {  printf("INVALID\n");  }
}

// this function is for determing if the credit card is VALID or INVALID
bool isValid(long cardNumber){

  if(cardNumber <= 0)
    return false;

  int *countedDigits = malloc(8*sizeof(int)); // this array will store every other number
  int *uncountedDigits = malloc(8*sizeof(int)); // this array will store every other number not counted by the countedDigits array
  int sumCountedDigits=0, sumUncountedDigits=0; // sum of counted and uncounted numbers

  for(int i=0; i <= cardNumber+10; i++){ // basically breaks the credit card number into digits, and stores them into their respective arrays, starting from the right to the left
    uncountedDigits[i] = cardNumber % 10;
    cardNumber = cardNumber / 10;

    countedDigits[i] = cardNumber % 10;
    cardNumber = cardNumber / 10;
  }

  for(int i=0; i<sizeof(countedDigits); i++){
    countedDigits[i] *= 2; // as per Luhn's Algorithm, multiplies every other digits (the counted digits) by 2
    while(countedDigits[i] >= 10){ // as per Luhn's Algorithm, we need to check if the number is higher than 10, because we are trying to get the digits and not the number itself, for example 15 should be 1 and 5

      sumCountedDigits += countedDigits[i] % 10;
      countedDigits[i] /= 10;

    }
      sumCountedDigits += countedDigits[i];
  }

  // finding the sum of uncounted digits
  for(int i=0; i<=sizeof(uncountedDigits); i++){
    sumUncountedDigits += uncountedDigits[i];
  }

  if((sumCountedDigits + sumUncountedDigits) % 10 == 0) // as per Luhn's Algorithm, if the final result % 10 == 0, then the credit card number is valid
    return true;

  return false;
}
