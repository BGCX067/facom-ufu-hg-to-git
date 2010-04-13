/* Copyright (C) 1988, 1990-1991, 1995-2010 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#define ERR_SUCESS 0
#define ERR_UNKNOW -1
#define ERR_GENERIC -2
#define ERR_ALLOC -3
#define ERR_ORDFUNC -4
#define ERR_UNKNOWFUNCTION -5

char const *errStrings[]=
{
	"Sucess",			/*  0 */
	"Unknow error",		/* -1 */
	"Generic error",	/* -2 */
	"Memory allocation error", /* -3 */
	"Ordenation function fails", /* -4 */
	"Pointer to a function not know", /* -5 */
	NULL
};

void err(int errCode, char file[], int line);