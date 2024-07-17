#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
	int id;
	char titlu[100];
	int durata;
	char gen[50];
	char clasificare[20];
	char descriere[200];
} Film;

#define MAX_FILME 100
Film filme[MAX_FILME];
int nr_filme = 0;

bool filmExist(int id){
	for(int i = 0; i< nr_filme; i++){
		if(filme[i].id == id){
			return true;
		}
	}
	return false;
}

void adaugareFilm(Film film){
	if(nr_filme >= MAX_FILME){
		printf("A fost atins numarul maxim de filme.\n");
		return;
	}
	filme[nr_filme] = film;
	nr_filme++;
	printf("Filmul %s a fost adaugat cu succes. \n", film.titlu);
}
void stergeFilm(int id){
	if(nr_filme == 0){
		printf("Nu sunt filme inregistrate.\n");
		return;
	}
	if(!filmExist(id)){
		printf("Id invalid.\n");
		return;
	}

	int index = -1;
	for(int i = 0; i < nr_filme; i++){
		if(filme[i].id == id){
			index = i;
			break;
		}
	}

	for(int i = index; i < nr_filme-1; i++){
		filme[i] = filme[i+1];
	}
	nr_filme--;
	printf("Filmul cu id-ul: %d a fost sters cu succes.\n", id);
	for(int  i = 0; i < nr_filme; i++){
		filme[i].id = i+1;
	}
}
void vizualizareFilme(){
	if(nr_filme == 0){
		printf("Nu sunt filme inregistrate.\n");
		return;
	}
	for(int i = 0; i < nr_filme; i++){
		printf("ID: %d\n", filme[i].id);
		printf("Titlu: %s\n", filme[i].titlu);
		printf("Durata: %d\n", filme[i].durata);
		printf("Gen: %s\n", filme[i].gen);
		printf("Clasificare: %s\n", filme[i].clasificare);
		printf("Descriere: %s\n", filme[i].descriere);
		printf("----------------------------\n");
	}
}

char* convertToLower(char* lower, const char* original){
	int i =0;
	while(original[i]){
		lower[i] = tolower(original[i]);
		i++;
	}
	lower[i] = '\0';
	return lower;
}

void cautaFilm(const char* titlu){
	char titluLower[100];
	convertToLower(titluLower, titlu);
	for(int i = 0; i < nr_filme; i++){
		char titluFilmLower[100];
		convertToLower(titluFilmLower, filme[i].titlu);
		if(strcmp(titluLower, titluFilmLower) == 0){
			printf("ID: %d\n", filme[i].id);
                	printf("Titlu: %s\n", filme[i].titlu);
                	printf("Durata: %d\n", filme[i].durata);
                	printf("Gen: %s\n", filme[i].gen);
                	printf("Clasificare: %s\n", filme[i].clasificare);
                	printf("Descriere: %s\n", filme[i].descriere);
                	printf("----------------------------\n");
			return;
		}
	}
	printf("Filmul nu a fost gasit.\n");
}
void actualizareFilme(int id, Film film){
	if(!filmExist(id)){
		printf("Id invalid.\n");
		return;
	}
	filme[id-1] = film;
	printf("Filmul cu id-ul: %d a fost actualizat cu succes.\n", id);
}
typedef struct{
	int id;
	int id_film;
	char dataOra[20];
	int id_sala;
}ProgramFilm;

#define MAX_PROGRAM_FILM 150
ProgramFilm programFilme[MAX_PROGRAM_FILM];
int nr_programe = 0;

bool programExist(int id){
	for(int i = 0; i< nr_programe; i++){
		if(programFilme[i].id == id){
			return true;
		}
	}
	return false;
}

void stergeProgramFilm(int id){
	if(nr_programe == 0){
		printf("Nu sunt programe inregistrate.\n");
		return;
	}
	if(!programExist(id)){
		printf("Id invalid.\n");
		return;
	}
	for(int i = id - 1; i < nr_programe-1; i++){
		programFilme[i] = programFilme[i+1];
	}
	nr_programe--;
	printf("Programul cu id-ul: %d a fost sters cu succes.\n", id);
}
void vizualizareProgramFilm(){
	if(nr_programe == 0){
		printf("Nu sunt programe inregistrate.\n");
		return;
	}
	for(int i = 0; i < nr_programe; i++){
		printf("ID: %d\n", programFilme[i].id);
		printf("ID film: %d\n", programFilme[i].id_film);
		printf("Data si ora filmului: %s\n", programFilme[i].dataOra);
		printf("ID sala: %d\n", programFilme[i].id_sala);
		printf("----------------------------\n");
	}
}
void actualizareProgramFilm(int id, ProgramFilm program){
	if(!programExist(id)){
		printf("Id invalid.\n");
		return;
	}
	programFilme[id-1] = program;
	printf("Programul cu id-ul: %d a fost actualizat cu succes.\n", id);
}
typedef struct{
	int id;
	int nr_locuri;
	int locuri[10][10];
}Sala;
#define MAX_NUMAR_SALI 7
Sala salaCinema[MAX_NUMAR_SALI];
int nr_sali = 0;

bool salaExist(int id){
	for(int i = 0; i < nr_sali; i++){
		if(salaCinema[i].id == id){
			return true;
		}
	}
	return false;
}

bool locuriDisponibile(int id_program, int locuri[], int nr_locuri){
	ProgramFilm program;
	Sala salaTemp;

	bool programGasit = programExist(id_program);
	if(!programGasit) return false;

	for(int i = 0; i < nr_programe; i++){
		if(programFilme[i].id == id_program){
			program = programFilme[i];
			break;
		}
	}

	bool salaGasita = salaExist(program.id_sala);
	if(!salaGasita) return false;

	for(int i = 0 ; i < nr_sali; i++){
		if(salaCinema[i].id == program.id_sala){
			salaTemp = salaCinema[i];
			break;
		}
	}

	for(int i = 0; i < nr_locuri; i++){
		int loc = locuri[i];
		int row = loc / 10;
		int col = loc % 10;
		if(salaTemp.locuri[row][col] != 0){
			return false;
		}
	}
	return true;
}
void adaugaSala(Sala sala){
	if(nr_sali > MAX_NUMAR_SALI){
		printf("Numarul maxim de salii a fost atins.\n");
		return;
	}
	salaCinema[nr_sali] = sala;
	nr_sali++;
	printf("Sala cu id-u: %d a fost adaugata cu succes.\n", sala.id);
}
void stergeSala(int id){
	if(nr_sali == 0 ){
		printf("Nu sunt sali inregistrate.\n");
		return;
	}
	for(int i = id - 1; i < nr_sali -1; i++){
		salaCinema[i] = salaCinema[i+1];
	}
	nr_sali--;
	printf("Sala cu id-ul: %d a fost eliminata cu succes.\n", id);
}
void vizualizareSali(){
	if(nr_sali == 0){
		printf("Nu sunt sali inregistrate.\n");
		return;
	}
	for(int i = 0; i < nr_sali; i++){
		printf("ID: %d\n", salaCinema[i].id);
		printf("Nr Locuri: %d\n", salaCinema[i].nr_locuri);
		printf("Locuri in sala: \n");
		for(int j = 0; j < 10; j++){
			for(int k = 0; k < 10; k++){
				printf("%d, ",salaCinema[i].locuri[j][k]);
			}
			printf("\n");
		}
		printf("----------------------------\n");
	}
}
void actualizareSala(int id, Sala sala){
	if(id < 0 || id > nr_sali){
		printf("ID invalid.\n");
		return;
	}
	salaCinema[id-1] = sala;
	printf("Sala cu id-ul: %d a fost actualizat cu succes.\n", id);
}
typedef struct{
	int id;
	int id_program_film;
	int id_utilizator;
	int locuri[10];
	int nr_locuri;
	char status[20];
}Rezervare;

#define MAX_REZERVARI 10
Rezervare rezervareFilm[MAX_REZERVARI];
int nr_rezervari = 0;

bool rezervareExist(int id){
	for(int i = 0; i < nr_rezervari; i++){
		if(rezervareFilm[i].id == id){
			return true;
		}
	}
	return false;
}
void vizualizareRezervari(){
	if(nr_rezervari == 0){
		printf("Nu sunt rezervari inregistrate.\n");
		return;
	}
	for(int i = 0; i < nr_rezervari; i++){
		printf("ID: %d\n",rezervareFilm[i].id);
		printf("ID program: %d\n", rezervareFilm[i].id_program_film);
		printf("ID utilizator: %d\n", rezervareFilm[i].id_utilizator);
		printf("Locurile rezervate: \n");
		for(int j = 0; j < 10; j++){
			printf("%d, ",rezervareFilm[i].locuri[j]);
		}
		printf("\n");
		printf("Nr locuri: %d\n", rezervareFilm[i].nr_locuri);
		printf("Status: %s\n", rezervareFilm[i].status);
	}
}
typedef struct{
	int id;
	char nume[100];
}User;
#define MAX_USERS 10
User users[MAX_USERS];
int nr_user = 0;

bool userExist(int id){
	for(int i = 0; i < nr_user; i++){
		if(users[i].id == id){
			return true;
		}
	}
	return false;
}

void adaugaUser(User user){
	if(nr_user > MAX_USERS){
		printf("Numarul maxim de utilizatori a fost atins.\n");
		return;
	}
	users[nr_user] = user;
	nr_user++;
	printf("Utilizatorul %s a fost adaugat cu succes.\n", user.nume);
}
void stergeUser(int id){
	if(id < 0 || id > nr_user){
		printf("Id invalid.\n");
		return;
	}
	for(int i = id -1; i < nr_user-1; i++){
		users[i] = users[i+1];
	}
	nr_user--;
	printf("Utilizatorul cu id-ul %d a fost sters cu succes.\n", id);
}
void vizualizareUsers(){
	if(nr_user == 0){
		printf("Nu sunt utilizatori inregistrati.\n");
		return;
	}
	for(int i = 0; i <nr_user; i++){
		printf("ID: %d\n", users[i].id);
		printf("Nume: %s\n", users[i].nume);
	}
}
void actualizareUser(int id, User user){
	if(id < 0 || id > nr_user){
		printf("ID invalid.\n");
		return;
	}
	users[id-1] = user;
	printf("Utilizatorul cu id-ul: %d a fost actualizat cu succes.\n", id);
}

void adaugareProgramFilm(ProgramFilm program){
        if(nr_programe >= MAX_PROGRAM_FILM){
                printf("A fost atins numarul maxim de programe.\n");
                return;
        }
        if(!filmExist(program.id_film)){
                printf("Filmul cu id-ul: %d nu exista.\n", program.id_film);
                return;
        }
        if(!salaExist(program.id_sala)){
                printf("Sala cu id-ul %d nu exista. \n", program.id_sala);
                return;
        }
        programFilme[nr_programe] = program;
        nr_programe++;
        printf("Programul %d a fost adaugat cu succes.\n", program.id);
}

void adaugaRezervare(Rezervare rezervare){
        if(nr_rezervari >= MAX_REZERVARI){
                printf("A fost atins numarul maxim de rezervari.\n");
                return;
        }
	if(!programExist(rezervare.id_program_film)){
		printf("Programul cu id-ul %d nu exista. \n", rezervare.id_program_film);
		return;
	}
	if(!userExist(rezervare.id_utilizator)){
		printf("User-ul cu id-ul: %d nu exista. \n", rezervare.id_utilizator);
		return;
	}
	if(!locuriDisponibile(rezervare.id_program_film, rezervare.locuri, rezervare.nr_locuri)){
		printf("Locurile specificate nu sunt disponibile.\n");
		return;
	}
	ProgramFilm program = programFilme[rezervare.id_program_film - 1];
	Sala sala = salaCinema[program.id_sala - 1];
	for(int i = 0; i < rezervare.nr_locuri; i++){
		int loc = rezervare.locuri[i];
		int row = loc / 10;
		int col = loc % 10;
		sala.locuri[row][col] = 1;
	}
	salaCinema[program.id_sala - 1] = sala;
	rezervareFilm[nr_rezervari] = rezervare;
	nr_rezervari++;
        printf("Rezervare realizata cu succes.\n");
}

void anuleazaRezervare(int id){
        if(nr_rezervari == 0){
                printf("Nu sunt rezervari inregistrate.\n");
                return;
        }
	if(id < 0 || id > nr_rezervari){
		printf("Id invalid.\n");
		return;
	}
	Rezervare rezervare = rezervareFilm[id -1];
	ProgramFilm program = programFilme[rezervare.id_program_film - 1];
	Sala sala = salaCinema[program.id_sala -1];

	for(int i = 0; i < rezervare.nr_locuri; i++){
		int loc = rezervare.locuri[i];
		int row = loc / 10;
		int col = loc % 10;
		sala.locuri[row][col] = 0;
	}
	salaCinema[program.id_sala - 1] = sala;
        for(int i = id - 1;i < nr_rezervari - 1; i++){
                rezervareFilm[i] = rezervareFilm[i+1];
        }
        nr_rezervari--;
        printf("Rezervarea cu id-ul: %d a fost anulata cu succes: \n", id);
}


int main(){
	Film film1 = {1, "Inception", 148, "SF", "12+", "Un hoț care fură secrete prin intermediul tehnologiei de partajare a viselor."};
    	Film film2 = {2, "The Matrix", 136, "Action", "16+", "Un hacker descoperă adevărata natură a realității și rolul său în războiul împotriva controlului mașinilor."};
    	adaugareFilm(film1);
    	adaugareFilm(film2);

    	vizualizareFilme();

	Sala sala1 = {1, 100, {{0}}};
    	Sala sala2 = {2, 100, {{0}}};
    	adaugaSala(sala1);
    	adaugaSala(sala2);

    	vizualizareSali();

	User user1 = {1, "Andrei"};
    	User user2 = {2, "George"};
    	adaugaUser(user1);
    	adaugaUser(user2);

    	vizualizareUsers();

	ProgramFilm program1 = {1, 1, "2024-07-07 19:00", 1};
    	ProgramFilm program2 = {2, 2, "2024-07-08 20:00", 2};
    	adaugareProgramFilm(program1);
    	adaugareProgramFilm(program2);

    	vizualizareProgramFilm();

    	Rezervare rezervare1 = {1, 1, 1, {11, 12, 13}, 3, "Confirmata"};
    	adaugaRezervare(rezervare1);

    	vizualizareRezervari();

    	anuleazaRezervare(1);

    	vizualizareRezervari();

    	stergeFilm(1);

    	vizualizareFilme();

    	Film film3 = {1, "The Matrix Reloaded", 138, "Action", "16+", "Continuarea aventurilor lui Neo în lupta împotriva mașinilor."};
    	actualizareFilme(1, film3);

    	vizualizareFilme();

    	stergeSala(1);

    	vizualizareSali();

    	Sala sala3 = {1, 120, {{0}}};
    	actualizareSala(1, sala3);

    	vizualizareSali();

    	stergeProgramFilm(1);

    	vizualizareProgramFilm();

    	ProgramFilm program3 = {1, 2, "2024-07-09 21:00", 2};
    	actualizareProgramFilm(1, program3);

    	vizualizareProgramFilm();

    	stergeUser(1);

    	vizualizareUsers();

    	User user3 = {1, "Marian"};
    	actualizareUser(1, user3);

    	vizualizareUsers();
	return 0;
}
