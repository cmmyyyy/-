#include<stdio.h>
#include<malloc.h>
#include<assert.h>

struct Node {
	int digit;
	struct Node* next, * prev;
};

struct UBN {
	int DigitCount;
	struct Node* head, * tail;
};

struct Node* _NewNode()
{
	struct Node* p;
	p = (struct Node*)malloc(sizeof(struct Node));
	assert(p != NULL);
	return p;
}

int _AppendDigit(struct UBN* ubn, int digit)
{
	if (ubn->DigitCount == 1 && ubn->tail->digit == 0) {
		ubn->tail->digit = digit;
		return 0;
	}
	struct Node* p = _NewNode();
	p->digit = digit;
	p->next = NULL;
	p->prev = ubn->tail;
	ubn->tail->next = p;
	ubn->tail = p;
	ubn->DigitCount++;
	return 0;
}

int _Normalize(struct UBN* ubn)
{
	if (ubn->DigitCount == 0) {
		_AppendDigit(ubn, 0);
	}
	while (ubn->DigitCount > 1 && ubn->head->next->digit == 0) {
		struct Node* p;
		p = ubn->head->next;
		ubn->head->next = ubn->head->next->next;
		free(p);
		ubn->DigitCount--;
	}
	return 0;
}

int _InitUBN(struct UBN* ubn)
{
	struct Node* p = _NewNode();
	ubn->head = ubn->tail = p;
	p->next = p->prev = NULL;
	ubn->DigitCount = 0;
	return 0;
}



struct UBN InputUBN()
{
	struct UBN result;
	_InitUBN(&result);
	char ch;
	do
		ch = getchar();
	while (ch < '0' || ch>'9');
	while (ch >= '0' && ch <= '9') {
		_AppendDigit(&result, ch - '0');
		ch = getchar();
	}
	_Normalize(&result);
	return result;
};

int PrintUBN(struct UBN ubn)
{
	assert(ubn.DigitCount > 0 && ubn.head->next != NULL);
	struct Node* la = ubn.head->next;
	while (la) {
		printf("%d", la->digit);
		la = la->next;
	}
	return 0;

}

struct UBN SubUBN(struct UBN ubn1, struct UBN ubn2)
{

	struct UBN ubn;
	_InitUBN(&ubn);
	int n = ubn1.DigitCount;
	int m = ubn2.DigitCount;
	int x = 0;
	while (m-- && n--)
	{
		struct Node* p = _NewNode();
		p->digit = ubn1.tail->digit - ubn2.tail->digit + x;
		if (p->digit >= 0)x = 0;
		if (p->digit < 0) {
			x = -1;
			p->digit += 10;
		}
		if (ubn.head->next != NULL) {
			p->prev = ubn.head;
			p->next = ubn.head->next;
			ubn.head->next->prev = p;
			ubn.head->next = p;
			ubn.DigitCount++;
		}
		if (ubn.head->next == NULL) {
			ubn.head->next = p;
			p->next = NULL;
			p->prev = ubn.head;
			ubn.tail = p;
			ubn.DigitCount++;
		}
		ubn1.tail = ubn1.tail->prev;
		ubn2.tail = ubn2.tail->prev;
	}
	while (n--)
	{
		struct Node* p = _NewNode();
		p->digit = ubn1.tail->digit + x;
		if (p->digit >= 0)
			x = 0;
		if (p->digit < 0) {
			x = -1;
			p->digit += 10;
		}
		p->prev = ubn.head;
		p->next = ubn.head->next;
		ubn.head->next->prev = p;
		ubn.head->next = p;
		ubn.DigitCount++;
		ubn1.tail = ubn1.tail->prev;
	}
	_Normalize(&ubn);
	return ubn;
}

struct UBN AddUBN(struct UBN ubn1, struct UBN ubn2)
{
	struct UBN ubn;
	_InitUBN(&ubn);
	int n = ubn1.DigitCount;
	int m = ubn2.DigitCount;
	int x = 0;
	while (m-- && n--)
	{
		struct Node* p = _NewNode();
		p->digit = ubn1.tail->digit + ubn2.tail->digit + x;
		x = p->digit / 10;
		p->digit = p->digit % 10;
		if (ubn.head->next != NULL) {
			p->prev = ubn.head;
			p->next = ubn.head->next;
			ubn.head->next->prev = p;
			ubn.head->next = p;
			ubn.DigitCount++;
		}
		if (ubn.head->next == NULL) {
			ubn.head->next = p;
			p->next = NULL;
			p->prev = ubn.head;
			ubn.tail = p;
			ubn.DigitCount++;
		}
		ubn1.tail = ubn1.tail->prev;
		ubn2.tail = ubn2.tail->prev;
	}
	while (n--)
	{
		struct Node* p = _NewNode();
		p->digit = ubn1.tail->digit + x;
		x = p->digit / 10;
		p->digit = p->digit % 10;
		p->prev = ubn.head;
		p->next = ubn.head->next;
		ubn.head->next->prev = p;
		ubn.head->next = p;
		ubn.DigitCount++;
		ubn1.tail = ubn1.tail->prev;
	}
	_Normalize(&ubn);
	return ubn;

}

int Destroy(struct UBN ubn)
{
	struct Node* p = ubn.head;
	while (p->next != NULL)
	{
		struct Node* la = p->next;
		free(p);
		p = la;
	}
	free(p);
	ubn.head = ubn.tail = NULL;
	return 0;
}