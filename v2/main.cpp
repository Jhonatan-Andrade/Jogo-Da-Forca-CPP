#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

char player01[20];
char player02[20];

int highScorePlayer01;
int highScorePlayer02;
bool roundPlayer = true;


char* nameTheme;
  // função  de limpar telas
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

int game(char *word,char* nameTheme) {

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
		printf("\n\n\tDigite uma letra: ");
		scanf(" %c", &lyrics);
		
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
			highScorePlayer01 = highScore;
			roundPlayer = false;
		} else {
			highScorePlayer02 = highScore;
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

char* getWord() {


	// Lista de temas e palavras
	char *themes[] = {"Frutas", "Animais", "Country","Cores","Profissões","objetos","esportes","comidas","filmes","meios de transporte"};
	char *fruits[] = {"abacaxi", "melancia", "morango", "banana", "uva"};
	char *animals[] = {"elefante", "girafa", "jacare", "tigre", "cachorro"};
	char *country[] = {"brasil", "canada", "japao", "argentina", "egito"};
	char *color[] = {"Rosa","Vermelho","Roxo","Azul","Verde","Preto"};
	char *professions[] = {"Médico","Professor","Engenheiro","Programador","Advogado"};
	char *objects[] = {"Relógio","Cadeira","Janela","Mochila","Tesoura"};
	char *sports[] = {"Futebol","Basquete","Vôlei","Natação","Tênis"};
	char *food[] = {"Lasanha","Pizza","Sushi","Feijoada","Hambúrguer"};
	char *films[] = {"Titanic","Avatar","Shrek","Gladiador","Frozen"};
	char *meansOfTransport[] = {"Carro","Avião","Onibus","Bicicleta","Trem"};

	// Escolha do tema
	int idTheme;
	int numberOfThemes = sizeof(themes)/sizeof(themes[0]);

	while(true) {
		printf("\n\tEscolha um tema.\n");
		for(int i = 0 ; i<numberOfThemes; i++) {
			printf("\n\t%d:%s",i+1,themes[i]);
		}
		printf("\n\n\t");
		scanf("%d",&idTheme);

		if(!(idTheme <= numberOfThemes && idTheme>0 ) ) {

			// Informar ao jogador que a opção e invalida.
			clearScreen();
			printf("\n\t%d : não é uma opção. ",idTheme);
		} else {

			// Escolha da palavra com base no tema
			char *word;
			srand(time(NULL));
			switch(idTheme) {
			case 1 :
				word = fruits[rand() % 5];
				nameTheme = "frutas";
				break;
			case 2 :
				word = animals[rand() % 5];
				nameTheme = "animais";
				break;
			case 3 :
				word = country[rand() % 5];
				nameTheme = "paises";
				break;
			case 4 :
				word = color[rand() % 5];
				nameTheme = "cores";
				break;
			case 5 :
				word = professions[rand() % 5];
				nameTheme = "Profissões";
				break;
			case 6 :
				word = objects[rand() % 5];
				nameTheme = "objetos";
				break;
			case 7 :
				word = sports[rand() % 5];
				nameTheme = "esportes";
				break;
			case 8 :
				word = food[rand() % 5];
				nameTheme = "comidas";
				break;
			case 9 :
				word = films[rand() % 5];
				nameTheme = "filmes";
				break;
			case 10 :
				word = meansOfTransport[rand() % 5];
				nameTheme = "meios de transporte";
				break;
			default:
				word = "jhonatan";
				nameTheme = "Dev Name";
			}
			clearScreen();
			return word;
		}
	}
}

void highScoreScreen() {

	printf("\n\t%s:%d    %s:%d\n\n",player01,highScorePlayer01,player02,highScorePlayer02);
}

int main() {
	printf("\n\tNome do primeiro player : ");
	scanf("%s",player01);
	printf("\n\tNome do segundo player : ");
	scanf("%s",player02);

    //loop principal
    
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
		char* word = getWord();
		highScoreScreen();
		
		//iniciar a jogada.
		int res = game(word,nameTheme);
		
		// Feedback da jogada.
		if(res) {
			if(roundPlayer) {
				printf("\n\n\tParabéns! %s Você venceu! \n\tA palavra era: %s",player02,word);
			} else {
				printf("\n\n\tParabéns! %s Você venceu! \n\tA palavra era: %s",player01,word);
			}
		} else {
			if(roundPlayer) {
				printf("\n\n\tVocê perdeu %s talvez na proxima. \n\tA palavra era: %s",player02,word);
			} else {
				printf("\n\n\tVocê perdeu %s talvez na proxima. \n\tA palavra era: %s",player01,word);
			}
		}

        //iniciar a proxima jogada .
		printf("\n\n\tPrecione ENTER para proxima jogada");
		getchar();
		
		//printf("\n\n\t Ou precione (esc) para sair");

	}
	clearScreen();
	
	//Mostra quem ganhou
	if(highScorePlayer01>highScorePlayer02){
	    //Player01 Vence
	    printf("\n\n\tParabéns! %s Você venceu!",player01);
	}else if(highScorePlayer01<highScorePlayer02){
	    //Player02 Vence
	    printf("\n\n\tParabéns! %s Você venceu!",player02);
	}else if(highScorePlayer01 == highScorePlayer02){
	    //Empate
	    printf("\n\n\tEmpate!!!",player02);
	}
}
  
