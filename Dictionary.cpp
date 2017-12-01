//
//  Dictionary.cpp
//  Assignment 3
//
//  Created by Berk Dehrioğlu on 29/11/2017.
//  Copyright © 2017 Berk Dehrioğlu. All rights reserved.
//

#include "Dictionary.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <ctime>



Dictionary::Dictionary(){
    for(auto i = 0; i < SIZE; i++){
        this->dictionaryArr[i] = nullptr;
    }
    A = (sqrt(5) - 1)/2;
    //A = 0.61803398875;
    this->collision = 0;
    this->totalCollision = 0;
    this->lookupCollision = 0;
    this->counter = 0;
    
    std::cout << "DICTIONARY" << std::endl << std::endl ;
}

Dictionary::~Dictionary(){
    
}

void Dictionary::readFile(){
    std::string row;
    std::string key;
    std::ifstream myfile("ds-set-input.txt");
    int j = 0;
    auto startDictionary= std::chrono::system_clock::now();
    auto endDictionary = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsDictionary ;
    std::vector<int> collisionVector;
    
    if (myfile.is_open())
    {
        while (std::getline(myfile, row) )//read file line by line
        {
            
            std::string page, line, index, character;
            std::istringstream iss(row);//stream to split line
            
            iss >> page ;
            iss >> line;
            iss >> index;
            iss >> character;
            key = page + line + index;
            
            startDictionary = std::chrono::system_clock::now();
            
            if(j == 999 || j == 9999 || j == 99999){
                collisionVector.push_back(totalCollision);
            }
            insert(std::make_unique<BookCharacter>(page,line,index,character), atoi(key.c_str()));
            
            endDictionary = std::chrono::system_clock::now();
            
            elapsedSecondsDictionary = elapsedSecondsDictionary + ( endDictionary -startDictionary);
            j++;
        }
    }
    
    std::cout << "Dictionary insertion finished after " << elapsedSecondsDictionary.count() << " seconds\n" << std::endl;
    
    std::cout << "Average number of collisions (first 1,000) || " << (float)collisionVector[0]/1000 << std::endl;
    std::cout << "Average number of collisions (first 10,000) || " << (float)collisionVector[1]/10000 << std::endl;
    std::cout << "Average number of collisions (first 100,000) || " << (float)collisionVector[2]/100000 << std::endl;
    std::cout << "Average number of collisions (overall) || " << (float)this->totalCollision/SIZE -1 << std::endl << std::endl ;
    
}

void Dictionary::insert(BookCharPtr ptr, unsigned long long key){
    double B = A * (float) key;
    double C = B - (int)B;
    double flr = (double)SIZE * C;
    int h = floor( flr );
    unsigned long long newKey;
    

    
    if(dictionaryArr[h] == nullptr){
        dictionaryArr[h] = std::move(ptr);
        counter ++;
        
    }
    else{
        collision = 0 ;
        while(1){
            
            collision++;
            
            
            newKey = (unsigned long long)(h + (7 * this->collision) + (3 * this->collision * this->collision)) ;
            newKey = newKey%SIZE;
            if(dictionaryArr[newKey] == nullptr){
                break;
            }
        }
        dictionaryArr[newKey] = std::move(ptr);
        totalCollision += collision;
        counter ++;
    }
}

unsigned long long Dictionary::probing(unsigned long long hash){//Not used same code but collision count goes much higher
    unsigned long long newKey;
    collision++;
    
    
    newKey = (unsigned long long)(hash + (7 * this->collision) + (3 * this->collision * this->collision)) ;
    newKey = newKey % SIZE;
    if(dictionaryArr[newKey] == nullptr){
        return newKey;
    }
    else{
        return probing(newKey);
    }
}

void Dictionary::lookup(){
    std::string row;
    std::string key,keyDictionary;
    unsigned long long newHash;
    std::ifstream myfile("ds-set-lookup.txt");
    std::ofstream out("ds-set-output-dictionary.txt");
    int j = 0;
    
    auto startDictionary = std::chrono::system_clock::now();
    auto endDictionary = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsDictionary ;
    
    if (myfile.is_open())
    {
        while (std::getline(myfile, row) )//read file line by line
        {
            
            std::string page, line, index;
            std::istringstream iss(row);//stream to split line
            
            iss >> page ;
            iss >> line;
            iss >> index;
            key = page + line + index;
            
            BookCharPtr ptr = std::make_unique<BookCharacter>(page,line,index,"");
            
            double B = A * (atof(key.c_str()));
            double C = B - (int)B;
            double flr = (double)SIZE * C;
            int h = floor( flr );
            
            startDictionary = std::chrono::system_clock::now();
            keyDictionary = dictionaryArr[h]->getPage() + dictionaryArr[h]->getLine() + dictionaryArr[h]->getIndex();
            
            if(dictionaryArr[h] != nullptr && keyDictionary.compare(key) == 0){
                    std::string characterAdder = dictionaryArr[h]->getCharacter();
                    ptr->setCharacter(characterAdder);
                    j++;
            }
            else{
                
                newHash = lookupProbing(h,key);
                std::string characterAdder = dictionaryArr[newHash]->getCharacter();
                ptr->setCharacter(characterAdder);
                lookupCollision = 0;
                j++;
            }
    
            endDictionary = std::chrono::system_clock::now();
            elapsedSecondsDictionary = elapsedSecondsDictionary + ( endDictionary - startDictionary);
            out << ptr->getPage() << "\t" <<  ptr->getLine() << "\t" << ptr->getIndex() << "\t" << ptr->getCharacter() << "\n" ;
        }
    }
    std::cout << "Dictionary  lookup finished after " << elapsedSecondsDictionary.count() << " seconds\n" << std::endl;
}

unsigned long long Dictionary::lookupProbing(unsigned long long hash,std::string key){
    std::string keyDictionary;
    unsigned long long newHash;
    while(1){
        
        lookupCollision++;
        
        
        newHash = (unsigned long long)( hash + (7 * this->lookupCollision) + (3 * this->lookupCollision * this->lookupCollision)) ;
        newHash = newHash % SIZE;
        
        if(dictionaryArr[newHash] != nullptr){
            keyDictionary = dictionaryArr[newHash]->getPage() + dictionaryArr[newHash]->getLine() + dictionaryArr[newHash]->getIndex();
            if(keyDictionary.compare(key) == 0){
                break;
            }
            
        }
        if(lookupCollision >5000){//If collision is too high look linearly
            for(auto i = 0 ; i < SIZE-1 ; i++ )
            {
                if(dictionaryArr[i] != nullptr){
                    keyDictionary = dictionaryArr[i]->getPage() + dictionaryArr[i]->getLine() + dictionaryArr[i]->getIndex();
                    if( keyDictionary == key){
                        return i;
                    }
                }
                
                
            }
        }
    }
    return newHash;
}
