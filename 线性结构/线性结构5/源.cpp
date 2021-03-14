#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include "Node.h"


int main()
{
	struct List list = create();
	struct Node* s;
	int m, n, i;
	scanf("%d %d", &m, &n);
	for (i = 1;i <= m;i++)
	{
		list = NodeInsert(list, i);
	}
	s = list.head;
	list.tail->next = list.head->next;
	while (list.head->next->data != list.tail->data)
	{
		i = n;
		while (--i)
		{
			s = s->next;
		}
		printf("%d ", s->next->data);
		if (s->next == list.tail)
		{
			list.tail = list.tail->next;
		}
		struct Node* p = s->next;
		s->next = s->next->next;
		free(p);
	}
	list.head = list.tail = NULL;
	
	return 0;
}
