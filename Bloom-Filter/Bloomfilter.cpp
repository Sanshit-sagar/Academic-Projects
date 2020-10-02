#include "BloomFilter.hpp"
#include <string>
#include <iostream>

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>


using namespace std;

/* Create a new bloom filter with the size in bytes */
BloomFilter::BloomFilter(size_t numBytes)
{
    numSlots = numBytes * 8;
    table = allocTable(numSlots);
}

unsigned char* BloomFilter::allocTable(int tableSize) {
    unsigned char * new_table = (unsigned char *) malloc(tableSize/8);
    memset(new_table, 0, numSlots);
    for(int i = 0; i<tableSize; i++) {
      new_table[i] = 0x00;
    }
    return new_table;
}

void BloomFilter::printTable() {
  for(int i = 0; i<numSlots; i++) {
    unsigned char currCharPtr = table[i];
    printChar(currCharPtr);
  }
  cout << endl;
}

void BloomFilter::printChar(unsigned char currChar) {
  cout << hex << (int)currChar;
}

unsigned char BloomFilter::setBit(unsigned char curr_char_ptr, int bitIndex) {
  if(bitIndex<0 || bitIndex>7) {
    cout << "The provided bitIndex should be between 0 and 7" << endl;
    return curr_char_ptr;
  }
  unsigned char flag = 1U;
  int i = 1;
  while(i<=bitIndex) {
    flag = flag << 1;
    ++i;
  }
  curr_char_ptr |= flag;
  return curr_char_ptr;
}

bool BloomFilter::checkBit(unsigned char curr_char_ptr, int bitIndex) {
    if(bitIndex<0 || bitIndex>7) {
      cout << "The provided bitIndex should be between 0 and 7" << endl;
      return false;
    }
    //Returns true if the bit at the bitIndex in curr_char_ptr is set already
    unsigned char flag = 1U;
    int i = 1;
    while(i<=bitIndex) {
      flag = flag << 1;
      ++i;
    }
    bool res = curr_char_ptr & flag;
    return res;
}

int BloomFilter::getArrayIndex(int hash_index) {
  int arr_ind = hash_index/8;
  return arr_ind;
}
int BloomFilter::getArrayIndexOffset(int hash_index) {
  int arr_ind_offset = hash_index%8;
  return arr_ind_offset;
}

void BloomFilter::updateTable(int given_hash_val) {
//  cout << given_hash_val << "****"<< endl;
  div_t res = div(given_hash_val, 8);
  int hash_index = res.quot;
  int hash_offset = res.rem;
//  cout << "Setting bit at ind: " << hash_index << " with offset: " << hash_offset << endl;
  unsigned char hash_uc = table[hash_index];
//  cout << "BEFORE" << endl;
//  printChar(hash_uc);
  hash_uc = setBit(hash_uc, hash_offset);

//  cout << "AFTER" << endl;
//  printChar(hash_uc);
  table[hash_index] = hash_uc;
//  cout << "Updated Table. Exiting." << endl;
}

bool BloomFilter::checkTable(int given_hash_val) {
  //cout << given_hash_val << ", Inside checkTable" << endl;
  div_t res = div(given_hash_val, 8);
  int hash_index = res.quot;
  int hash_offset = res.rem;
//  cout << "Checking bit at ind: " << hash_index << " with offset: " << hash_offset << endl;
  unsigned char hash_uc = table[hash_index];
  bool does_exist = checkBit(hash_uc, hash_offset);
  return does_exist;
}

int BloomFilter::hashAB(std::string word)
{
    int result = 0;
    for(size_t i = 0; i < word.length(); ++i) {
        result += word[i] * pow(31, i);
    }
    return result%numSlots;
}


int BloomFilter::RSHash(std::string str)
{
    unsigned int b    = 378551;
    unsigned int a    = 63689;
    unsigned int hash = 0;

    for(std::size_t i = 0; i < str.length(); i++)
    {
        hash = hash * a + str[i];
        a    = a * b;
    }
  //  cout << "RSHash: " << (hash & 0x7FFFFFFF) << endl;
    unsigned int res = (hash & 0x7FFFFFFF) + 62;
    unsigned int s_res = (int) res;
    return s_res%numSlots;
 }

int BloomFilter::JSHash(std::string str)
 {
      unsigned int hash = 1315423911;

      for(std::size_t i = 0; i < str.length(); i++)
      {
          hash ^= ((hash << 5) + str[i] + (hash >> 2));
      }
      //cout << "JSHash: " << (hash & 0x7FFFFFFF) << endl;
      unsigned int res = (hash & 0x7FFFFFFF) + 62;
      int s_res = (int) res;
      return s_res%numSlots;
 }

/* Insert an item into the bloom filter */
void BloomFilter::insert(std::string item)
{
  int hashA =  hashAB(item);
  int hashB =  RSHash(item);
  int hashC =  JSHash(item);

  updateTable(hashA);
  updateTable(hashB);
  updateTable(hashC);
}

/* Determine whether an item is in the bloom filter */
bool BloomFilter::find(std::string item)
{
  int hashA =  hashAB(item);
  int hashB =  RSHash(item);
  int hashC =  JSHash(item);

  if(checkTable(hashA)==true && checkTable(hashB)==true && checkTable(hashC)==true) {
    return true;
  }
  return false;
}

/* Destrctor for the bloom filter */
BloomFilter::~BloomFilter()
{
    delete[] table;
}