# Introduction #

This code was written in response to a weekly code challenge for my
local Linux Users Group. It is meant to be an example of coding
techniques for people who are not professional programmers. I hoped to
demonstrate that a coding assignment is often far more than just
writing code; a testing framework to demonstrate correctness and
testing use cases, as well as detailed documentation for the end user
as well as any future maintainers are critical and integral components
of the expected deliverables.

# Why string.h? #

For the most part, these string functions are familiar to even new
practitioners of the C language, and are easy to implement. Since
there are reference implementations of all these functions readily
available on most platforms, writing the test harness is also trivial,
so this material should not be intimidating to most students.

# Functions implemented #

The following subset of string functions were implemented. Please see
[html/index.html](html/index.html) for details.

* `size_t strlen(const char *s);`
* `char *strdup(const char *s);`
* `char *strtok(char *s, const char *delim);`
* `char *strtok_r(char *s, const char *delim, char **ptrptr);`
* `char *strchr(const char *s, int c);`
* `char *strstr(const char *haystack, const char *needle);`
* `int strcmp(const char *s1, const char *s2);`
* `int strncmp(const char *s1, const char *s2, size_t n);`
* `int strcasecmp(const char *s1, const char *s2);`
* `int strncasecmp(const char *s1, const char *s2, size_t n);`
* `char *strcat(char *dest, const char *src);`
* `char *strncat(char *dest, const char *src, size_t n);`
* `char *strcpy(char *dest, const char *src);`
* `char *strncpy(char *dest, const char *src, size_t n);`

Rules:
1. no looking at source to libc, X, kernel, or any other reimplimented these functions
2. You may use other headers as needed as long as they themselves don't circularly depend on <string.h>
3. Entries must be portable.


# Copyright (C) 2003 Manoj Srivastava #

This sample implementation of string functions is free software; you
can redistribute it and/or modify it under the terms of the GNU
General Public License as published by the Free Software Foundation;
either version 2, or (at your option) any later version.

This sample implementation of string functions is distributed in the
hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with This sample implementation of string functions; see the
file COPYING. If not, write to the Free Software Foundation, Inc., 59
Temple Place - Suite 330, Boston, MA 02111-1307, USA.
