#include <stdio.h>
#include <math.h>
#define true 1
#define false 0
//O(log(number)) base 10
int isPalindrome(int number)
{
	return (reversNumber(number) == number) ? true : false;
}
//O(log(number)) base 10
int reversNumber(int number)
{
	if (!number)
		return 0;
	return (number % 10) * pow(10, floor(log10(number))) + reversNumber(number / 10);
}
//O(log(number)) base 10
int isArmstrong_t(int number, int digit)
{
	if (!number)
		return 0;
	return pow(number % 10, digit) + isArmstrong_t(number / 10, digit);
}
//O(log(number)) base 10
int isArmstrong(int number)
{
	return (isArmstrong_t(number, log10(number) + 1) == number) ? true : false;
}
