//
//  Dictionary.hpp
//  Assignment 3
//
//  Created by Berk Dehrioğlu on 29/11/2017.
//  Copyright © 2017 Berk Dehrioğlu. All rights reserved.
//

#ifndef Dictionary_hpp
#define Dictionary_hpp



#include <stdio.h>
#include <vector>

#include "BookCharacter.hpp"



class Dictionary{
public:
    
    Dictionary();
    ~Dictionary();
    void readFile();
    void lookup();
    unsigned long long lookupProbing(unsigned long long hash,std::string key);
private:
    void insert(BookCharPtr ptr, unsigned long long key);
    unsigned long long probing(unsigned long long hash);
    BookCharPtr dictionaryArr[SIZE];
    int collision;
    int lookupCollision;
    int counter;
    double A;
};

#endif /* Dictionary_hpp */

