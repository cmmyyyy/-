#include<stdio.h>
#include<assert.h>
#include"UBigNumber.h"

int main()
{
	struct UBN ubn1, ubn2;
	ubn1 = InputUBN();
	ubn2 = InputUBN();
	
	struct UBN addubn = AddUBN(ubn1, ubn2);
	struct UBN sububn = SubUBN(ubn1, ubn2);
	PrintUBN(addubn);
	printf("\n");
	PrintUBN(sububn);
	Destroy(ubn1);
	Destroy(ubn2);
	Destroy(addubn);
	Destroy(sububn);
	
}