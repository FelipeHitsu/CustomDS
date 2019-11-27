#pragma once


template<class T>
class InsertionSort
{
public:

	InsertionSort::InsertionSort(T arr[],int tam)
	{
		T  index;
		for (int j = 1; j < tam; j++)
		{
			index = arr[j];
			int i = j - 1;
			while (i >= 0 && arr[i] < index)
			{
				arr[i + 1] = arr[i];
				i = i - 1;
			}
			arr[i + 1] = index;
		}

	}

	InsertionSort::~InsertionSort()
	{

	}
};

