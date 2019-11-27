#pragma once
#include <iostream>

template <class T>
class Array
{
public:
	T* m_array;
	int m_size;

	Array(int p_size)
	{
		m_array = new T[p_size];
		m_size = p_size;
	}

	~Array()
	{
		if (m_array != 0)
			delete[] m_array;
		m_array = 0;
	}

	void Resize(int p_size)
	{
		T* newarray = new T[p_size];

		if (newarray == 0)
			return;

		int min = (p_size < m_size) ? p_size : m_size;

		for (int index = 0; index < min; index++)
			newarray[index] = m_array[index];

		m_size = p_size;

		if (m_array != 0)
			delete[] m_array;

		m_array = newarray;
	}

	T& operator[] (int p_index)
	{
		return m_array[p_index];
	}

	operator T* ()
	{
		return m_array;
	}

	void Insert(T p_item, int p_index)
	{
		for (int i = m_size - 1; i > p_index; i--)
			m_array[i] = m_array[i - 1];

		m_array[p_index] = p_item;
	}

	void Remove(int p_index)
	{
		for (int i = p_index + 1; i < m_size; i++)
			m_array[index - 1] = m_array[index];
	}

	int Size()
	{
		return m_size;
	}
};