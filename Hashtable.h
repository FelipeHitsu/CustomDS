#pragma once
#include<iostream>
#include<string>
#include"Array.h"
#include "Lista.h"

template<class TKey, class TValue>
class HashEntry
{ 
public:
	TKey m_key; 
	TValue m_data;

};
template<class TKey, class TValue>
class HashTable
{
public:
	typedef HashEntry<TKey, TValue> Entry;
	int m_size;// tamanho do array 
	int m_count; // quantidade de elementos 
	Array<DLinkedList<Entry>> m_table;
	unsigned long int(*m_hash)(TKey); 
	// ponteiro para função com um parametroTKey

	HashTable(int p_size, unsigned long int(*p_hash)(TKey))
		: m_table(p_size)
	{
		m_size = p_size;
		m_hash = p_hash;
		m_count = 0;
	}

	void Insert(TKey p_key, TValue p_data)
	{
		Entry entry;
		entry.m_key = p_key;
		entry.m_data = p_data;
		int index = m_hash(p_key) % m_size;
		m_table[index].Append(entry);
		m_count++;
	}

	Entry* Find(TKey p_key)
	{
		int index = m_hash(p_key) % m_size;
		DListIterator<Entry> itr = m_table[index].GetIterator();
		while (itr.Valid())
		{
			if (itr.Item().m_key == p_key)
				return&(itr.Item());
			itr.Forth();
		}
		return 0;
	}

	bool Remove(TKey p_key)
	{
		int index = m_hash(p_key) % m_size;
		DListIterator<Entry> itr = m_table[index].GetIterator();
		while (itr.Valid())
		{
			if (itr.Item().m_key == p_key)
			{
				m_table[index].Remove(itr);
				m_count--;
				return true;
			}
			itr.Forth();
		}
		return false;
	}

	
};

class CustomString
{ 

public:
	char m_string[64]; 
	CustomString()
	{
		strcpy_s(m_string, ""); 
	}
	CustomString(char* p_string)
	{ 
		strcpy_s(m_string, p_string); 
	}
	bool operator == (CustomString& p_right)
	{ 
		return !strcmp(m_string, p_right.m_string); 
	}
};