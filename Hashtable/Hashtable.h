#ifndef DICTIONARY_HASHTABLE_H
#define DICTIONARY_HASHTABLE_H

#include <string>

class DictionaryHashtable {

public: 
  DictionaryHashtable();

  bool insert(std::string word);

  bool find(std::string word) const;

  ~DictionaryHashtable();

};

#endif 
