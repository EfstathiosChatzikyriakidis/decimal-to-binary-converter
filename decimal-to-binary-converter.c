/*
 *  Decimal To Binary Converter.
 *
 *  Copyright (C) 2008 Efstathios Chatzikyriakidis (contact@efxa.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* unsigned long long int: 0 to 18,446,744,073,709,551,615 */

/*
 * headers' includes.
 */

/* standard includes. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * defines.
 */

/* max line characters. */
#define MAX_LINE 1024

/* the translation base. */
#define TRANSLATION_BASE 2

/* new line character. */
#define NEW_LINE "\n"

/*
 * typedefs.
 */

/* boolean data type by using enumeration. */
typedef enum bool { false, true } bool;

/* const pointer to const char. */
typedef const char *const unique;

/* unsigned double long integer. */
typedef unsigned long long int u2long;

/*
 * function prototypes.
 */

/* my functions. */
void dec2bin (u2long, char *);
u2long my_pow (int, int);

/* global variables. */
static unique program_usage_a = "Usage:";
static unique program_usage_b = "<positive integer>";

/*
 * functions.
 */

/* the body of the program. */
int
main (int argc, char *argv[])
{
  /* local variables. */

  /* an array which contains a
     binary value as a string. */
  char binary[MAX_LINE] = { '\0' };

  /* the user inputs that number. */
  register int input_number = 0;

  /* the maximum number to print. */
  register u2long max_number;

  /* index which is used for the loop
     and decimal transformation, that
     is why it is unsigned 2 long int. */
  register u2long i;

  /* set all start variables to zero. */
  max_number = i = 0UL;

  /* check if the program called with args. */
  if (argc < 2)
    {
      fprintf (stdout, "%s %s %s", program_usage_a, argv[0], program_usage_b);
      fprintf (stdout, "%s", NEW_LINE);

      /* inform the proccess with error code. */
      return 1;
    }

  /* transform argument string to number. */
  input_number = atoi (argv[1]);

  /* is the number negative or zero? */
  if (input_number <= 0)
    {
      fprintf (stdout, "%s %s %s", program_usage_a, argv[0], program_usage_b);
      fprintf (stdout, "%s", NEW_LINE);
      return 1;
    }

  /* the input is a positive integer. */

  /* show calculate the maximum number to print. */
  max_number = my_pow (TRANSLATION_BASE, input_number);

  /* producing and printing the binary numbers. */
  while (true)
    {
      /* is used for the length of the binary array. */
      register int str_len;

      /* now transform the current number to
         binary and save it to binary array. */
      dec2bin (i, binary);

      /* count the length of the array. */
      str_len = strlen (binary);

      /* fill the gap with zeros.. */
      while (str_len < input_number)
        {
          fprintf (stdout, "%c", '0');
          str_len++;
        }

      /* print binary. */
      fprintf (stdout, "%s <- (%llu)", binary, i);

      /* dont print the last newline. */
      if (i + 1 != max_number)
        fprintf (stdout, "%s", NEW_LINE);

      /* is the current number the max number? */
      if (++i == max_number)
        break;
    }

  fprintf (stdout, "%s", NEW_LINE);

  /* exit success. */
  return 0;
}

/*
 the following function gets an unsigned long
 integer number and translates it to binary,
 and after that saves it to an array.
*/
void
dec2bin (u2long decimal, char *binary)
{
  register unsigned char remain;
  char temp[MAX_LINE];
  register int k = 0, n = 0;

  /* try to tranform and save it. */
  do
    {
      /* keep the remainer. */
      remain = decimal % 2;

      /* whittle down the decimal number. */
      decimal = decimal / 2;

      /* converts digit 0 or 1 to character '0' or '1'. */
      temp[k++] = remain + '0';
    }
  while (decimal > 0);

  /* reverse the spelling. */
  while (--k >= 0)
    binary[n++] = temp[k];

  binary[n] = '\0';                /* end with NULL. */
}

/* the following function tries to act like `pow()'. */
u2long
my_pow (int base, int power)
{
  /* keeps the result each time. */
  register u2long result;

  /* is used for the loop. */
  register int i;

  /* cases from math. */
  if (power == 0)
    return 1;
  if (power == 1)
    return base;

  /* otherwise. */

  /* calculate. */
  result = base;
  for (i = 1; i < power; i++)
    result = result * base;

  /* return the result. */
  return result;
}
