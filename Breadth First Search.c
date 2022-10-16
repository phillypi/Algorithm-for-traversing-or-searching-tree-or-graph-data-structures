#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/************** Estruturas ****************/

struct no{   /* Fila que se transforma em arvore no final kkkk */
        struct no *ant;
        struct no *pai;
       int matriz[3][3];
  };

struct arvore{
  struct arvore *pai, *esq, *meioEsq, *meioDir, *dir;
  int matriz[3][3];
  int pass; //pass = visitado
};


typedef struct arvore arv;
typedef struct no fila;

fila *filaInicio; //aponta para o primeiro elemento inserido.
fila *filaFim;    //aponta para o ultimo.

int L, C, no;

      int matFINAL[3][3] = {0, 1, 2,
                            3, 4, 5, 
                            6, 7, 8};

  /*
    int matINICIAL[3][3] = {1, 0, 2, 
                            3, 4, 5, 
                            6, 7, 8};
  */
   
   
    int matINICIAL[3][3] = {1, 6, 5,  //Esse o meu pc segura mas enche a memória... 
                            0, 3, 4, 
                            7, 2, 8};

                      
/*
   int matINICIAL[3][3] = {1, 2, 0, 
                           3, 4, 5, 
                           6, 7, 8};
*/

/** PROTÓTIPOS DAS FUNÇÕES*/
fila *removeInic(fila *inic);
fila *espacoFilaVazio(int matriz[3][3]);
void criaFilaVazia(fila *aux, int matriz[3][3]);
void insereFimFila(fila *FFim, int matriz[3][3]);

void imprimeCaminhoVolta(fila *ini);

int testaMatriz(int estadoATUAL[3][3], int estadoMETA[3][3]);
void imprimeMatriz(int matriz[3][3]);
void procuraVazio(int matriz[3][3]);
void copiaMatriz(int mat3x3[3][3], int matriz[3][3]);
void moveDaDireita(int matriz[3][3]);
void moveDaEsquerda(int matriz[3][3]);
void moveODeBaixo(int matriz[3][3]);
void moveODeCima(int matriz[3][3]);

arv *espacoArvoreComMatriz(int original[3][3]);

fila *expande_no(fila *x, arv *pai);
int BFS(int matriz[3][3]);

/*********FUNCAO PRINCIPAL***********/
int main(){
    no = 0; ///contador de "nos", não de níveis.
    
    if(BFS(matINICIAL)){
        
       printf("\nEstado final alcancado com [%d] nos expandidos da fila .. : \n", no);
     
       imprimeMatriz(filaInicio->matriz);  

       printf("\nCaso queira ver o caminho de volta ao problema inicial a partir da solucao, digite ENTER... \n");
       getchar();
    }

    fila *x = filaInicio;

    while( x!=NULL ){
      imprimeMatriz(x->matriz);
      x = x->pai;
    }

   return 0;
}


/************** CODIGO PARA ARVORE ******************/

arv *espacoArvoreComMatriz(int original[3][3]){
  arv *aux = (arv*)malloc(sizeof(arv));
  aux->pai = NULL;
  aux->esq = NULL;
  aux->meioEsq = NULL;
  aux->meioDir = NULL;
  aux->dir = NULL;
  aux->pass = 0;
  copiaMatriz(aux->matriz, original);
  return aux;
}

int BFS(int matriz[3][3]){

   criaFilaVazia(filaInicio, matriz);//CRIA A FILA
   printf("Matriz inicial:");
   imprimeMatriz(filaInicio->matriz);  ///print no problema.

   fila *x;
   arv *arv_aux = espacoArvoreComMatriz(matriz); //primeiro elemento na arvore

while(1){   

     x = filaInicio;  
    
     if(testaMatriz(x->matriz, matFINAL)) //Para a execussão, se caso for Estado meta, ele retorna o resultado
          return 1; 
      
     removeInic(filaInicio);
     expande_no(x, arv_aux);       
     no++; 
 }

 return 0;
}


fila *expande_no(fila *x, arv *pai){
     no++; //contador 
     

       
   fila *aux1, *aux2, *aux3, *aux4;
        
         x = filaInicio;   
         procuraVazio(x->matriz);

        if((L == 0)&&(C == 0)){                  ///[2 jogadas poss?veis] //// [L = 0, C = 1]
            aux1 =  espacoFilaVazio(x->matriz);   
            moveDaDireita(aux1->matriz);
            insereFimFila(filaFim, aux1->matriz);
          
            filaFim->pai = filaInicio;
           
            aux2 =  espacoFilaVazio(x->matriz);
            moveODeBaixo(aux2->matriz);
            insereFimFila(filaFim, aux2->matriz);

            filaFim->pai = filaInicio;
           

        }
        else if((L == 0)&&(C == 1)){             ///[3 jogadas poss?veis] /// [L = 0, C = 1]
            aux1 =  espacoFilaVazio(x->matriz);           
            moveDaDireita(aux1->matriz);
            insereFimFila(filaFim, aux1->matriz);

            filaFim->pai = filaInicio;
            
            aux2 =  espacoFilaVazio(x->matriz);
            moveDaEsquerda(aux2->matriz);
            insereFimFila(filaFim, aux2->matriz);

            filaFim->pai = filaInicio;
            
            aux3 =  espacoFilaVazio(x->matriz);            
            moveODeBaixo(aux3->matriz);
            insereFimFila(filaFim, aux3->matriz);

            filaFim->pai = filaInicio;     

        }
        else if((L == 0)&&(C == 2)){             ///[2 jogadas poss?veis] //// [L = 0, C = 2]
            aux1 =  espacoFilaVazio(x->matriz);           
            moveDaEsquerda(aux1->matriz);
            insereFimFila(filaFim, aux1->matriz);

            filaFim->pai = filaInicio;
            
            aux2 =  espacoFilaVazio(x->matriz);          
            moveODeBaixo(aux2->matriz);
            insereFimFila(filaFim, aux2->matriz);

            filaFim->pai = filaInicio;

        }
        else if((L == 1)&&(C == 0)){             ///[3 jogadas poss?veis] //// [L = 1, C = 0]
            aux1 =  espacoFilaVazio(x->matriz);          
            moveDaDireita(aux1->matriz);
            insereFimFila(filaFim, aux1->matriz); 

            filaFim->pai = filaInicio;         

            aux2 =  espacoFilaVazio(x->matriz);           
            moveODeCima(aux2->matriz);
            insereFimFila(filaFim, aux2->matriz);

            filaFim->pai = filaInicio;

            aux3 =  espacoFilaVazio(x->matriz);          
            moveODeBaixo(aux3->matriz);
            insereFimFila(filaFim, aux3->matriz);

            filaFim->pai = filaInicio;

        }
        else if((L == 1)&&(C == 1)){             ///[4 jogadas possiveis] //// [L = 1, C = 1] MEIO
            aux1 =  espacoFilaVazio(x->matriz);           
            moveDaDireita(aux1->matriz);
            insereFimFila(filaFim, aux1->matriz);

            filaFim->pai = filaInicio;

            aux2 =  espacoFilaVazio(x->matriz);          
            moveDaEsquerda(aux2->matriz);
            insereFimFila(filaFim, aux2->matriz); 

            filaFim->pai = filaInicio;         

            aux3 =  espacoFilaVazio(x->matriz);       
            moveODeCima(aux3->matriz);
            insereFimFila(filaFim, aux3->matriz);

            filaFim->pai = filaInicio;

            aux4 =  espacoFilaVazio(x->matriz);           
            moveODeBaixo(aux4->matriz);
            insereFimFila(filaFim, aux4->matriz);

            filaFim->pai = filaInicio;
            
        }
        else if((L == 1)&&(C == 2)){             ///[3 jogadas poss?veis] //// [L = 1, C = 2]
            aux1 =  espacoFilaVazio(x->matriz);         
            moveDaEsquerda(aux1->matriz);
            insereFimFila(filaFim, aux1->matriz);

            filaFim->pai = filaInicio;

            aux2 =  espacoFilaVazio(x->matriz);          
            moveODeBaixo(aux2->matriz);
            insereFimFila(filaFim, aux2->matriz);

            filaFim->pai = filaInicio;
            
            aux3 =  espacoFilaVazio(x->matriz);          
            moveODeCima(aux3->matriz);
            insereFimFila(filaFim, aux3->matriz);

            filaFim->pai = filaInicio;

        }
        else if((L == 2)&&(C == 0)){             ///[2 jogadas poss?veis] //// [L = 2, C = 0]
            aux1 =  espacoFilaVazio(x->matriz);           
            moveDaDireita(aux1->matriz);
            insereFimFila(filaFim, aux1->matriz);

            filaFim->pai = filaInicio;
        
            aux2 =  espacoFilaVazio(x->matriz);         
            moveODeCima(aux2->matriz);
            insereFimFila(filaFim, aux2->matriz);

            filaFim->pai = filaInicio;
           
        }
        else if((L == 2)&&(C == 1)){             ///[3 jogadas poss?veis] //// [L = 2, C = 1]
            aux1 =  espacoFilaVazio(x->matriz);         
            moveDaDireita(aux1->matriz);
            insereFimFila(filaFim, aux1->matriz);

            filaFim->pai = filaInicio;

            aux2 =  espacoFilaVazio(x->matriz);    
            moveDaEsquerda(aux2->matriz);
            insereFimFila(filaFim, aux2->matriz);

            filaFim->pai = filaInicio;

            aux3 =  espacoFilaVazio(x->matriz);          
            moveODeCima(aux3->matriz);
            insereFimFila(filaFim, aux3->matriz);

            filaFim->pai = filaInicio;

        }
        else if((L == 2)&&(C == 2)){             ///[2 jogadas poss?veis] //// [L = 2, C = 2]
            aux1 =  espacoFilaVazio(x->matriz);           
            moveODeCima(aux1->matriz);
            insereFimFila(filaFim, aux1->matriz);

            filaFim->pai = filaInicio;

            aux2 =  espacoFilaVazio(x->matriz);         
            moveDaEsquerda(aux2->matriz);
            insereFimFila(filaFim, aux2->matriz);  

            filaFim->pai = filaInicio;    
            
        }
        else{
            printf("PO");
        }


}


/***************** CODIGO PARA TIPO FILA ******************/

fila *espacoFilaVazio(int matriz[3][3]){
    
    fila *aux = (fila*)malloc(sizeof(fila));
    aux->ant = NULL;
    aux->pai = NULL;
    copiaMatriz(aux->matriz, matriz);
    return aux;
}

void criaFilaVazia(fila *aux, int matriz[3][3]){
    aux = espacoFilaVazio(matriz);      //Aloca espaço vazio para a inserção de itens na fila
    filaInicio = aux;
    filaFim = aux;             //O fim é o único elemento
}

void insereFimFila(fila *FFim, int matriz[3][3]){
    if(FFim == NULL){
    fila *aux = espacoFilaVazio(matriz);
    filaFim = aux;
    filaInicio = aux;
    }

    else{
      fila *aux = espacoFilaVazio(matriz);
      FFim->ant = aux;
      filaFim = aux;
    }
}

fila *removeInic(fila *inic){
  if(inic == NULL){
    printf("\nInicio da fila NULO... \n");
    exit(0);
  }

    if(inic->ant == NULL)
      return inic;

    fila *aux;
    aux = filaInicio;
    filaInicio = filaInicio->ant;
  
    return aux;
}


/************** CODIGO PARA MATRIZES ******************/

void imprimeMatriz(int matriz[3][3]){
    int i, j;
    printf("\n ----------- \n");
        for(i = 0; i <= 2; i++){
            for(j = 0; j <= 2; j++){
               printf("  %d ", matriz[i][j]);
            }
            printf("\n");
        }
  printf(" ----------- \n");
}

int testaMatriz(int estadoATUAL[3][3], int estadoMETA[3][3]){ //compara apenas uma matriz
 
  if((estadoATUAL == NULL)||(estadoMETA == NULL))
    return 0;

  int i, j;

  for(i = 0; i <= 2; i++){
      for(j = 0; j <= 2; j++){
        if(estadoATUAL[i][j] != estadoMETA[i][j])
            return 0;                                //No momento que encontra um diferente, ele para, assim evitando comparações extras.
        }
  }
       return 1;
}

void procuraVazio(int matriz[3][3]){
   int i, j;
   L = C = 0;
    for(i=0; i<=2; i++){
        for(j=0; j<=2; j++){
            if(matriz[i][j] == 0){
               L = i;
               C = j;
            }
        }
    }
}

void copiaMatriz(int mat3x3[3][3], int matriz[3][3]){
    int i, j;
   for(i = 0; i<=2; i++){
        for(j = 0; j<=2; j++){
                 if(matriz[i][j] == 0)
                   mat3x3[i][j] = 0;

            else if(matriz[i][j] == 1)
                   mat3x3[i][j] = 1;

            else if(matriz[i][j] == 2)
                   mat3x3[i][j] = 2;

            else if(matriz[i][j] == 3)
                   mat3x3[i][j] = 3;

            else if(matriz[i][j] == 4)
                   mat3x3[i][j] = 4;

            else if(matriz[i][j] == 5)
                   mat3x3[i][j] = 5;

            else if(matriz[i][j] == 6)
                   mat3x3[i][j] = 6;

            else if(matriz[i][j] == 7)
                   mat3x3[i][j] = 7;

            else if(matriz[i][j] == 8)
                   mat3x3[i][j] = 8;

                   else{
                    printf("\nBUG copiaMatriz\n");
                   }
        }
   }
}

void moveDaDireita(int matriz[3][3]){
    procuraVazio(matriz);
    matriz[L][C] = matriz[L][C+1];
    matriz[L][C+1] = 0;

}

void moveDaEsquerda(int matriz[3][3]){
    procuraVazio(matriz);
    matriz[L][C] = matriz[L][C-1];
    matriz[L][C-1] = 0;
}

void moveODeBaixo(int matriz[3][3]){
    procuraVazio(matriz);
    matriz[L][C] = matriz[L+1][C];
    matriz[L+1][C] = 0;

}

void moveODeCima(int matriz[3][3]){
    procuraVazio(matriz);
    matriz[L][C] = matriz[L-1][C];
    matriz[L-1][C] = 0;

}

void imprimeCaminhoVolta(fila *ini){
  fila *aux = ini;

  while(aux != NULL){
    imprimeMatriz(aux->matriz); 
    aux = aux->pai;
  }
}


