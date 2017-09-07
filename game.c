#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define MAG 9


//Learning System Functions
void experimentGen();
//deprecated
void performanceSys();
void performanceSystem2();
void critic();
void generalizer();

//Game Play Functions


//all deprecated
void move(int);
void move_2();
int isWinner();
int isDraw();
float v_hat(int,int);
float v_hat_2(int []);

int logicTurn();
void makeMove(int);


void printBoard();
void player1move();
void player2move();
int gameIsDraw();
int player1wins();
int player2wins();
int boardIndicatesGameOver();

//Global Variables
int epsilon;
int Board[MAG];
float Weights[(MAG*2)+1];
int Trace[MAG];
int BoardHistory[MAG][MAG];
int V_train[MAG];
float nu;
int whom;

int main(){
  int logic,learning,dven;
  logic = 0;
  learning = 0;
  dven = 0;
  epsilon = 0;
  do {
    experimentGen();
    performanceSys();
    switch(whom){
    case 1:
      logic++;
      break;
    case -1:
      learning++;
      break;
    case 0:
      dven++;
      break;
    default:
      printf("Error in main.\n");
    }
    //    printBoard();
    critic();
    generalizer();
    epsilon++;
  } while (epsilon < 1);
  printf("ML %d,Logic %d, Draw %d\n",learning,logic,dven);
  return 0;
}
void printBoard(){
  int i;
    for (i = 0; i < MAG; ++i){
      if (!(i % 3)){
	putchar('\n');
      }
      switch(Board[i]){
      case 1:
	putchar('X');
	break;
      case -1:
	putchar('O');
	break;
      default:
	putchar('-');
      }
    }
    putchar('\n');
}
void experimentGen(){
  int i,j;
  for ( i = 0; i < MAG; ++i){
    Board[i]=0; //Zero Represents a blank Board
    Trace[i]=-1; //-1 Means nothing has happended yet,
    //Trace is populated by a number zero thru eight representing valid move
  }
  for ( i =0; i < MAG; ++i){
    for ( j = 0; j < MAG; ++j){
      BoardHistory[i][j] = 0;
    }
  }
  FILE *fp;
  fp = fopen("weights.txt","r");
  for ( i = 0; i < (MAG *2) + 1; ++i){
    fscanf(fp,"%f",&Weights[i]);
  }
  fclose(fp);
}

void performaceSystem2(){

  int i;
  for (i = 0; i < MAG; ++i){
    player1move();
    if (boardIndicatesGameOver()){
      goto endGame;
    }
    player2move();
    if (boardIndicatesGameOver()){
      goto endGame;
    }
  }
 endGame: return;
}

int gameIsDraw(){
  int i;
  for ( i = 0; i < MAG; ++i){
    if (!Board[i]){
      return 0;
    }
  }
  return 1;
}

int player1wins(){
  return 1;
}

int player2wins(){
  return 1;
}

int boardIndicatesGameOver(){
  if (gameIsDraw() || player1wins() || player2wins() ){
    return 1;
  } else {
    return 0;
  }
}

void player1move(){
}

void player2move(){
}

void performanceSys(){
  whom = 0;
  srand(time(NULL));
  int flip,m;
  flip = (rand()%2);
  flip = 0; //temporary advantage for learner
  do {
    if (flip){
      makeMove(logicTurn());
      if (isWinner()){
	whom = 1;
	goto theEnd;
      } else if (isDraw()){
	goto theEnd;
      }
      move(1);
      if (isWinner()){
	whom = -1;
	goto theEnd;
      } else if (isDraw()){
	goto theEnd;
      }
    } else {
      move(1);
      if (isWinner()){
	whom = -1;
	goto theEnd;
      } else if (isDraw()){
	goto theEnd;
      }
      makeMove(logicTurn());
      if (isWinner()){
	whom = 1;
	goto theEnd;
      } else if (isDraw()){
	goto theEnd;
      }
    }
  } while (1);
 theEnd: return;
}

void makeMove(int m){
  //check if valid
  if (Board[m]){
    printf("Error.\n");
  }
  //set board
  Board[m] = -1;
  //set trace
  int i;
  for ( i = 0 ; i < MAG; ++i){
    if (Trace[i] == -1){
      Trace[i] = m;
      break;
    }
  }
}


int logicTurn(){
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

void move(int p){
  int i,u;
  float max_v,aux;
  int max_i;
  int anyol;
  srand(time(NULL));
  do {
  anyol = (rand()%(MAG));
  } while (Board[anyol]);
  max_v = v_hat(anyol,p);
  max_i = anyol;
  for (i = 0; i < MAG; ++i){
    if (!Board[i]){
      aux = v_hat(i,p);
      if (max_v < aux){
	max_v = aux;
	max_i = i;
      }
    }
  }
  Board[max_i]=p;
  for (u = 0; u < MAG; ++u){
    if( Trace[u] == -1 ){
      Trace[u] = max_i;
      break;
    }
  }
}

float v_hat(int m,int p){
  int B[MAG];
  int i;
  for (i = 0; i < MAG; ++i){
    B[i]=Board[i];
  }
  B[m]=p;
  return v_hat_2(B);
}

int isWinner(){
  if (Board[0]){
    if ((Board[0] == Board[1]) && ( Board[1] == Board[2])){
      return 1;
    } else if ((Board[0] == Board[3]) && ( Board[3] == Board[6])){
      return 1;
    } else if ((Board[0] == Board[4]) && ( Board[4] == Board[8])){
      return 1;
    }
  } else if (Board[1]){
    if ((Board[1] == Board[4]) && ( Board[4] == Board[7])){
      return 1;
    }
  } else if (Board[2]){
    if (( Board[2] == Board[4]) && (Board[4] == Board[6])){
      return 1;
    } else if ((Board[2] == Board[5] ) && (Board[5] == Board[8])){
      return 1;
    }
  } else if (Board[3]){
    if ((Board[3] == Board[4]) && (Board[4] == Board[5])){
      return 1;
    }
  } else if (Board[6]){
    if ((Board[6] == Board[7]) && (Board[7] == Board[8])){
      return 1;
    }
  }
  return 0;
}

int isWinner_2(int B[]){
  if (B[0]){
    if ((B[0] == B[1]) && ( B[1] == B[2])){
      return 1;
    } else if ((B[0] == B[3]) && ( B[3] == B[6])){
      return 1;
    } else if ((B[0] == B[4]) && ( B[4] == B[8])){
      return 1;
    }
  } else if (B[1]){
    if ((B[1] == B[4]) && ( B[4] == B[7])){
      return 1;
    }
  } else if (B[2]){
    if (( B[2] == B[4]) && (B[4] == B[6])){
      return 1;
    } else if ((B[2] == B[5] ) && (B[5] == B[8])){
      return 1;
    }
  } else if (B[3]){
    if ((B[3] == B[4]) && (B[4] == B[5])){
      return 1;
    }
  } else if (B[6]){
    if ((B[6] == B[7]) && (B[7] == B[8])){
      return 1;
    }
  }
  return 0;
}

int isWinner_2_1(int B[]){
  if (B[0]){
    if ((B[0] == B[1]) && ( B[1] == B[2])){
      if (B[0] == 1){
	return 1;
      } else {
	return 0;
      }
    } else if ((B[0] == B[3]) && ( B[3] == B[6])){
      if (B[0] == 1){
	return 1;
      } else {
	return 0;
      }
    } else if ((B[0] == B[4]) && ( B[4] == B[8])){
      if (B[0] == 1){
	return 1;
      } else {
	return 0;
      }
    }
  }
  if (B[1]){
    if ((B[1] == B[4]) && ( B[4] == B[7])){
      if (B[1] == 1){
	return 1;
      } else {
	return 0;
      }
    }
  }
  if (B[2]){
    if (( B[2] == B[4]) && (B[4] == B[6])){
      if (B[2] == 1){
	return 1;
      } else {
	return 0;
      }
    } else if ((B[2] == B[5] ) && (B[5] == B[8])){
      if (B[2] == 1){
	return 1;
      } else {
	return 0;
      }
    }
  }
  if (B[3]){
    if ((B[3] == B[4]) && (B[4] == B[5])){
      if (B[3] == 1){
	return 1;
      } else {
	return 0;
      }
    }
  }
  if (B[6]){
    if ((B[6] == B[7]) && (B[7] == B[8])){
      if (B[6] == 1){
	return 1;
      } else {
	return 0;
      }
    }
  }
  return -1;
}

int isDraw(){
  int i;
  for (i = 0; i < MAG; ++i){
    if (!Board[i]){
      return 0;
    }
  }
  return 1;
}

int isDraw_2(int B[]){
  int i;
  for (i = 0; i < MAG; ++i){
    if (!B[i]){
      return 0;
    }
  }
  return 1;
}

void critic(){
  int i,j;
  for ( i = 0; i < MAG; ++i){
    for (j = 0; j <= i; ++j){
      if (!(j%2)){
	  BoardHistory[i][Trace[j]]=1;
	} else {
	  BoardHistory[i][Trace[j]]=-1;
	}
    }
  }
  for ( i = 0; i < MAG; ++i){
    V_train[i]=0;
  }
  for ( i = 0; i < (MAG-1); ++i){
    V_train[i]=v_hat_2(BoardHistory[i+1]);
  }
}


float v_hat_2(int b[]){
  int r;
  r = isWinner_2_1(b);
  if ( r == 0){
    return 100.0;
  } else if (r == 1){
    return -100.0;
  } else if (isDraw_2(b)){
    return 0.0;
  }
  int i;
  int X[(MAG * 2) + 1];
  X[0]=1;
  for ( i = 1; i < (2 * MAG) + 1; ++i){
    X[i] = 0;
  }
  float result;
  result = 0.0;
  for (i = 0 ; i < (MAG * 2) + 1; ++i){
    result += Weights[i] * X[i];
  }
  return result;
}
void generalizer(){
  int i,j,k;
  float temp;
  int X[MAG][(MAG*2)+1];

  for (i = 0; i < MAG; ++i){
    for ( j = 0; j < (2 * MAG) + 1; ++j){
      X[i][j]=0;
    }
  }
  for (i = 0; i < MAG; ++i){
    X[i][0]=1;
    for (j = 0; j < MAG; ++j){
      if (BoardHistory[i][j] == 0){
	X[i][j+1] = 0;
	X[i][(j*2)+1]=0;
      } else if ( j % 2){
	X[i][j+1] = 1;
      } else {
	X[i][(2 * j) + 1] = 1;
      }
    }
  }
  nu = 0.01;
  for ( j = 0; j < MAG; ++j){
    //what if the game doesn't go on for 9 moves?
    for ( k = 0; k < ( 2 * MAG ) + 1; ++k){
      temp = (V_train[j] - v_hat_2(BoardHistory[j])) * X[j][k];
      Weights[k] = Weights[k] + (nu * temp);
    }
  }

  FILE *fp;
  fp = fopen("weights.txt","w+");
  for (i = 0; i < (2 * MAG) + 1; ++i){
    fprintf(fp,"%f ",Weights[i]);
  }
  fclose(fp);
}
