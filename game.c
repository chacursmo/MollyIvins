#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define MAG 9


//Learning System Functions
void experimentGen();
void performanceSys();
void critic();
void generalizer();

//Game Play Functions
void move(int);
void move_2();
int isWinner();
int isDraw();
float v_hat(int,int);
float v_hat_2(int []);
void printBoard();
int logicTurn();
void makeMove(int);

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
  putchar('2');
  int logic,learning,dven;

  logic = 0;
  learning = 0;
  dven = 0;
  
  epsilon = 0;
  do {
    //    printf("a\n");
    experimentGen();
    //    printf("1\n");
    //    printf("b\n");
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
	//    printf("c\n");
    //    printf("2\n");
    /*
    printf("After a performance the board looks like\n");
    int i;
    for (i = 0; i < MAG; ++i){
      printf("%d ",Board[i]);
    }

    putchar('\n');
    */
        printBoard();
        critic();
    //    printf("d\n");
    //    printf("3\n");
        generalizer();
    //    printf("e\n");
    //    printf("4\n");
    epsilon++;
    //    printf("%d\n",epsilon);
   } while (epsilon < 3);
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
  /*  
  for (i = 0; i < (MAG*2) + 1; ++i){
    printf("%f ",Weights[i]);
  }
  */
  
}

void performanceSys(){


  whom = 0;
  srand(time(NULL));
  int flip,m;
  flip = (rand()%2);
  
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

void move_2(){
  int move;
  move = -1;
  if (( Board[0] == 1) && ( Board[6] == 1)){
    move = 3;
  } else if ((Board[0] == 1) && ( Board[2] == 1 )){
    move = 1;
  } else if ((Board[0] == 1) && ( Board[8] == 1)){
    move = 4;
  } else if ((Board[0] == 1) && ( Board[1] == 1)){
    move = 2;
  } else if ((Board[0] == 1) && ( Board[3] == 1)){
    move = 6;
  } else if ((Board[0] == 1) && ( Board[4] == 1)){
    move = 8;
  } else if ((Board[1] == 1) && ( Board[2] == 1)){
    move = 0;
  } else if ((Board[1] == 1) && ( Board[4] == 1)){
    move = 7;
  } else if ((Board[1] == 1) && ( Board[7] == 1)){
    move = 4;
  } else if ((Board[2] == 1) && ( Board[5] == 1)){
    move = 8;
  } else if ((Board[2] == 1) && ( Board[8] == 1)){
    move = 5;
  } else if ((Board[3] == 1) && ( Board[6] == 1)){
    move = 0;
  } else if ((Board[3] == 1) && ( Board[4] == 1)){
    move = 5;
  } else if ((Board[3] == 1) && ( Board[5] == 1)){
    move = 4;
  } else if ((Board[4] == 1) && ( Board[8] == 1)){
    move = 0;
  } else if ((Board[4] == 1) && ( Board[7] == 1)){
    move = 1;
  } else if ((Board[4] == 1) && ( Board[6] == 1)){
    move = 2;
  } else if ((Board[4] == 1) && ( Board[5] == 1)){
    move = 3;
  } else if ((Board[5] == 1) && ( Board[8] == 1)){
    move = 2;
  } else if ((Board[6] == 1) && ( Board[7] == 1)){
    move = 8;
  } else if ((Board[6] == 1) && ( Board[8] == 1)){
    move = 7;
  } else if ((Board[7] == 1) && ( Board[8] == 1)){
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
  }
  if (move > 0){  
    Board[move]=1;
    int u;
    for (u = 0; u < MAG; ++u){
      if( Trace[u] == -1 ){
	Trace[u] = move;
	break;
      }
    }
  } else {
    printf("Error in move\n");
  }
}

void move(int p){
  putchar('1');
  int i,u;
  float max_v,aux;
  int max_i;

  int anyol;
  srand(time(NULL));
  do {
  anyol = (rand()%(MAG-1));
  } while (Board[anyol]);
  max_v = v_hat(anyol,p);
  max_i = anyol;
  
  for (i = 0; i < MAG; ++i){
    if (!Board[i]){
      aux = v_hat(i,p);
      //           printf("aux:%f ",aux);
      if (max_v < aux){
	max_v = aux;
	max_i = i;
	//	printf("i%d\n",i);
      }
    }
  }
  //  putchar('\n');

  //  printf("max_i:%d \n",max_i);
  /*
        for (i = 0; i < MAG; ++i){
	printf("%d ",Board[i]);

	}
  */
  /*
	if (max_i > 8){
	  printf("Error");
	  max_i = 0;
	} else if ( max_i < 0 ){
	  max_i = 0;
	}
  */
  //  	          printf("%d %d\n",p,max_i);
      //      Board[8] = -1;
      
	      //    getchar();
  /*
  printf("The Move function has decided for player %d\n",p);
  printf("The best move to be %d.\n",max_i);
  */
  //  printf("max_i: %d \n",max_i);
  Board[max_i]=p;
  //All subsequent moves are set 
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

  /*
  float V;
  int i;
  int len;
  len = (MAG*2);
  int X[len];
  for (i = 0; i < MAG; ++i){
    if ((Board[i] == 1) || ( (i == m) && (p == 1))){
      X[i] = 1;
    } else {
      X[i]=0;
    }
  }
  
  for (i = MAG; i < len; ++i){
    if ((Board[i-MAG] == -1 ) || ( ((i-MAG) == m) && ( p == -1 ))){
      X[i]=1;
    } else {
      X[i]=0;
    }
  }
  V = Weights[0];
  for (i = 0; i < len; ++i){
    V+=Weights[i+1]*X[i];
  }
  return V;
  */
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
  //  printf("draw\n");
  /*
  for (i = 0; i < MAG; ++i){
    printf("%d ",Board[i]);
  }
  */
  for (i = 0; i < MAG; ++i){
    if (!Board[i]){
      return 0;
    }
  }
  return 1;
}

int isDraw_2(int B[]){
  int i;
  //  printf("draw\n");
  /*
  for (i = 0; i < MAG; ++i){
    printf("%d ",Board[i]);
  }
  */
  for (i = 0; i < MAG; ++i){
    if (!B[i]){
      return 0;
    }
  }
  return 1;
}

void critic(){
  int i,j;
  /*
  printf("We have reached the critic\n");
  printf("Status of game trace\n");

  for ( i = 0; i < MAG; ++i){
    printf("%d ",Trace[i]);
  }
  putchar('\n');
  */
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
    printf("here");
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
  /*
  for ( i = 0; i < MAG; ++i){
    for ( j = 0; j < (MAG * 2) + 1; ++j){
      printf("%d ",X[i][j]);
    }
    putchar('\n');
  }
  */
  nu = 0.01;
  /*
  printf("We have reached Generalizer\n");
  printf("Status of BoardHistory\n");
  for (i = 0; i < MAG; ++i){
    for (j = 0; j < MAG; ++j){
      printf("%d ",BoardHistory[i][j]);
    }
    putchar('\n');
  }

  printf("V_train.\n");
  for (i = 0; i < MAG; ++i){
    printf("%d ",V_train[i]);
  }
  putchar('\n');

  printf("Status of X vector\n");
  for (i = 0; i < MAG; ++i){
    for (j = 0;j < (2 * MAG) + 1; ++j){
      printf("%d ",X[i][j]);
    }
    putchar('\n');
  }
  */
  for ( j = 0; j < MAG; ++j){

    //what if the game doesn't go on for 9 moves?
    for ( k = 0; k < ( 2 * MAG ) + 1; ++k){
      
      temp = (V_train[j] - v_hat_2(BoardHistory[j])) * X[j][k];
      //      printf("te: %f \n",temp);
      Weights[k] = Weights[k] + (nu * temp);
      //      printf("W_k: %f \n",Weights[k]);
    }
    /*    printf("Weights after %d Loop\n",j+1);
    for (i = 0; i < (2 * MAG) + 1; ++i){
      printf("%f ",Weights[i]);
    }
    putchar('\n');
    */
  }

  FILE *fp;
  fp = fopen("weights.txt","w+");
  for (i = 0; i < (2 * MAG) + 1; ++i){
    fprintf(fp,"%f ",Weights[i]);
  }
  putchar('Z');
  fclose(fp);
}
