#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* encrypt(const char* text, int key){
	int len = strlen(text);
	char* encryptText = (char*) malloc((len+1) * sizeof(char));
	for(int i = 0; i< len; i++){
		char letter = text[i];
		if(letter >= 'a' && letter <='z'){
			encryptText[i] = ((letter-'a' + key)%26) + 'a';
		}
		else if(letter >= 'A' && letter <= 'Z'){
			encryptText[i] = ((letter-'A' + key)%26) + 'A';
		}
		else{
			encryptText[i] = letter;
		}
	}
	encryptText[len] = '\0';
	return encryptText;
}

char* decrypt(const char* text, int key){
	int len = strlen(text);
	char* decryptText = (char*) malloc((len+1)*sizeof(char));
	for(int i=0; i<len;i++){
		char letter = text[i];
		if(letter >='a' && letter <='z'){
			decryptText[i] = ((letter-'a' - key+26)%26)+'a';
		}
		else if(letter >='A' && letter <= 'Z'){
			decryptText[i] = ((letter - 'A' - key + 26) % 26) + 'A';
		}
		else{
			decryptText[i] = letter;
		}
	}
	decryptText[len] = '\0';
	return decryptText;
}

int main(){
	char text[256];
	int key;
	printf("Introdu un text:");
	scanf("%s", text);
	printf("\nIntrodu key-ul:");
	scanf("%d", &key);
	char* textEncrypt = encrypt(text, key);
	printf("Textul criptat este: %s",encrypt(text, key));
	printf("\nTextul decriptat este: %s", decrypt(textEncrypt, key)); 
	printf("\n");	
	return 0;
}
