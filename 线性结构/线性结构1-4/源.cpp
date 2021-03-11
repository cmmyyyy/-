#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include "Node.h"



int fun1(struct List plist,struct List qlist)
{
	Print(plist);
	printf("\n");
	Print(qlist);
	printf("\n");

	return 0;
}

int fun2(struct List plist, struct List qlist)
{
	struct List list = AddList(plist, qlist);
	Print(list);
	printf("\n");
	Destroy(list);
	return 0;

}

int fun3(struct List plist, struct List qlist)
{
	struct List i_list = ListInvert(plist);
	Print(i_list);
	printf("\n");
	i_list = ListInvert(qlist);
	Print(i_list);
	printf("\n");
	Destroy(i_list);
	return 0;
}

int fun4(struct List list)
{
	SeperateNode(list);
	return 0;
}

int main()
{
	struct List plist = create();//正数链表
	struct List qlist = create();//负数链表

	int num;
	while (scanf("%d", &num))
	{
		if (num == 0)break;
		if (num > 0)NodeInsert(plist, num);
		if (num < 0)NodeInsert(qlist, num);
	}
	struct List addlist = AddList(plist, qlist);
	fun1(plist, qlist);
	fun2(plist, qlist);
	fun3(plist, qlist);
	fun4(addlist);


	Destroy(plist);
	Destroy(qlist);
	
}