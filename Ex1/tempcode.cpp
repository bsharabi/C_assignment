//O{n*log(number))
int isPalindrome(int number) {
	if (number == -1)
		return 1;
	int st = number % 10;
	int tempLoop = number;
	int en=-1,temp=1;
	number = 0;
	if(tempLoop>99)
		//O(log(number)) base 10
	while (tempLoop /=  10) {
		int digit = (tempLoop>9)?tempLoop % 10:0;
		if (tempLoop <= 9)
			en = tempLoop;
		number += (digit!=0)?temp * digit:0;
		temp *= 10;
	}
	else {
		if(tempLoop>9)
			en = (tempLoop/10)%10;
		else
			en= tempLoop % 10;
		number = -1;
	}
	if (st == en) {

		return	isPalindrome(number);
	}
	 return 0;
}