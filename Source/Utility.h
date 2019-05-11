#pragma once

#include <iostream>
	using std::ostream;
#include <vector>
	using std::vector;

//Write any kind of Vector
template <typename T> 
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;
}

std::string getFileExt(const std::string& s);

std::string getFileDir(const std::string& s);

/* All credit to Cormac Guerin: https://stackoverflow.com/questions/10248728/how-to-find-longest-common-substring-using-c
 * */
std::string longestCommonString( std::string a, std::string b );