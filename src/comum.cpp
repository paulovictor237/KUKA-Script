#include <iostream>
#include <fstream>
#include <iomanip>      // std::setprecision & std::setw
#include <algorithm>    // std::count
#include <math.h>       // M_PI
#include <sstream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

#include "comum.h"


std::string split_string(std::string tokenString,string delim,int saida){
  vector<string> tokens;
  std::regex delimiters {delim};
  sregex_token_iterator tokens_begin { tokenString.begin(), tokenString.end(), delimiters, -1 };
  auto tokens_end=sregex_token_iterator {};
  for (auto token_it=tokens_begin; token_it != tokens_end; token_it++)tokens.push_back(*token_it);
  return tokens[saida];
}
vector<string> split_string(std::string tokenString,string delim,bool print){
  vector<string> tokens;
  std::regex delimiters {delim};
  sregex_token_iterator tokens_begin { tokenString.begin(), tokenString.end(), delimiters, -1 };
  auto tokens_end=sregex_token_iterator {};
  for (auto token_it=tokens_begin; token_it != tokens_end; token_it++)tokens.push_back(*token_it);
  
  if(print==true){
    int i=0;
    for (auto &outt : tokens){
      cout << "[" << i << "]"<< "-> " << outt << "\n";
      i++;
    }
  }
  return tokens;
}

void split_string_print(std::string tokenString,string delim)
{
  vector<string> aux=split_string(tokenString,delim);
  int i=0;
  for (auto &outt : aux){
    cout << "[" << i << "]"<< "-> " << outt << "\n";
    i++;
  }
}


std::string ponto_remove_turn(std::string entrada)
{
  std::string aux = split_string(entrada,",T")[0] + "}";
  return aux;
}

int copy_file(std::ofstream &out,std::string in1,std::string in2)
{
  std::ifstream Pallet1 (in1);
  std::ifstream Pallet2 (in2);
  out << ";FOLD PALLET 1" << endl;
  out << Pallet1.rdbuf();
  out << ";ENDFOLD" << endl;
  out << ";FOLD PALLET 2" << endl;
  out << Pallet2.rdbuf();
  out << ";ENDFOLD" << endl;
  Pallet1.close();
  Pallet2.close();
  return 0;
}