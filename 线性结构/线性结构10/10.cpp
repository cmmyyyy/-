#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include "Node.h"

int main()
{
	struct stack sta;
	sta.head = (struct Node*)malloc(sizeof(struct Node)*100);
	struct queue que;
	que.head = que.tail = _NewNode();
	int n;
	while (scanf("%d", &n) == 1)
	{
		if (n == 0)break;
		if (n > 0) {
			sta = stack_push(sta, n);
		}
		if (n < 0) {
			que = queue_push(que, n);
		}
		if (getchar() == '\n')break;
	}
	stack_Print(sta);
	queue_Print(que);
	free(sta.head);
	sta.head = NULL;
	sta.length = 0;
	return 0;
}