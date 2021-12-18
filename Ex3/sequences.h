/**
 * @file sequence.h
 * @author Barak Sharabi (https://github.com/bsharabi) 
 * @brief 
 * @version 0.1
 * @date 2021-12-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NO_OF_CHARS 256
#define TXT 1024
#define WORD 30
/**
 * @brief finds all minimal sequences in txt with the same gimatric value as word
 */
void Gematria(char* txt,char* word );

/**
 * @brief finds all minimal sequences in txt that are atbash or the reversed atbash of word
 */
void Atbash(char* txt,char* word );

/**
 * @brief finds all minimal sequences in txt that are constructed ONLY from (all) characters in word and whitespaces
 */
void Anagram(char* txt,char* word );