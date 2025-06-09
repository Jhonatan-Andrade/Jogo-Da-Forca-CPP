#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#include "user.cpp"
#include "getWord.cpp"

char player01[20];
char player02[20];

int highScorePlayer01;
int highScorePlayer02;
bool roundPlayer = true;

void clearScreen() {
	#if defined(_WIN32)
		system("cls");
	#elif defined(_WIN64)
		system("cls");
	#elif defined(__linux__)
		system("clear");
	#elif defined(__APPLE__) && defined(__MACH__)
		system("clear");
	#elif defined(__unix__)
		system("clear");
	#else
		system("clear");
	#endif
}

int roundGame(const char *word, const char* nameTheme) {

	// Array que vai receber as letras corretas.

	int size = strlen(word);
	char secretWord[size+1];
	int tentativas = 0;
	int acertos = 0;
	char lyricsList[size+7];
	int lyricsListsize = sizeof(lyricsList)/sizeof(lyricsList[0]);
	char lyrics;
	int gameRound = 0;

	int highScore = size;

	// Colocando um espaço em branco para  cada posição da lista.
	for(int i = 0; i < size; i++) {
		secretWord[i] = 32;
	}
	secretWord[size] = '\0';
	lyricsList[lyricsListsize] = '\0';
	for(int i = 0 ; i<lyricsListsize; i++)lyricsList[i] = 32;


	// Loop do game.

	// Em uma jogo da forca a cada erro, remove um membro do boneco .
	// 2:pernas + 2:braços + 1:corpo + 1:cabeça = 6.

	// Uma palavra com 4 caracteres só pode ter 4 acertos.


	while(tentativas < 6 && acertos < size) {

		//Cantador de erros.
		printf("\n\n\tTentativas : %d/6", 6 - tentativas);


		//Informar o tema escolhido.
		printf("\n\tTema : %s  \n\n",nameTheme);

		//Mostrar as letras descobertas.
		printf("\t");
		for(int i = 0; i < size; i++) {
			printf("%c   ", secretWord[i]);
		}

		//Mostrar tamanho da palavra.
		printf("\n\t");
		for(int i = 0; i < size; i++) {
			printf("__  ");
		}
		printf("\n\t");
		for(int i = 1; i < size+1; i++) {
			if(i<10) {
				printf("0%d  ",i);
			} else {
				printf("%d  ",i);
			}
		}

		//Mostrar as letras digitadas.
		printf("\n\n\tLetras digitadas.\n\t");

		for(int i = 0; i < lyricsListsize; i++) {
			if(lyricsList[i] != 32) {
				printf("%c  ",lyricsList[i]);
			}
		}
		// Interação com o jogador.
		printf("\n\tDigite uma letra:");
		scanf(" %c", &lyrics);
		clearScreen();
		printf("\n\n\n");
		
		
		// Converte para maiuscula.
		lyrics = toupper(lyrics);
        

		//Verificar se a letra digitada existe na palavra.
		int acertou = 0;
		for( int i = 0; i < size; i++) {

			if(toupper(word[i]) == lyrics && secretWord[i] == 32) {
				secretWord[i] = lyrics;
				acertos++;
				acertou = 1;
			}
		}

		//Guardando as letras digitadas.
		lyricsList[gameRound] = lyrics;
		gameRound++;

		//Feedback para o jogodor.
		if(!acertou) {
			highScore--;
			tentativas++;
		}
		clearScreen();

	}

	// Fim do Game.
	if(acertos == size) {
		getchar();
		if(roundPlayer) {
			highScorePlayer01 += highScore;
			roundPlayer = false;
		} else {
			highScorePlayer02 += highScore;
			roundPlayer = true;
		}
		return 1;
	} else {
		getchar();
		if(roundPlayer) {
			highScorePlayer01 = highScore;
			roundPlayer = false;
		} else {
			highScorePlayer02 = highScore;
			roundPlayer = true;
		}
		return 0;
	}

}

void highScoreScreen() {
	printf("\n\t%s:%d",player01,highScorePlayer01);
	printf("    ");
	printf("%s:%d\n\n",player02,highScorePlayer02);
}

int game() {
    clearScreen();
	bool p1c = true ; 
	int errp1 = 0;
	while (p1c){
		if (errp1 == 0){printf("\n\tNome do primeiro player : ");}

	    scanf("%s",player01);
		User user = searchUniqueUser(player01);
    	if (strcmp(user.name, "") == 0) {
			if (errp1 == 0){printf("\tPlayer01 nao encontrado\n");}
    	} else {p1c = false;errp1++;}
	}
	clearScreen();
	bool p2c = true ; 
	int errp2 = 0;
	while (p2c){
		if (errp2 == 0){printf("\n\tNome do segundo player : ");}
		scanf("%s",player02);
		User user = searchUniqueUser(player02);
		if (strcmp(user.name, "") == 0) {
			if (errp2 == 0){printf("\tPlayer02 nao encontrado\n");}
		} else {p2c = false;errp2++;}
	}
	
	while(true) {
	    //Limpa a tela e mostra os pontos.
		clearScreen();
		highScoreScreen();
		
		//alternando entre os jogadores
		if(roundPlayer) {
			printf("\n\tSua vez  %s.",player01);
		} else {
			printf("\n\tSua vez  %s.",player02);
		}
        // gerar a palavra.
		ResGetWord data = getWord();
		highScoreScreen();
		
		//iniciar a jogada.
		int res = roundGame(data.word,data.nameTheme);
		
		// Feedback da jogada.
		clearScreen();
		if(res) {
			if(roundPlayer) { 
				printf("\n\n\tParabéns! %s Você venceu! \n\tA palavra era: %s",player02,data.word);} 
			else{printf("\n\n\tParabéns! %s Você venceu! \n\tA palavra era: %s",player01,data.word);}
		} else {
			if(roundPlayer) {
				printf("\n\n\tVocê perdeu %s talvez na proxima. \n\tA palavra era: %s",player02,data.word);} 
			else {printf("\n\n\tVocê perdeu %s talvez na proxima. \n\tA palavra era: %s",player01,data.word);}
		}

		// Perguntar se o usuário deseja jogar novamente ou encerrar com ESC
		printf("\n\n\tENTER     : Próxima jogada");
		printf("\n\tESC+ENTER : Sair/Salvar\n\t");


		int ch = getchar();
		if (ch == 27) {break;}
		while (ch != '\n' && ch != EOF) {ch = getchar();}

	}
	clearScreen();
		


	//Mostra quem ganhou
	if(highScorePlayer01>highScorePlayer02){

	    highScoreScreen();
	    printf("\n\tParabéns! %s Você venceu!\n\n",player01);
		addPoints(player01,highScorePlayer01);
		addPoints(player02,highScorePlayer02);


	}else if(highScorePlayer01<highScorePlayer02){

	    highScoreScreen();
	    printf("\n\tParabéns! %s Você venceu!\n\n",player02);
		addPoints(player01,highScorePlayer01);
		addPoints(player02,highScorePlayer02);

	}else if(highScorePlayer01 == highScorePlayer02){

	    highScoreScreen();
	    printf("\n\tEmpate!!!\n\n");
		addPoints(player01,highScorePlayer01);
		addPoints(player02,highScorePlayer02);
	}

}

void showRanking(){
	printf("\n\n");
	clearScreen();

	Users users = searchAllUser();
	// Ordenar usuários do maior para o menor com base nos pontos
	for (int i = 0; i < users.numberUser - 1; i++) {
		for (int j = i + 1; j < users.numberUser; j++) {
			if (users.users[j].point > users.users[i].point) {
				User temp = users.users[i];
				users.users[i] = users.users[j];
				users.users[j] = temp;
			}
		}
	}
	// Exibir ranking ordenado
	for (int i = 0; i < users.numberUser; i++) {
		int indexTest = strlen(users.users[i].name);
		int pstUser = i+1;
		if (pstUser < 10) { printf("\n\t "); }else{printf("\n\t");}
		printf("%dº", pstUser);
		printf(" %s", users.users[i].name);
		int loopV = 15;
		if (users.users[i].point < 1000) { loopV = 21 - indexTest; }
		if (users.users[i].point < 100) { loopV = 22 - indexTest; }
		for (size_t k = 0; k < loopV; k++) { printf(" "); }
		printf("%d", users.users[i].point);
	}
	printf("\n\n\tPressione ENTER para voltar...");
	getchar();getchar();
}

void createUser(){
	printf("\n\n");
	clearScreen();

	bool userExit = true;
	Users users = searchAllUser();

	
	while (userExit)
	{
		char playerName[100]; 
		printf("\n\tCriar player");
		printf("\n\tDigite o nome do player: ");
		scanf("%99s", playerName); 
		int found = 0;
		for(int i = 0; i < users.numberUser; i++) {
			if (strcmp(users.users[i].name, playerName) == 0) {
				clearScreen();
				printf("\n\tUsuario já existe: %s\n", users.users[i].name);
				found = 1;
				break;
			}
		}
		if (!found) {
			createUser(playerName);
			userExit = false;
		}
	}
}

int main() {
	while (true){
		clearScreen();
		int optn;
		printf("\n\t[ 1 ]Ver  classificação");
		printf("\n\t[ 2 ]Criar  Player");
		printf("\n\t[ 3 ]Jogar");
		printf("\n\n\n\n\t");
		scanf("%d",&optn);

		switch (optn){
		case 1:showRanking();
		break;
		case 2:createUser();
		break;
		case 3:game();
		break;
		}
	}
    


}