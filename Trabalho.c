#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

/* JOGO DA VELHA
##IMPORTANTE##  1: HUMANO  2: COMPUTADOR   #####
EM DESENVOLVIMENTO
*/

/***********************************************/
/* Definição dos Registros                     */
/***********************************************/
typedef struct {          // registro
       int id;			 // id para jogadas
} INFORMACAO;

typedef struct arv {
       INFORMACAO info;   // dados do registro
       struct arv* subd;  // ponteiro para o nodo da direita
       struct arv* sube;  // ponteiro para o nodo da esquerda
} ARVORE;


/***********************************************/
/* Definição das Funções                       */
/***********************************************/
void criarJogo ( ARVORE **r, int tabuleiro[3][3] );
void jogar ( ARVORE **r, int id, int idAux, int tabuleiro[3][3]);
void entradaDados ( ARVORE *no );
void analisarJogo ( ARVORE **r, int id, int tabuleiro[3][3]);
void desenhoTabuleiro ();
void tabuleiroAtual (int tabuleiro[3][3]);
void jogarHuman (int tabuleiro[3][3]);
int procurarPerca (int tabuleiro[3][3], int codVencedor, int codPerdedor);
void jogarAleatorio (int tabuleiro[3][3]);
int progressoTabuleiro (int tabuleiro[3][3]);


/***********************************************/
/* Programa Principal                          */
/***********************************************/
int main(){

	setlocale (LC_ALL,"");
	int x, i; // Índices
	int tabuleiro[3][3]; // Tabuleiro para o jogo da velha
	ARVORE *r = NULL;

	for( i = 0; i < 3; i++ ){ // Definição inicial da matriz em 0
		for( x = 0; x < 3; x++ )
			tabuleiro[x][i] = 0;
	}

	criarJogo ( &r, tabuleiro );

} // Final programa principal


/************************************************
 * Funções                                      *
 ************************************************/
 void criarJogo ( ARVORE **r, int tabuleiro[3][3] ){
 	    ARVORE *no = ( ARVORE * ) malloc ( sizeof( ARVORE )); // aloca novo espaco em memória
        no->subd = NULL;                                 // inicializa subárvore da direita
        no->sube = NULL;								 // inicializa subárvore da esquerda
        no->info.id = 20;
        *r= no;                                         // anterior aponta para novo registro
        analisarJogo( r ,no->info.id, tabuleiro );					// Envia o id
 }


 void jogar ( ARVORE **r, int id, int idAux, int tabuleiro[3][3]){

 	ARVORE *aux = *r;

 	while( aux->info.id != id ){

 		if(aux->info.id > id)
 			aux = aux->sube;
 		else
 			aux = aux->subd;
	}

   	ARVORE *no = ( ARVORE * ) malloc ( sizeof( ARVORE )); // aloca novo espaco em memória
   	no->info.id = idAux;
   	no->subd = NULL;									// inicializa subárvore da direita
   	no->sube = NULL;								 // inicializa subárvore da esquerda
   	*aux = *no;



   	analisarJogo( r ,no->info.id, tabuleiro );					// Envia o id
 }


 void analisarJogo ( ARVORE **r, int id, int tabuleiro[3][3] ){ // Analisar jogada posicionada na árvore

 	int idAux;				//  Variável para próximo no
 	int codVencedor;		// Variável para procurar pontos de vitórias ou derrotas CPU/HUMANO
 	int codPerdedor;		// Variável para procurar pontos de vitórias ou derrotas CPU/HUMANO
 	int condicional; 		// Return da função para procurar perdedor ou ganhador (procurarPerca)
 	int terminoJogo = 0;	// Verifica se o jogo terminou

 	switch( id ){ 		// Possibilidade de jogadas de acordo com o id da árvore
 		case 5 :

 			while(1){

	 			system("cls");

	 			codVencedor = 2;
	 			codPerdedor = 2;
	 			condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor);	// Procurar vitória da CPU (retorna false se achar ou true se não achar)

	 			if(condicional == 0){
	 				tabuleiroAtual(tabuleiro);
	 				puts("\n\n   [VOCÊ PERDEU!]");
	 				break;
				 }

	 			if(condicional){
	 				codVencedor = 1; 					// define a procura de quem irá perder CPU ou PESSOA
	 				codPerdedor = 2;
	 				condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor); // Procurar ponto de derrota da CPU (retorna false se achar ou true se não achar)
				 }

				 // Procurar diagonal que ganhe o jogo PROX

				if(condicional){	// Jogar aleatório (falta de jogadas)
					jogarAleatorio(tabuleiro);
				}

				 tabuleiroAtual(tabuleiro);		// Mostrar tabuleiro
				 jogarHuman(tabuleiro);			// Pessoa joga

				 terminoJogo = progressoTabuleiro( tabuleiro );		// Guardar resposta do possível término do jogo

				 if(terminoJogo){ 	// Verificar se o jogo terminou com empate
				 	system("cls");
				 	tabuleiroAtual(tabuleiro);	// mostrar tabuleiro
				 	puts("\n\n    [EMPATOU!]");
	 				break;
				 }

 			}

 		break;

 		case 10 :
 			system("cls"); // Limpar tela
 			tabuleiro [0][2] = 2; // PC joga
 			tabuleiroAtual(tabuleiro);  		// Mostrar tabuleiro

			jogarHuman(tabuleiro); 				// Vez da pessoa jogar

 			tabuleiroAtual(tabuleiro); 			// Mostrar tabuleiro

 			if ( tabuleiro[0][0] == 1 || tabuleiro[0][2] == 1  || tabuleiro[2][0] == 1  || tabuleiro[2][2] == 1 ) // Condicional para definir próximo passo na árvore
 				idAux = 5;
 			else
 				idAux = 15;

 			jogar( r, id, idAux, tabuleiro); // Nova jogada

 		break;

 		case 15 :
 				while(1){

	 			system("cls");

	 			codVencedor = 2;
	 			codPerdedor = 2;
	 			condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor);	// Procurar vitória da CPU (retorna false se achar ou true se não achar)

	 			if(condicional == 0){
	 				tabuleiroAtual(tabuleiro);
	 				puts("\n\n   [VOCÊ PERDEU!]");
	 				break;
				 }

	 			if(condicional){
	 				codVencedor = 1; 					// define a procura de quem irá perder CPU ou PESSOA
	 				codPerdedor = 2;
	 				condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor); // Procurar ponto de derrota da CPU (retorna false se achar ou true se não achar)
				 }

				 // Procurar diagonal que ganhe o jogo PROX

				if(condicional){
					jogarAleatorio(tabuleiro);
				}

				 tabuleiroAtual(tabuleiro);
				 jogarHuman(tabuleiro);

				 terminoJogo = progressoTabuleiro( tabuleiro );

				 if(terminoJogo){	// Verificar se o jogo terminou com empate
				 	system("cls");
				 	tabuleiroAtual(tabuleiro);
				 	puts("\n\n    [EMPATOU!]");
	 				break;
				 }
 			}
 		break;

 		case 20 :
			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
			jogarHuman(tabuleiro);					// Vez da pessoa jogar
 			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro

 			if ( tabuleiro[1][1] != 0 )
 				idAux = 10;
 			else
 				idAux = 80;

 			jogar( r, id, idAux, tabuleiro);

 		break;

 		case 35 :
 		break;

	 }

 }

 void desenhoTabuleiro(){
 	puts("\n");
 	puts("   1 | 2 | 3");
 	puts(" -------------");
 	puts("   4 | 5 | 6");
 	puts(" -------------");
 	puts("   7 | 8 | 9 ");
 }

 void tabuleiroAtual( int tabuleiro[3][3] ){
 	puts("\n");
 	printf("      %d | %d | %d", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
 	puts("\n    -------------");
 	printf("      %d | %d | %d", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
 	puts("\n    -------------");
 	printf("      %d | %d | %d", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
 }

 void jogarHuman(int tabuleiro[3][3]){ 		// Função para receber jogada da pessoa via input

 	int autenticacao = 0;		// Controle do do while
 	int jogada = 0;			// recebe posição do tabuleiro, digitado pela pessoa

 	do{
 		puts("\n\n    [SUA VEZ!]");
 		scanf("%d", &jogada);			// recebe posição do tabuleiro, digitado pela pessoa
 		autenticacao = 0;		// Controle do do while

 		switch(jogada){ 		// Restringir jogada, dependendo da condição da casa escolhida (livre ou ocupada)
 		case 1:
 			if (tabuleiro[0][0] == 0 )		// Condição para verificar ocupação do tabuleiro ( 0 = livre )
 				tabuleiro [0][0] = 1;
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
 		break;

 		case 2:
 			if (tabuleiro[0][1] == 0 )
 				tabuleiro [0][1] = 1;
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }

 		break;

 		case 3:
 			if (tabuleiro[0][2] == 0 )
 				tabuleiro [0][2] = 1;
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }

 		break;

 		case 4:
 			if (tabuleiro[1][0] == 0 )
 				tabuleiro [1][0] = 1;
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }

 		break;

 		case 5:
 			if (tabuleiro[1][1] == 0 )
 				tabuleiro [1][1] = 1;
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }

 		break;

 		case 6:
 			if (tabuleiro[1][2] == 0 )
 				tabuleiro [1][2] = 1;
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }

 		break;

 		case 7:
 			if (tabuleiro[2][0] == 0 )
 				tabuleiro [2][0] = 1;
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }

 		break;

 		case 8:
 			if (tabuleiro[2][1] == 0 )
 				tabuleiro [2][1] = 1;
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }

 		break;

 		case 9:
 			if (tabuleiro[2][2] == 0 )
 				tabuleiro [2][2] = 1;
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
		break;
 		default:
 			printf ("Está posição não existe");
 			autenticacao = 1;

		}

	} while ( autenticacao != 0 );

 }

 int procurarPerca (int tabuleiro[3][3], int codVencedor, int codPerdedor){
 		// VERIFICAR HORIZONTAL LINHA 1
 	if ( tabuleiro[0][0] == codVencedor && tabuleiro [0][1] == codVencedor && tabuleiro [0][2] == 0 ){
 		tabuleiro[0][2] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][0] == codVencedor && tabuleiro[0][1] == 0 && tabuleiro[0][2] == codVencedor ){
 		tabuleiro[0][1] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][0] == 0 && tabuleiro[0][1] == codVencedor && tabuleiro[0][2] == codVencedor ){
 		tabuleiro[0][0] = codPerdedor;
 		return 0;
	 }

 		// VERIFICAR DIAGONAL 1
 	else if ( tabuleiro[0][0] == codVencedor && tabuleiro[1][1] == codVencedor && tabuleiro[2][2] == 0 ){
 		tabuleiro[2][2] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][0] == codVencedor && tabuleiro[1][1] == 0 && tabuleiro[2][2] == codVencedor ){
 		tabuleiro[1][1] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][0] == 0 && tabuleiro [1][1] == codVencedor && tabuleiro [2][2] == codVencedor ){
 		tabuleiro[0][0] = codPerdedor;
 		return 0;
	 }

 		// VERIFICAR DIAGONAL 2
 	else if ( tabuleiro[0][2] == codVencedor && tabuleiro[1][1] == codVencedor && tabuleiro[2][0] == 0 ){
 		tabuleiro[2][0] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][2] == codVencedor && tabuleiro[1][1] == 0 && tabuleiro[2][0] == codVencedor ){
 		tabuleiro[1][1] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][2] == 0 && tabuleiro [1][1] == codVencedor && tabuleiro [2][0] == codVencedor ){
 		tabuleiro[0][2] = codPerdedor;
 		return 0;
	 }

 		// VERIFICAR HORIZONTAL LINHA 2
 	else if ( tabuleiro[1][0] == codVencedor && tabuleiro [1][1] == codVencedor && tabuleiro [1][2] == 0 ){
 		tabuleiro[1][2] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[1][0] == codVencedor && tabuleiro[1][1] == 0 && tabuleiro[1][2] == codVencedor ){
 		tabuleiro[1][1] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[1][0] == 0 && tabuleiro[1][1] == codVencedor && tabuleiro[1][2] == codVencedor ){
 		tabuleiro[1][0] = codPerdedor;
 		return 0;
	 }

 		// VERIFICAR HORIZONTAL LINHA 3
 	else if ( tabuleiro[2][0] == codVencedor && tabuleiro [2][1] == codVencedor && tabuleiro [2][2] == 0 ){
 		tabuleiro[2][2] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[2][0] == codVencedor && tabuleiro[2][1] == 0 && tabuleiro[2][2] == codVencedor ){
 		tabuleiro[2][1] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[2][0] == 0 && tabuleiro[2][1] == codVencedor && tabuleiro[2][2] == codVencedor ){
 		tabuleiro[2][0] = codPerdedor;
 		return 0;
	 }

 		// VERIFICAR VERTICAL COLUNA 1
 	else if ( tabuleiro[0][0] == codVencedor && tabuleiro [1][0] == codVencedor && tabuleiro [2][0] == 0 ){
 		tabuleiro[2][0] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][0] == codVencedor && tabuleiro[1][0] == 0 && tabuleiro[2][0] == codVencedor ){
 		tabuleiro[1][0] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][0] == 0 && tabuleiro[1][0] == codVencedor && tabuleiro[2][0] == codVencedor ){
 		tabuleiro[0][0] = codPerdedor;
 		return 0;
	 }

 		// VERIFICAR VERTICAL COLUNA 2
 	else if ( tabuleiro[0][1] == codVencedor && tabuleiro [1][1] == codVencedor && tabuleiro [2][1] == 0 ){
 		tabuleiro[2][1] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][1] == codVencedor && tabuleiro[1][1] == 0 && tabuleiro[2][1] == codVencedor ){
 		tabuleiro[1][1] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][1] == 0 && tabuleiro[1][1] == codVencedor && tabuleiro[2][1] == codVencedor ){
 		tabuleiro[0][1] = codPerdedor;
 		return 0;
	 }

 		// VERIFICAR VERTICAL COLUNA 3
 	else if ( tabuleiro[0][2] == codVencedor && tabuleiro [1][2] == codVencedor && tabuleiro [2][2] == 0 ){
 		tabuleiro[2][2] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][2] == codVencedor && tabuleiro[1][2] == 0 && tabuleiro[2][2] == codVencedor ){
 		tabuleiro[1][2] = codPerdedor;
 		return 0;
	 } else if ( tabuleiro[0][2] == 0 && tabuleiro[1][2] == codVencedor && tabuleiro[2][2] == codVencedor ){
	 	tabuleiro[0][2] = codPerdedor;
 		return 0;
	 } else
	 	return 1;

 }

 void jogarAleatorio (int tabuleiro[3][3]){

 	for( int i = 0; i < 3; i++ ){ // Definição inicial da matriz em 0
		for( int x = 0; x < 3; x++ ){
			if( tabuleiro[x][i] == 0 ){
				tabuleiro[x][i] = 2;
				return;
			}
		}
 	}
 }

 int progressoTabuleiro (int tabuleiro[3][3]){

 	for( int i = 0; i < 3; i++ ){ // Definição inicial da matriz em 0
		for( int x = 0; x < 3; x++ ){
			if( tabuleiro[x][i] == 0 )
				return 0;
		}
 	}

 	return 1;

 }

