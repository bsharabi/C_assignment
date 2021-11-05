#include <math.h>
#include <stdio.h>
#define true 1
#define false 0

int isPalindrome(int n) {
	int palindrome = 0;
	int temp = n;
	do
		palindrome = palindrome * 10 + temp % 10;
	 while (temp /= 10);
	 return (n == palindrome) ? true : false;
}
int isArmstrong(int n) {
	int nDigits = floor(log10(abs(n))) + 1;
	int temp = n;
	int armsNumber = 0;
	do
		armsNumber += pow(temp % 10, nDigits);
	while (temp/=10);
	return (n == armsNumber) ? true : false;
}