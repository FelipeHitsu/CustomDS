#pragma once
#include"DLinkedList.h"
#include"Array.h"
#include "Queue.h"

template<class TNode, class TArc>
class GraphNode;

template<class TNode,class TArc>
class GraphArc
{
public:
	
	GraphNode<TNode, TArc>* m_node;
	TArc m_weight;

};

template<class TNode, class TArc>
class GraphNode
{
public:

	typedef GraphArc<TNode, TArc> Arc;
	typedef GraphNode<TNode, TArc> Node;

	TNode m_data;
	DLinkedList<Arc> m_arcList;
	bool m_marked;

	void AddArc(Node* p_node, TArc p_weight)
	{
		Arc a;

		a.m_node = p_node;
		a.m_weight = p_weight;
		m_arcList.Append(a);


	}

	Arc* GetArc(Node* p_node)
	{
		DListIterator<Arc> itr;
		itr = m_arcList.GetIterator();

		for (itr.Start(); itr.Valid(); itr.Forth())
		{
			if (itr.Item().m_node == p_node)
				return &(itr.Item());
		}

		return 0;
	}

	void RemoveArc(Node* p_node)
	{

		DListIterator<Arc> itr;
		itr = m_arcList.GetIterator();

		for (itr.Start(); itr.Valid(); itr.Forth())
		{
			if (itr.Item().m_node == p_node)
				m_arcList.Remove(itr);

		}
	}
};

template<class TNode,class TArc>
class Graph
{

public:
	typedef GraphArc<TNode, TArc> Arc;
	typedef GraphNode<TNode, TArc> Node;

	Array<Node*> m_nodes;

	int m_count;

	Graph(int p_size) : m_nodes(p_size)
	{
		for (int i = 0; i < p_size; i++)
			m_nodes[i] = nullptr;

		m_count = 0;
	}

	~Graph()
	{
		for (int i = 0; i < m_nodes.m_size; i++)
		{
			if (m_nodes[i] != 0)
				delete m_nodes[i];
		}
	}

	bool AddNode(TNode p_data, int p_index)
	{

		if (m_nodes[p_index] != 0)
			return false;

		m_nodes[p_index] = new Node;
		m_nodes[p_index]->m_data = p_data;
		m_nodes[p_index]->m_marked = false;
		m_count++;

		return true;

	}

	void RemoveNode(int p_index)
	{
		if (m_nodes[p_index] == 0)
			return;

		Arc* arc;

		for (int i = 0; i < m_nodes.Size(); i++)
		{
			if (m_nodes[i] != 0)
			{
				arc = m_nodes[i]->GetArc(m_nodes[p_index]);
				if (arc != 0)
					RemoveArc(i, p_index);
			}
		}

		delete m_nodes[p_index];
		m_nodes[p_index] = 0;
		m_count--;

	}

	bool AddArc(int p_from, int p_to, TArc p_weight)
	{
		if (m_nodes[p_from] == 0 || m_nodes[p_to] == 0)
			return false;

		if (m_nodes[p_from]->GetArc(m_nodes[p_to]) != 0)
			return false;

		m_nodes[p_from]->AddArc(m_nodes[p_to], p_weight);
			return true;
	}

	void RemoveArc(int p_from, int p_to)
	{
		if (m_nodes[p_from] == 0 || m_nodes[p_to] == 0)
			return;

		m_nodes[p_from]->RemoveArc(m_nodes[p_to]);
	}

	Arc* GetArc(int p_from, int p_to)
	{
		if (m_nodes[p_from] == 0 || m_nodes[p_to] == 0)
			return 0;

		return m_nodes[p_from]->GetArc(m_nodes[p_to]);
	}

	void ClearMarks()
	{
		for (int i = 0; i < m_nodes.m_size; i++)
		{
			if (m_nodes[i] != 0)
				m_nodes[i]->m_marked = false;
		}
	}

	void DepthFirst(Node* p_node, void(*p_process)(Node*))
	{
		if (p_node == 0)
			return;
		p_node->m_marked = true;
		p_process(p_node);
		DListIterator<GraphArc<TNode, TArc>> itr = p_node->m_arcList.GetIterator();
		for (itr.Start(); itr.Valid(); itr.Forth())
		{
			if (itr.Item().m_node->m_marked == false)
				DepthFirst(itr.Item().m_node, p_process);
		}
	}

	void BreadthFirst(Node* p_node,
		void(*p_process)(Node*))
	{
		if (p_node == 0)
			return;
		LQueue<Node*> queue;
		DListIterator<Arc> itr;
		queue.Enqueue(p_node);
		p_node->m_marked = true;
		while (queue.Count() != 0)
		{
			p_process(queue.Front());
			itr = queue.Front()->m_arcList.GetIterator();
			for (itr.Start(); itr.Valid(); itr.Forth())
			{
				if (itr.Item().m_node->m_marked == false)
				{
					//itr.Item().m_node->m_marked == true;
					queue.Enqueue(itr.Item().m_node);
				}
			}
			queue.Dequeue();
		}
	}
};