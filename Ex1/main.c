#include <stdio.h>
void main() {
	int num1, num2;
	printf("Enter two numbers to set a range\n");
	scanf_s("%d %d", &num1,&num2);
	printf("Range is [%d , %d].\n", num1,num2);
	for (int i = num1;i <= num2;i++) {
		 isArmstrong(num1);
		 isPalindrome(num1);
		 isPrime(num1);
		 isStrong(num1);
	}
}
