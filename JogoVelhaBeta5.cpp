#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

/* JOGO DA VELHA 
##IMPORTANTE##  1: HUMANO  2: COMPUTADOR   #####
EM DESENVOLVIMENTO
*/

/***********************************************/ 
/* Defini��o dos Registros                     */
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
/* Defini��o das Fun��es                       */
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
	int x, i; // �ndices
	int tabuleiro[3][3]; // Tabuleiro para o jogo da velha
	ARVORE *r = NULL;

	for( i = 0; i < 3; i++ ){ // Defini��o inicial da matriz em 0
		for( x = 0; x < 3; x++ )
			tabuleiro[x][i] = 0;
	}
	
	criarJogo ( &r, tabuleiro );
	
} // Final programa principal


/************************************************ 
 * Fun��es                                      *
 ************************************************/
 void criarJogo ( ARVORE **r, int tabuleiro[3][3] ){
 	    ARVORE *no = ( ARVORE * ) malloc ( sizeof( ARVORE )); 		// aloca novo espaco em mem�ria
        no->subd = NULL;                                 			// inicializa sub�rvore da direita
        no->sube = NULL;								 			// inicializa sub�rvore da esquerda
        no->info.id = 20;
        *r= no;                                         			// anterior aponta para novo registro
        analisarJogo( r ,no->info.id, tabuleiro );					// Envia o id
 }
 
 
 void jogar ( ARVORE **r, int id, int idAux, int tabuleiro[3][3]){
	
 	ARVORE *aux = *r;				// Auxiliar para percorrer �rvore
	 	
 	while( aux->info.id != id ){	// Buscar ID
 		
 		if(aux->info.id > id)		
 			aux = aux->sube;
 		else
 			aux = aux->subd;
	}	
 	
   	ARVORE *no = ( ARVORE * ) malloc ( sizeof( ARVORE )); // aloca novo espaco em mem�ria
   	no->info.id = idAux;
   	no->subd = NULL;									// inicializa sub�rvore da direita
   	no->sube = NULL;								 // inicializa sub�rvore da esquerda
   	*aux = *no;
   	

   	
   	analisarJogo( r ,no->info.id, tabuleiro );					// Envia o id
 }
 
 
 void analisarJogo ( ARVORE **r, int id, int tabuleiro[3][3] ){ // Analisar jogada posicionada na �rvore
 	
 	int idAux;				//  Vari�vel para pr�ximo no
 	int codVencedor;		// Vari�vel para procurar pontos de vit�rias ou derrotas CPU/HUMANO
 	int codPerdedor;		// Vari�vel para procurar pontos de vit�rias ou derrotas CPU/HUMANO
 	int condicional; 		// Return da fun��o para procurar perdedor ou ganhador (procurarPerca)
 	int terminoJogo = 0;	// Verifica se o jogo terminou
 	int cont = 0;
 	
 	switch( id ){ 		// Possibilidade de jogadas de acordo com o id da �rvore
 		case 5 :	// FOLHA
 			
 			while(1){
			 
	 			system("cls");
	 			
	 			codVencedor = 2;	// C�digo para verifica��o de ganhador/perdedor
	 			codPerdedor = 2;
	 			condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor);	// Procurar vit�ria da CPU (retorna false se achar ou true se n�o achar)
	 			
	 			if(condicional == 0){			// Vit�ria do computador
	 				tabuleiroAtual(tabuleiro);	// Mostrar tabuleiro
	 				puts("\n\n   [VOC� PERDEU!]");
	 				break;
				 }
	 				
	 			if(condicional){
	 				codVencedor = 1; 					// define a procura de quem ir� perder CPU ou PESSOA
	 				codPerdedor = 2;
	 				condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor); // Procurar ponto de derrota da CPU (retorna false se achar ou true se n�o achar)
				 }
				 
				 // Procurar diagonal que ganhe o jogo PROX
				 
				if(condicional){			// Jogar aleat�rio (falta de jogadas)
					jogarAleatorio(tabuleiro);
				}
				 
				 tabuleiroAtual(tabuleiro);		// Mostrar tabuleiro
				 jogarHuman(tabuleiro);			// Pessoa joga
				 
				 terminoJogo = progressoTabuleiro( tabuleiro );		// Guardar resposta do poss�vel t�rmino do jogo
				 
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
 			
 			if ( tabuleiro[0][0] == 1 || tabuleiro[0][2] == 1  || tabuleiro[2][0] == 1  || tabuleiro[2][2] == 1 ) // Condicional para definir pr�ximo passo na �rvore
 				idAux = 5;		
 			else
 				idAux = 15;
 			
 			jogar( r, id, idAux, tabuleiro); 			// Entra na �rvore para procurar pr�ximo passo
 			
 		break;
 		
 		case 15 :	// FOLHA
 			
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padr�es ( buscar vit�rio, buscar derrota, buscar empate )
 				
 		break;
 		
 		case 20 :
			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
			jogarHuman(tabuleiro);					// Vez da pessoa jogar
 			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
 			
 			if ( tabuleiro[1][1] != 0 )				// Raiz, determina caminho da �rvore ( se jogou meio ou n�o )
 				idAux = 10;				// SIM, jogou meio
 			else
 				idAux = 80;				// N�O jogou meio
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na �rvore para procurar pr�ximo passo
 				
 		break;
 		
 		case 80 :
 			system("cls");
 			tabuleiro [1][1] = 2; 					// PC joga
 			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
 			
 			if ( tabuleiro[0][0] == 1 || tabuleiro[0][2] == 1  || tabuleiro[2][0] == 1  || tabuleiro[2][2] == 1 ) // Condicional para definir pr�ximo passo na �rvore
 				idAux = 50;			// SIM, jogou diagonal
 			else
 				idAux = 90;			// N�O jogou diagonal
 			
 			jogar( r, id, idAux, tabuleiro);		// Entra na �rvore para procurar pr�ximo passo
 			
 		break;

 		case 90 :
 			system("cls");
 			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
 			jogarHuman(tabuleiro);					// Pessoa joga
 			tabuleiroAtual(tabuleiro);				// Mostrar tabuleiro
 			
 			codVencedor = 1;
 			codPerdedor = 0;
 			condicional = procurarPerca (tabuleiro, codVencedor, codPerdedor);		// Perde pr�ximo lance?
 			
 			if ( condicional == 0 )		// SIM, perde
 				idAux = 85;
 			else						// N�O perde
 				idAux = 95;
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na �rvore para procurar pr�ximo passo
 			
 		break;
 		
 		case 85 :	// FOLHA
 		
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padr�es ( buscar vit�rio, buscar derrota, buscar empate )
 			
 		break;
 		
 		case 95 :	// FOLHA
 			system("cls");
 			
 			jogarDiagonal( tabuleiro );				// Jogada de defesa do PC
 			tabuleiroAtual( tabuleiro );			// Mostrar tabuleiro
 			jogarHuman( tabuleiro );				// Vez da pessoa jogar
 			system("cls");							// Limpar tela
 			tabuleiroAtual( tabuleiro );			// Mostrar tabuleiro
 			
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padr�es ( buscar vit�rio, buscar derrota, buscar empate )
 			
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
 			else					// N�O jogou diagonal
 				idAux = 60;
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na �rvore para procurar pr�ximo passo
 			
 		break;
 		
 		case 40:
 			
 			codVencedor = 1;
 			codPerdedor = 0;
 			condicional = procurarPerca (tabuleiro, codVencedor, codPerdedor);		// Perde pr�ximo lance?
 			
 			if ( condicional == 0 )					// SIM, perde
 				idAux = 35;
 			else									// N�O perde
 				idAux = 45;
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na �rvore para procurar pr�ximo passo
 			
 		break;
 		
 		case 35:	// FOLHA
 			
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padr�es ( buscar vit�rio, buscar derrota, buscar empate )
 			
 		break;
 		
 		case 45:	// FOLHA
 			
 			system("cls");							// Limpar tela
 			tabuleiro[1][2] = 2;					// Vez do PC jogar
 			tabuleiroAtual ( tabuleiro );			// Mostrar tabuleiro
 			jogarHuman ( tabuleiro );				// Vez da pessoa jogar
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padr�es ( buscar vit�rio, buscar derrota, buscar empate )
 			
 		break;
 		
 		case 60 :
 			codVencedor = 1;
 			codPerdedor = 0;
 			condicional = procurarPerca (tabuleiro, codVencedor, codPerdedor);		// Perde pr�ximo lance?
 			
 			if ( condicional == 0 )			// SIM, perde
 				idAux = 55;
 			else							// N�O perde
 				idAux = 65;
 				
 			jogar( r, id, idAux, tabuleiro);		// Entra na �rvore para procurar pr�ximo passo
 		break;
 		
 		case 55 :	// FOLHA
 			
 			padraoWinLoseDraw ( tabuleiro );		// Jogadas padr�es ( buscar vit�rio, buscar derrota, buscar empate )
 			
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
 			
 			padraoWinLoseDraw ( tabuleiro );	// Jogadas padr�es ( buscar vit�rio, buscar derrota, buscar empate )	
 				
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
 
 void jogarHuman(int tabuleiro[3][3]){ 		// Fun��o para receber jogada da pessoa via input
 	
 	int autenticacao = 0;					// Controle do do while
 	int jogada = 0;							// recebe posi��o do tabuleiro, digitado pela pessoa
 	
 	do{			
 		puts("\n\n    [SUA VEZ!]");
 		scanf("%d", &jogada);				// recebe posi��o do tabuleiro, digitado pela pessoa
 		autenticacao = 0;					// Controle do while
 		
 		switch(jogada){ 					// Restringir jogada, dependendo da condi��o da casa escolhida (livre ou ocupada)
 		case 1:
 			if (tabuleiro[0][0] == 0 )		// Condi��o para verificar ocupa��o do tabuleiro ( 0 = livre )
 				tabuleiro [0][0] = 1;		// Matriz: Linha 1 Coluna 1
 			else{
 				puts("Posi��o inv�lida");
 				autenticacao = 1;
			 }
 		break;
 		
 		case 2:
 			if (tabuleiro[0][1] == 0 )
 				tabuleiro [0][1] = 1;		// Matriz: Linha 1 Coluna 2
 			else{
 				puts("Posi��o inv�lida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 3:
 			if (tabuleiro[0][2] == 0 )
 				tabuleiro [0][2] = 1;		// Matriz: Linha 1 Coluna 3
 			else{
 				puts("Posi��o inv�lida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 4:
 			if (tabuleiro[1][0] == 0 )
 				tabuleiro [1][0] = 1;		// Matriz: Linha 2 Coluna 1
 			else{
 				puts("Posi��o inv�lida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 5:
 			if (tabuleiro[1][1] == 0 )
 				tabuleiro [1][1] = 1;		// Matriz: Linha 2 Coluna 2
 			else{
 				puts("Posi��o inv�lida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 6:
 			if (tabuleiro[1][2] == 0 )
 				tabuleiro [1][2] = 1;		// Matriz: Linha 2 Coluna 3
 			else{
 				puts("Posi��o inv�lida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 7:
 			if (tabuleiro[2][0] == 0 )
 				tabuleiro [2][0] = 1;		// Matriz: Linha 3 Coluna 1
 			else{
 				puts("Posi��o inv�lida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 8:
 			if (tabuleiro[2][1] == 0 )
 				tabuleiro [2][1] = 1;		// Matriz: Linha 3 Coluna 2
 			else{
 				puts("Posi��o inv�lida");
 				autenticacao = 1;
			 }
			 
 		break;
 		
 		case 9:
 			if (tabuleiro[2][2] == 0 )
 				tabuleiro [2][2] = 1;		// Matriz: Linha 3 Coluna 3
 			else{
 				puts("Posi��o inv�lida");
 				autenticacao = 1;
			 }
		break;
 		default:
 			printf ("Est� posi��o n�o existe");		// Caso a posi��o digitada n�o exista ( matriz )
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
 
 void jogarAleatorio (int tabuleiro[3][3]){			// Realizar uma jogada aleat�ria
 	
 	for( int i = 0; i < 3; i++ ){ 					// Buscar posi��o livre
		for( int x = 0; x < 3; x++ ){
			if( tabuleiro[x][i] == 0 ){
				tabuleiro[x][i] = 2;
				return;
			}	
		}
 	}
 }
 
 int progressoTabuleiro (int tabuleiro[3][3]){		// Verifica��o para saber se o jogo j� terminou
 	
 	for( int i = 0; i < 3; i++ ){ 					// Caso acho um espa�o vazio, o jogo continua
		for( int x = 0; x < 3; x++ ){
			if( tabuleiro[x][i] == 0 )
				return 0;
		}
 	}
 	
 	return 1;										// Caso n�o ache espa�o vazio, o jogo termina
 	
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
 
 void padraoWinLoseDraw ( int tabuleiro[3][3] ){		// Jogadas comuns nas folhas, Procura posi��o de v�toria; derrota e empate
 	
 	while(1){
			 
	 	system("cls");
	 			
	 	int codVencedor = 2;
	 	int codPerdedor = 2;
	 	int condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor);	// Procurar vit�ria da CPU (retorna false se achar ou true se n�o achar)
	 			
	 	if(condicional == 0){
	 		tabuleiroAtual(tabuleiro);
	 		puts("\n\n   [VOC� PERDEU!]");
	 		break;
			}
	 				
	 	if(condicional){
	 		codVencedor = 1; 					// define a procura de quem ir� perder CPU ou PESSOA
	 		codPerdedor = 2;
	 		condicional = procurarPerca(tabuleiro, codVencedor, codPerdedor); // Procurar ponto de derrota da CPU (retorna false se achar ou true se n�o achar)
			}
				 
		 // Procurar diagonal que ganhe o jogo PROX
				 
		if(condicional){			// Jogar aleat�rio (falta de jogadas)
			jogarAleatorio(tabuleiro);
		}
				 
		 tabuleiroAtual(tabuleiro);		// Mostrar tabuleiro
		 jogarHuman(tabuleiro);			// Pessoa joga
				 
		int terminoJogo = progressoTabuleiro( tabuleiro );		// Guardar resposta do poss�vel t�rmino do jogo
				 
		if(terminoJogo){ 	// Verificar se o jogo terminou com empate
			system("cls");
			tabuleiroAtual(tabuleiro);	// mostrar tabuleiro
			puts("\n\n    [EMPATOU!]");
	 		break;
		}

 	}
 }
