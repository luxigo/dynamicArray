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

#define __DYNAMIC_ARRAY_C__
#include <dynamicArray.h>

/**
 * Create a dynamic array instance
 * @param storage initial memory block (optional)
 * @param storageSize initial memory block size
 * @param storageSizeInc storage size increment (default=storageSize)
 * @param itemSize array item size
 * @param itemCount initial array item count (optional)
 * @return dynamic array pointer or NULL
 */
dynamicArray *dynamicArray_new(void *storage, size_t storageSize, size_t storageSizeIncr, size_t itemSize, unsigned long itemCount) {
  struct dynamicArray *da=calloc(sizeof(dynamicArray),1);
  if (!da) {
    return NULL;
  }
  da->type=type;
  da->storage=storage;
  da->storageSize=storageSize;
  da->storageSizeIncr=storageSizeIncr?storageSizeIncr:storageSize;
  da->itemSize=itemSize;
  da->itemCount=itemCount;
  da->push=dynamicArray_push;
  da->pop=dynamicArray_pop;
  da->shift=dynamicArray_shift;
  da->set=dynamicArray_set;
  da->get=dynamicArray_get;
  return da;
}

/**
 * Check whether index fits in storage, resize storage and call moved() if needed
 * @param this the array
 * @param index 
 * @return -1 on error, 0 otherwise
 */
int dynamicArray_fitIndex(dynamicArray *this, unsigned long index) {
  char moved=0;
  while (this->itemSize*(index+1)>=this->storageSize){
    void *storage;
    size_t storageSize=this->storageSize+this->storageSizeIncr;
    if (storageSize<=this->storageSize) {
      return -1;
    }
    storage=realloc(this->storage,storageSize);
    if (!storage) {
      return -1;
    }
    moved=moved||(this->storage!=storage);
    this->storage=storage;
    this->storageSize=storageSize;
  }
  if (moved && this->moved) {
    this->moved(this);
  }
  return 0;
}

/**
 * Append item to array
 * @param this the array
 * @param item the item pointer
 * @return the item pointer or NULL on error
 */
void *dynamicArray_push(dynamicArray *this,void *item) {
  if (dynamicArray_fitIndex(this,this->itemCount)<0) {
    return NULL;
  }
  item=memcpy(this->storage+this->itemSize*this->itemCount,item,this->itemSize);
  ++this->itemCount;
  return item;
}

/**
 * Return the last item array and remove it
 * @param this the array
 * @return the item pointer or NULL on error
 */
void *dynamicArray_pop(dynamicArray *this) {
  if (!this->itemCount) {
    return NULL;
  }
  --this->itemCount;
  return this->storage+this->itemSize*this->itemCount;
}

/**
 * Copy the specified item at the specified location
 * @param this the array
 * @param index the item index
 * @param item the item pointer
 */
void *dynamicArray_set(dynamicArray *this,unsigned long index,void *item) {
  if (dynamicArray_fitIndex(this,index)<0) {                 
    return NULL;                                                       
  }      
  item=memcpy(this->storage+this->itemSize*index,item,this->itemSize);
  return item;
}

/**
 * Get the specified item pointer
 * @param this the array
 * @param index the item index
 * @return the item pointer or NULL on error
 */
void *dynamicArray_get(dynamicArray *this,unsigned long index) {
  if (index>=this->itemCount) {
    return NULL;
  }
  return this->storage+this->itemSize*index;
}
