//+-------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-------------------------------------------------------------------------------+
// BIBLIOTECAS C++

// COMPILAR
// g++ *.cpp -o executavel -std=c++11 && ./executavel 

#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

vector<string> split_string(std::string tokenString,string delim){
  vector<string> tokens;
  std::regex delimiters {delim};
  sregex_token_iterator tokens_begin { tokenString.begin(), tokenString.end(), delimiters, -1 };
  auto tokens_end = sregex_token_iterator {};
  for (auto token_it = tokens_begin; token_it != tokens_end; token_it++)tokens.push_back(*token_it);
  return tokens;
}

int main()
{
  // string a ser separada
  string tokenString { "$OUT[301]=TRUE" };

  vector<string> tokens=split_string(tokenString,"[=]+");

  int i=0;
  for (const string& token: tokens){
    cout << "[" << i << "]"<< "-> " << token << "\n";
    i++;
  }
  // cout << "* [" << tokens[2] << "]\n";
  return 0;
}