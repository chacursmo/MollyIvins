#include <stdio.h>

#define MAG 9


//Learning System Functions
void experimentGen();
void performanceSys();
void critic();
void generalizer();

//Game Play Functions
void move(int);
int isWinner();
int isDraw();
float v_hat(int,int);

//Global Variables
float epsilon;
int Board[MAG];
int Weights[(MAG*2)+1];
int Trace[MAG];
int Score;
int BoardHistory[MAG][MAG];
int V_train[MAG];

int main(){
  do {
    experimentGen();
    performanceSys();
    critic();
    generalizer();
  } while (epsilon > .01);
  return 0;
}

void experimentGen(){
  int i,j;
  for ( i = 0; i < MAG; ++i){
    Board[i]=0;
    Trace[i]=-1;
  }

  for ( i =0; i < MAG; ++i){
    for ( j = 0; j < MAG; ++j){
      BoardHistory[i][j] = 0;
    }
  }
}

void performanceSys(){

  do {
    move(1);
    if (isWinner()){
      Score = 100;
      break;
    } else if (isDraw()){
      Score = 0;
      break;
    }
      
    move(-1);
    if (isWinner()){
      Score = -100;
      break;
    } else if (isDraw()){
      Score = 0;
      break;
    }
  } while (1);
}


void move(int p){
  int i,u;
  float max_v,aux;
  int max_i;
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
    if( Trace[u] != -1 ){
      Trace[u] = max_i;
      break;
    }
  }
}




float v_hat(int m,int p){
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


int isDraw(){
  int i;
  for (i = 0; i < MAG; ++i){
    if (!Board[i]){
      return 0;
    }
  }
  return 1;
}

  
  
void critic(){
  int i,j;
  for ( i = 0; i < MAG; ++i){
    for (j = 0; j < i; ++j){
	if (j%2){
	  BoardHistory[i][Trace[j]]=1;
	} else {
	  BoardHistory[i][Trace[j]]=-1;
	}
    }
    V_train[i]=Trace[i];
  }
}


void generalizer(){
  int i;
  for ( i = 0; i < MAG; ++i){
    
  }

  Weights[i] = Weights[i] + nu * ( V
}
