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
float v_hat_2(int []);

//Global Variables
int epsilon;
int Board[MAG];
float Weights[(MAG*2)+1];
int Trace[MAG];
int Score;
int BoardHistory[MAG][MAG];
int V_train[MAG];
float nu;

int main(){
  epsilon = 0;

  do {
    experimentGen();
    printf("1\n");
    performanceSys();
    printf("2\n");
    critic();
    printf("3\n");
    generalizer();
    printf("4\n");
    epsilon++;
    printf("%d\n",epsilon);
  } while (epsilon < 1);
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

  do {
    move(1);
    if (isWinner()){
      Score = 100;
      printf("1 W\n");
      break;
    } else if (isDraw()){
      printf("1 D\n");
      Score = 0;
      break;
    }
    printf("1.1\n");
    
    move(-1);
    if (isWinner()){
      Score = -100;
      printf("2 W\n");
      break;
    } else if (isDraw()){
      printf("2 D\n");      
      Score = 0;
      break;
    }
        printf("1.2\n");
  } while (1);
}


void move(int p){
  int i,u;
  float max_v,aux;
  int max_i;
  max_i = 0;
  max_v = 0;
  for (i = 0; i < MAG; ++i){


    if (!Board[i]){
      aux = v_hat(i,p);
      printf("aux:%f \n",aux);
      if (max_v < aux){
	max_v = aux;
	max_i = i;
	printf("i%d\n",i);
      }
    }
  }

  printf("max_i:%d \n",max_i);
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
	//          printf("\n%d %d\n",p,max_i);
      //      Board[8] = -1;
      
	      //    getchar();
      
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
  printf("draw\n");
  for (i = 0; i < MAG; ++i){
    printf("%d ",Board[i]);
  }
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


float V_hat_2(int b[]){

  int X[(MAG * 2) + 1];
  X[0]=1;
  int i;
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
      
  nu = 0;
  
  for ( i = 0; i < MAG; ++i){
    for ( j = 0; j < MAG; ++j){
      for ( k = 0; k < ( 2 * MAG ) + 1; ++k){
	temp = (V_train[j] - V_hat_2(BoardHistory[j])) * X[j][k];
	Weights[k] = Weights[k] + nu * temp;
      }
    }
  }

  FILE *fp;
  fp = fopen("weights.txt","w+");
  for (i = 0; i < (2 * MAG) + 1; ++i){
    fprintf(fp,"%f ",Weights[i]);
  }
  fclose(fp);
}
