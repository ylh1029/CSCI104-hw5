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
        if(in.size() - n < floating.size()){
        //Earlier base case: if the size of float is larger than 
        //the remaining spots then impossible so return
            return;
        }

        else if(n == in.length()){
        //Base case
            if(floating.empty() && dict.find(temp) != dict.end()){
            //Floating is empty, meaning we've satisfied all the requirement AND 
            //Exists in dict 
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
                    char curr = 'a' + i;
                    if(floating.find(curr) != std::string::npos){
                    //If the particular character is in floating: remove and then recurse, then undo that remove
                        int index = floating.find(curr);
                        floating.erase(index, 1);
                        build_all_string(in, floating, dict, result, temp+curr, n+1);
                        floating.push_back(curr);
                    }
                    else{
                    //Simply recurse to the next step
                        build_all_string(in, floating, dict, result, temp+curr, n+1);
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
    build_all_string(in, floating, dict, result, "", 0);
    return result;
}

// Define any helper functions here
