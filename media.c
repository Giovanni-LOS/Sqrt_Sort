#include <stdio.h>

int main(int argc, char *argv[]) {

	FILE *fPtr;
	fPtr = fopen(argv[1], "r");
	float numbers[5];

	int i = 0;
	while(!feof(fPtr)) {
		fscanf(fPtr,"%f", &numbers[i++]);
	}
	fclose(fPtr);
	
	float soma = 0;
	for(i = 0; i<5; i++) {
		soma += numbers[i];
	}

	float r = soma / 5;
	printf("%f\n", r);

	return 0;
}
