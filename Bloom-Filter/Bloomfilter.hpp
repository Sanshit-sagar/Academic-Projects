#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <string>
#include <iostream>
#include <math.h>

using namespace std;

/**
 * The class for bloom filter that provides memory efficient check
 * of whether an item has been inserted before. Small amount of
 * false positives is possible but there will be no false negatives.
 */
class BloomFilter {

public:

    /** Create a new bloom filter with the size in bytes
     * @param numBytes number of bytes
     */
    BloomFilter(size_t numBytes);
    unsigned char * allocTable(int tableSize);

    void printChar(unsigned char curr_char);
    void printTable();

    unsigned char setBit(unsigned char curr_char, int bitIndex);
    bool checkBit(unsigned char curr_char, int bitIndex);

    int getArrayIndex(int hash_index);
    int getArrayIndexOffset(int hash_index);

    int hashAB(std::string key);
    int RSHash(std::string str);
    int JSHash(std::string str);

    void updateTable(int given_hash_val);
    bool checkTable(int given_hash_val);


    /** Insert an item into the bloom filter
     * @param item the item to be inserted
     */
    void insert(std::string item);

    /** Determine whether an item is in the bloom filter
     * @param item item to be searched
     * @return if the item is in the bloom filter
     */
    bool find(std::string item);

    /* Destrctor for the bloom filter */
    ~BloomFilter();


private:

    // The char array as the hash table
    unsigned char* table;
    unsigned int numSlots;

    // TODO: Add your own data and method here

};
#endif 