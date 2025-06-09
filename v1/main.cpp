#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
	while(true) {
	    system("clear");
        char word[9]="jhonatan";
    	int size = strlen(word);
    	char secretWord[size+1];
    	
    	int tentativas = 0;
    	int acertos = 0;
    	
    	char lyricsList[size+7];
    	int lyricsListsize = sizeof(lyricsList)/sizeof(lyricsList[0]);
    	char lyrics;
    	
    	
    	int gameRound = 0;

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
            system("clear");
    		//Cantador de erros.
    		printf("\n\n\tTentativas : %d/6", 6 - tentativas);
    
    		//Mostrar as letras descobertas.
    		printf("\n\n\t");
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
            printf("\n\t");
    		for(int i = 0; i < lyricsListsize; i++) {
    			if(lyricsList[i] != 32) {
    				printf("%c  ",lyricsList[i]);
    			}
    		}
    		// Interação com o jogador.
    		printf("\n\n\tDigite uma letra: ");
    		scanf(" %c", &lyrics);
    		system("clear");
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
    			tentativas++;
    		}
    
    	}
	}
}
  