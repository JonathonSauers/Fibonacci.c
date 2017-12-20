// Jonathon Sauers
// jo046326
// COP 3502, Spring 2017
// Fibonacci.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Fibonacci.h"

// Return a pointer to a new, dynamically allocated HugeInteger
// struct that contains the result of adding the huge integers
// represented by p and q.
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{
  int i, carryTemp = 0, pTemp = 0, qTemp = 0, sumTemp = 0;
  HugeInteger *total = malloc(sizeof(HugeInteger));

  // Make sure everything we need is valid.
  if(total == NULL || p == NULL || q == NULL)
    return NULL;

  // Determines which is bigger (p or q), and sets that value to
  // HugeInteger total->length.
  if(p->length > q->length)
    total->length = p->length + 1;

  else
    total->length = q->length + 1;

  total->digits = calloc(total->length, sizeof(int));

  // Adds p and q.
  for(i = 0; i < total->length; i++)
  {
    // Determines the value at index i in p which will be added.
    // If we run out of numbers, this will be set to 0.
    if(i > p->length - 1)
      pTemp = 0;
    else
      pTemp = p->digits[i];

    // Determines the value at index i in q which will be added.
    // If we run out of numbers, this will be set to 0.
    if(i > q->length - 1)
      qTemp = 0;
    else
      qTemp = q->digits[i];

    // Adds the values of p and q plus the carryTemp
    // (i.e. if p at i and q at i are greater than 9)
    sumTemp = carryTemp + pTemp + qTemp;

    // If sumTemp > 9, we need only the ones value.
    // The carryTemp will take care of the tens value.
    if(sumTemp > 9)
    {
      sumTemp -= 10;
      carryTemp = 1;
    }
    else
      carryTemp = 0;

    total->digits[i] += sumTemp;
  }

  // Accounts for the carryTemp value for the last digit.
  if(carryTemp == 1)
    total->digits[i++] = 1;

  // Corrects the length of total if needed.
  if(total->length == i && total->digits[i-1] == 0)
    total->length -= 1;

  return total;
}

// Destroy any and all dynamically allocated memory with HugeInteger p.
HugeInteger *hugeDestroyer(HugeInteger *p)
{
  if(p == NULL)
    return NULL;

  // If p has numbers, it needs to be freed.
  if(p->digits != NULL)
  {
    free(p->digits);
    free(p);
  }

  return NULL;
}

// Convert a number from string format to HugeInteger format.
HugeInteger *parseString(char *str)
{
  int i = 0, j = 0, length;
  char *emptyStr = "";
  HugeInteger *temp;

  if(str == NULL)
    return NULL;

  temp = malloc(sizeof(HugeInteger));

  if(temp == NULL)
  {
    free(temp);
    return NULL;
  }

  // If str is "", we treat it as a 0
  if(strcmp(emptyStr, str) == 0)
    str = "0";

  // Determines how long str is, and sets HugeInteger temp values.
  temp->length = strlen(str);
  length = temp->length;
  temp->digits = calloc(length + 1, sizeof(int));

  if(temp->digits == NULL)
  {
    free(temp);
    return NULL;
  }

  // Converts the string to HugeInteger in ASCII, 0 => 48.
  while(length >= 0)
  {
    temp->digits[i] = str[length - 1] - 48;
    i++;
    length--;
  }

  return temp;
}

// Convert the unsigned integer n to HugeInteger format/
HugeInteger *parseInt(unsigned int n)
{
  int i = 0, length = 1;
  unsigned int temp = 0, num = n;

  HugeInteger *huge = malloc(sizeof(HugeInteger));

  if(huge == NULL)
    return NULL;

  huge->digits = calloc(10000, sizeof(int));

  if(huge->digits == NULL)
  {
    free(huge);
    return NULL;
  }

  // Finds the length of num.
  while(num > 1)
  {
    if(num /= 10)
      length++;
  }

  huge->length = length;

  // Converts the unsigned int to HugeInteger.
  while(length >= 0)
  {
    temp = n % 10;
    huge->digits[i] = temp;
    n = (n / 10);
    i++;
    length--;
  }
  return huge;
}

// Convert the integer represented by p to a dynamically allocated
// unsigned int, and return a pointer to that value.
unsigned int *toUnsignedInt(HugeInteger *p)
{
  int i, tens = 1;
  unsigned int *temp, num = 0;

  if(p == NULL || p->length > 10)
    return NULL;

  temp = malloc(sizeof(unsigned int));

  if(temp == NULL)
    return NULL;

  for(i = 0; i < p->length; i++)
  {
    // Makes sure num doesn't exceed the max value allowed.
    if(num > UINT_MAX)
    {
      free(temp);
      return NULL;
    }

    // Converts p to unsigned int temp1.
    num += (p->digits[i] % 10) * tens;
    tens *= 10;
  }

  *temp = num;

  return temp;
}

// An iterative fibonacci sequence which runs in O(nk).
HugeInteger *fib(int n)
{
  int i;

  HugeInteger *fib = malloc(sizeof(HugeInteger));
  HugeInteger *temp1 = malloc(sizeof(HugeInteger));
  HugeInteger *temp2 = malloc(sizeof(HugeInteger));

  if(fib == NULL || temp1 == NULL || temp2 == NULL)
    return NULL;

  fib->digits = calloc(10000, sizeof(int));
  temp1->digits = calloc(10000, sizeof(int));
  temp2->digits = calloc(10000, sizeof(int));

  if(fib->digits == NULL || temp1->digits == NULL || temp2->digits == NULL)
  {
    free(fib);
    free(temp1);
    free(temp2);
    return NULL;
  }

  // The first value of the fibonacci sequence.
  if(n == 0)
  {
    fib = parseInt(0);
    return fib;
  }

  // The second value of the fibonacci sequence.
  if(n == 1)
  {
    fib = parseInt(1);
    return fib;
  }

  // Store the first two numbers of the fibonacci sequence.
  temp2 = parseInt(0);
  temp1= parseInt(1);

  // Iterative fibonacci sequence in O(n).
  for(i = 0; i < n-1; i++)
  {
    fib = hugeAdd(temp1,temp2);
    temp2 = temp1;
    temp1 = fib;
  }

  return fib;
}

// How difficult I found this assignment.
double difficultyRating(void)
{
  return 3.5;
}

// How long it took me to complete this assignment.
double hoursSpent(void)
{
  return 16.0;
}
