//
//  BookCharacter.cpp
//  Assignment 3
//
//  Created by Berk Dehrioğlu on 29/11/2017.
//  Copyright © 2017 Berk Dehrioğlu. All rights reserved.
//

#include "BookCharacter.hpp"
#include <iostream>


BookCharacter::BookCharacter(std::string page, std::string line, std::string index, std::string character){
    this->character = character;
    this->page = page;
    this->line = line;
    this->index = index;
}

BookCharacter::~BookCharacter(){
    
}

std::string BookCharacter::getLine(){
    return this->line;
}

std::string BookCharacter::getPage(){
    return this->page;
}
std::string BookCharacter::getIndex(){
    return this->index;
}

std::string BookCharacter::getCharacter(){
    return this->character;
}

void BookCharacter::setCharacter(std::string str){
    this->character = str;
}
