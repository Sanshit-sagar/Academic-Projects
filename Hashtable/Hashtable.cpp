#include "util.h"
#include "DictionaryHashtable.h"
#include <unordered_set>

std::unordered_set<std::string> hashTable;
std::unordered_set<std::string>::iterator itT; 

DictionaryHashtable::DictionaryHashtable(){}

bool DictionaryHashtable::insert(std::string word)
{
  itT = hashTable.find(word);
  if(itT != hashTable.end()){
    return false;
  }  
  else{
    hashTable.insert(word);
    return true;
  }
}

bool DictionaryHashtable::find(std::string word) const
{
  itT = hashTable.find(word);
  if(itT != hashTable.end()){
    return true;
  }
  else{

    return false;
  }   
}

DictionaryHashtable::~DictionaryHashtable(){}