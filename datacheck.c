#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datacheck.h"

#define BUFF_SIZE 35

static int checkClient(char *line);
static int checkProduct(char *line);
static int checkSaleLn(char *line, CATALOG product, CATALOG client);

void writeCatalog (FILE *file, CATALOG cat, int mode, int *sucLn, int *failLn) {
	int checked_line, suc, fail;
	char buf[BUFF_SIZE], *line;
	int (*checker)(char *) = NULL;

	suc = fail = 0;

	switch(mode) {
		case M_CLIENTS: checker = checkClient; break;
		case M_PRODUCTS: checker = checkProduct; break;
	}

	while(fgets(buf, BUFF_SIZE, file)) {
		line = strtok (buf, "\n\r");
		checked_line = checker(line);

		if (checked_line) {
			insert(cat, line);
			suc++;
		} else
			fail++;
	}

	*sucLn = suc;
	*failLn = fail;
}

int checkSales (FILE *file, CATALOG products, CATALOG clients, int *sucLn, int *failLn) {
	int checked_line, suc, fail;
	char buf[BUFF_SIZE], *line, print[BUFF_SIZE];
	FILE * validSales = fopen ("Vendas_1MValidas.txt", "w");
	FILE * invalidSales = fopen ("Vendas_1mInvalidas.txt", "w");

	suc = fail = 0;

	while(fgets(buf, BUFF_SIZE, file)) {
		line = strtok (buf, "\n\r");
		strcpy(print, line);
		checked_line = checkSaleLn(line, products, clients);

		/*(checked_line) ? suc++ : fail++; */
		if (checked_line) {
			fprintf(validSales, "%s\n", print);
			suc++;
		} else {
			fprintf(invalidSales, "%s\n", print);
			fail++;
		}
	}

	*sucLn = suc;
	*failLn = fail;

	fclose(validSales);
	fclose(invalidSales);
	return 0;
}

static int checkProduct (char *line){
	int i, lnOk;

	lnOk = 1;

	for (i = 0; lnOk && i < 6; i++){
		switch (i){
			case 0:
			case 1: lnOk = (line[i] >= 'A' && line[i] <= 'Z');
					break;
			case 2: lnOk = (line[i] == '1');
					break;
			case 3:
			case 4:
			case 5: lnOk = (line[i] >= '0' && line[i] <= '9');
					break;
			case 6: lnOk = (line[i] == '\n');
		}
	}

	return lnOk;
}

static int checkClient (char *line) {
	int i, lnOk;

	lnOk = 1;

	for (i = 0; lnOk && i < 6; i++){
		switch (i){
			case 0: lnOk = (line[i] >= 'A' && line[i] <= 'Z');
					break;
			case 1: lnOk = (line[i] >= '1' && line[i] <= '5');
					break;
			case 2:
			case 3:
			case 4: lnOk = (line[1] == '5' && line[i] == '0') ||
							   (line[1] != '5' && line[i] >= '0' && line[i] <= '9');
					break;
		}
	}

	return lnOk;
}

static int checkSaleLn (char *line, CATALOG productCat, CATALOG clientCat) {
	int i, lnOk, quant, month, filial;
	double price;
	char *token;

	lnOk = 1;
	token = strtok(line, " ");

	for (i = 0; lnOk && token != NULL; i++){
		switch(i) {
			case 0: lnOk = lookUp(productCat, token);
						break;
			case 1: lnOk = ((price = atof(token)) >= 0 && price <= 999.99);
						break;
			case 2: lnOk = ((quant = atoi(token)) >= 1 && quant <= 200);
						break;
			case 3: lnOk = !strcmp(token, "P") || !strcmp(token, "N");
						break;
			case 4: lnOk = lookUp(clientCat, token);
						break;
			case 5: lnOk = (month = atoi(token) >= 1 && month < 12);
						break;
			case 6: lnOk = ((filial = atoi(token)) >= 1 && filial <= 3);
						break;
			default: lnOk = 0;
		}
		token = strtok(NULL, " ");
	}

	return lnOk;
}
