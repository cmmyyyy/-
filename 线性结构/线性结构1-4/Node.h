#include <stdio.h>
#include <assert.h>
#include <malloc.h>
typedef int Dataelem;

struct Node {
	Dataelem data;
	struct Node* next;
};

typedef struct Node Position;

struct List {
	struct Node* head;
	struct Node* tail;
};

struct Node* NewNode()
{
	struct Node* p= (struct Node*)malloc(sizeof(struct Node));
	assert(p != NULL);
	return p;
}
struct List create()
{
	struct List list;
	list.head = list.tail = (struct Node*)malloc(sizeof(struct Node));
	if (list.head != NULL)
		list.head->next = NULL;
	return list;
}
int NodeInsert(struct List list, int num)
{
	struct Node* q = NewNode();
	q->data = num;
	struct Node* p = list.head;
	while (p->next && num > p->next->data)
	{
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int Print(struct List list)
{
	printf("(");
	struct Node* p = list.head->next;
	printf("%d", p->data);
	p = p->next;
	while (p)
	{
		printf(",%d", p->data);
		p = p->next;
	}
	printf(")");
	return 0;
}

int Destroy(struct List list)
{
	struct Node* p = list.head;
	while (p)
	{
		struct Node* la = p->next;
		free(p);
		p = la;
	}
	return 0;
}

struct List AddList(struct List plist, struct List qlist)
{
	if (plist.head->next->data > qlist.head->next->data) 
	{
		struct List li;
		li = plist;
		plist = qlist;
		qlist = li;
	}//交换p、q，保持递增
	struct List list = create();
	if (list.head == NULL)
		return list;
	struct Node* s = NewNode();
	s = plist.head->next;
	while (s != NULL)
	{
		struct Node* p = NewNode();
		p->data = s->data;
		list.tail->next = p;
		p->next = NULL;
		list.tail = p;
		s = s->next;
	}
	s = qlist.head->next;
	while (s != NULL)
	{
		struct Node* p = NewNode();
		p->data = s->data;
		list.tail->next = p;
		p->next = NULL;
		list.tail = p;
		s = s->next;
	}
	return list;
}

struct List ListInvert(struct List list)
{
	struct List i_list = create();
	struct Node* p = list.head->next;
	while (p != NULL)
	{
		struct Node* ad_head = NewNode();
		ad_head->next = i_list.head;
		i_list.head = ad_head;
		i_list.head->next->data = p->data;
		p = p->next;
	}
	return i_list;
}

int SeperateNode(struct List list)
{
	struct List sep_list = create();
	struct Node* s = list.head;
	while (s->next != NULL)
	{
		if (s->next->data % 2 == 0)
		{
			NodeInsert(sep_list, s->next->data);
			s->next = s->next->next;
			
		}
		s = s->next;
	}
	Print(list);
	printf("\n");
	Print(sep_list);
	printf("\n");
	return 0;
}