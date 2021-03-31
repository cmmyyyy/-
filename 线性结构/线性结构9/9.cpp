#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <assert.h>
#include "BN.h"

int main()
{
	struct BN bn1, bn2;
	bn1 = InputBN();
	bn2 = InputBN();

	struct BN addbn = AddBN(bn1, bn2);
	struct BN subbn = SubBN(bn1, bn2);
	PrintBN(addbn);
	printf("\n");
	PrintBN(subbn);
	Destroy(bn1);
	Destroy(bn2);
	Destroy(addbn);
	Destroy(subbn);

}