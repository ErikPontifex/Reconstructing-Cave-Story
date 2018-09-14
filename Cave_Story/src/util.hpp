//
//  util.hpp
//  Cave_Story
//
//  Created by Erik Pontifex on 2018-09-13.
//  Copyright © 2018 Erik Pontifex. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class Utils {
public:
    
    
    // split str wherever ch is found
    // store the substrings in a vector strs
    // returns the size of the vector
    static unsigned long split(const string &txt, vector<string> &strs, char ch) {
        unsigned long pos = txt.find(ch);
        unsigned long initialPos = 0;
        strs.clear();
        
        while (pos != string::npos) {
            strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
            initialPos = pos + 1;
            
            pos = txt.find(ch, initialPos);
        }
        
        strs.push_back(txt.substr(initialPos, min<unsigned long>(pos, txt.size() - (initialPos + 1))));
        
        return strs.size();
    }
};

#endif /* util_hpp */
