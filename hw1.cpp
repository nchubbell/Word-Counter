
/*
 Name: Nathan Hubbell
 Email: nchubbell@crimson.ua.edu
 Course Section: Fall 2024 CS 201
 Homework #: 1
 To Compile: g++ -std=c++20 hw1.cpp
 To Run: ./a input.txt
*/

#include <iostream>
#include <vector>
#include <regex>
#include <fstream>
#include <chrono>
#include <thread>

#include "ST.hpp"
#include "RBTPrint.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputFile(argv[1]);
    std::string text;
    std::vector<std::string> tokens;
    // open input file for reading, creates a text string to hold each word, creates a vector token to store every word as an element
    const std::regex delim("\\s+"); 

    while (inputFile >> text) { 
        auto begin = std::sregex_token_iterator(text.begin(), text.end(), delim, -1);
        auto end = std::sregex_token_iterator();
        for (std::sregex_token_iterator word = begin; word != end; word++) {
         tokens.push_back(*word);
        }
    }
    // given code parses all the words into the vector tokens

    // sorts the vector into alphabetical order
    sort(tokens.begin(), tokens.end());

    // new vector used for each uniwue word
    vector<string> unique;  
    
    // loop fills unique vector with one of each word in tokens
    for (int i=0; i<tokens.size(); i++) {
        string word = tokens[i];
        if (i==0) {
            // for the instance of the starting value
            unique.push_back(word);
            continue;
        }
        // skips if word has already been put into the vector unique
        if (word == tokens[i-1]) continue;
        // puts word into unique vector
        else unique.push_back(word);
    }

    // creates array to store number of times a word appears
    int array[unique.size()] = {0};
    int j=0;
    // loop determines number of times each word appears
    for (int i=0; i<tokens.size(); i++) {
        if (tokens[i] == unique[j]) { // word appearance
            array[j] = array[j] + 1; // add one to word count
        } else {
            j += 1;
            array[j] = array[j] + 1; // add one to word count
        }
    }

    // array of sorted numbers from greatest to least
    int sorted[unique.size()]; 

    // loop puts array values into sorted
    for (int i=0; i<unique.size(); i++) {
        sorted[i] = array[i];
    }

    // sort function sorts the integers from greatest to least
    sort(sorted,sorted + unique.size(), greater<int>());
    int k=0;
    int i=0;
    // new vector that will have the words in alphabetical order
    // corresponding to the sorted array
    vector<string> newUn;
    // loop creates newUn array of sorted words by number of appearances
    while (k<unique.size()) {
        if (array[i] == sorted[k]) { // integer matched wit integer
            
            newUn.push_back(unique[i]); // pushes unique word into newUn
            k += 1; // move to next integer
            array[i] = 0; // ensures loop doesn't reiterate the same unique word
            i = 0; // reset array to find new integer
            continue;
        }
        i += 1;
        // moves to next value
    }

    // loop outputs sorted words with values from greatest to least in alphabetical order
    for (int i=0; i<unique.size(); i++) {
        cout << newUn[i] << ": " << sorted[i] << endl;
    }


    // close file
    inputFile.close();
    return 0;
}