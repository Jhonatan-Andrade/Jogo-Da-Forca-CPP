#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>



typedef struct {
	const char *word;
	const char *nameTheme;
} ResGetWord;

void clearScreenInGetWord() {
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


const char* nameTheme;

ResGetWord getWord() {


	// Lista de temas e palavras
	const char *themes[] = {"Frutas", "Animais", "Country","Cores","Profissões","objetos","esportes","comidas","filmes","meios de transporte"};
	const char *fruits[] = {"abacaxi", "melancia", "morango", "banana", "uva"};
	const char *animals[] = {"elefante", "girafa", "jacare", "tigre", "cachorro"};
	const char *country[] = {"brasil", "canada", "japao", "argentina", "egito"};
	const char *color[] = {"Rosa","Vermelho","Roxo","Azul","Verde","Preto"};
	const char *professions[] = {"Médico","Professor","Engenheiro","Programador","Advogado"};
	const char *objects[] = {"Relógio","Cadeira","Janela","Mochila","Tesoura"};
	const char *sports[] = {"Futebol","Basquete","Vôlei","Natação","Tênis"};
	const char *food[] = {"Lasanha","Pizza","Sushi","Feijoada","Hambúrguer"};
	const char *films[] = {"Titanic","Avatar","Shrek","Gladiador","Frozen"};
	const char *meansOfTransport[] = {"Carro","Avião","Onibus","Bicicleta","Trem"};

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
			clearScreenInGetWord();
			printf("\n\t%d : não é uma opção. ",idTheme);
		} else {

			// Escolha da palavra com base no tema
			const char *word;
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
			clearScreenInGetWord();

            ResGetWord data;
            data.word = word;
            data.nameTheme = nameTheme;
			return data;
		}
	}
}

