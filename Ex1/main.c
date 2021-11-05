#include <stdio.h>
#include <math.h>
#include "NumClass.h"
#define true 1
#define false 0
void main()
{
	int num1, num2;
	printf("Enter two numbers to set a range\n");
	scanf("%d %d", &num1, &num2);
	printf("Range is [%d , %d].\n", num1, num2);
	int chooise = 4;
	while (chooise)
	{
		switch (chooise)
		{
		case 1:
			printf("\nThe Strong numbers are:");
			break;
		case 2:
			printf("\nThe Prime numbers are:");
			break;
		case 3:
			printf("\nThe Palindromes are:");
			break;
		case 4:
			printf("The Armstrong numbers are:");
			break;
		}
		for (int i = num1; i <= num2; i++)
		{
			if (chooise == 4 && isArmstrong(i))
				printf(" %d", i);
			else if (chooise == 3 && isPalindrome(i))
				printf(" %d", i);
			else if (chooise == 2 && isPrime(i))
				printf(" %d", i);

			else if (chooise == 1 && isStrong(i))
				printf(" %d", i);
		}
		chooise--;
	}
	printf("\n");
}
