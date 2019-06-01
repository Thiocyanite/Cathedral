//
// Created by dominik on 11.05.19.
//

#include "Utility.h"

#include <sstream>

std::string getFileExt(const std::string &s) {

    size_t i = s.rfind('.', s.length());
    if (i != std::string::npos) {
        return(s.substr(i+1, s.length() - i));
    }

    return("");
}

std::string getFileDir(const std::string &s) {
#ifdef _WIN32

size_t i = s.rfind('\\', s.length()); //Windows version
    return(s.substr(0, i));
#else
    size_t i = s.rfind('/', s.length()); //*nix version
    return(s.substr(0, i));

#endif
}

std::string longestCommonString(std::string a, std::string b) {
    if( a.empty() || b.empty() ) return {} ;

    std::string current_lcs;

    for(int i=0; i< a.length(); i++) {
        size_t fpos = b.find(a[i], 0);
        while(fpos != std::string::npos) {
            std::string tmp_lcs;
            tmp_lcs += a[i];
            for (size_t x = fpos+1; x < b.length(); x++) {
                tmp_lcs+=b[x];
                size_t spos = a.find(tmp_lcs, 0);
                if (spos == std::string::npos) {
                    break;
                } else {
                    if (tmp_lcs.length() > current_lcs.length()) {
                        current_lcs = tmp_lcs;
                    }
                }
            }
            fpos = b.find(a[i], fpos+1);
        }
    }
    return current_lcs;
}

std::string numToStrWithPadding(int num, int width)
{
    std::stringstream ss;

    // the number is converted to string with the help of stringstream
    ss << num;
    std::string ret;
    ss >> ret;

    // Append zero chars
    int str_length = ret.length();
    for (int i = 0; i < width - str_length; i++)
        ret = "0" + ret;
    return ret;
}