#pragma once
#include <iostream>
#include "Array.h"


template <class T>
void SwapArray(T& left, T& right)
{
	T aux = left;
	left = right;
	right = aux;
}

template <class T>
void BubbleSort(Array<T>& p_array, int(*p_compare)(T, T))
{
	int top = p_array.Size() - 1;
	int swaps = 1;

	while (top != 0 && swaps != 0)
	{
		swaps = 0;

		for (int index = 0; index < top; index++)
		{
			if (p_compare(p_array[index], p_array[index + 1]) > 0)
			{
				SwapArray(p_array[index], p_array[index + 1]);
				swaps++;
			}
		}
		
		top--;
	}
}

