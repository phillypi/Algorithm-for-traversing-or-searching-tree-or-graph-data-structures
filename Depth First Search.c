#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//estruturas
struct pilh{
	struct pilh *ant;
	int matriz[3][3];
};

struct list{
	struct list *prox;
	int matriz[3][3];
};

struct arvore{
	struct arvore *pai, *esq, *meioEsq, *meioDir, *dir;
	int matriz[3][3];
	int pass; //pass = visitado
};

typedef struct pilh pilha;
typedef struct list lista;
typedef struct arvore arv;

int DFS(int mat[3][3]);

arv *espacoArvoreComMatriz(int original[3][3]);
void expandeNoArvore(arv *ARV);

lista *espacoListaComMatriz(int original[3][3]);
int ComparaElementoslista(lista *list, int matriz[3][3]);
void insereFimLista(lista *list, int matriz[3][3]);

pilha *espacoPilhaComMatriz(int original[3][3]);
void push(pilha *topo, int matriz[3][3]);
void pop();
void imprimePilha();

int testaMatriz(int estadoATUAL[3][3], int estadoMETA[3][3]);
void imprimeMatriz(int matriz[3][3]);
void moveDaDireita(int matriz[3][3]);
void moveDaEsquerda(int matriz[3][3]);
void moveODeBaixo(int matriz[3][3]);
void moveODeCima(int matriz[3][3]);
void procuraVazio(int matriz[3][3]);
void copiaMatriz(int mat3x3[3][3], int matriz[3][3]);


//Variaveis globais abaixo
pilha *top;

int L, C;  


int estadoINICIAL[3][3] = {1, 4, 2, //alterar o estado inicial aqui
						   3, 0, 5,
						   6, 7, 8};

int estadoMETA[3][3] = {0, 1, 2,
	                    3, 4, 5,
	                    6, 7, 8};


int main(){	
	
	if(DFS(estadoINICIAL)){
		printf("\nEstado Final alcancado \n");
		imprimeMatriz(top->matriz);
		//exit(0);
	}

    printf("\nPara ver o retorno ao estado inicial a partir da solução, aperte ENTER: \n");
    getchar();

    imprimePilha(); //vai imprimir a pilha a partir do TOP

	return 0;
}

                    

int DFS(int mat[3][3]){
	arv *raizArv = espacoArvoreComMatriz(mat);//raiz da arvore
	arv *arv_aux = raizArv; //NO auxiliar para percorrer a arvore

	lista *list = espacoListaComMatriz(mat);
	top = espacoPilhaComMatriz(mat);

    printf("\nEstado inicial: \n");
    imprimeMatriz(arv_aux->matriz);

    while(1){  	  
		
		if(testaMatriz(top->matriz, estadoMETA))//Primeiro testa se é o a meta
					       return 1;
	
		else if((arv_aux != NULL)&&(arv_aux->esq == NULL)&&(arv_aux->pass != 1)){ 	//Só expande se não tiver sido expandido, ou se não tiver sido visitado(pass = 1 )...
					 						 
					 expandeNoArvore(arv_aux);
				     push(NULL, arv_aux->matriz);	//NULL porque estou usando variavel global		     	
		}


		if(ComparaElementoslista(list, arv_aux->matriz))// Compara com todos os que já foram testados, se caso for igual a um deles, mata o no.
				arv_aux->pass = 1; 			

		else 
			insereFimLista(list, arv_aux->matriz);	 //se for desconhecido na lista, ele insere.

				if((arv_aux->pass == 1)&&(arv_aux->pai != NULL)){ //Se já passou por ele e o pai não for nulo... 
				    arv_aux = arv_aux->pai;
				    pop();
				}

        /*  Daqui para baixo nesta função, apenas percorre... dando enfase ao lado esquerdo*/

				if((arv_aux->esq != NULL)&&(arv_aux->esq->pass != 1))
					arv_aux = arv_aux->esq;
				

				else if((arv_aux->meioEsq != NULL)&&(arv_aux->meioEsq->pass != 1))
					arv_aux = arv_aux->meioEsq;
				

				else if((arv_aux->meioDir != NULL)&&(arv_aux->meioDir->pass != 1))
					arv_aux = arv_aux->meioDir;
				

				else if((arv_aux->dir != NULL)&&(arv_aux->dir->pass != 1))
					arv_aux = arv_aux->dir;

	}	
		return 0;	
}


//***************** CODIGOS REFERENTES A ARVORE **********************//

void expandeNoArvore(arv *ARV){ //acrescenta mais nos para serem visitados

    if(ARV == NULL)
        	printf("\nProblema expandeNoArvore()\n");

    else{
        	procuraVazio(ARV->matriz); //busca onde está a posição NULAe joga pra Linha | Coluna (L e C)

        if((L == 0)&&(C == 0)){                  ///[2 jogadas poss?veis] //// [L = 0, C = 1] D, B
           
            arv *aux1 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaDireita(aux1->matriz);
            ARV->esq = aux1;
            aux1->pai = ARV;

            arv *aux2 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeBaixo(aux2->matriz);
            ARV->meioEsq = aux2;
            aux2->pai = ARV;
        }

        else if((L == 0)&&(C == 1)){             ///[3 jogadas poss?veis] /// [L = 0, C = 1] D, E, B
           
            arv *aux1 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaEsquerda(aux1->matriz);
            ARV->esq = aux1;
            aux1->pai = ARV;
            
            arv *aux2 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaDireita(aux2->matriz);
            ARV->meioEsq = aux2;
            aux2->pai = ARV;

            arv *aux3 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeBaixo(aux3->matriz);
            ARV->meioDir = aux3;
            aux3->pai = ARV;
        }

        else if((L == 0)&&(C == 2)){             ///[2 jogadas poss?veis] //// [L = 0, C = 2] E, B
            
            arv *aux1 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaEsquerda(aux1->matriz);
            ARV->esq = aux1;
            aux1->pai = ARV;

            arv *aux2 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeBaixo(aux2->matriz);
            ARV->meioEsq = aux2;
            aux2->pai = ARV;
        }

        else if((L == 1)&&(C == 0)){             ///[3 jogadas poss?veis] //// [L = 1, C = 0] D, C, B
            
            arv *aux1 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaDireita(aux1->matriz);
            ARV->esq = aux1;
            aux1->pai = ARV;
            
            arv *aux2 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeCima(aux2->matriz);
            ARV->meioEsq = aux2;
            aux2->pai = ARV;

            arv *aux3 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeBaixo(aux3->matriz);
            ARV->meioDir = aux3;
            aux3->pai = ARV;
        }
       
        else if((L == 1)&&(C == 1)){             ///[4 jogadas possiveis] //// [L = 1, C = 1] MEIO D, E, C, B
          
            arv *aux1 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaDireita(aux1->matriz);
            ARV->esq = aux1;
            aux1->pai = ARV;
            
            arv *aux2 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeCima(aux2->matriz);
            ARV->meioEsq = aux2;
            aux2->pai = ARV;

            arv *aux3 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeBaixo(aux3->matriz);
            ARV->meioDir = aux3;
            aux3->pai = ARV;

            arv *aux4 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaEsquerda(aux4->matriz);
            ARV->esq = aux4;
            aux4->pai = ARV;
        }
        
        else if((L == 1)&&(C == 2)){             ///[3 jogadas poss?veis] //// [L = 1, C = 2] E, B, C
            
            arv *aux1 =  espacoArvoreComMatriz(ARV->matriz);         
            moveDaEsquerda(aux1->matriz);
            ARV->esq = aux1;
            aux1->pai = ARV;
           
            arv *aux2 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeBaixo(aux2->matriz);
            ARV->meioEsq = aux2;
            aux2->pai = ARV;

            arv *aux3 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeCima(aux3->matriz);
            ARV->meioDir = aux3;
            aux3->pai = ARV;
        }
        
        else if((L == 2)&&(C == 0)){             ///[2 jogadas poss?veis] //// [L = 2, C = 0] D, C
           
            arv *aux1 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaDireita(aux1->matriz);
            ARV->esq = aux1;
            aux1->pai = ARV;

            arv *aux2 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeCima(aux2->matriz);
            ARV->meioEsq = aux2;
            aux2->pai = ARV;
        }
        
        else if((L == 2)&&(C == 1)){             ///[3 jogadas poss?veis] //// [L = 2, C = 1]
           
            arv *aux1 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaDireita(aux1->matriz);
            ARV->esq = aux1;
            aux1->pai = ARV;

            arv *aux2 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaEsquerda(aux2->matriz);
            ARV->meioEsq = aux2;
            aux2->pai = ARV;

            arv *aux3 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeCima(aux3->matriz);
            ARV->meioDir = aux3;
            aux3->pai = ARV;
        }

        else if((L == 2)&&(C == 2)){             ///[2 jogadas poss?veis] //// [L = 2, C = 2]
         
            arv *aux1 =  espacoArvoreComMatriz(ARV->matriz);
            moveODeCima(aux1->matriz);
            ARV->meioEsq = aux1;
            aux1->pai = ARV;

            arv *aux2 =  espacoArvoreComMatriz(ARV->matriz);
            moveDaEsquerda(aux2->matriz);
            ARV->meioEsq = aux2;
            aux2->pai = ARV;
        }
       
        else{
            printf("\nProblema no expandeNoArvore() ELSE\n");
        }
    }
}	

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

//***************** CODIGOS REFERENTES A LISTA **********************//

int ComparaElementoslista(lista *list, int matriz[3][3]){ //compara todas as matrizes da lista
	
	if(list == NULL) 
		return 0;

	else if(list->prox == NULL) //ignora o primeiro: estado inicial
		return 0;

	else{

		lista *aux = list;

		for(;aux->prox != NULL; aux = aux->prox){
			if(testaMatriz(aux->matriz, matriz) == 1)  
				return 1;  //iguais
		}
		    	return 0;  //diferentes
	}
}

void insereFimLista(lista *list, int matriz[3][3]){
	
	lista *novo = espacoListaComMatriz(matriz);

	if(testaMatriz(list->matriz, matriz)) //não compara o primeiro elemento... 
		return;

	if(list == NULL){  //Se não houver elementos na lista
		printf("\ninsereFimLista NULL\n");
		exit(0);
	}

	else if(list->prox == NULL){ //se houver apenas um elemento
		list->prox = novo;
	}

	else{

		lista *aux = list;

		do{
			aux = aux->prox;

		}while(aux->prox != NULL);//Procurando o ultimo elemento
		
		    aux->prox = novo;	
	}	
}

lista *espacoListaComMatriz(int original[3][3]){
	lista *list = (lista*)malloc(sizeof(lista));
	list->prox = NULL;
    copiaMatriz(list->matriz, original);
	return list;
}

//***************** CODIGOS REFERENTES A PILHA **********************//

pilha *espacoPilhaComMatriz(int original[3][3]){
	pilha *aux = (pilha*)malloc(sizeof(pilha));
	aux->ant = NULL;
    copiaMatriz(aux->matriz, original);
    return aux;
}

void imprimePilha(){ //Imprime na ordem inversa (topo para o inicio)

	if(top == NULL){
		printf("\nPilha vazia:::imprimePilha();\n");
		exit(0);
	}
	else if(top->ant == NULL)
		imprimeMatriz(top->matriz);

	else{
		pilha *p;

		while(top != NULL){
						
				p = top;
                system("clear"); 
                imprimeMatriz(p->matriz);
                usleep(100000);
				top = top->ant;
				free(p);                              
		}

	}
}

void pop(){	
	if(top == NULL){
		printf("\nProblema para POP\n");
		exit(0);
	}

	else if(top->ant == NULL){ //ignora o primeiro elemento da pilha
		
		/*pilha *aux;
		aux = top;
		top = NULL;*/
	}

	else{
		
		pilha *aux;
		aux = top;
		top = top->ant;
		free(aux);
	}
}

//Insere um elemento (matriz) na pilha
void push(pilha *topo, int matriz[3][3]){
	
  if(top == NULL)
		top = espacoPilhaComMatriz(matriz);
	
	else{

		pilha *x;
		x = espacoPilhaComMatriz(matriz);
		x->ant = top;
		top = x;
	}
}


//***************** CODIGOS REFERENTES A MATRIZ **********************//

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

//Copia o estado atual da matriz para uma nova
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
