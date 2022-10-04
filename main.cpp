/*main.cpp

                        Project 2  - Search Engine
        Written [10/02/2022] by [George Fashho] for CS 251, Fall 2022

    [ A program that has the functionality of a search engine where users
        can search for specific terms and filter out unwanted URLS with
        [+/-]                                                           ]


                              [CREATIVE COMPONENT]
                      set<string>stopWords(string fileName)
    Included in my submission is a txt file named stopwords.txt. The purpose of this
    function to  filter out any stop words (unnecessary words) from the index and make
    it smaller. To have this feature work please uncomment lines 115 & 124 in search.h .

*/
#include <iostream>
#include "search.h"
using namespace std;

int main() {

    string filename ;
    filename = "cplusplus.txt";

    searchEngine(filename);


                               /*------TEST CASES------*/

/*----------------------------------------------------------------------------------------*/

                            /*------Clean Token Tests------*/

//    string ans = "hello";
//    cout << "1. " << (ans = cleanToken(".-h.e.l.l.o.")) << endl;
//    cout << "2. " << (ans = cleanToken("...hello")) << endl;
//
//    ans = cleanToken("....2312^#@@@....");
//    cout << ans << endl ;

/*----------------------------------------------------------------------------------------*/

                           /*------Gather Tokens Tests------*/

//    set<string> tokens = gatherTokens("to be or ///+n,ot!!!& to be");
//    set<string> tokensANS;
//    tokensANS.insert("to");
//    tokensANS.insert("be");
//    tokensANS.insert("or");
//    tokensANS.insert(cleanToken("///n,ot!!!&"));
//    tokensANS.insert("to");
//    tokensANS.insert("be");
//
//    cout << "1. " << (tokens.size() == 4) << endl;
//    cout << "2. " << (tokens == tokensANS) << endl;

/*----------------------------------------------------------------------------------------*/

                       /*------BuildIndex() & findQueryMathes() Tests------*/

//    set<string>results;
//    map<string, set<string>> index ;
//
//    cout<< buildIndex("tiny.txt",index);
//    string sentence  = "fish" ;
//    results =  findQueryMatches(index,sentence);
//
//    for (auto& str: results){
//
//        cout<< str<<"\n";
//    }  //should print 2 URLS


//    cout<< buildIndex("tiny.txt",index);
//    string sentence  = "fish -one" ;
//    results =  findQueryMatches(index,sentence);
//
//    for (auto& str: results){
//
//        cout<< str<<"\n";
//    }  //should print 1 URL


//    cout<< buildIndex("tiny.txt",index);
//    string sentence  = "fish +one " ;
//    results =  findQueryMatches(index,sentence);
//
//    for (auto& str: results){
//
//        cout<< str<<"\n";
//    }  //should print 2 URLS


//    cout<< buildIndex("tiny.txt",index);
//    string sentence  = "red fish" ;
//    results =  findQueryMatches(index,sentence);
//
//    for (auto& str: results){
//
//        cout<< str<<"\n";
//    }  //should print 3 URLS


//    cout<< buildIndex("tiny.txt",index);
//    string sentence  = "not -trying" ;
//    results =  findQueryMatches(index,sentence);
//
//    for (auto& str: results){
//
//        cout<< str<<"\n";
//    }  //blank


//    cout<< buildIndex("tiny.txt",index);
//    string sentence  = "fish +red yellow +red" ; //FISH and RED //OR// yellow and red
//    results =  findQueryMatches(index,sentence);
//
//    for (auto& str: results){
//
//        cout<< str<<"\n";
//    }  //should print 2 URLS rainbow.org/ dr.sues


//    cout<< buildIndex("tiny.txt",index);
//    string sentence  = "fish -red blue +fish" ; //FISH without RED //OR// blue and fish
//    results =  findQueryMatches(index,sentence);
//
//    for (auto& str: results){
//
//        cout<< str<<"\n";
//    }  //should print 2 URLS rainbow.org/ dr.sues

/*----------------------------------------------------------------------------------------*/

    /*------Stop Words------*/
//    set<string>temp = stopWords("stopwords.txt");
//
//    for(auto &str: temp){
//        cout<< str << endl ;
//    }

    return 0;
}//end main

