#include<stdio.h>
#include<malloc.h>
#include<assert.h>

struct Node {
	int digit;
	struct Node* next, * prev;
};

struct BN {
	int DigitCount;
	char sign = 0;
	struct Node* head, * tail;
};

struct Node* _NewNode()
{
	struct Node* p;
	p = (struct Node*)malloc(sizeof(struct Node));
	assert(p != NULL);
	return p;
}

int _AppendDigit(struct BN* bn, int digit)
{
	if (bn->DigitCount == 1 && bn->tail->digit == 0) {
		bn->tail->digit = digit;
		return 0;
	}
	struct Node* p = _NewNode();
	p->digit = digit;
	p->next = NULL;
	p->prev = bn->tail;
	bn->tail->next = p;
	bn->tail = p;
	bn->DigitCount++;
	return 0;
}

int _Normalize(struct BN* bn)
{
	if (bn->DigitCount == 0) {
		_AppendDigit(bn, 0);
	}
	while (bn->DigitCount > 1 && bn->head->next->digit == 0) {
		struct Node* p;
		p = bn->head->next;
		bn->head->next = bn->head->next->next;
		free(p);
		bn->DigitCount--;
	}
	return 0;
}

int _InitBN(struct BN* bn)
{
	struct Node* p = _NewNode();
	bn->head = bn->tail = p;
	p->next = p->prev = NULL;
	bn->DigitCount = 0;
	return 0;
}

struct BN InputBN()
{
	struct BN result;
	_InitBN(&result);
	char ch;
	ch = getchar();
	if (ch == '-') {
		result.sign = ch;
		ch = getchar();
	}
	while (ch < '0' || ch>'9')
		ch = getchar();
	while (ch >= '0' && ch <= '9') {
		_AppendDigit(&result, ch - '0');
		ch = getchar();
	}
	_Normalize(&result);
	return result;
};

int PrintBN(struct BN bn)
{
	assert(bn.DigitCount > 0 && bn.head->next != NULL);
	struct Node* la = bn.head->next;
	if (bn.sign == '-')printf("-");
	while (la) {
		printf("%d", la->digit);
		la = la->next;
	}
	return 0;

}

struct BN SubUBN(struct BN bn1, struct BN bn2)
{
	
	struct BN bn;
	_InitBN(&bn);
	int n = bn1.DigitCount;
	int m = bn2.DigitCount;
	int x = 0;
	while (m-- && n--)
	{
		struct Node* p = _NewNode();
		p->digit = bn1.tail->digit - bn2.tail->digit + x;
		if (p->digit >= 0)x = 0;
		if (p->digit < 0) {
			x = -1;
			p->digit += 10;
		}
		if (bn.head->next != NULL) {
			p->prev = bn.head;
			p->next = bn.head->next;
			bn.head->next->prev = p;
			bn.head->next = p;
			bn.DigitCount++;
		}
		if (bn.head->next == NULL) {
			bn.head->next = p;
			p->next = NULL;
			p->prev = bn.head;
			bn.tail = p;
			bn.DigitCount++;
		}
		bn1.tail = bn1.tail->prev;
		bn2.tail = bn2.tail->prev;
	}
	while (n--)
	{
		struct Node* p = _NewNode();
		p->digit = bn1.tail->digit + x;
		if (p->digit >= 0)
			x = 0;
		if (p->digit < 0) {
			x = -1;
			p->digit += 10;
		}
		p->prev = bn.head;
		p->next = bn.head->next;
		bn.head->next->prev = p;
		bn.head->next = p;
		bn.DigitCount++;
		bn1.tail = bn1.tail->prev;
	}
	_Normalize(&bn);
	return bn;
}

struct BN AddUBN(struct BN bn1, struct BN bn2)
{
	struct BN bn;
	_InitBN(&bn);
	int n = bn1.DigitCount;
	int m = bn2.DigitCount;
	int x = 0;
	while (m-- && n--)
	{
		struct Node* p = _NewNode();
		p->digit = bn1.tail->digit + bn2.tail->digit + x;
		x = p->digit / 10;
		p->digit = p->digit % 10;
		if (bn.head->next != NULL) {
			p->prev = bn.head;
			p->next = bn.head->next;
			bn.head->next->prev = p;
			bn.head->next = p;
			bn.DigitCount++;
		}
		if (bn.head->next == NULL) {
			bn.head->next = p;
			p->next = NULL;
			p->prev = bn.head;
			bn.tail = p;
			bn.DigitCount++;
		}
		bn1.tail = bn1.tail->prev;
		bn2.tail = bn2.tail->prev;
	}
	while (n--)
	{
		struct Node* p = _NewNode();
		p->digit = bn1.tail->digit + x;
		x = p->digit / 10;
		p->digit = p->digit % 10;
		p->prev = bn.head;
		p->next = bn.head->next;
		bn.head->next->prev = p;
		bn.head->next = p;
		bn.DigitCount++;
		bn1.tail = bn1.tail->prev;
	}
	_Normalize(&bn);
	return bn;

}

int Destroy(struct BN bn)
{
	struct Node* p = bn.head;
	while (p->next != NULL)
	{
		struct Node* la = p->next;
		free(p);
		p = la;
	}
	free(p);
	bn.head = bn.tail = NULL;
	return 0;
}


int UBNcmp(struct BN bn1,struct BN bn2)
{//符号相同情况下
	int x = 0;
	if (bn1.DigitCount > bn2.DigitCount)
		return 1;
	if (bn1.DigitCount < bn2.DigitCount)
		return -1;

	struct Node* p = bn1.head->next, * q = bn2.head->next;
	while (p != NULL && q != NULL) {
		x = p->digit - q->digit;
		if (x > 0)
			return 1;

		if (x < 0)
			return -1;

		p = p->next;
		q = q->next;
	}
	return 0;
}

int BNcmp(struct BN bn1, struct BN bn2)
{
	int x = 0;
	if (bn1.sign == '-' && bn2.sign == 0)return -1;
	if (bn1.sign == 0 && bn2.sign == '-')return 1;
	x = UBNcmp(bn1, bn2);
	if (bn1.sign == 0)
		return x;
	if (bn1.sign == '-') {
		if (x == 1)return -1;
		if (x == -1)return 1;
	}
	return 0;

}

struct BN AddBN(struct BN bn1, struct BN bn2)
{
	struct BN result;
	if (UBNcmp(bn1, bn2) == -1) {
		struct BN bn;
		bn = bn1;
		bn1 = bn2;
		bn2 = bn;
	}
	if (bn1.sign == bn2.sign) {
		result = AddUBN(bn1, bn2);
		result.sign = bn1.sign;
	}
	else {
		result = SubUBN(bn1, bn2);
		result.sign = bn1.sign;
	}
	return result;
}

struct BN SubBN(struct BN bn1, struct BN bn2)
{
	struct BN result;
	int x = 0;
	if (UBNcmp(bn1, bn2) == -1) {
		struct BN bn;
		bn = bn1;
		bn1 = bn2;
		bn2 = bn;
		x = 1;
	}
	if (bn1.sign == bn2.sign) {
		result = SubUBN(bn1, bn2);
		result.sign = bn1.sign;
	}
	else {
		result = AddUBN(bn1, bn2);
		result.sign = bn1.sign;
	}
	if (x == 1 && result.sign == 0)result.sign = '-';
	else if (x == 1 && result.sign == '-')result.sign = 0;
	return result;
}