#include <stdio.h>
#include <stdlib.h>

void dec2bin(int dec, char *bin, int pos)
{
	if(dec <= 0){
		if(0 == pos) return;
		*bin = '0';
		*(bin+1) = 0;
		dec2bin(dec, bin + 1, pos - 1);
	}
	if(dec % 2) *bin = '1';
	else *bin = '0';
	*(bin + 1) = 0;
	dec2bin(dec / 2, bin + 1, pos - 1);
}

int validate(const char *goodip, const char *testip, int mask)
{
	if(mask == 0) return 1;
	if(mask > 32) mask = 32;
	if(NULL == goodip || NULL == testip) return 0;
	int one;
	int two;
	int three;
	int four;
	char bin1[40];
	char bin2[40];
	char first[9];
	char second[9];
	char third[9];
	char fourth[9];
	//convert ip to bitstring
	sscanf(goodip, "%d.%d.%d.%d", &one, &two, &three, &four);
	dec2bin(one, first, 8);
	dec2bin(two, second, 8);
	dec2bin(three, third, 8);
	dec2bin(four, fourth, 8);
	sprintf(bin1, "%s%s%s%s", fourth, third, second, first);
	printf("good ip bitstring=%s\n", bin1);
	
	sscanf(testip, "%d.%d.%d.%d", &one, &two, &three, &four);
	dec2bin(one, first, 8);
	dec2bin(two, second, 8);
	dec2bin(three, third, 8);
	dec2bin(four, fourth, 8);
	sprintf(bin2, "%s%s%s%s", fourth, third, second, first);
	printf("test ip bitstring=%s\n", bin2);

	//compare ip address are backwards, check from end to begining
	int x = 0;
	for(; x < mask; ++x){
		int index = 32 - x - 1;
		//mismatch
		if(bin1[index] != bin2[index]) return 0;
	}
	return 1;
}

int main()
{
	int dec = 10;
	char bin[9] = {0};
	dec2bin(dec, bin, 8);

	const char *goodip = "192.168.1.1";
	const char *testip = "192.168.1.2";
	printf("result=%s ret=%d\n", bin, validate(goodip, testip, 30));
	return 0;
}
