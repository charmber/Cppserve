#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctype.h>

//查找键值对
void FindKeyValue(std::unordered_map<std::string,std::string>&Te,std::string s,int start,std::string Key);

//查找Json
void FindJson(std::string &json,std::string s,int start);