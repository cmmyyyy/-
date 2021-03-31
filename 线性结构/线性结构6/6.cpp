#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include "Node.h"


int main()
{
	struct List list1 = create();
	struct List list2 = create();
	struct Node* s;
	int m, n, k, i, j;
	scanf("%d %d %d", &m, &n,&k);
	for (i = 1;i <= m;i++)
	{
		list1 = NodeInsert(list1, i);
	}
	s = list1.head;
	list1.tail->next = list1.head->next;
	j = m;
	while (j--)
	{
		i = n;
		while (--i)
		{
			s = s->next;
		}
		
		if (s->next == list1.tail)
		{
			list1.tail = list1.tail->next;
		}
		struct Node* p = s->next;
		s->next = s->next->next;
		struct Node* q = NewNode();
		q->data = p->data;
		list2.tail->next = q;
		list2.tail = q;
		free(p);
		
	}
	s = list2.head;
	list2.tail->next = list2.head->next;
	j = m;
	while (j--)
	{
		i = k;
		while (--i)
		{
			s = s->next;
		}
		printf("%4d", s->next->data);
		if (s->next == list2.tail)
		{
			list2.tail = list2.tail->next;
		}
		struct Node* p = s->next;
		s->next = s->next->next;
		free(p);
	}
	
	list1.head = list1.tail = NULL;
	list2.head = list2.tail = NULL;
	return 0;
}