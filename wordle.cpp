#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
//One recursive call is responsible for nth location in the string
void build_all_string(
    const std::string& in, 
    std::string floating, 
    const std::set<std::string>& dict, 
    std::set<std::string>& result,
    std::string temp,
    size_t n){
        if(n == in.length()){
        //Base case
            if(floating.empty()){
            //Floating is empty, meaning we've satisfied all the requirement
                result.insert(temp);
            }
            return;
        }
        else{
            if(in[n] != '-'){
            //If the particular spot is already determined by in
                build_all_string(in, floating, dict, result, temp+in[n], n+1);
            }
            else{
                for(int i = 0; i < 26; i++){
                //Iterate through all alphabet
                    char curr = 'A' + i;
                    if(floating.find(curr) != std::string::npos){
                    //If the particular character is in floating: remove and then recurse, then undo that remove
                        int index = floating.find(curr);
                        floating.erase(index);
                        build_all_string(in, floating, dict, result, temp+(curr), n+1);
                        floating.push_back(index);
                    }
                    else{
                    //Simply recurse to the next step
                        build_all_string(in, floating, dict, result, temp+(curr), n+1);
                    }
                }
            }
        }
}


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> result{};

    //Recursion
    build_all_string(in, floating, dict, result, "", 0);

    std::set<std::string>::iterator it = result.begin();
    for(; it != result.end(); ++it){
        //Iterate through the result
        if(dict.find(*it) == dict.end()){
        //An element from result doesn't exist in the dictionary: not valid word
            result.erase(*it);
        }
    }

    return result;
}

// Define any helper functions here
