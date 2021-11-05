#include <math.h>
#include <stdio.h>
#define true 1
#define false 0
//O(log(number)) base 10
int isPalindrome(int number)
{
	int palindrome = 0;
	int temp = number;
	do
		palindrome = palindrome * 10 + temp % 10;
	while (temp /= 10);
	return (number == palindrome) ? true : false;
}
//O(log(number)) base 10
int isArmstrong(int number)
{
	number = abs(number);
	int nDigits = floor(log10(abs(number))) + 1;
	int temp = number;
	int armsNumber = 0;
	do
		armsNumber += pow(temp % 10, nDigits);
	while (temp /= 10);
	return (number == armsNumber) ? true : false;
}