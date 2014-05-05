/*   dynamicArray
 *
 *   Copyright (C) 2014 Foxel SA
 *               
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *               
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *               
 *   You should have received a copy of the GNU General Public Licenseu
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Luc Deschenaux
 *
 */
#ifndef __DYNAMIC_ARRAY__
#define __DYNAMIC_ARRAY__

#ifdef __DYNAMIC_ARRAY_C__
#define __extern
#else
#define __extern extern
#endif

#include <string.h>
#include <stdlib.h>

typedef struct dynamicArray dynamicArray;

struct dynamicArray {
  void *storage;
  size_t storageSize;
  size_t storageSizeIncr;
  size_t itemSize;
  unsigned long itemCount;
  void *(*push)(dynamicArray *this,void *item);
  void *(*pop)(dynamicArray *this);
  void *(*set)(dynamicArray *this,unsigned long index,void *item);
  void *(*get)(dynamicArray *this,unsigned long index);
  void *(*moved)(dynamicArray *this);
};

__extern dynamicArray *dynamicArray_new(void *storage, size_t storageSize, size_t storageSizeIncr, size_t itemSize, unsigned long itemCount);
__extern int dynamicArray_fitIndex(dynamicArray *this, unsigned long index);
__extern void *dynamicArray_push(dynamicArray *this,void *item);
__extern void *dynamicArray_pop(dynamicArray *this);
__extern void *dynamicArray_set(dynamicArray *this,unsigned long index,void *item);
__extern void *dynamicArray_get(dynamicArray *this,unsigned long index);

#undef __extern

#endif


