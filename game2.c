#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define S 9

int Board[S];

int playGame();
int computerTurn();
int getStatus();
void printBoard();
int winner();
int draw();

int main(){

  int result = playGame();
  if (result == 1){
    printf("You Win!\n");
  } else if (result == 0){
    printf("Draw Game.\n");
  } else {
    printf("Computer Wins.\n");
  }
  return 0;
}

int playGame(){
    

  int coin,flip,i,m,status;
  //Clear Board for new Game
  for ( i = 0; i < S; ++i){
    Board[i] = 0;
  }
  printf("Choose Head(1) or Tails(0) to decide who goes first: ");
  scanf("%d",&coin);
  srand(time(NULL));
  flip = (rand()%2);
  printf("And the flip is: %c.\n",flip?'H':'T');
  do {
    //think about check for draw in between turns
    //also error checking for move
    if ( coin == flip) {
      printBoard();
      scanf("%d",&m);
      Board[m]=1;
      if (winner()){
	goto endGame;
      } else if (draw()){
	goto endGame;
      }
      m = computerTurn();
      Board[m]=-1;
      if (winner()){
	goto endGame;
      } else if (draw()){
	goto endGame;
      }
    } else {
      m = computerTurn();
      Board[m]=-1;
      if (winner()){
	goto endGame;
      } else if (draw()){
	goto endGame;
      }
      printBoard();
      scanf("%d",&m);
      Board[m]=1;
      if (winner()){
	goto endGame;
      } else if (draw()){
	goto endGame;
      }
    }
    status = getStatus();    
  } while (status == 10);
  return status;
 endGame: status = getStatus();
  return status;
}

int winner(){
  return (getStatus() == 1);
};

int draw(){
  return (getStatus() == 0);
}

int getStatus(){
  int i,j;
  if (Board[0]){
    if ((Board[0] == Board[1]) && (Board[1] == Board[2])){
      return 1;
    } else if ((Board[0] == Board[3]) && (Board[3] == Board[6])){
      return 1;
    } else if ((Board[0] == Board[4]) && (Board[4] == Board[8])){
      return 1;
    }
  }else if(Board[4]){
    if ((Board[3] == Board[4]) && (Board[4] == Board[5])){
      return 1;
    } else if ((Board[1] == Board[4]) && (Board[4] == Board[7])){
      return 1;
    } else if ((Board[2] == Board[4]) && (Board[4] == Board[6])){
      return 1;
    }
  } else if(Board[8]){
    if ((Board[6] == Board[7]) && (Board[7] == Board[8])){
      return 1;
    } else if ((Board[2] == Board[5]) && (Board[5] == Board[8])){
      return 1;
    }
  }
  for (i = 0 ; i < S; ++i){
    if (Board[i]){
      return 10;
    }
  }
  return 0;
}

int computerTurn(){
  int move;
  srand(time(NULL));
  move = -1;
  if ((( Board[0] == -1) && ( Board[6] == -1))&& !Board[3]){
    move = 3;
  } else if (((Board[0] == -1) && ( Board[2] == -1 ))&& !Board[1]){
    move = 1;
  } else if (((Board[0] == -1) && ( Board[8] == -1))&& !Board[4]){
    move = 4;
  } else if (((Board[0] == -1) && ( Board[1] == -1))&& !Board[2]){
    move = 2;
  } else if (((Board[0] == -1) && ( Board[3] == -1))&& !Board[6]){
    move = 6;
  } else if (((Board[0] == -1) && ( Board[4] == -1))&& !Board[8]){
    move = 8;
  } else if (((Board[1] == -1) && ( Board[2] == -1))&& !Board[0]){
    move = 0;
  } else if (((Board[1] == -1) && ( Board[4] == -1))&& !Board[7]){
    move = 7;
  } else if (((Board[1] == -1) && ( Board[7] == -1))&& !Board[4]){
    move = 4;
  } else if (((Board[2] == -1) && ( Board[5] == -1))&& !Board[8]){
    move = 8;
  } else if (((Board[2] == -1) && ( Board[8] == -1))&& !Board[5]){
    move = 5;
  } else if (((Board[3] == -1) && ( Board[6] == -1))&& !Board[0]){
    move = 0;
  } else if (((Board[3] == -1) && ( Board[4] == -1))&& !Board[5]){
    move = 5;
  } else if (((Board[3] == -1) && ( Board[5] == -1))&& !Board[4]){
    move = 4;
  } else if (((Board[4] == -1) && ( Board[8] == -1))&& !Board[0]){
    move = 0;
  } else if (((Board[4] == -1) && ( Board[7] == -1))&& !Board[1]){
    move = 1;
  } else if (((Board[4] == -1) && ( Board[6] == -1))&& !Board[2]){
    move = 2;
  } else if (((Board[4] == -1) && ( Board[5] == -1))&& !Board[3]){
    move = 3;
  } else if (((Board[5] == -1) && ( Board[8] == -1))&& !Board[2]){
    move = 2;
  } else if (((Board[6] == -1) && ( Board[7] == -1))&& !Board[8]){
    move = 8;
  } else if (((Board[6] == -1) && ( Board[8] == -1))&& !Board[7]){
    move = 7;
  } else if (((Board[7] == -1) && ( Board[8] == -1))&& !Board[6]){
    move = 6;
  } else if ((( Board[0] == 1) && ( Board[6] == 1)) && !Board[3]){
    move = 3;
  } else if (((Board[0] == 1) && ( Board[2] == 1 ))&& !Board[1]){
    move = 1;
  } else if (((Board[0] == 1) && ( Board[8] == 1))&& !Board[4]){
    move = 4;
  } else if (((Board[0] == 1) && ( Board[1] == 1))&& !Board[2]){
    move = 2;
  } else if (((Board[0] == 1) && ( Board[3] == 1))&& !Board[6]){
    move = 6;
  } else if (((Board[0] == 1) && ( Board[4] == 1))&& !Board[8]){
    move = 8;
  } else if (((Board[1] == 1) && ( Board[2] == 1))&& !Board[0]){
    move = 0;
  } else if (((Board[1] == 1) && ( Board[4] == 1))&& !Board[7]){
    move = 7;
  } else if (((Board[1] == 1) && ( Board[7] == 1))&& !Board[4]){
    move = 4;
  } else if (((Board[2] == 1) && ( Board[5] == 1))&& !Board[8]){
    move = 8;
  } else if (((Board[2] == 1) && ( Board[8] == 1))&& !Board[5]){
    move = 5;
  } else if (((Board[3] == 1) && ( Board[6] == 1))&& !Board[0]){
    move = 0;
  } else if (((Board[3] == 1) && ( Board[4] == 1))&& !Board[5]){
    move = 5;
  } else if (((Board[3] == 1) && ( Board[5] == 1))&& !Board[4]){
    move = 4;
  } else if (((Board[4] == 1) && ( Board[8] == 1))&& !Board[0]){
    move = 0;
  } else if (((Board[4] == 1) && ( Board[7] == 1))&& !Board[1]){
    move = 1;
  } else if (((Board[4] == 1) && ( Board[6] == 1))&& !Board[2]){
    move = 2;
  } else if (((Board[4] == 1) && ( Board[5] == 1))&& !Board[3]){
    move = 3;
  } else if (((Board[5] == 1) && ( Board[8] == 1))&& !Board[2]){
    move = 2;
  } else if (((Board[6] == 1) && ( Board[7] == 1))&& !Board[8]){
    move = 8;
  } else if (((Board[6] == 1) && ( Board[8] == 1))&& !Board[7]){
    move = 7;
  } else if (((Board[7] == 1) && ( Board[8] == 1))&& !Board[6]){
    move = 6;
  } else if (!Board[0]){
    move = 0;
  } else if (!Board[2]){
    move = 2;
  } else if (!Board[4]){
    move = 4;
  } else if (!Board[6]){
    move = 6;
  } else if (!Board[8]){
    move = 8;
  } else {
    do {
      move = (rand()%9);
    } while (Board[move]);
  }
  return move;
}

void printBoard(){
  int i;
  for (i = 0; i < S; ++i){
    if (!(i%3)) putchar('\n');
    if (Board[i] == 0){
      putchar('-');
    } else if (Board[i] == 1){
      putchar('X');
    } else {
      putchar('O');
    }
  }
  putchar('\n');
}
