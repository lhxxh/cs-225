/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream reader(word_list_fname);
    string word,word2,word3;
    if(reader.is_open()){
      while(getline(reader,word)){
        word2=word.substr(1);
        word3=word.substr(0);
        word3.erase(word3.begin()+1);
        if(d.homophones(word,word2)&&d.homophones(word,word3)&&d.homophones(word2,word3))
        ret.push_back(make_tuple(word,word2,word3));      
      }
    }
    return ret;
}
