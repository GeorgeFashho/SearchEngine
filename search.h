/*search.h  - header file that includes all functions needed to operate
               the search engine

            written by: [George Fashho] on [10/02/2022]
 */

#pragma once

#include <iostream>
#include <set>
#include <map>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <utility>
#include <algorithm>

using namespace std;


/* CleanToken(string param1):
 *  Function that cleans a string from any punctuation at the
 *  start and end of the string but leaves any punctuation
 *  in-between
 *
 * @param s : String to clean
 * ...
 */
string cleanToken(string s) {

    bool isPunc; //bool to check if there is a punctuation
    int length = 0;

    for (char i: s) {  //counting amount of punctuations at the start of a string

        isPunc = ispunct(i);
        if (isPunc) {
            length++;
        } else {
            break;
        }
    }

    if (length > 0) {  //erasing punctuations at start of string
        s.erase(0, length);
    }

    length = 0;

    for (int i = s.size() - 1; i >= 0; i--) { //counting amount of punctuations at the end of a string

        isPunc = ispunct(s.at(i));
        if (isPunc) {
            length++;
        } else {
            break;
        }
    }

    if (length > 0) { //erasing punctuations at the end of string
        s.erase(s.size() - length, s.size() - 1);
    }

    int chrCount = 0;

    for (char i: s) { //checking if at-least one character is a letter

        if (isalpha(i)) {
            chrCount++;
        }
    }

    if (chrCount == 0) { //returning null if not an actual word
        return "";
    }

    transform(s.begin(), s.end(), s.begin(), ::tolower); //making word lowercase
    return s;
}//end cleanTokens()


/* stopWords(string param1):
 * Function that adds a txt file of stop words into a set,
 * function is called in gather tokens to filter out stop words
 * and make index smaller. Returns a set of unique stop words
 *
 * @param filename : name of file
 * ...
 */
set<string>stopWords(string fileName){
    set<string>temp;

    ifstream file ;
    string line;
    file.open(fileName);
    while(getline(file,line)){
        temp.insert(line);
    }
    file.close();
    return temp;

}//end stopWords


/* gatherTokens(string param1):
 *  Function that splits a string of words at a space, cleans the words
 *  then pushes them into a set of unique tokens
 *
 * @param text : String to split and clean words from
 * ...
 */
set<string> gatherTokens(string text) {

    set<string> tokens;
//    set<string>stopwords = stopWords("stopwords.txt");

    istringstream s(text);
    string chr;

    while (getline(s, chr, ' ')) { // splitting string at every space

        chr = cleanToken(chr); //cleaning tokens

        if (chr.empty() /*|| stopwords.count(chr) == 1*/) { //if a word not returned from clean token continue to next
            continue;
        }

        tokens.insert(chr); //inserting words into set
    }

    return tokens;
}//end gatherTokens()


/* buildIndex(string param1, map<string, set<string>> &param2):
 *  This function maps every token word with URLS that had those words
 *  in their descriptions
 *
 * @param filename : txt file that contains all the URLS and descriptions
 * @param index : a map with keys being a unique token mapped to a
 *                  set of URLS matching the description
 * ...
 */
int buildIndex(string filename, map<string, set<string>> &index) {

    int webPagesProcessed = 0;

    string url, keyword;
    set<string> temp; //temp container to fill and push back into the map

    ifstream infile(filename);
    string line;

    if (!infile.is_open()) {  //error handling for invalid file name
        cout << "Error: unable to open '" << filename << "'\n";
        return 0;
    }

    while (!infile.eof()) {

        getline(infile, line, '\n'); //first line is always URL
        url = line;
        getline(infile, line, '\n'); //second line description
        keyword = line;

        if (url.empty()) { //eof breaks loop to prevent blank lines in set
            break;
        }

        temp = gatherTokens(keyword); // Calling gathertokens function and adding to
                                         // a temporary set container
        for (auto token: temp) {     //Looping through every element in the set
                                          //adding the token as the maps key and pushing
            index[token].insert(url); //urls into a set as the keys elements
        }
        webPagesProcessed++; //incrementing URLS processed
    }
    return webPagesProcessed;
}//end buildIndex()


/* findQueryMatches( map<string, set<string>> &param1, string param2):
 *  This function takes input from user in the form of a string of words,
 *  words can be prefaced with a "+" (standing for an AND operator) or a
 *  "-" (standing for WITHOUT). After taking user input it finds URLS
 *  matching that description word, looks for intersection, difference
 *  or union if multiple words were inputted
 *
 * @param index : a map with keys being a unique token mapped to a
 *                  set of URLS matching the description
 * @param sentence : user input for search terms
 * ...
 */
set<string> findQueryMatches(map<string, set<string>> &index, string sentence) {
    set<string> result; //set to return results

    set<string> second; //temp set to hold URLS
    set<string> inserterSet;

    vector<string> words; //list of query words

    stringstream ss(sentence);
    string word;

    while (getline(ss, word, ' ')) { //splitting  up words, pushing into a vector
        words.push_back(word);
    }

    if(words.size()>1) { //checking to see if user inputted more than one search term

        string firstTerm = cleanToken(words.at(0));
        result = index[firstTerm]; //adding set of URLS into result set
        string tempStringClean;

        for (int i = 0; i < words.size(); i++) {

            if (words.at(i)[0] == '+') { //checks if user specified "+" then finding intersection between URLS
                tempStringClean = cleanToken(words.at(i));
                second = index[tempStringClean];
                set_intersection(result.begin(), result.end(), second.begin(), second.end(),
                                 inserter(inserterSet, inserterSet.begin()));

            }
            else if (words.at(i)[0] == '-') {//checks if user specified "-" then finding difference between URLS
                tempStringClean = cleanToken(words.at(i));
                second = index[tempStringClean];
                set_difference(result.begin(), result.end(), second.begin(), second.end(),
                               inserter(inserterSet, inserterSet.begin()));

            }
            else { //if user does not specify any preface before words then default is to find union between URLS
                tempStringClean = cleanToken(words.at(i));
                second = index[tempStringClean];
                set_union(result.begin(), result.end(), second.begin(), second.end(),
                          inserter(inserterSet, inserterSet.begin()));
            }

            result = inserterSet;
            inserterSet.clear();
        }
    }
    else { //if only one word inputted then all URLS fitting that description are added
        string searchTerm = cleanToken(words.at(0));

        result = index[searchTerm];
    }
    return result;
}//end findQueryMatches


/* findQueryMatches(string param1):
 * A function that puts all the previous functions to use.
 * Asks user to input query words and returns matching URLS
 * depending on what filters they added.
 *
 * @param filename : name of txt file to build index
 * ...
 */
void searchEngine(string filename) {

    int webPagesIndexed;
    map<string, set<string>> index;

    cout << "Stand by while building index...\n";
    webPagesIndexed = buildIndex(std::move(filename), index);
    cout << "Indexed " << webPagesIndexed << " pages containing " << index.size() << " unique terms\n";

    string searchTerms;
    set<string> queryMatches;

    do { //asks user input for query sentences until enter is pressed to exit program
        cout << "Enter query sentence (press enter to quit):\n";
        getline(cin, searchTerms);

        if (searchTerms.empty()) {
            cout << "Thank you for searching!\n";
            break;
        }

        queryMatches = findQueryMatches(index, searchTerms);

        cout << "Found " << queryMatches.size() << " matching pages\n";

        for (auto &webpage: queryMatches) { //returns URLS matching query
            cout << webpage << "\n";
        }

    } while (!searchTerms.empty());

}//end searchEngine()



