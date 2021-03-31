#include <stdio.h>
#include <assert.h>
#include <malloc.h>

struct Node {
	int digit;
	struct Node* next;
};

struct stack {
	int length=0;
	struct Node* head;
};

struct queue {
	struct Node* head, * tail;
};

struct Node* _NewNode()
{
	struct Node* p;
	p = (struct Node*)malloc(sizeof(struct Node));
	assert(p != NULL);
	return p;
}

struct stack stack_push(struct stack sta, int n)
{
	if (sta.length < 100) {
		sta.head[sta.length].digit = n;
		sta.length++;
	}
	return sta;
}
int stack_Print(struct stack sta)
{
	while (sta.length != 0)
	{
		printf("%d ", sta.head[sta.length - 1].digit);
		sta.length--;
	}
	printf("\n");
	return 0;
}

struct queue queue_push(struct queue que, int n)
{
	struct Node* p = _NewNode();
	p->digit = n;
	p->next = NULL;
	que.tail->next = p;
	que.tail = p;
	return que;
}
int queue_Print(struct queue que)
{
	que.head = que.head->next;
	while (que.head != que.tail)
	{
		printf("%d ", que.head->digit);
		struct Node* p=que.head;
		que.head = que.head->next;
		free(p);
	}
	printf("%d\n", que.head->digit);
	free(que.head);
	que.head = que.tail = NULL;
	return 0;
}



