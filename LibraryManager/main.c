#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct Carte{
	int id;
	char autor[100];
	char titlu[100];
	char ISBN[20];
	bool disponibil;
};
struct Utilizator{
	int id;
	char nume[100];
	int cartiImprumutate[10];
	int nrCartiImprumutate;
};
struct Imprumut{
	char numeUtilizator[100];
	char titluCarte[100];
	char dataImprumut[11];
	char dataRetur[11];
};

Carte carti[100];
int nr_Carti = 0;

Utilizator user[50];
int nr_Users = 0;

Imprumut imprumuturi[100];
int nr_Imprumuturi = 0;

void adaugaCarte(const char* autor, const char* titlu, const char* ISBN){
	if(nr_Carti >= 100){
		printf("S-a atins numarul maxim de carti.\n");
		return;
	}
	carti[nr_Carti].id = nr_Carti+1;
	strcpy(carti[nr_Carti].autor, autor);
	strcpy(carti[nr_Carti].titlu, titlu);
	strcpy(carti[nr_Carti].ISBN, ISBN);
	carti[nr_Carti].disponibil = true;
	nr_Carti++;
	printf("Carte adaugata cu succes. \n");
}
void stergeCarte(int id){
	if(id <= 0 || id > nr_Carti){
		printf("Id invalid.\n");
		return;
	}
	if(!carti[id-1].disponibil){
		printf("Cartea nu poate fi stearsa deoarece este imprumutata.\n");
		return;
	}
	for(int i = id-1; i< nr_Carti; i++){
		carti[i] = carti[i+1];
		carti[i].id = i+1;
	}
	nr_Carti--;
	printf("Carte stearsa cu succes");
}

char* convertToLower(char* lower, const char* original){
	int i = 0;
	while(original[i]){
		lower[i] = tolower(original[i]);
		i++;
	}
	lower[i] = '\0';
	return lower;
}

int cautareCarte(const char* titlu){
	int titluLen = strlen(titlu);
	char titluLower[titluLen + 1];

	convertToLower(titluLower, titlu);

	for(int i = 0; i< nr_Carti; i++){
		char titluCarteLower[100];
		convertToLower(titluCarteLower, carti[i].titlu);
		if(strcmp(titluCarteLower, titluLower) == 0){
			return i;
		}
	}
	return -1;
}

void adaugaUtilizator(const char* nume){
	if(nr_Users > 50){
		printf("S a atins numarul maxim de utilizatori\n");
		return;
	}
	user[nr_Users].id = nr_Users+1;
	strcpy(user[nr_Users].nume, nume);
	for(int i=0; i<10; i++){
		user[nr_Users].cartiImprumutate[i] = 0;
	}
	user[nr_Users].nrCartiImprumutate = 0;
	nr_Users++;
	printf("Utilizator adaugat cu succes\n");
}
void stergeUtilizator(int id){
	if(id < 0 || id > nr_Users){
		printf("Id invalid\n");
		return;
	}
	for(int i = id- 1; i < nr_Users; i++){
		user[i] = user[i+1];
		user[i].id =i+1;
	}
	nr_Users--;
	printf("User sters cu succes\n");
}

void imprumutareCarte(const char *titlu, const char* nume, const char* dataImprumut, const char* dataRetur){
	int id_carte = cautareCarte(titlu);
	if(id_carte == -1){
		printf("Cartea nu a fost gasita\n");
		return;
	}
	if(!carti[id_carte].disponibil){
		printf("Cartea dorita este deja imprumutata de altcineva.\n");
		return;
	}
	int id_User = -1;
	char numeLower[100];
	convertToLower(numeLower, nume);
	for(int i = 0; i < nr_Users; i++){
		char numeUser[100];
		convertToLower(numeUser, user[i].nume);
		if(strcmp(numeUser, numeLower) == 0){
			id_User = i;
		}
	}
	if(id_User == -1){
		printf("Userul nu a fost gasit.\n");
		return;
	}
	if(user[id_User].nrCartiImprumutate >=10){
		printf("Userul a atins numarul maxim de carti imprumutate\n");
		return;
	}
	carti[id_carte].disponibil = false;
	user[id_User].cartiImprumutate[user[id_User].nrCartiImprumutate] = carti[id_carte].id;
	user[id_User].nrCartiImprumutate++;

	strcpy(imprumuturi[nr_Imprumuturi].numeUtilizator, user[id_User].nume);
	strcpy(imprumuturi[nr_Imprumuturi].titluCarte, carti[id_carte].titlu);
	strcpy(imprumuturi[nr_Imprumuturi].dataImprumut, dataImprumut);
	strcpy(imprumuturi[nr_Imprumuturi].dataRetur, dataRetur);

	nr_Imprumuturi++;
	printf("Cartea %s a fost imprumutata cu succes de userul %s.\n",titlu, nume);
}
void returneazaCarte(const char* titlu, const char* nume){
	int id_carte = cautareCarte(titlu);
	if(id_carte == -1){
		printf("Cartea nu a fost gasita.\n");
		return;
	}
	if(carti[id_carte].disponibil){
		printf("Cartea nu a fost imprumutata.\n");
		return;
	}
	int id_User = -1;
	char numeLower[100];
	convertToLower(numeLower, nume);
	for(int i = 0; i < nr_Users; i++){
		char numeUser[100];
		convertToLower(numeUser, user[i].nume);
		if(strcmp(numeLower, numeUser) == 0){
			id_User = i;
			break;
		}
	}

	int id_Imprumut = -1;
	for(int i = 0; i < nr_Imprumuturi; i++){
		if(strcmp(imprumuturi[i].numeUtilizator, user[id_User].nume) == 0 && strcmp(imprumuturi[i].titluCarte, carti[id_carte].titlu) == 0){
			id_Imprumut = i;
			break;
		}
	}

	int pos_Carte = -1;
	for(int i = 0; i < user[id_User].nrCartiImprumutate; i++){
		if(user[id_User].cartiImprumutate[i] == carti[id_carte].id){
			pos_Carte = i;
			break;
		}
	}

	for(int i = pos_Carte; i < user[id_User].nrCartiImprumutate - 1; i++){
		user[id_User].cartiImprumutate[i] = user[id_User].cartiImprumutate[i+1];
	}
	for(int i = id_Imprumut; i < nr_Imprumuturi - 1; i++){
		imprumuturi[i] = imprumuturi[i+1];
	}
	user[id_User].nrCartiImprumutate--;
	carti[id_carte].disponibil = true;
	nr_Imprumuturi--;
	printf("Cartea %s a fost returnata cu succes de %s\n",titlu, nume);
}
void listeazaCarti(int id){
	if(id == -1){
		if(nr_Carti == 0){
			printf("Nu exista carti inregistrate.\n");
			return;
		}
		printf("Lista cartilor din biblioteca:\n");
		for(int i = 0; i < nr_Carti; i++){
			printf("ID: %d\n", carti[i].id);
			printf("Titlu: %s\n", carti[i].titlu);
			printf("Autor: %s\n", carti[i].autor);
			printf("ISBN: %s\n", carti[i].ISBN);
			printf("Disponibil: %s\n", carti[i].disponibil ? "Da" : "Nu");
			printf("----------------------\n");
		}
	}
	else{
		printf("ID: %d\n", carti[id].id);
		printf("Titlu: %s\n", carti[id].titlu);
		printf("Autor: %s\n", carti[id].autor);
		printf("ISBN: %s\n", carti[id].ISBN);
		printf("Disponibil: %s\n", carti[id].disponibil ? "Da" : "Nu");
		printf("----------------------\n");
	}
	printf("\n");
}

void listeazaUsers(){
	if(nr_Users == 0){
		printf("Nu sunt conturi inregistrate.\n");
		return;
	}
	printf("Lista utilizatorilor din biblioteca:\n");
	for(int i = 0; i < nr_Users; i++){
		printf("ID: %d\n", user[i].id);
		printf("Nume: %s\n", user[i].nume);
		printf("Numar carti imprumutate: %d\n", user[i].nrCartiImprumutate);
		printf("Carti imprumutate(ID-uri): ");
		for(int j = 0; j < user[i].nrCartiImprumutate; j++){
			printf("%d, ", user[i].cartiImprumutate[j]);
		}
		printf("\n");
		printf("----------------------\n");
	}
	printf("\n");
}
void listeazaImprumuturi(){
	if(nr_Imprumuturi == 0){
		printf("Nu sunt carti imprumutate\n");
		return;
	}
	printf("Lista imprumuturilor din biblioteca:\n");
	for(int i = 0; i < nr_Imprumuturi; i++){
		printf("Nume utilizator: %s\n", imprumuturi[i].numeUtilizator);
		printf("Titlu Carte: %s\n", imprumuturi[i].titluCarte);
		printf("Data imprumut: %s\n", imprumuturi[i].dataImprumut);
		printf("Data retur: %s\n", imprumuturi[i].dataRetur);
		printf("----------------------\n");
	}
	printf("\n");
}
void curataBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}
void meniuPrincipal(){
	int optiune;
	do{
		printf("Meniul principal al bibliotecii.\n");
		printf("1. Adaugare Carte\n");
		printf("2. Sterge Carte\n");
		printf("3. Cauta Carte\n");
		printf("4. Adaugare Utilizator\n");
		printf("5. Sterge Utilizator\n");
		printf("6. Imprumuta Carte\n");
		printf("7. Returneaza Carte\n");
		printf("8. Listeaza Carti\n");
		printf("9. Listeaza Utilizatori\n");
		printf("10. Listeaza Imprumuturi\n");
		printf("0. Exit\n");
		printf("Introdu optiunea dorita: \n");
		scanf("%d", &optiune);
		char titlu[100], nume[100], autor[100], ISBN[20], dataImprumut[11], dataRetur[11];
		int id;
		curataBuffer();
		switch(optiune){
			case 1:
				printf("Introdu titlul cartii: ");
				fgets(titlu, sizeof(titlu), stdin);
				titlu[strcspn(titlu, "\n")] = '\0';
				printf("Introdu autorul cartii: ");
				fgets(autor, sizeof(autor), stdin);
				autor[strcspn(autor, "\n")] = '\0';
				printf("Introdu ISBN-ul cartii: ");
				scanf("%s",ISBN);
				printf("\n");
				adaugaCarte(autor, titlu, ISBN);
				break;
			case 2:
				printf("Pentru a sterge o carte este nevoie de introduci un id: \n");
				scanf("%d", &id);
				stergeCarte(id);
				break;
			case 3:
				printf("Introdu titlul cartii pe care doresti sa o cauti: \n");
				scanf("%[^\n]", titlu);
				id = cautareCarte(titlu);
				listeazaCarti(id);
				break;
			case 4:
				printf("Introdu numele noului utilizator: \n");
				scanf("%[^\n]", nume);
				adaugaUtilizator(nume);
				break;
			case 5:
				printf("Introdu id-ul utilizatorului: \n");
				scanf("%d", &id);
				stergeUtilizator(id);
				break;
			case 6:
				printf("Introdu titlul cartii: ");
				fgets(titlu, sizeof(titlu), stdin);
                                titlu[strcspn(titlu, "\n")] = '\0';

				printf("Introdu numele utilizatorului: ");
				fgets(nume, sizeof(nume), stdin);
				nume[strcspn(nume, "\n")] = '\0';

				printf("Introdu data cand se face imprumutul: ");
				fgets(dataImprumut, sizeof(dataImprumut), stdin);
				dataImprumut[strcspn(dataImprumut, "\n")] = '\0';
				curataBuffer();

				printf("Introdu data cand se face returul: ");
				fgets(dataRetur, sizeof(dataRetur), stdin);
				dataRetur[strcspn(dataRetur, "\n")] = '\0';
				curataBuffer();

				imprumutareCarte(titlu, nume, dataImprumut, dataRetur);
				break;
			case 7:
                                printf("Introdu titlul cartii: ");
                                fgets(titlu, sizeof(titlu), stdin);
				titlu[strcspn(titlu, "\n")] = '\0';

                                printf("Introdu numele utilizatorului: ");
                                fgets(nume, sizeof(nume), stdin);
				nume[strcspn(nume, "\n")] = '\0';

				returneazaCarte(titlu, nume);
				break;
			case 8:
				listeazaCarti(-1);
				break;
			case 9:
				listeazaUsers();
				break;
			case 10:
				listeazaImprumuturi();
				break;
			case 0:
				printf("Iesire...\n");
				break;
		}
	}while(optiune != 0);
}
int main(){
	meniuPrincipal();
	return 0;
}
