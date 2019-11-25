/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
using std::string;
using std::pair;
/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream reader(filename);
    string word;
    if(reader.is_open()){
      while(getline(reader,word)){
        string wordcpy=word;
        std::sort(wordcpy.begin(),wordcpy.end());
        if(dict.find(wordcpy)!=dict.end()){
        dict[wordcpy].push_back(word);
       }
       else{
         vector<string> vec;
         vec.push_back(word);
         dict[wordcpy]=vec;
       }
    }
  }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(const string& it:words){
      string wordcpy=it;
      std::sort(wordcpy.begin(),wordcpy.end());
      if(dict.find(wordcpy)!=dict.end()){
      dict[wordcpy].push_back(it);
     }
     else{
       vector<string> vec;
       vec.push_back(it);
       dict[wordcpy]=vec;
     }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string word1=word;
    std::sort(word1.begin(),word1.end());
    if(dict.find(word1)!=dict.end())
    return dict.find(word1)->second;
    else
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;
    for(const pair<string,vector<string>>& it:dict){
      if(it.second.size()>1)
      ret.push_back(it.second);
    }
    return ret;
}
