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
  string tokenString { "pick_esteira[Pallet_1,2] = Pick_E_1_P_2" };

  vector<string> tokens=split_string(tokenString,"[_]+");

  int i=0;
  system("clear");
  for (const string& token: tokens){
    cout << "[" << i << "]"<< "-> " << token << "\n";
    i++;
  }
  std::string teste = split_string(tokenString,"[_]+")[0] + "}" ;
  cout << endl;
  cout << tokenString << endl;
  cout << teste << endl;
  // cout << "* [" << tokens[2] << "]\n";
  return 0;
}