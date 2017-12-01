//
//  List.hpp
//  Assignment 3
//
//  Created by Berk Dehrioğlu on 01/12/2017.
//  Copyright © 2017 Berk Dehrioğlu. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include <vector>


#include "BookCharacter.hpp"



class List{
public:
    
    List();
    ~List();
    void readFile();
    void lookup();
private:
    void insert(BookCharPtr ptr);
    BookCharPtr listArr[SIZE];

};

#endif /* List_hpp */
