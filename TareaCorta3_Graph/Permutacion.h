#pragma once

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>

using namespace std;

int * genere(int n) {

	int * valores = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		valores[i] = i;
	}
	for (int i = 0; i < n; i++) {
		int aux1 = valores[i];
		int aux3 = rand() % n;
		int aux2 = valores[aux3];
		valores[i] = aux2;
		valores[aux3] = aux1;
	}
	return valores;
}
