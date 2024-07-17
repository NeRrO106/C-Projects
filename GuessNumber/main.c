#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int level, lives, number, max_number;
	srand(time(NULL));
	printf("Alege un nivel de joc(1, 2, 3):\n");
	printf("Nivel 1 - 3 incercari numarul este intre 0 si 20\n");
	printf("Nivel 2 - 5 incercari numarul este intre 0 si 50\n");
	printf("Nivel 3 - 10 incercari numarul este intre 0 si 100\n");
	scanf("%d",&level);
	switch(level){
		case 1:
			lives = 3;
			number = rand() % 21;
			max_number = 20;
			break;
		case 2:
			lives = 5;
			number = rand() % 51;
			max_number = 50;
			break;
		case 3:
			lives = 10;
			number = rand () % 101;
			max_number = 100;
			break;
		default:
			printf("Nivelul ales nu este valid\n");
			return 1;
	}
	printf("Ai ales level: %d sa incepem\n", level);
	while(lives > 0){
		int guess;
		printf("Ai %d incercari disponibile\n", lives);
		printf("Introdu un numar:\n");
		scanf("%d", &guess);
		if(guess < 0 || guess > max_number){
			printf("Numarul nu este in intervalul permis(0 - %d)\n", max_number);
			continue;
		}
		if(guess == number){
			printf("Felicitari ai ghicit numarul\n");
			break;
		}
		else if(guess < number){
			printf("Numarul introdus este mai mic\n");
		}
		else{
			printf("Numarul introdus este mai mare\n");
		}
		lives--;
	}
	if(lives == 0){
		printf("Ai epuizat toate incercarile, numarul corect era: %d\n", number);
	}
	return 0;
}
