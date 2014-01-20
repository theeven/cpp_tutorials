#ifndef GETDICTIONARY_H
#define GETDICTIONARY_H

#include <iostream>
#include <vector>

const char * const dictionaryFile = "./diction.txt";

std::vector<std::string> getDictionary( std::size_t n = -1 );

#endif
