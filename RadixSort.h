#pragma once
#include "Array.h"
#include"Inimigo.h"

template<class T>
void RadixSort(Array<Inimigo>& arr, int p_size){
	

	int i;
	int maior = arr[0].getEnergia();
	int exp = 1;

		Array<Inimigo> b(p_size);

		for (i = 0; i < p_size; i++) {
			if (arr[i].getEnergia() > maior)
				maior = arr[i].getEnergia();
		}

		while (maior / exp > 0) {
			int bucket[10] = { 0 };
			for (i = 0; i < p_size; i++)
				bucket[(arr[i].getEnergia() / exp) % 10]++;
			for (i = 1; i < 10; i++)
				bucket[i] += bucket[i - 1];
			for (i = p_size - 1; i >= 0; i--)
				b[--bucket[(arr[i].getEnergia() / exp) % 10]] = arr[i];
			for (i = 0; i < p_size; i++)
				arr[i] = b[i];
			exp *= 10;
		}
	}


