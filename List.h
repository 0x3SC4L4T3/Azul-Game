#pragma once
#include <iostream>
using namespace std;
class Node {
public:
	Player *data;
	Node *next;

	Node()
	{
		next = NULL;
	}

	Node(Player *_data)
	{
		{
			data = _data;
			next = NULL;
		}
	}

};

class List {
private:
	Node *head;
	
public:
	List()
	{
		head = NULL;
	}
	void insert(Player *p)
	{
		Node *newNode = new Node(p);
		if (head == NULL)
			head = newNode;
		else
		{
			Node *current, *nxt;
			current = head;
			nxt = current->next;
			while (nxt)
			{
				current = nxt;
				nxt = current->next;
			}
			current->next = newNode;
			newNode = NULL;
		}
	}
	Player* get(int x)
	{
		Node *temp;
		int i = 0;
		temp = head;
		while (temp)
		{
			if (i == x)
			{
				return temp->data;
			}
			else
			{
				temp = temp->next;
				i++;
			}
		}
		return NULL;
	}
	

};