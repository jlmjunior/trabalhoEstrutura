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
void jogarAleatorio (int tabuleiro[3][3]);
void jogarDiagonal ( int tabuleiro[3][3] );
void padraoWinLoseDraw ( int tabuleiro[3][3] );
int procurarPerca (int tabuleiro[3][3], int codVencedor, int codPerdedor);
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
 	    ARVORE *no = ( ARVORE * ) malloc ( sizeof( ARVORE )); 		// aloca novo espaco em memória
        no->subd = NULL;                                 			// inicializa subárvore da direita
        no->sube = NULL;								 			// inicializa subárvore da esquerda
        no->info.id = 20;
        *r= no;                                         			// anterior aponta para novo registro
        analisarJogo( r ,no->info.id, tabuleiro );					// Envia o id
 }
 
 
 void jogar ( ARVORE **r, int id, int idAux, int tabuleiro[3][3]){
	
 	ARVORE *aux = *r;				// Auxiliar para percorrer árvore
	 	
 	while( aux->info.id != id ){	// Buscar ID
 		
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
 	int cont = 0;
 	
 	switch( id ){ 		// Possibilidade de jogadas de acordo com o id da árvore
 		case 5 :	// FOLHA
 			
 			while(1){
			 
	 			system("cls");
	 			
	 			codVencedor = 2;	// Código para verificação de ganhador/perdedor
	 			codPerdedor = 2;
	 			condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor);	// Procurar vitória da CPU (retorna false se achar ou true se não achar)
	 			
	 			if(condicional == 0){			// Vitória do computador
	 				tabuleiroAtual(tabuleiro);	// Mostrar tabuleiro
	 				puts("\n\n   [VOCÊ PERDEU!]");
	 				break;
				 }
	 				
	 			if(condicional){
	 				codVencedor = 1; 					// define a procura de quem irá perder CPU ou PESSOA
	 				codPerdedor = 2;
	 				condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor); // Procurar ponto de derrota da CPU (retorna false se achar ou true se não achar)
				 }
				 
				 // Procurar diagonal que ganhe o jogo PROX
				 
				if(condicional){			// Jogar aleatório (falta de jogadas)
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
 			
 			jogar( r, id, idAux, tabuleiro); 			// Entra na árvore para procurar próximo passo
 			
 		break;
 		
 		case 15 :	// FOLHA
 			
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padrões ( buscar vitório, buscar derrota, buscar empate )
 				
 		break;
 		
 		case 20 :
			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
			jogarHuman(tabuleiro);					// Vez da pessoa jogar
 			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
 			
 			if ( tabuleiro[1][1] != 0 )				// Raiz, determina caminho da árvore ( se jogou meio ou não )
 				idAux = 10;				// SIM, jogou meio
 			else
 				idAux = 80;				// NÃO jogou meio
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na árvore para procurar próximo passo
 				
 		break;
 		
 		case 80 :
 			system("cls");
 			tabuleiro [1][1] = 2; 					// PC joga
 			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
 			
 			if ( tabuleiro[0][0] == 1 || tabuleiro[0][2] == 1  || tabuleiro[2][0] == 1  || tabuleiro[2][2] == 1 ) // Condicional para definir próximo passo na árvore
 				idAux = 50;			// SIM, jogou diagonal
 			else
 				idAux = 90;			// NÃO jogou diagonal
 			
 			jogar( r, id, idAux, tabuleiro);		// Entra na árvore para procurar próximo passo
 			
 		break;

 		case 90 :
 			system("cls");
 			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
 			jogarHuman(tabuleiro);					// Pessoa joga
 			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
 			
 			codVencedor = 1;
 			codPerdedor = 0;
 			condicional = procurarPerca (tabuleiro, codVencedor, codPerdedor);		// Perde próximo lance?
 			
 			if ( condicional == 0 )		// SIM, perde
 				idAux = 85;
 			else						// NÃO perde
 				idAux = 95;
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na árvore para procurar próximo passo
 			
 		break;
 		
 		case 85 :	// FOLHA
 		
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padrões ( buscar vitório, buscar derrota, buscar empate )
 			
 		break;
 		
 		case 95 :	// FOLHA
 			system("cls");
 			
 			jogarDiagonal( tabuleiro );				// Jogada de defesa do PC
 			tabuleiroAtual( tabuleiro );			// Mostrar tabuleiro
 			jogarHuman( tabuleiro );				// Vez da pessoa jogar
 			system("cls");							// Limpar tela
 			tabuleiroAtual( tabuleiro );			// Mostrar tabuleiro
 			
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padrões ( buscar vitório, buscar derrota, buscar empate )
 			
 		break;
 		
 		case 50 :
 			cont = 0;
 			system("cls");
 			tabuleiroAtual ( tabuleiro );
 			jogarHuman ( tabuleiro );
 			system("cls");
 			tabuleiroAtual ( tabuleiro ); 
 			
			if ( tabuleiro[0][0] == 1 )				// Verificar se jogou diagonal novamente
				cont++;
			if ( tabuleiro[0][2] == 1 )
				cont++;
			if ( tabuleiro[2][0] == 1 )
				cont++;
			if ( tabuleiro[2][2] == 1 )
				cont++;

 			if ( cont >= 2 )		// SIM, jogou diagonal
 				idAux = 40;
 			else					// NÃO jogou diagonal
 				idAux = 60;
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na árvore para procurar próximo passo
 			
 		break;
 		
 		case 40:
 			
 			codVencedor = 1;
 			codPerdedor = 0;
 			condicional = procurarPerca (tabuleiro, codVencedor, codPerdedor);		// Perde próximo lance?
 			
 			if ( condicional == 0 )					// SIM, perde
 				idAux = 35;
 			else									// NÃO perde
 				idAux = 45;
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na árvore para procurar próximo passo
 			
 		break;
 		
 		case 35:	// FOLHA
 			
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padrões ( buscar vitório, buscar derrota, buscar empate )
 			
 		break;
 		
 		case 45:	// FOLHA
 			
 			system("cls");							// Limpar tela
 			tabuleiro[1][2] = 2;					// Vez do PC jogar
 			tabuleiroAtual ( tabuleiro );			// Mostrar tabuleiro
 			jogarHuman ( tabuleiro );				// Vez da pessoa jogar
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padrões ( buscar vitório, buscar derrota, buscar empate )
 			
 		break;
 		
 		case 60 :
 			codVencedor = 1;
 			codPerdedor = 0;
 			condicional = procurarPerca (tabuleiro, codVencedor, codPerdedor);		// Perde próximo lance?
 			
 			if ( condicional == 0 )			// SIM, perde
 				idAux = 55;
 			else							// NÃO perde
 				idAux = 65;
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na árvore para procurar próximo passo
 		break;
 		
 		case 55 :	// FOLHA
 			
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padrões ( buscar vitório, buscar derrota, buscar empate )
 			
 		break;
 		
 		case 65 :	// FOLHA
 			
 			system("cls");
 			
 			if ( tabuleiro[0][0] == 1 )			// Computador joga contra a diagonal ( nessa etapa, precisa jogar para evitar derrota )
 				tabuleiro[2][2] = 2;
 			else if ( tabuleiro[0][2] == 1 )
 				tabuleiro[2][0] = 2;
 			else if ( tabuleiro[2][0] == 1 )
 				tabuleiro[0][2] = 2;
 			else if ( tabuleiro[2][2] == 1 )
 				tabuleiro[0][0] = 2;
 				
 			tabuleiroAtual ( tabuleiro );		// Mostrar tabuleiro
 			jogarHuman ( tabuleiro );			// Vez da pessoa jogar
 			system("cls");						// Limpar tela
 			tabuleiroAtual ( tabuleiro );		// Mostrar tabuleiro
 			
 			padraoWinLoseDraw ( tabuleiro );	// Jogadas padrões ( buscar vitório, buscar derrota, buscar empate )	
 				
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
 
 void tabuleiroAtual( int tabuleiro[3][3] ){		// Mostrar o andamento do tabuleiro
 	puts("\n");
 	printf("      %d | %d | %d", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);	// Linha 1 da matriz
 	puts("\n    -------------");		
 	printf("      %d | %d | %d", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);	// Linha 2 da matriz
 	puts("\n    -------------");
 	printf("      %d | %d | %d", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);	// Linha 3 da matriz
 }
 
 void jogarHuman(int tabuleiro[3][3]){ 		// Função para receber jogada da pessoa via input
 	
 	int autenticacao = 0;					// Controle do do while
 	int jogada = 0;							// recebe posição do tabuleiro, digitado pela pessoa
 	
 	do{			
 		puts("\n\n    [SUA VEZ!]");
 		scanf("%d", &jogada);				// recebe posição do tabuleiro, digitado pela pessoa
 		autenticacao = 0;					// Controle do while
 		
 		switch(jogada){ 					// Restringir jogada, dependendo da condição da casa escolhida (livre ou ocupada)
 		case 1:
 			if (tabuleiro[0][0] == 0 )		// Condição para verificar ocupação do tabuleiro ( 0 = livre )
 				tabuleiro [0][0] = 1;		// Matriz: Linha 1 Coluna 1
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
 		break;
 		
 		case 2:
 			if (tabuleiro[0][1] == 0 )
 				tabuleiro [0][1] = 1;		// Matriz: Linha 1 Coluna 2
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 3:
 			if (tabuleiro[0][2] == 0 )
 				tabuleiro [0][2] = 1;		// Matriz: Linha 1 Coluna 3
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 4:
 			if (tabuleiro[1][0] == 0 )
 				tabuleiro [1][0] = 1;		// Matriz: Linha 2 Coluna 1
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 5:
 			if (tabuleiro[1][1] == 0 )
 				tabuleiro [1][1] = 1;		// Matriz: Linha 2 Coluna 2
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 6:
 			if (tabuleiro[1][2] == 0 )
 				tabuleiro [1][2] = 1;		// Matriz: Linha 2 Coluna 3
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 7:
 			if (tabuleiro[2][0] == 0 )
 				tabuleiro [2][0] = 1;		// Matriz: Linha 3 Coluna 1
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 8:
 			if (tabuleiro[2][1] == 0 )
 				tabuleiro [2][1] = 1;		// Matriz: Linha 3 Coluna 2
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 9:
 			if (tabuleiro[2][2] == 0 )
 				tabuleiro [2][2] = 1;		// Matriz: Linha 3 Coluna 3
 			else{
 				puts("Posição inválida");
 				autenticacao = 1;
			 }
		break;
 		default:
 			printf ("Está posição não existe");		// Caso a posição digitada não exista ( matriz )
 			autenticacao = 1;
 			
		}
		
	} while ( autenticacao != 0 );
	
 }
 
 int procurarPerca (int tabuleiro[3][3], int codVencedor, int codPerdedor){
 	
 		// ##### VERIFICAR HORIZONTAL LINHA 1 #####
 		
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
 		
 		// ##### VERIFICAR DIAGONAL 1 #####
 		
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
 		
 		// ##### VERIFICAR DIAGONAL 2 #####
 		
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
 		
 		// ##### VERIFICAR HORIZONTAL LINHA 2 #####
 		
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
 		
 		// ##### VERIFICAR HORIZONTAL LINHA 3 #####
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
 		
 		//  ##### VERIFICAR VERTICAL COLUNA 1 #####
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
 		
 		// ##### VERIFICAR VERTICAL COLUNA 2 #####
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
 		
 		// ##### VERIFICAR VERTICAL COLUNA 3 #####
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
 
 void jogarAleatorio (int tabuleiro[3][3]){			// Realizar uma jogada aleatória
 	
 	for( int i = 0; i < 3; i++ ){ 					// Buscar posição livre
		for( int x = 0; x < 3; x++ ){
			if( tabuleiro[x][i] == 0 ){
				tabuleiro[x][i] = 2;
				return;
			}	
		}
 	}
 }
 
 int progressoTabuleiro (int tabuleiro[3][3]){		// Verificação para saber se o jogo já terminou
 	
 	for( int i = 0; i < 3; i++ ){ 					// Caso acho um espaço vazio, o jogo continua
		for( int x = 0; x < 3; x++ ){
			if( tabuleiro[x][i] == 0 )
				return 0;
		}
 	}
 	
 	return 1;										// Caso não ache espaço vazio, o jogo termina
 	
 }
 
 void jogarDiagonal ( int tabuleiro[3][3] ) {		// Realiza uma jogada na diagonal, de acordo com a jogada da pessoa
 	if ( tabuleiro[0][1] == 1 ){
 		if ( tabuleiro[0][0] == 0 )
 			tabuleiro[0][0] = 2;
 		else
 			tabuleiro[0][2] = 2;
 			
	 } else if ( tabuleiro[1][0] == 1 ) {
	 	if( tabuleiro[0][0] == 0 )
	 		tabuleiro[0][0] = 2;
	 	else
	 		tabuleiro[2][0] = 2;
	 } else if ( tabuleiro[1][2] == 1 ) {
	 	if( tabuleiro[0][2] == 0 )
	 		tabuleiro[0][2] = 2;
	 	else
	 		tabuleiro[2][2] = 2;
	 } else if ( tabuleiro[2][1]) {
	 	if ( tabuleiro[2][0] == 0)
	 		tabuleiro[2][0] = 2;
	 	else
	 		tabuleiro[2][2] = 2;
	 }
 }
 
 void padraoWinLoseDraw ( int tabuleiro[3][3] ){		// Jogadas comuns nas folhas, Procura posição de vítoria; derrota e empate
 	
 	while(1){
			 
	 	system("cls");
	 			
	 	int codVencedor = 2;
	 	int codPerdedor = 2;
	 	int condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor);	// Procurar vitória da CPU (retorna false se achar ou true se não achar)
	 			
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
				 
		if(condicional){			// Jogar aleatório (falta de jogadas)
			jogarAleatorio(tabuleiro);
		}
				 
		 tabuleiroAtual(tabuleiro);		// Mostrar tabuleiro
		 jogarHuman(tabuleiro);			// Pessoa joga
				 
		int terminoJogo = progressoTabuleiro( tabuleiro );		// Guardar resposta do possível término do jogo
				 
		if(terminoJogo){ 	// Verificar se o jogo terminou com empate
			system("cls");
			tabuleiroAtual(tabuleiro);	// mostrar tabuleiro
			puts("\n\n    [EMPATOU!]");
	 		break;
		}

 	}
 }
