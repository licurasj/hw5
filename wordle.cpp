#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(std::set<std::string>& words, std::string in, std::vector<char> floatVector);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> words; //set to store all words generated
    std::vector<char> floatVector(floating.begin(),floating.end());

    wordleHelper(words, in, floatVector);
    
    std::set<std::string>::iterator it=words.begin();
    /*
    std::set<std::string>::iterator itD=dict.begin();
    std::set<std::string> out;
    while(itD!=dict.end()){
        while(it!=words.end()){
            if(*it == *itD){
                out.insert(*it);
            }
            it++;
        }
        itD++;
    }
    */
    
    while(it!=words.end()){
        if(dict.find(*it)== dict.end()){
            it = words.erase(it);
            continue;
        }
        it++;
    }
    
    return words;
}

// Define any helper functions here
void wordleHelper(std::set<std::string>& words, std::string in, std::vector<char> floatVector){
    
    size_t spaceOpen = 0; //number of spaces open in the string in
    int ind = -1; //index number of in to be worked on for this iteration
    for(size_t i=0; i<in.size();i++){
        if (in[i]=='-'){
            if(ind==-1){
                ind = i;
            }
            spaceOpen++;
        }
    }

    //check if all spaces filled
    if(spaceOpen==0){ //word complete
        words.insert(in);//insert into set
        return;
    }

    //check if enough space for floating char
    bool noSpace = false;
    if(spaceOpen <= floatVector.size()){ //float size vs remaining space
        noSpace= true;
    }
    
    std::string alphabet="abcdefghijklmnopqrstuvwxyz";
    std::string::iterator it;

    for(it=alphabet.begin();it!=alphabet.end();it++){ //loop try all alphabet
        
        bool isFloat = false;
        std::vector<char>::iterator itV = floatVector.begin();
        while(itV!=floatVector.end()){
            if(*it==*itV){
                itV = floatVector.erase(itV);
                isFloat=true;
                break;
            }
            itV++;
        }
        
        if(noSpace && !isFloat){
            continue;
        }

        in[ind]=*it; //set in with character
        wordleHelper(words, in, floatVector); // recurese
        
        if(isFloat){ // reset float and in after trying
            floatVector.push_back(*it);
        }
        in[ind]='-';
    } 
}