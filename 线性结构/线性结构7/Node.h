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
	struct Node* p = (struct Node*)malloc(sizeof(struct Node));
	assert(p != NULL);
	p->next = NULL;
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
struct List NodeInsert(struct List list, int num)
{
	struct Node* q = NewNode();
	q->data = num;
	q->next = NULL;
	struct Node* p = list.head;
	while (p->next && num > p->next->data)
	{
		p = p->next;
	}
	if (p->next != NULL)
	{
		q->next = p->next;
		p->next = q;
	}
	else {
		p->next = q;
		list.tail = q;
	}
	return list;
}

int Print(struct List list)
{
	
	struct Node* p = list.head->next;
	printf("%d", p->data);
	p = p->next;
	while (p)
	{
		printf(" %d", p->data);
		p = p->next;
	}
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
	list.head = list.tail = NULL;
	return 0;
}

struct List AddList(struct List plist, struct List qlist)
{
	if (plist.head != NULL && qlist.head != NULL && plist.head->next->data > qlist.head->next->data)
	{
		struct List li;
		li = plist;
		plist = qlist;
		qlist = li;
	}//
	struct List list = create();
	if (list.head == NULL)
		return list;
	struct Node* s = NewNode();
	if (plist.head != NULL) {
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
	}
	if (qlist.head != NULL) {
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