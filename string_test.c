/*                               -*- Mode: C -*- 
 * string_test.c --- 
 * Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
 * Created On       : Thu Feb 20 12:43:59 2003
 * Created On Node  : glaurung.green-gryphon.com
 * Last Modified By : Manoj Srivastava
 * Last Modified On : Thu Feb 27 17:53:16 2003
 * Last Machine Used: ember.green-gryphon.com
 * Update Count     : 285
 * Status           : Unknown, Use with caution!
 * HISTORY          : 
 * Description      : 
 * 
 */

static const char* version = 
  "$Id: string_test.c,v 1.6 2003/03/03 01:36:47 srivasta Exp $";

/** @file string_test.c
 *  @ingroup Utilities
 *  @brief An sample implementation of common string functions
 *
 * Copyright (C) 2003 Manoj Srivastava
 *
 * This is my entry for the code challenge. I do make use of the
 * string.h header file, but only in the regression testing area,
 * where my reimplementation of the string functions are tested
 * against the libc versions. 
 *
 * These functions are rather more straight forward than those I am
 * used to coding, and is therefore terser, and with fewer comments,
 * than is my natural style -- all except the Boyer-Moore
 * implementation in strstr, which was by far the most challenging. 
 *
 * I had fun coding this. I had forgotten how liberating C can be,
 * coming back from C++ and java.
 */

/*! @mainpage This weeks code challenge (NLUG)
 *
 * \section intro Introduction
 *
 * This code was written in response to a weekly code challenge for my
 * local Linux Users Group. It is meant to be an example of coding
 * techniques for people who are not professional programmers.  I
 * hoped to demonstrate that a coding assignment is often far more
 * than just writing code; a testing framework to demonstrate
 * correctness and testing use cases, as well as detailed
 * documentation for the end user as well as any future maintainers
 * are critical and integral components of the expected deliverables.
 * 
 *
 * \section string Why string.h?
 *
 * For the most part, these string functions are familiar to even new
 * practitioners of the C language, and are easy to implement. Since
 * there are reference implementations of all these functions redily
 * available on most platforms, writing the test harness is also
 * trivial, so this material should not be intimidating to most
 * students. 
 *
 * \subsection functions Functions implemented 
 *  
 * The following subset of string functions were implemented.
 *       - size_t strlen(const char *s);
 *       - char  *strdup(const char *s);
 *       - char  *strtok(char *s, const char *delim);
 *       - char  *strtok_r(char *s, const char *delim, char **ptrptr);
 *       - char  *strchr(const char *s, int c);
 *       - char  *strstr(const char *haystack, const char *needle);
 *       - int    strcmp(const char *s1, const char *s2);
 *       - int    strncmp(const char *s1, const char *s2, size_t n);
 *       - int    strcasecmp(const char *s1, const char *s2);
 *       - int    strncasecmp(const char *s1, const char *s2, size_t n);
 *       - char  *strcat(char *dest, const char *src);
 *       - char  *strncat(char *dest, const char *src, size_t n);
 *       - char  *strcpy(char *dest, const char *src);
 *       - char  *strncpy(char *dest, const char *src, size_t n);
 *
 * Rules:
 *       -# no looking at source to libc, X, kernel, or any other  reimplimented these functions
 *       -# You may use other headers as needed as long as they themselves don't circularly depend on <string.h>
 *       -# Entries must be portable.
 * 
 * \section copyright Copyright (C) 2003 Manoj Srivastava
 * 
 * This sample implementation of string functions is free software;
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software
 * Foundation; either version 2, or (at your option) any later
 * version.
 *
 * This sample implementation of string functions is distributed in
 * the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with This sample implementation of string functions; see the
 * file COPYING.  If not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

extern int errno;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>


size_t manoj_strlen(const char *s);
int test_strlen(void);

char * manoj_strcpy(char *dest, const char *src);
int test_strcpy(void);

char *manoj_strncpy(char *dest, const char *src, size_t n);
int test_strncpy(void);

char *manoj_strdup(const char *s);
int test_strdup(void);

char *manoj_strcat(char *dest, const char *src);
int test_strcat(void);

char *manoj_strncat(char *dest, const char *src, size_t n);
int test_strncat(void);

int manoj_strcmp(const char *s1, const char *s2);
int test_strcmp(void);

int manoj_strncmp(const char *s1, const char *s2, size_t n);
int test_strncmp(void);


extern int strcasecmp(const char *s1, const char *s2);
int manoj_strcasecmp(const char *s1, const char *s2);
int test_strcasecmp(void);

extern int strncasecmp(const char *s1, const char *s2, size_t n);
int manoj_strncasecmp(const char *s1, const char *s2, size_t n);
int test_strncasecmp(void);

char *manoj_strchr(const char *s, int c);
int test_strchr(void);

char *manoj_strrchr(const char *s, int c);
int test_strrchr(void);

char *manoj_strtok(char *s, const char *delim);
int test_strtok(void);

extern char *strtok_r(char *s, const char *delim, char **ptrptr);
char *manoj_strtok_r(char *s, const char *delim, char **ptrptr);
int test_strtok_r(void);

char *manoj_strstr(const char *haystack, const char *needle);
int test_strstr(void);

/**
 * @brief Begin blocks for macros
 *
 * Macros are dangerous if they use an  if--then--else control statement,
 * because  they may  be  used in  an   if--then--else control  statement
 * themselsves, and should be enclosed  in the following block to prevent
 * problems (like dangling else statements).
 */
#define      BEGIN_BLOCK     do {        /* begin macros with this */

/**
 * @brief And the corresponding End  block
 */
#define      END_BLOCK       } while (0) /* end macros with this */



/** 
 * @brief 7.21.6.3 The strlen function 
 * @param src_p A pointer to the char array to whose length is  required
 * @return The strlen() function returns the number of characters in src_p
 * 
 * The strlen function computes the length of the string pointed to by
 * src_p. The strlen function returns the number of characters that
 * precede the null character.
 */
size_t manoj_strlen(const char *src_p)
{
  size_t i = 0;
  if(*src_p){ while(*(src_p++)) i++; } 
  return i;
}

/**
 * @brief 7.21.2.3 The strcpy function 
 * @param src_p The source string
 * @param dest_p The destination the source string is copied to
 * @return The strcpy function returns the value of dest_p.
 *
 * The strcpy function copies the string pointed to by src_p (including 
 * the terminating null character) into the array pointed to by dest_p. If
 * copying takes place between objects that overlap, the behavior is
 * undefined.  
 */
char * manoj_strcpy(char *dest_p, const char *src_p)
{
  char * ret_p = dest_p;
  while(*src_p) *(dest_p++) = *(src_p++);
  *dest_p = 0;
  return ret_p;
}

/**
 * @brief 7.21.2.4 The strncpy function
 * @param src_p The source string
 * @param dest_p The destination the source string is copied to
 * @param n The number of bytes copied
 * @return The strncpy function returns the value of dest_p.
 *
 * The strncpy function copies not more than n characters (characters
 * that follow a null character are not copied) from the array pointed
 * to by src_p to the array pointed to by dest_p.  if there is no null
 * byte among the first n bytes of src_p, the result will not be
 * null-terminated. 
 *
 * In the case where the length of src_p is less than that of n, the
 * remainder of dest_p will be padded with nulls.
 *
 */
char *manoj_strncpy(char *dest_p, const char *src_p, size_t n)
{
  char * ret_p = dest_p;
  size_t j = 0;
  memset (dest_p, 0, n);
  while(j++ < n && *src_p) *(dest_p++) = *(src_p++);
  return ret_p;
}

/**
 * @brief The strdup function
 * @param src_p The source string
 * @return The strdup function returns a copy of the input string, or NULL
 *
 * This is not an ANSI C standard function, so no reference exists.   
 * The  strdup()  function  returns  a  pointer to a new string which
 * is a duplicate of the string src_p.  Memory for the new string is
 * obtained  with malloc(3), and can be freed with free(3).
 */
char *manoj_strdup(const char *src_p)
{
  char *dest_p = malloc(strlen(src_p) + 1);
  if(dest_p) (void) strcpy(dest_p, src_p);
  return dest_p;
}

/**
 * @brief 7.21.3.1 The strcat function 
 * @param src_p The source string
 * @param dest_p The destination the source string is appended to
 * @return The strcat function returns the value of dest_p.
 *
 * The strcat function appends a copy of the string pointed to by
 * src_p  (including the terminating null character) to the end of the
 * string pointed to by dest_p. The initial character of src_p overwrites
 * the null character at the end of dest_p. If copying takes place between
 * objects that overlap, the behavior is undefined. 
 *
 * Memory for the new string is obtained  with malloc(3), and can be
 * freed with free(3). 
 */
char *manoj_strcat(char *dest_p, const char *src_p)
{
  char * ret_p = dest_p;
  while(*(dest_p++)) ;
  dest_p--;
  while(*src_p) *(dest_p++) = *(src_p++);
  *dest_p = 0;
  return ret_p;
}

/**
 * @brief 7.21.3.2 The strncat function  
 * @param src_p The source string
 * @param dest_p The destination the source string is appended to
 * @param n The number of bytes appended
 * @return The strncat function returns the value of dest_p.
 *
 * The strncat function appends not more than n characters (a null
 * character and characters that follow it are not appended) from the
 * array pointed to by  src_p to the end of the string pointed to by
 * dest_p. The initial character of src_p overwrites the null
 * character at the end of dest_p. If copying takes place between
 * objects that overlap, the behavior is undefined. 
 */
char *manoj_strncat(char *dest_p, const char *src_p, size_t n)
{  
  char * ret_p = dest_p;
  size_t j = 0;
  while(*(dest_p++)) ;
  dest_p--;
  while(j++ < n && *src_p) *(dest_p++) = *(src_p++);
  return ret_p;
}

/**
 * @brief 7.21.4.2 The strcmp function Synopsis
 * @param s1 The first of two strings to be compared
 * @param s2 The second of two strings to be compared
 * @return The strcmp function returns an integer
 *
 * The strcmp function compares the string pointed to by s1 to the
 * string pointed to by s2. The strcmp function returns an integer
 * greater than, equal to, or less than zero, accordingly as the
 * string pointed to by s1 is greater than, equal to, or less than the
 * string s2. 
 */
int manoj_strcmp(const char *s1, const char *s2)
{
  while(*s1 && *s2 && *s1 == *s2) {s1++; s2++; };
  if(*s1)
   {
     if(*s2)
      {
	return ((*s1 < *s2) ? -1 : ((*s1 == *s2) ? 0 : 1));
      } 
     else	return 1; 	/* s1 is longer than s2, but identical */
   } 
  else
   {
     if(*s2) return -1; 	/* s1 is shorter, and hence less than s2*/
     else return 0;	    	/* Both strings are identical*/
   }   
}


/**
 * @brief 7.21.4.4 The strncmp function Synopsis
 * @param s1 The first of two strings to be compared
 * @param s2 The second of two strings to be compared
 * @param n The number of bytes compared
 * @return The strncmp function returns an integer
 *
 * The strncmp function compares not more than n characters
 * (characters that follow a null character are not compared) from the
 * array pointed to by s1 to the array pointed to by s2.  The strncmp
 * function returns an integer greater than, equal to, or less than
 * zero,  accordingly as the possibly null-terminated array pointed to
 * by s1 is greater than, equal to, or less than the possibly
 * null-terminated array pointed to by s2. 
 */
int manoj_strncmp(const char *s1, const char *s2, size_t n)
{
  size_t j = 0;
  if(n <= 0) return 0;
  while(j++ < n && *s1 && *s2 && *s1 == *s2) {s1++; s2++; };
  if(j == n) return 0;
  if(*s1)
   {
     if(*s2)
      {
	return ((*s1 < *s2) ? -1 : ((*s1 == *s2) ? 0 : 1));
      } 
     else	return 1; 	/* s1 is longer than s2, but identical */
   } 
  else
   {
     if(*s2) return -1; 	/* s1 is shorter, and hence less than s2*/
     else return 0;	    	/* Both strings are identical*/
   }   
}

/**
 * @brief The strcasecmp function Synopsis
 * @param s1 The first of two strings to be compared
 * @param s2 The second of two strings to be compared
 * @return The strcasecmp function returns an integer
 *
 * This is not an ANSI C function, but a BSD 4.4 extention. 
 * The strcasecmp function compares the string pointed to by s1 to the
 * string pointed to by s2. The strcasecmp function returns an integer
 * greater than, equal to, or less than zero, accordingly as the
 * string pointed to by s1 is greater than, equal to, or less than the
 * string s2. 
 */
int manoj_strcasecmp(const char *s1, const char *s2)
{
  while(*s1 && *s2 && toupper(*s1) == toupper(*s2)) {s1++; s2++; };
  if(*s1)
   {
     if(*s2)
      {
	return ((toupper(*s1) < toupper(*s2)) ? -1 :
		((toupper(*s1) ==toupper( *s2)) ? 0 : 1));
      } 
     else	return 1; 	/* s1 is longer than s2, but identical */
   } 
  else
   {
     if(*s2) return -1; 	/* s1 is shorter, and hence less than s2*/
     else return 0;	    	/* Both strings are identical*/
   }   
}


/**
 * @brief The strncasecmp function Synopsis
 * @param s1 The first of two strings to be compared
 * @param s2 The second of two strings to be compared
 * @param n The number of bytes compared
 * @return The strncasecmp function returns an integer
 *
 * This is not an ANSI C function, but a BSD 4.4 extention. 
 * The strncasecmp function compares not more than n characters
 * (characters that follow a null character are not compared) from the
 * array pointed to by s1 to the array pointed to by s2.  The strncasecmp
 * function returns an integer greater than, equal to, or less than
 * zero,  accordingly as the possibly null-terminated array pointed to
 * by s1 is greater than, equal to, or less than the possibly
 * null-terminated array pointed to by s2. 
 */
int manoj_strncasecmp(const char *s1, const char *s2, size_t n)
{
  size_t j = 0;
  if(n <= 0) return 0;
  while(j++ < n && *s1 && *s2 && toupper(*s1) == toupper(*s2)) {s1++; s2++; } ;
  if(j == n) return 0;
  if(*s1)
   {
     if(*s2)
      {
	return ((toupper(*s1) < toupper(*s2)) ? -1 :
		((toupper(*s1) ==toupper( *s2)) ? 0 : 1));
      } 
     else	return 1; 	/* s1 is longer than s2, but identical */
   } 
  else
   {
     if(*s2) return -1; 	/* s1 is shorter, and hence less than s2*/
     else return 0;	    	/* Both strings are identical*/
   }   
}

/**
 * @brief 7.21.5.2 The strchr function 
 * @param str_p The string to search in
 * @param c The character being searched for.
 * @return  A pointer to the located charcter, or NULL
 *
 * The strchr function locates the first occurrence of c (converted to
 * a char) in the string pointed to by str_p. The terminating null
 * character is considered to be part  of the string. The strchr
 * function returns a pointer to the located character, or a null
 * pointer if the character does not occur in the string. 
 */
char *manoj_strchr(const char *str_p, int c)
{
  char i = (char) c;
  char * j = (char *) str_p; 	/* This produces a warning */
  while(*j && *j != i) j++;
  if(*j) return j;
  else   return 0;
}
 

/**
 * @brief 7.21.5.5 The strrchr function 
 * @param str_p The string to search in
 * @param c The character being searched for.
 * @return  A pointer to the located charcter, or NULL
 *
 * The strrchr function locates the last occurrence of c (converted to
 * a char) in the string pointed to by str_p. The terminating null
 * character is considered to be part  of the string. The strchr
 * function returns a pointer to the located character, or a null
 * pointer if the character does not occur in the string. 
 */
char *manoj_strrchr(const char *str_p, int c)
{
  char i = (char) c;
  char * j = (char *) str_p;	/* This produces a warning */
  while(*(j++));
  j--;
  while(j >= str_p && *j != i) j--;
  if(j > str_p) return j;
  else
   {
     if(*j == i) return j;
     else        return 0;
   }
}

/* 
 * The warning produced in the casts above seem to have no work
 * arounds; how can these functions return a pointrer to a mutable
 * string when the input string itself is a const string? This seems
 * like a defect in the C99 standard.
 */


/**
 * @brief 7.21.5.8 The strtok function
 * @param str_p The string to be tokenized
 * @param delim The string conmtaining the list of token separators
 * @return  The strtok function returns a pointer to the first token, or NULL
 *
 * A sequence of calls to the strtok function breaks the string
 * pointed to by str_p into a sequence of tokens, each of which is
 * delimited by a character from the string pointed to by delim. The
 * first call in the sequence has a non-null first argument;
 * subsequent calls in the sequence have a null first argument.  The
 * separator string pointed to by delim may be different from call to
 * call. 
 *
 * The first call in the sequence searches the string pointed to by
 * str_p for the first character that is not contained in the current
 * separator string pointed to by delim. If no such character is
 * found, then there are no tokens in the string pointed to by s1 and
 * the strtok function returns a null pointer. If such a character is
 * found, it is the start of the first token. 
 *
 * The strtok function then searches from there for a character that
 * is contained in the current separator string. If no such character
 * is found, the current token extends to the end of the string
 * pointed to by s1, and subsequent searches for a token will return a
 * null pointer. If such a character is found, it is overwritten by a
 * null character, which terminates the current token. The strtok
 * function saves a pointer to the following character, from which the
 * next search for a token will start. 
 *
 * Each subsequent call, with a null pointer as the value of the first
 * argument, starts searching from the saved pointer and behaves as
 * described above. 
 *
 * The implementation shall behave as if no library function calls the
 * strtok function. 
 *
 * The strtok function returns a pointer to the first character of a
 * token, or a null pointer if there is no token.
 *
 * This function modifies its first argument. The strtok() function
 * uses a static  buffer  while  parsing,  so it's not thread
 * safe. The strtok() function  cannot be used on constant strings.
 */
char *manoj_strtok(char *str_p, const char *delim)
{
  static char * index_p;
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  
  if(! delim) return 0;
  if(str_p)  index_p = str_p;	/* initialize, since a new string is given*/
  if(! index_p) return 0;

  j = strlen(delim);
  k = strlen(index_p);

  /* Skip over initial matches */
  for(l = 0; l < k; l++)
   {
     if(strchr(delim, index_p[l])) continue;
     index_p = index_p + l;
     break;
   }


  for(l = 0; l < k; l++)
   {
     for(i = 0; i < j; i++)
      {
	if(index_p[l] == delim[i])
	 {
	   char *retval_p = index_p;
	   index_p[l] = 0;
	   index_p = index_p + l +1;
	   return retval_p;
	 }
      }
   }
  return 0;			/* found noyhing */
}

/**
 * @brief The strtok_r function
 * @param str_p The string to be tokenized
 * @param delim The string conmtaining the list of token separators
 * @param ptrptr Pointer to a user allocated buffer 
 * @return  The strtok function returns a pointer to the first token, or NULL
 *
 * This is a POSIX extention, and is not a ANSI C function.
 * The  strtok_r()  function  is a reentrant version of the strtok()
 * function, which instead of using its own static buffer, requires a
 * pointer to  a user allocated char*. This pointer, the ptrptr
 * parameter, must be the same while parsing the same string. 
 *
 * This function modifies its first argument, and cannot be used on
 * constant strings. 
 */
char *manoj_strtok_r(char *str_p, const char *delim, char **ptrptr)
{
  char * index_p;
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;

  if(! delim) return 0;
  if(str_p)  (void) strcpy (*ptrptr, str_p);
  index_p = *ptrptr;	
  if(! index_p) return 0;

  j = strlen(delim);  
  k = strlen(index_p);
  /* Skip over initial matches */
  for(l = 0; l < k; l++)
   {
     if(strchr(delim, index_p[l])) continue;
     index_p = index_p + l;
     break;
   }

  for(l = 0; l < k; l++)
   {
     for(i = 0; i < j; i++)
      {
	if(index_p[l] == delim[i])
	 {
	   char *retval_p = index_p;
	   index_p[l] = 0;
	   *ptrptr = index_p + l +1 ;
	   return retval_p;
	 }
      }
   }
  return 0;			/* found noyhing */
}

/**
 * @brief The size of the alphabet -- which happens to be the ascii namespace
 */
#define ASIZE 256


/**
 * @brief 7.21.5.7 The strstr function
 * @param haystack The string space to search in
 * @param needle The string to search for
 * @return The strstr function returns a pointer to the located string, or NULL
 *
 * The strstr function locates the first occurrence in the string
 * pointed to by haystack of the sequence of characters (excluding
 * the terminating null character) in the string pointed to by
 * needle. 

 * The strstr function returns a pointer to the located string, or a
 * null pointer if the string is not found. If needle points to a string
 * with zero length, the function returns haystack. 
 *
 * This implementation uses the Boyer-Moore algorithm. This algorithm
 * searches for the pattern in a window that slides along the string
 * to be searched. It is as if we have opened a window on the text to
 * allow us to see only pat_lenght characters. Later, the window is
 * slid to the right, allowing us to view other positions. The text of
 * the pattern is ompared to the text exposed in the window, in a right to
 * left order. In case of a mimatch, the window is slid over and the
 * match restarted. The value of Boyer-Moore is that the window is
 * slid over by more than one character (which is what the brute
 * force method does), and this improes the efficiency of the
 * algorithm, since we do not look at unfeasible positions to start
 * matching. The amount by which we slide the window over is the
 * maximum safe value (we do not want to slide the window too far, in
 * case we miss a match. 
 *
 * How much we can skip is determined by thte following hueristics:
 *   -# The bad character rule: looking just at the character that didn't match
 *   -# The Good suffix rule: Looking at the suffix matched so far
 */
char *manoj_strstr(const char *haystack, const char *needle)
{
  int skip[ASIZE];
  int *shift = 0;
  int *suffix_length = 0;
  
  int i = 0;
  int j = 0;
  size_t right_end = 0;
  int needle_len = strlen(needle);
  /*
   * If needle[needle_len - 1] does not exist elsewhere in needle,
   * then shift by needle_len
   */ 

  if(!needle) return 0;

  /**
   * The bad character rule. 
   *
   * Look at the character in the window that is being compared at
   * the moment. In case of a mismatch, if the character does not occur
   * in the search pattern at all, then there is no possibility that
   * that character can be part of a match, and any instance of the
   * pattern in the text must start to the right of the mismatched
   * character, so the whole window can be slid over just beyond
   * the character. (In other words, any orientation of the window that
   * spans the mismatched charactercan't result in a match). So, if we 
   * had already matched m charactrers from the right hand side of 
   * the window, the window slides patlenght - m steps in this case.
   *
   *  - Observation 1: If char in the window is known not to occur in
   *    the pattern, then there is no need to consider the
   *    possibility of the pattern occuring anywhere bedore the
   *    current char. If we had already matched d chars, the window
   *    shifts by patlen -d characters.
   *
   * If the mismatched character does occur in the pattern, we need
   * to slide the window over until the character in the pattern
   * matches the character in the string. If the character occuers
   * multiple times in the pattern, we need to slide the rightmost
   * occurance of the character over the text in the string; however,
   * sometimes that means sliding the window backwards, which we know
   * can't be right. So at the very least, the minimum skip is at
   * least one charactrer.
   *
   *  - Observation 2: If the rightmost occurrence of the character
   *    being tested is d characters from the rightmost character in
   *    the pattern, then we can slide down d characters without
   *    looking for matches, to align the character in the text and
   *    in the pattern. If we slide any less than d, the characters
   *    won't match.(We need to allow for any characters already
   *    matched when we slide the window, since what we really are
   *    doing is to align the characters). 
   *
   * Uses knowledge of one character in the text, the character that
   * is current;ly being examined. 
   */

  /* 
   * initialize the skip table. Chars not in the pattern slide all
   * the way forward.
   */
  for(i = 0; i < ASIZE; i++) skip[i] = needle_len;
  /*
   * Now for chars that are in the key Need to fill from left to
   * right
   */
  for(i = 0; i < needle_len - 1; i++) 
    skip[ (int) needle[i] ] = needle_len -i -1;
  /**
   * The Good Suffix Hueristic
   *
   * This hueristic applies for patterns with repeating strings. The
   * bad charcter  hueristic shall also work for patterns with
   * repeating subpatterns, but the search will not be as eficient as
   * possible. By examining partial matches and repeats in the search
   * pattern, it is possible to make more drastic shifts in the
   * window and match more rapidly. This hueristic represents the
   * largest skip which can be made until the characters that have
   * been matched coincide with another sequence in the
   * pattern. Thus, we use our knowledge of a substring that exists
   * in the text to help determine the safe shift. Any new position
   * of the pattern that overlaps the current postion in the text
   * _must_ match the characters we already know exist at this
   * location (since we have matched them), since otherwise a
   * mismatch is inevitable. In addition, the character that caused a
   * mismatch right now must match its counterpart in the pattern in
   * the new shift, or else the same mimatch would occur again. 
   *
   * The amount we shift is the lenght of the longest suffix of the
     matched pattern that matches a prefix of the pattern. 
   */

  /* suffixes[i]=k s.t. x[i-k+1,...,i]=x[m-k,...,m-1] */

  shift = (int *) malloc(sizeof(int) * (needle_len + 1));
  if(!shift)
   {
     errno = ENOMEM;
     return 0;
   } 
  suffix_length = (int *) malloc(sizeof(int) * (needle_len + 1));
  if(!suffix_length)
   {
     errno = ENOMEM;
     return 0;
   } 
  
  /* 
   * Set suffix_length[i] = number of characters right ended at needle[i]
   * which match the characters right ended at needle[needle_len - 1].
   */
  for (i = 1; i < needle_len; i++){ 
    for (j = 0; 
	 j <= i && needle[needle_len - 1 - j] == needle[i - j];
	 j++);
    suffix_length[i] = j;
#ifdef LIB_DEBUG
    fprintf(stderr, "suffix_length[i(%2d)] = %2d %c\n", i, j, needle[i]);
    if(j)
     {
       int k = 0;
       fprintf(stderr, "%s\n", needle);
       for(k = 0; k <= needle_len - 1 -j; k++)
	{
	  fprintf(stderr, " ");
	} /* end of for(k = 0; k < j; k++) */
       for(k = needle_len - 1 - j; k < needle_len - 1; k++)
	{
	  fprintf(stderr, "|");
	} /* end of for(k = 0; k < j; k++) */
       fprintf(stderr, "\n");
       for(k = 0; k <= i -j; k++)
	{
	  fprintf(stderr, " ");
	} /* end of for(k = 0; k < j; k++) */
       for(k = i - j; k < i; k++)
	{
	  fprintf(stderr, "^");
	} /* end of for(k = 0; k < j; k++) */
       fprintf(stderr, "\n");
     } /* end of if(j) */
#endif
  }
  /* Zero the relevant section of the array */
  for (i = 1; i < needle_len; i++) shift[i] = 0;
  /* 
   * Fix up by shifting to the rightmost occurrence of the matched
   * chars. Note that suffix_length[i] is the length of the suffix
   * matched at the point i in the pattern. So, when we have matched a
   * suffix of length suffix_length[i], a similar string is at
   * position i, and we need to shift the string by needle_len - 1 - i
   * to bring that other substring under tecurrently matched string. 
   */
  for (i = 0; i <  needle_len; i++)
   {
     shift[suffix_length[i]] = needle_len - 1 - i;
#ifdef LIB_DEBUG
     fprintf(stderr, "shift[suffix_length[i](%2d)] = i(%2d);\n",
	     suffix_length[i], i);
#endif
   }

  /* Let the skip array take care of the case for zero matches */
  shift[0] = 1;
  /* 
   * Fix up by considering matches that would run off the end of the
   * pattern. So, things where the substring was not found, we shift
   * enough to move the window beyond the matched pattern, but no
   * more (let the minimum shift be at least 1). 
   */
  for (i = 1; i < needle_len; i++)
    {
      if (shift[i] == 0)
       {
	 shift[i] = (needle_len - 1 - i > 1) ?
		    needle_len - 1 - i : 1;
#ifdef LIB_DEBUG
	 fprintf(stderr, "shift[i(%2d)] = max_gap(%2d);\n",
	     i, shift[i]);
#endif
       }
    }

#ifdef LIB_DEBUG
  for (i = 0; i < needle_len; i++){ 
    fprintf(stderr, "%2d %3c %3d %3d\n", i, needle[i],
	    suffix_length[i], shift[i]);
  }
#endif

  right_end = needle_len -1;
  while(right_end < strlen(haystack))
   {
     int sk = 0;
     int sh = 0;
#ifdef LIB_DEBUG
     fprintf(stderr, "\n%s\n", haystack);
     for(i = 0; i < right_end - needle_len + 1; i++)
      {
	fprintf(stderr, " ");
      } /* end of for(i = 0; i < right_end - needle_len + 1; i++) */
     fprintf(stderr, "%s\n", needle);
#endif

     for(i = 0; 
	 i < needle_len && haystack[right_end - i] == needle[needle_len -1 -i];
	 i++);
     if(i == needle_len)
      {
#ifdef LIB_DEBUG
	fprintf(stderr, "Found at %d\n", right_end - needle_len + 1);
#endif
	return haystack + right_end - needle_len + 1;
      } /* end of if(i == needle_len) */
#ifdef LIB_DEBUG
     for(j = 0; j < right_end - i; j++)
      {
	fprintf(stderr, " ");
      } /* end of for(i = 0; i < right_end - needle_len + 1; i++) */
     fprintf(stderr, "|\n");
     
     fprintf(stderr, 
	     "Mismatch at %d == haystack[%d]=%c != needle[%d]=%c\n",
	     right_end - i, right_end - i, haystack[right_end - i], 
	     needle_len -1 -i, needle[needle_len -1 -i]);
#endif

     sk = skip[(int)haystack[right_end - i]];
     sh = shift[i];
     right_end = (right_end - i + sk > right_end + sh) ?
		 right_end - i + sk : right_end + sh;
#ifdef LIB_DEBUG
     if(sk > sh)
      {
	fprintf(stderr, "Using skip table to shift by  %d\n",
		sk);
      } /* end of if(sk > sh) */
     else
      {
	fprintf(stderr, "Using shift table to shift by  %d\n",
		sh);
      } /* end of else */
#endif     
   } /* end of while(right_end < strlen(haystack)) */
#ifdef LIB_DEBUG
  fprintf(stderr, "NOT Found\n");
#endif
  return 0;
}


/*
 ####################################################################
 ####################################################################
 ####################################################################
 */

/** 
 * @brief A set of test strings used for regression testing
 * 
 */
const char *strings_to_test[] = 
  {
   "This ia a longish text string, but not that long, at that",
   "The long jump \0 and some trailing text at-that",
   "",
   "Some more test strings",
   "Yet another one",
   "what-finally-stops--at-at-that point", 
   "aksdy923492p4  p39475 q0349750[q3hf30q79340 320496t034 03q495609324uy509y",
   "character is considered to be part of the string. The chr at-that point",
   0
  };


/**
 * @brief Test the manoj_strlen function
 * @return 0 on success, a negative integer on failure
 */
int test_strlen(void)
{
  int retval = 0;
  int i;

#ifdef DEBUG
  fprintf (stderr, "manoj_strlen - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     if(strlen(strings_to_test[i]) != manoj_strlen(strings_to_test[i]))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strlen Failed test %d. Got %d, expected %d\n",
		 i, manoj_strlen(strings_to_test[i]),
		 strlen(strings_to_test[i]));
      }
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   } 
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif     
  return retval;
}

/**
 * @brief Test the manoj_strcpy function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strcpy(void)
{
  int retval = 0;
  char buffer[1024];
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strcpy - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig = 0;
     memset(buffer,0,1024);
     orig = manoj_strcpy(buffer, strings_to_test[i]);
     if(strcmp(orig,strings_to_test[i]))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strcpy Failed test %d. \n",
		 i);
      } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief Test the manoj_strncpy function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strncpy(void)
{
  int retval = 0;
  char buffer[1024];
  char copy[1024];
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strncpy - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig  = 0;
     char * dummy = 0;
     memset(buffer,0,1024);
     memset(copy,0,1024);
     orig  = manoj_strncpy(buffer, strings_to_test[i], 5);
     dummy =       strncpy(copy,   strings_to_test[i], 5);
     if(strcmp(orig,dummy))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strncpy Failed test %d. \n",
		 i);
      } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief Test the manoj_strdup function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strdup(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strdup - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig = 0;
     orig = manoj_strdup(strings_to_test[i]);
     if(orig)
      {
	if(strcmp(orig,strings_to_test[i]))
	  {
	    retval--;
	    fprintf (stderr, 
		     "ERROR: manoj_strdup Failed test %d. \n",
		     i);
	  } 
	free(orig);
      } 
     else
      {
	fprintf (stderr, 
		 "ERROR: manoj_strdup Failed test %d -- failed malloc\n",
		 i);
      }
#ifdef DEBUG
     fprintf (stderr, ".");
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}



/**
 * @brief Test the manoj_strcat function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strcat(void)
{
  int retval = 0;
  char buffer[1024];
  char copy[1024];
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strcat - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig = 0;
     char * dummy = 0;
     memset(buffer,0,1024);
     memset(copy,0,1024);
     (void) strcpy(buffer, "Original String ");
     (void) strcpy(copy,   "Original String ");
     orig  = manoj_strcat(buffer, strings_to_test[i]);
     dummy =       strcat(copy,   strings_to_test[i]);
     if(strcmp(orig,dummy))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strcat Failed test %d. \n",
		 i);
	fprintf (stderr, 
		 "  orig (%s)\n dummy (%s)\n",
		 orig, dummy);
      } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief Test the manoj_strncat function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strncat(void)
{
  int retval = 0;
  char buffer[1024];
  char copy[1024];
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strncat - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig  = 0;
     char * dummy = 0;
     memset(buffer,0,1024);
     memset(copy,0,1024);
     (void) strcpy(buffer, "Original String ");
     (void) strcpy(copy,   "Original String ");
     orig  = manoj_strncat(buffer, strings_to_test[i], 5);
     dummy =       strncat(copy,   strings_to_test[i], 5);
     if(strcmp(orig,dummy))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strncat Failed test %d. \n",
		 i);
	fprintf (stderr, 
		 "  orig (%s)\n dummy (%s)\n",
		 orig, dummy);
       } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief A macro to determine the signed state of an integer
 *
 * This is slightly misnamed, since it does distinguish between a 0
 * value and positive values -- it really does return a tristate
 * value, ideal for testing strcmp like function return values.
 */
#define sign(x) (x>0 ? 1 : (x<0 ? -1 : 0))

/**
 * @brief Test the manoj_strcmp function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strcmp(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strcmp - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     int m = manoj_strcmp(strings_to_test[i], "The long jump ");
     int o =       strcmp(strings_to_test[i], "The long jump ");

     if(sign(m) != sign(o))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strcmp Failed test %d. %d != %d\n",
		 i, m, o);
	fprintf (stderr, 
		 "ERROR: (%s) != (The long jump )  \n",
		 strings_to_test[i]);
      } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief Test the manoj_strncat function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strncmp(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strncmp - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     int m = manoj_strncmp(strings_to_test[i], "The long jump ", 5);
     int o = strncmp(strings_to_test[i], "The long jump ", 5);
     
     if(sign(m) != sign(o))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strncmp Failed test %d. %d != %d\n",
		 i, m, o);
	fprintf (stderr, 
		 "ERROR: (The long jump ) != (%s) \n",
		 strings_to_test[i]);
       } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}


/**
 * @brief Test the manoj_strcasecmp function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strcasecmp(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strcasecmp - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     int m = manoj_strcasecmp(strings_to_test[i], "The long jump ");
     int o = strcasecmp(strings_to_test[i], "The long jump ");
     
     if(sign(m) != sign(o))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strcasecmp Failed test %d. \n",
		 i);
      } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief Test the manoj_strncat function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strncasecmp(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strncasecmp - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     int m = manoj_strncasecmp(strings_to_test[i], "The long jump ", 5);
     int o = strncasecmp(strings_to_test[i], "The long jump ", 5);
     
     if(sign(m) != sign(o))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strncasecmp Failed test %d. \n",
		 i);
       } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief Test the manoj_strnchr function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strchr(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strchr - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     if(manoj_strchr(strings_to_test[i], 'j') != 
	strchr(strings_to_test[i], 'j'))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strchr Failed test %d. \n",
		 i);
       } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief Test the manoj_strnchr function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strrchr(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strrchr - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     if(manoj_strrchr(strings_to_test[i], 'j') != 
	strrchr(strings_to_test[i], 'j'))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strrchr Failed test %d. \n",
		 i);
       } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief Test the manoj_strtok function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strtok(void)
{
  int 	 	 retval   = 0;
  int 	 	 i 	  = 0;
  char 		*buffer_p = 0;
  char 		*copy_p   = 0;
  const char 	*delim_p  = " eta";
  char 		*tok1 	  = 0;
  char 		*tok2 	  = 0;
  
  
#ifdef DEBUG
  fprintf (stderr, "manoj_strtok - "); 
#endif

  buffer_p = malloc(128);
  if(! buffer_p) return -1;

  copy_p = malloc(128);
  if(! copy_p) return -1;

  (void) strcpy(buffer_p, "The quick brown fox jumps over the lazy dog");
  (void) strcpy(copy_p,   "The quick brown fox jumps over the lazy dog");

  tok1 = manoj_strtok(buffer_p, delim_p);
  tok2 =       strtok(copy_p,   delim_p);
  if(strcmp(tok1, tok2))
   {
     retval--;
     fprintf (stderr, 
	      "ERROR: manoj_strtok Failed test %d. Got (%s), expected (%s)\n",
	      i++, tok1, tok2);
   } 
#ifdef DEBUG
  else
   {
     fprintf (stderr, ".");
   } 
#endif     

  while((tok1 =  manoj_strtok(0, delim_p)))
   {
     tok2 = strtok(0, delim_p);
     if(strcmp(tok1, tok2))
      {
	retval--;
	fprintf(stderr, 
		"ERROR: manoj_strtok Failed test %d. Got (%s), expected (%s)\n",
		 i++, tok1, tok2);
      } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } 
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}


/**
 * @brief Test the manoj_strtok_r function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strtok_r(void)
{
  int 	 	 retval   = 0;
  int 	 	 i 	  = 0;
  char 		*orig_p   = 0;
  char 		*buffer_p = 0;
  char 		*copy_p   = 0;
  const char 	*delim_p  = " eta";
  char 		*tok1 	  = 0;
  char 		*tok2 	  = 0;

  
#ifdef DEBUG
  fprintf (stderr, "manoj_strtok_r - "); 
#endif

  orig_p = malloc(128);
  if(! orig_p) return -1;

  buffer_p = malloc(128);
  if(! buffer_p) return -1;

  copy_p = malloc(128);
  if(! copy_p) return -1;

  (void) strcpy(orig_p, "The quick brown fox jumps over the lazy dog");

  tok1 = manoj_strtok_r(orig_p, delim_p, &buffer_p);
  tok2 =       strtok_r(orig_p, delim_p, &copy_p);
  if(strcmp(tok1, tok2))
   {
     retval--;
     fprintf (stderr, 
	      "ERROR: manoj_strtok_r Failed test %d. Got (%s), expected (%s)\n",
	      i++, tok1, tok2);
   } 
#ifdef DEBUG
  else
   {
     fprintf (stderr, ".");
   } 
#endif     

  while((tok1 =  manoj_strtok_r(0, delim_p, &buffer_p)))
   {
     tok2 = strtok_r(0, delim_p, &copy_p);
     if(strcmp(tok1, tok2))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strtok_r Failed test %d. Got (%s), expected (%s)\n",
		 i++, tok1, tok2);
      } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } 
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}

/**
 * @brief Test the manoj_strtsr function
 * @return 0 on success, a negative integer on failure
 *
 */
int test_strstr(void)
{
  int 	 	 retval   = 0;
  int 	 	 i 	  = 0;
  
#ifdef DEBUG
  fprintf (stderr, "manoj_strstr - "); 
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     if(manoj_strstr(strings_to_test[i], "at-that") != 
	strstr(strings_to_test[i], "at-that"))
      {
	retval--;
	fprintf (stderr, 
		 "ERROR: manoj_strstr Failed test %d. \n",
		 i);
       } 
#ifdef DEBUG
     else
      {
	fprintf (stderr, ".");
      } /* end of else */
#endif     
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif  
  return retval;
}


/**
 * @brief The main entry point for this testing routine
 * @return EXIT_SUCCESS on success, EXIT_FAILURE oterwise
 */
int main(void)
{
  int 	retval 	 = 0;
  int 	retval1  = 0;
  int 	retval2  = 0;
  int 	retval3  = 0;
  int 	retval4  = 0;
  int 	retval5  = 0;
  int 	retval6  = 0;
  int 	retval7  = 0;
  int 	retval8  = 0;
  int 	retval9  = 0;
  int 	retval10 = 0;
  int 	retval11 = 0;
  int 	retval12 = 0;
  int 	retval13 = 0;
  int 	retval14 = 0;

  fprintf (stderr, "stringtest Version %s\n\n", version);
  
  retval = test_strlen();
  if(retval)   fprintf (stderr, "strlen Test Failed\n");

  retval1 = test_strcpy();
  if(retval1)  fprintf (stderr, "strcpy Test Failed\n");

  retval2 = test_strncpy();
  if(retval2)  fprintf (stderr, "strncpy Test Failed\n");

  retval3 = test_strdup();
  if(retval3)  fprintf (stderr, "strdup Test Failed\n");

  retval4 = test_strcat();
  if(retval4)  fprintf (stderr, "strcat Test Failed\n");

  retval5 = test_strncat();
  if(retval5)  fprintf (stderr, "strncat Test Failed\n");

  retval6 = test_strcmp();
  if(retval6)  fprintf (stderr, "strncmp Test Failed\n");

  retval7 = test_strncmp();
  if(retval7)  fprintf (stderr, "strncmp Test Failed\n");

  retval8 = test_strcasecmp();
  if(retval8)  fprintf (stderr, "strcat Test Failed\n");

  retval9 = test_strncasecmp();
  if(retval9)  fprintf (stderr, "strncasecmp Test Failed\n");

  retval10 = test_strchr();
  if(retval10)  fprintf (stderr, "strchr Test Failed\n");

  retval11 = test_strrchr();
  if(retval11)  fprintf (stderr, "strrchr Test Failed\n");

  retval12 = test_strtok();
  if(retval12)  fprintf (stderr, "strtok Test Failed\n");

  retval13 = test_strtok_r();
  if(retval13)  fprintf (stderr, "strtok_r Test Failed\n");

  retval14 = test_strstr();
  if(retval14)  fprintf (stderr, "strstr Test Failed\n");

  if(!(retval   + retval1  + retval2  + retval3  + retval4  + retval5  +
       retval6  + retval7  + retval8  + retval9  + retval10 + retval11 +
       retval12 + retval13 + retval14))
   {
     fprintf (stderr, "\n\tSuccess\n");
      exit (EXIT_SUCCESS);
   }
  exit (EXIT_FAILURE);
}
