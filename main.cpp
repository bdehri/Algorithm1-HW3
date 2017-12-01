//
//  main.cpp
//  Assignment 3
//
//  Created by Berk Dehrioğlu on 29/11/2017.
//  Copyright © 2017 Berk Dehrioğlu. All rights reserved.
//

#include <iostream>

#include "Dictionary.hpp"
#include "List.hpp"


std::vector<int> vect;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Dictionary dic;
    dic.readFile();
    dic.lookup();
    List list;
    list.readFile();
    list.lookup();
 
    return 0;
}
