#pragma once
#include "Lista.h"
template<class T>
class Tree
{
public:

	Tree* m_parent;
	DLinkedList<Tree*> m_children;
	typedef Tree<T> Node;
	T m_data;

	Tree() : m_parent(0)
	{

	}

	void Destroy()
	{
		DListIterator<Node*> itr = m_children.GetIterator();

		Node* node = 0; 
		itr.Start();

		while (itr.Valid()) 
		{ 
			node = itr.Item(); 
			m_children.Remove(itr); 
			delete node; 
		}
	}

	int Count()
	{
		int c = 1;

		DListIterator<Node*> itr = m_children.GetIterator();

		for (itr.Start(); itr.Valid(); itr.Forth())
			c += itr.Item()->Count();

		return c;
	}

	~Tree()
	{
		Destroy();
	}
	

};

template<class T> 
class TreeIterator
{
public:
	typedef Tree<T> Node;
	Node* m_node;
	DListIterator<Node*> m_childitr;

	TreeIterator(Node* p_node = 0) 
	{ 
		*this = p_node 
	}

	void ResetIterator() 
	{ 
		
		if (m_node != 0) 
			m_childitr = m_node->m_children.GetIterator(); 
	
		else 
		{		
			m_childitr.m_list = 0;
			m_childitr.m_node = 0;
		} 
	}

	void operator= (Node* p_node) 
	{ 
		m_node = p_node; 
		ResetIterator(); 
	}

	void Root() 
	{ 
		if (m_node != 0) 
		{ 
			while (m_node->m_parent != 0) 
				m_node = m_node->m_parent; 
			
			ResetIterator(); 
		} 
	}

	void Up() 
	{ 
		if (m_node != 0) 
		{
			m_node = m_node->m_parent; 
			ResetIterator(); 
		} 
	}

	void Down() 
	{ 
		if (m_childitr.Valid()) 
		{ 
			m_node = m_childitr.Item(); 
			ResetIterator(); 
		} 
	}

	template <class T> 
	void Preorder(Tree<T>* p_node, void(*p_process)(Tree<T>*)) 
	{ 
		p_process(p_node); 
		DListIterator<Tree<T>*> itr; 
		itr = p_node->m_children->GetIterator(); 
		for (itr.Start(); itr.Valid(); itr.Forth()) 
			Preorder(itr.Item(), p_process); 
	}

	template <class T>
	void PostOrder(Tree<T>* p_node, void(*p_process)(Tree<T>*))
	{
		p_process(p_node);
		DListIterator<Tree<T>*> itr;
		itr = p_node->m_parent->GetIterator();
		for (itr.Start(); itr.Valid(); itr.Forth())
			PostOrder(itr.Item(), p_process);
	}

};