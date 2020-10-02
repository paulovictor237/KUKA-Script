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
  string tokenString { "DECL E6POS XP17TBTT={X 1100.19089,Y -381.19558,Z 914.55891,A -180,B 0,C -180,S 2,T 2,E1 0,E2 0,E3 0,E4 0,E5 0,E6 0}" };

  vector<string> tokens=split_string(tokenString,",T");

  int i=0;
  system("clear");
  for (const string& token: tokens){
    cout << "[" << i << "]"<< "-> " << token << "\n";
    i++;
  }
  std::string teste = split_string(tokenString,",T")[0] + "}" ;
  cout << endl;
  cout << tokenString << endl;
  cout << teste << endl;
  // cout << "* [" << tokens[2] << "]\n";
  return 0;
}