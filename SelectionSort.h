#pragma once


template<class T>
class SelectionSort 
{
public:

	SelectionSort::SelectionSort(T arr[], int tam)
	{
		for (int index = 0; index < tam; index++)
		{
			int aux = index;
			for (int i = index; i < tam; i++)
			{
				if (arr[i] > arr[aux])
					aux = i;
			}
			T temp = arr[index];
			arr[index] = arr[aux];
			arr[aux] = temp;
		}
		
	}

	SelectionSort ::~SelectionSort()
	{
	}

};

