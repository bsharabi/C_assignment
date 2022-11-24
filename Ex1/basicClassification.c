
#include "NumClass.h"

//O(log(n)) base 10 n is a digit of number
int isStrong(int n)
{
	const int Factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
	int factSum = 0;
	int temp = n;
	do
		factSum += Factorial[temp % 10];
	while (temp /= 10);
	return (factSum == n) ? true : false;
}
//O(n)
int isPrime(int n)
{
	if (n == 1)
		return true;
	for (int i = 2; i <= sqrt(n); ++i)
		if (n % i == 0)
			return false;
	return true;
}
