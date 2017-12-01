//
//  List.cpp
//  Assignment 3
//
//  Created by Berk Dehrioğlu on 01/12/2017.
//  Copyright © 2017 Berk Dehrioğlu. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <ctime>


#include "List.hpp"

List::List(){
    for(auto i = 0; i < SIZE; i++){
        this->listArr[i] = nullptr;
    }
    std::cout << "LIST" << std::endl << std::endl ;
}


List::~List(){
    
}

void List::readFile(){
    
    std::string row;
    std::string key;
    std::ifstream myfile("ds-set-input.txt");
    int j = 0;
    
    auto startList = std::chrono::system_clock::now();
    auto endList = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsList ;

    
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
            
            startList = std::chrono::system_clock::now();
            BookCharPtr ptr = std::make_unique<BookCharacter>(page,line,index,character);
            listArr[j] = std::move(ptr);
            endList = std::chrono::system_clock::now();
            
            elapsedSecondsList = elapsedSecondsList + ( endList - startList);
            j++;
        }
    }

    
    
    std::cout << "List  insertion finished after " << elapsedSecondsList.count() << " seconds\n" << std::endl;
}

void List::lookup(){
    
        std::string row;
        std::string keyList,keyFile;
        std::ifstream myfile("ds-set-lookup.txt");
        std::ofstream out("ds-set-output-list.txt");
    

        auto startList = std::chrono::system_clock::now();
        auto endList = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsedSecondsList ;
    
        if (myfile.is_open())
        {
            while (std::getline(myfile, row) )//read file line by line
            {
                
                std::string page, line, index;
                std::istringstream iss(row);//stream to split line
                
                iss >> page ;
                iss >> line;
                iss >> index;
                keyFile = page + line + index ;
                BookCharPtr ptr = std::make_unique<BookCharacter>(page,line,index,"");
                
                startList = std::chrono::system_clock::now();
                
                for(auto i = 0 ; i < SIZE-1 ; i++ )
                {
                        keyList = listArr[i]->getPage() + listArr[i]->getLine() + listArr[i]->getIndex();
                        if(keyList == keyFile){
                                    ptr->setCharacter(listArr[i]->getCharacter());
                        }
                    
                        
                }
                endList = std::chrono::system_clock::now();

                elapsedSecondsList = elapsedSecondsList + ( endList - startList);
                out << ptr->getPage() << "\t" <<  ptr->getLine() << "\t" << ptr->getIndex() << "\t" << ptr->getCharacter() << "\n" ;
                
            }
        }
    std::cout << "List  lookup finished after " << elapsedSecondsList.count() << " seconds\n" << std::endl;
}


