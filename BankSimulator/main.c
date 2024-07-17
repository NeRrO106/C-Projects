#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ContBancar{
	int id;
	char nume[100];
	float sold;
};

ContBancar conturi[100];
int nr_conturi = 0;

void createAccount(const char* name, float amount){
	if(nr_conturi >= 100){
		 printf("S a atins numarul maxim de conturi\n");
		return;
	}
	conturi[nr_conturi].id = nr_conturi+1;
	conturi[nr_conturi].sold = amount;
	strcpy(conturi[nr_conturi].nume, name);
	nr_conturi++;
	printf("Cont Creat cu succes\n");
}


void deposit(int id, float money){
	if(id<=0 || id>nr_conturi){
		printf("Id invalid\n");
		return;
	}
	conturi[id-1].sold += money;
	printf("Suma adaugata cu succes\n");
}
void withdraw(int id, float money){
	if(id<=0 || id>nr_conturi){
		printf("Id invalid\n");
		return;
	}
	if(conturi[id-1].sold < money){
		printf("Sold insuficient\n");
		return;
	}
	conturi[id-1].sold -= money;
	printf("Suma extrasa cu succes\n");
}

void ViewSold(int id){
	if(id<=0 || id>nr_conturi){
		printf("Id invalid\n");
		return;
	}
	printf("Soldul contului: %.2f: \n", conturi[id-1].sold);
}

int main()
{
	createAccount("Ion", 500.0);
	createAccount("Vasile", 7500.5);
	deposit(1,250.2);
	withdraw(2, 1500);
	ViewSold(1);
	ViewSold(2);
	return 0;
}
