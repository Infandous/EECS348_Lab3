#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//definitions of different ways to score
/*
#define TD 6
#define FG 3
#define SAFETY 2
#define TD_TWO_PT 8
#define TD_ONE_PT 7
*/

#define MAX_LEN 100
#define NUM_WAYS_TO_SCORE 5

//declare a struct to store each way to score
struct Data{
  char scoreType[MAX_LEN];
  int points;
};

void combinations(struct Data *data, int* scoreMethodCount, int score); //used to print out possible combinations of scores
int checkScore(struct Data *data, int* scoreMethodCount, int score); //checks score against current combination

int main(){
  int score; //used to store user input for score
  
  //an array of type Data to store all possible ways to score in football
  struct Data waysToScore[NUM_WAYS_TO_SCORE] = {{"TD + 2pt",8},{"TD + FG",7},{"TD",6},{"3pt FG",3},{"Safety",2}};
  int scoreMethodCount[NUM_WAYS_TO_SCORE] = {0,0,0,0,0}; //declare array to hold the number of a given type of score
  //loop to ask user for input, print out possible combinations, and repeat while user does not enter 0 or 1
  do{
  printf("Enter 0 or 1 to stop.\n");
  printf("Enter the NFL score: ");
  scanf("%d", &score); //get user input (0 or 1 will cause program to exit)
  if ((score==0)||(score==1)){ //continue if score is 0 or 1
    continue;
  }
  //print possible combinations
  printf("The possible combinations for the score %d are:\n",score);
  
  combinations(&waysToScore,&scoreMethodCount,score);
  }while ((score!=0)&&(score!=1));

  return 0;
}

void combinations(struct Data *data, int* scoreMethodCount,int score){
  int checked;
  //int scoreMethodCount[NUM_WAYS_TO_SCORE] = {0,0,0,0,0}; //declare array to hold the number of a given type of score
  for (int i = NUM_WAYS_TO_SCORE-1; i>=0; i--){ //for every way to score
    scoreMethodCount[i] = (scoreMethodCount[i]+1)%score; //increment scoreMethodCount
    checked = checkScore(data,scoreMethodCount,score);//check compared to score
    if (checked==2){ //if we've incremented too much
      scoreMethodCount[i]--;//decrement
    }else if(checked==1){//if just right
      printf("Combo found!\n");
      //printCombinations(data,scoreMethodCount);//call print combos function
      continue;
    }else{
      if (i!=(NUM_WAYS_TO_SCORE-1)){
        combinations(data,scoreMethodCount,score);
      }
    }
    //scoreMethodCount = {0,0,0,0,0};    
  }
}

int checkScore(struct Data *data, int* scoreMethodCount, int score){
  int temp = 0;
  for (int i = 0; i<NUM_WAYS_TO_SCORE; i++){
    for (int x=0;x<scoreMethodCount[x];x++){
      temp += data[i].points;
    }
  }
  if (temp>score){
    return 2;
  }else if (temp==score){
    return 1;
  }else{
    return 0;
  }
}
