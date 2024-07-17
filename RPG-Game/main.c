#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct{
	char nume[50];
	int hp;
	int attack;
	int deffend;
	int exp;
	int level;
	int x;
	int y;
}Player;

typedef struct{
	char nume[50];
	int hp;
	int attack;
	int deffend;
	int exp_reward;
	int x;
	int y;
}Enemy;

typedef struct{
	char nume_Item[50];
	int value;
	int x;
	int y;
}Item;

typedef struct{
	char nume[50];
	int value;
}Inventory;

typedef struct{
	char map[10][10];
}Map;

Player player;
Enemy enemies[10];
Item items[20];
Inventory inventar[5];
Map map;

int inventar_Index =0;

void combat();
void levelUp();
void takeItem();

void initializeGame(){
	//player
	strcpy(player.nume, "Hero");
	player.hp = 100;
	player.attack = 15;
	player.deffend = 5;
	player.exp = 10;
	player.level = 1;
	player.x = 1;
	player.y = 1;

	//enemies
	strcpy(enemies[0].nume, "Goblin");
	enemies[0].hp = 30;
	enemies[0].attack = 5;
	enemies[0].deffend = 2;
	enemies[0].exp_reward = 20;
	enemies[0].x = 3;
	enemies[0].y = 1;

	strcpy(enemies[1].nume, "Orc");
	enemies[1].hp = 50;
	enemies[1].attack = 10;
	enemies[1].deffend = 3;
	enemies[1].exp_reward = 40;
	enemies[1].x = 5;
	enemies[1].y = 7;

	//items
	strcpy(items[0].nume_Item, "HealthPotion");
	items[0].value = 20;
	items[0].x = 2;
	items[0].y = 3;

	strcpy(items[1].nume_Item, "ManaPotion");
	items[1].value = 15;
	items[1].x = 4;
	items[1].y = 5;

	//maps
	char tempMap[10][10] = {
      	 {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
       	 {'#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
       	 {'#', '.', '#', '.', '#', '.', '#', '#', '.', '#'},
       	 {'#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
       	 {'#', '.', '#', '#', '#', '#', '.', '#', '.', '#'},
       	 {'#', '.', '.', '.', '.', '#', '.', '#', '.', '#'},
       	 {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#'},
       	 {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#'},
       	 {'#', '.', '#', '#', '.', '.', '.', '#', '.', '#'},
       	 {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    	};

	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			map.map[i][j] = tempMap[i][j];
		}
	}

	map.map[player.y][player.x] = 'P';
	map.map[enemies[0].y][enemies[0].x] = 'E';
	map.map[enemies[1].y][enemies[1].x] = 'E';
	map.map[items[0].y][items[0].x] = 'I';
	map.map[items[1].y][items[1].x] = 'I';
}

void displayStat(){
	printf("Player: %s\n", player.nume);
	printf("Health: %d\n", player.hp);
	printf("Attack: %d\n", player.attack);
	printf("Defense: %d\n", player.deffend);
	printf("Exp: %d\n", player.exp);
	printf("Level: %d\n", player.level);

	printf("\n");

	for(int i = 0; i < 2; i++){
		printf("Enemy %d: %s\n", i+1, enemies[i].nume);
		printf("Health: %d\n", enemies[i].hp);
		printf("Attack: %d\n", enemies[i].attack);
		printf("Defense: %d\n", enemies[i].deffend);
		printf("Exp reward: %d\n", enemies[i].exp_reward);
	}

	printf("\n");

	for(int i = 0; i < 2; i++){
		printf("Item %d: %s\n", i+1, items[i].nume_Item);
		printf("Value: %d\n", items[i].value);
	}

	printf("\n");
}
void displayMap(){

        char tempMap[10][10] = {
         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
         {'#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
         {'#', '.', '#', '.', '#', '.', '#', '#', '.', '#'},
         {'#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
         {'#', '.', '#', '#', '#', '#', '.', '#', '.', '#'},
         {'#', '.', '.', '.', '.', '#', '.', '#', '.', '#'},
         {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#'},
         {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#'},
         {'#', '.', '#', '#', '.', '.', '.', '#', '.', '#'},
         {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
        };

        for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){
                        map.map[i][j] = tempMap[i][j];
                }
        }

        map.map[player.y][player.x] = 'P';
        map.map[enemies[0].y][enemies[0].x] = 'E';
        map.map[enemies[1].y][enemies[1].x] = 'E';
	if(items[0].value > 0){
        	map.map[items[0].y][items[0].x] = 'I';
	}
	if(items[1].value > 0){
        	map.map[items[1].y][items[1].x] = 'I';
	}


	printf("Map: \n");
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			printf("%c", map.map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void movePlayer(int direction){
	int newX = player.x;
	int newY = player.y;

	switch(direction){
		case 1://UP
			newY--;
			break;
		case 2://down
			newY++;
			break;
		case 3://left
			newX--;
			break;
		case 4://right
			newX++;
			break;
		default:
			printf("Directie invalida!\n");
			return;
	}
	if(newX >= 0 && newX < 10 && newY >= 0 && newY < 10 && map.map[newY][newX] != '#'){
		for(int i = 0; i < 10; i++){
			if(enemies[i].x == newX && enemies[i].y == newY){
				printf("Ai intalnit un inamic!\n");
			}
		}
		for(int i = 0; i < 20; i++){
			if(items[i].x == newX && items[i].y == newY){
				printf("Ai gasit un obiect: %s!\n", items[i].nume_Item);
			}
		}
		map.map[player.y][player.x] = '.';
		player.x = newX;
		player.y = newY;
		map.map[player.y][player.x] = 'P';
	}
	else{
		printf("Nu poti merge in acea directie!\n");
	}
}
void combat(){
	int enemyIndex = -1;
	for(int i = 0; i < 10; i++){
		if(enemies[i].x == player.x && enemies[i].y == player.y){
			enemyIndex = i;
			break;
		}
	}
	if(enemyIndex == -1){
		printf("Nu este niciun inamic aici!\n");
		return;
	}

	while(player.hp > 0 && enemies[enemyIndex].hp > 0){
		int damageToEnemy = player.attack - enemies[enemyIndex].deffend;
		if(damageToEnemy < 0) damageToEnemy = 1;
		enemies[enemyIndex].hp -= damageToEnemy;
		printf("Ai lovit %s cu %d damage!\n", enemies[enemyIndex].nume, damageToEnemy);

		if(enemies[enemyIndex].hp <=0){
			printf("Ai invins %s!\n", enemies[enemyIndex].nume);
			player.exp += enemies[enemyIndex].exp_reward;
			if(player.exp >= player.level * 10){
				levelUp();
			}
			map.map[enemies[enemyIndex].y][enemies[enemyIndex].x] = '.';
			enemies[enemyIndex].x = enemies[enemyIndex].y = -1;
			return;
		}
		int damageToPlayer = enemies[enemyIndex].attack - player.deffend;
		if(damageToPlayer < 0) damageToPlayer = 1;
		player.hp -= damageToPlayer;
		printf("%s te-a lovit cu %d damage!\n", enemies[enemyIndex].nume, damageToPlayer);

		if(player.hp <= 0){
			printf("Ai fost invins!\n");
			return;
		}
	}
}

void takeItem(){
	for(int i = 0; i < 20; i++){
       		if(items[i].x == player.x && items[i].y == player.y){
			inventar[inventar_Index].value = items[i].value;
			strcpy(inventar[inventar_Index].nume, items[i].nume_Item);
			inventar_Index++;
			map.map[items[i].y][items[i].x] = '.';
		        items[i].x = items[i].y = -1;
			items[i].value = -1;
			break;
        	}
	}
}
void manageInventory(){
	printf("Inventarul tau:\n");
	for(int i = 0; i < inventar_Index; i++){
		if(inventar[i].value > 0){
			printf("%s - Valoare: %d\n", inventar[i].nume, inventar[i].value);
		}
	}
	printf("Alege un obiect de folosit(0 pentru a iesi): ");
	int choice;
	scanf("%d", &choice);
	if(choice > 0 && choice <= inventar_Index && inventar[choice-1].value > 0){
		printf("Ai folosit %s. \n", inventar[choice - 1].nume);
		if(strcmp(inventar[choice-1].nume, "HealthPotion") == 0){
			player.hp += inventar[choice-1].value;
		}
		if(strcmp(inventar[choice-1].nume, "ManaPotion") == 0){
			player.deffend += inventar[choice-1].value;
		}
		inventar[choice-1].value = 0;
		if(choice < inventar_Index){
			for(int i = 0; i < 5; i++){
				inventar[i] = inventar[i+1];
			}
		}
	}
	else{
		printf("Alegere invalida!\n");
	}
}
void levelUp(){
	player.level ++;
	player.hp += 20;
	player.attack += 5;
	player.deffend += 3;
	player.exp = 0;

	printf("Ai avansat la nivelul %d! \n", player.level);
	printf("Hp-ul este acum %d. \n", player.hp);
	printf("Atacul tau este acum %d. \n", player.attack);
	printf("Apararea ta este acum %d. \n", player.deffend);
}
void saveGame(){
	FILE *file;
	file = fopen("savegame.txt", "w");
	if(file == NULL){
		printf("Eroare la deschiderea fisierului.\n");
		return;
	}
	fprintf(file, "%s %d %d %d %d %d %d %d\n",player.nume, player.hp, player.attack, player.deffend, player.exp, player.level, player.x, player.y);

	for(int i = 0; i < 10; i++){
		if(enemies[i].hp > 0){
			fprintf(file, "%s %d %d %d %d %d %d\n", enemies[i].nume, enemies[i].hp, enemies[i].attack, enemies[i].deffend, enemies[i].exp_reward, enemies[i].x, enemies[i].y);
		}
	}
	for(int i = 0; i < 20; i++){
		if(items[i].value > 0){
			fprintf(file, "%s %d %d %d\n", items[i].nume_Item, items[i].value, items[i].x, items[i].y);
		}
	}

	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			fprintf(file, "%c", map.map[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
	printf("Jocul a fost salvat cu succes");
}

void loadGame(){
	FILE *file = fopen("savegame.txt", "r");
	if(file == NULL){
		printf("Nu a fost gasit niciun fisier.\n");
		return;
	}

	fscanf(file, "%s %d %d %d %d %d %d %d\n", player.nume, &player.hp, &player.attack, &player.deffend, &player.exp, &player.level, &player.x, &player.y);


	for(int i = 0; i < 10; i++){
		fscanf(file, "%s %d %d %d %d %d %d\n", enemies[i].nume, &enemies[i].hp, &enemies[i].attack, &enemies[i].deffend, &enemies[i].exp_reward, &enemies[i].x, &enemies[i].y);
	}

	char line[100];

    	for (int i = 0; i < 20; i++) {
        	fgets(line, sizeof(line), file);
        	if (strncmp(line, "HealthPotion", 12) == 0) {
            		sscanf(line, "HealthPotion %d %d %d\n", &items[0].value, &items[0].x, &items[0].y);
        	} else if (strncmp(line, "ManaPotion", 10) == 0) {
            		sscanf(line, "ManaPotion %d %d %d\n", &items[1].value, &items[1].x, &items[1].y);
        	}
    	}

	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			fscanf(file, "%c", &map.map[i][j]);
		}
	}
	fclose(file);
	printf("Joc incarcat cu succes.\n");
}
void loadMenu(){
	int choice;
	do{
		printf("\n=== MENIU ===\n");
		printf("1. Muta jucatorul in sus\n");
		printf("2. Muta jucatorul in jos\n");
		printf("3. Muta jucatorul in stanga\n");
		printf("4. Muta jucatorul in dreapta\n");
		printf("5. Combat\n");
		printf("6. Inventar\n");
		printf("7. Load Game\n");
		printf("8. Save Game\n");
		printf("9. Take Item\n");
		printf("0. Iesire din joc\n");
		printf("============\n");
		printf("Introdu optiunea: ");
		scanf("%d", &choice);
		getchar();

		switch(choice){
			case 1:
				movePlayer(1);
				displayMap();
				break;
			case 2:
				movePlayer(2);
				displayMap();
				break;
			case 3:
				movePlayer(3);
				displayMap();
				break;
			case 4:
				movePlayer(4);
				displayMap();
				break;
			case 5:
				combat();
				displayStat();
				displayMap();
				break;
			case 6:
				manageInventory();
				displayMap();
				break;
			case 7:
				loadGame();
				displayStat();
				displayMap();
				break;
			case 8:
				saveGame();
				break;
			case 9:
				takeItem();
				displayStat();
				displayMap();
				break;
			case 10:
				displayStat();
				break;
			case 0:
				printf("Jocul a fost inchis!\n");
				break;
			default:
				printf("Optiunea invalida!");
				break;
		}
		printf("\n");
	}while(choice != 0);
}
int main(){
	initializeGame();
	displayStat();
	displayMap();
	loadMenu();
	return 0;
}
