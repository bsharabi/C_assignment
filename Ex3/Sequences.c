#include "sequences.h"
char *strrevers(char *str)
{
    char *p1, *p2;
    if (!str || !*str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

int gematricSum(char *word)
{
    //init sum and i to zero
    int sum = 0, i = 0;
    while (*(word + i) != '\0')
    {
        sum += (isalpha(*(word + i)) > 0) ? toupper(*(word + i)) - 64 : 0;
        i++;
    }
    return sum;
}

void Gematria(char *txt, char *word)
{
    int gematric = gematricSum(word);
    int i = 0, j = 0, sum = 0;
    int flag = 0;
    while (*(txt + i) != '\0' && *(txt + j) != '\0')
    {
        if (*(txt + i) == ' ' && sum == 0) {
			i++;
			continue;
		}
        sum += (isalpha(*(txt + j)) > 0) ? toupper(*(txt + j)) - 64 : 0;
        if (sum < gematric)
        {
            while (*(txt + ++j) != '\0' && isalpha(*(txt + j)) < 1)
                ;
            continue;
        }
        else if (sum > gematric)
        {
            while (*(txt + ++i) != '\0' && (isalpha(*(txt + i)) == 0 || (toupper(*(txt + i)) - 64) > gematric));
                
        }
        else
        {
            int k = i;
            if (flag > 0)
                printf("%c", '~');
            while (k <= j)
                printf("%c", *(txt + k++));
            while (*(txt + ++i) != '\0' && (isalpha(*(txt + i)) == 0 || (toupper(*(txt + i)) - 64) > gematric))
                ;
            flag++;
        }
        j = i;
        sum = 0;
    }
    printf("\n");
}

char *wordToAtbash(char *word)
{
    char *atbash = (char *)malloc(strlen(word) * sizeof(char));
    strcpy(atbash, word);
    int i = 0;
    char c = 0;
    while ((c = *(atbash + i)) != '\0')
        if (isalpha(c) > 0)
            *(atbash + i++) = isupper(c) ? 91 - (c - 64) : 123 - (c - 96);
        else
            i++;
    return atbash;
}

void Atbash(char *txt, char *word)
{
    //convert word to atbash
    char *atbash = wordToAtbash(word);
    //new allocate to revers atbash
    char *atbashFlip = (char *)malloc(strlen(atbash) * sizeof(char));
    //copy atbash word
    strcpy(atbashFlip, atbash);
    //revers atbash word to the new var allocate
    atbashFlip = strrevers(atbashFlip);
    int lenght = strlen(atbash);
    int i = 0, j = 0;
    int flag = 0;
    while (*(txt + i) != '\0')
    {
        while (lenght - j)
        {
            if (*(txt + i + j) == *(atbash + j) || *(txt + i + j) == *(atbashFlip + j))
            {
                j++;
                continue;
            }
            break;
        }
        if (lenght - j == 0)
        {
            int k = i;
            if (flag > 0)
                printf("%c", '~');
            while (k < i + j)
                printf("%c", *(txt + k++));
            flag++;
        }
        j = 0;
        i++;
    }
    printf("\n");
    free(atbash);
    free(atbashFlip);
}

void angramInit(int angram[NO_OF_CHARS], char *word)
{
    int l = 0;
    char c;
    while ((c = *(word + l)) != '\0') {
		(*(angram + c))=0;
		l++;
	}
	l = 0;
	while ((c = *(word + l)) != '\0') {
		(*(angram + c))++;
		l++;
	}
}

void Anagram(char *txt, char *word)
{
    //txt=n, word=m
    //O(n)
    int lengthTxt = strlen(txt);
    //O(m)
    int lengthWord = strlen(word);
    int count = lengthWord;
    if (lengthTxt == 0 || lengthWord == 0)
        return;
    //O(1)
    int angaramArray[NO_OF_CHARS] = {0};
    //O(m)
    angramInit(angaramArray, word);
    //O(1)
    int i = 0, j = 0, flag = 0;
    char c = *(txt + i + j);
    do
    {
        if (count == 0)
        {
            int k = i;
            if (flag > 0)
                printf("%c", '~');
            while (k < i + j)
                printf("%c", *(txt + k++));
            flag++;
            angramInit(angaramArray, word);
            count = lengthWord;
            i++;
            j = 0;
        }
        else if (c == ' ' && count == lengthWord)
        {
            i++;
            continue;
        }
        else if (c == ' ')
            j++;
        else if ((*(angaramArray + c)) != 0)
        {
            (*(angaramArray + c))--;
            count--;
            j++;
        }
        else if (*(angaramArray + c) == 0)
        {
            i++;
            j = 0;
            angramInit(angaramArray, word);
            count = lengthWord;
        }
    } while ((c = *(txt + i + j)) != '\0' || count == 0);
}