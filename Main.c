#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

struct Word {
	char* slovo;
	int counter;
}typedef word;


word createWord(char* value) {
	word newWord;
	newWord.slovo = value;
	newWord.counter = 1;
	return newWord;
}


word* addWord(word* poleSlov, word slovo, int* delkaPoleSlov) {
	
	if (*delkaPoleSlov == 0) {
		poleSlov = (word*)malloc(sizeof(word));
		poleSlov[0] = slovo;
		(*delkaPoleSlov)++;
		return poleSlov;
	}

	int i = 0;
	while (i<*delkaPoleSlov) {
		if (!strcmp(poleSlov[i].slovo, slovo.slovo)) {
			poleSlov[i].counter++;
			return poleSlov;
		}
		i++;
	}

	poleSlov = (word*)realloc(poleSlov, sizeof(word) * (*delkaPoleSlov+1));
	poleSlov[*delkaPoleSlov] = slovo;
	(*delkaPoleSlov)++;
	return poleSlov;
}


bool checkParam(char* value) {
	int delka = strlen(value);
	for (int i = 0; i < delka; i++)
	{
		if (value[i] < '0' || value[i] >'9') // ascii kod
		return false;
	}
	return true;
}


char* readWord(bool* konec) {
	char* slovo;
	int znak;
	slovo = (char*)malloc(sizeof(char));
	slovo[0] = '\0';
	int index = 0;
	while ((znak = getchar()) && znak != ' ' && znak != ',' && znak != '.' && znak != '!' && znak != '?' && znak != '\t' && znak != '\n' && znak != EOF) {
		slovo = (char*)realloc(slovo, sizeof(char) * (index + 2));
		slovo[index] = znak;
		slovo[index + 1] = '\0';
		index++;
	}
	if (znak == EOF)
		*konec = true;
	return slovo;
}


word* readInput(word* poleSlov, int* delkaPoleSlov) {
	bool isEOF = false;
	char* slovo;
	while (!isEOF){
		slovo = readWord(&isEOF);
		if (slovo[0] != '\0')
			poleSlov = addWord(poleSlov, createWord(slovo), delkaPoleSlov);
		else free(slovo);
	}
	return poleSlov;
}

// CPMPARATOR FOR QSORT FUNCRION FOR DESC SORTING
int compareElement(const void* a, const void* b) {
	return ((struct Word*)b)->counter - ((struct Word*)a)->counter;
}

void freeMem(word* pole, int delka) {
	for (int i = 0; i < delka; i++)
	{
		free(pole[i].slovo);
	}
}

// MAIN FUNCTION
int main(int arc, char** argv) {
	if (!checkParam(argv[1])) {
		printf("Wrong param");
			return 1;
	}
	int pocetSlov = atoi(argv[1]);
	int delkaPoleSlov = 0;
	word* pole;

	//FILLING THE ARRAY
	pole = readInput(pole, &delkaPoleSlov);

	//SORTING THE ARRAY OF WORDS
	qsort(pole, delkaPoleSlov, sizeof(word), compareElement);

	//PRINTING THE ARRAY !!
	if (pocetSlov > delkaPoleSlov)
		pocetSlov = delkaPoleSlov;

	for (int i = 0; i < pocetSlov; i++)
		printf("%s - %d\n", pole[i].slovo, pole[i].counter);

	freeMem(pole, delkaPoleSlov);
	free(pole);
	
	return 0;
}
