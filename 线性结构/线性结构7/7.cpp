#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include "Node.h"
using namespace std;


int main()
{
	struct List list = create();
	
	struct Node* s;
	
	int m, n, i, j;
	char c;
	scanf("%d", &m);
	for (i = 1;i <= m;i++)
	{
		list = NodeInsert(list, i);
	}
	getchar();
	while (c = getchar())
	{
		if (c == ' ')continue;
		if (c == '\n')break;
		n = c - '0';
		s = list.head;
		list.tail->next = list.head->next;
		j = m;
		struct List plist = create();
		while (j--)
		{
			i = n;
			while (--i)
			{
				s = s->next;
			}
			//printf("%d ", s->next->data);
			if (s->next == list.tail)
			{
				list.tail = list.tail->next;
			}
			struct Node* q = s->next;
			
			s->next = s->next->next;
			struct Node* p = NewNode();
			p->data = q->data;

			plist.tail->next = p;
			plist.tail = p;
			free(q);
			
		}
		list.head = list.tail = NULL;
		list = AddList(list, plist);
		

	}
	Print(list);
	list.head = list.tail = NULL;

	return 0;
}