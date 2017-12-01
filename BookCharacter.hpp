//
//  BookCharacter.hpp
//  Assignment 3
//
//  Created by Berk Dehrioğlu on 29/11/2017.
//  Copyright © 2017 Berk Dehrioğlu. All rights reserved.
//

#ifndef BookCharacter_hpp
#define BookCharacter_hpp

#include <stdio.h>
#include <string>
#include <memory>


#define SIZE 131071


class BookCharacter{
    
public:
    
    BookCharacter(std::string page, std::string line, std::string index, std::string character);
    ~BookCharacter();
    std::string hashFunction();
    std::string getPage();
    std::string getLine();
    std::string getIndex();
    std::string getCharacter();
    void setCharacter(std::string);
    
private:
    
    std::string page;
    std::string line;
    std::string index;
    std::string character;
};

typedef std::unique_ptr<BookCharacter> BookCharPtr;

#endif /* BookCharacter_hpp */
