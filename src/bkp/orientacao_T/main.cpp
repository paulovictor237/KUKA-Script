//+-------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-------------------------------------------------------------------------------+
// BIBLIOTECAS C++

// COMPILAR
// g++ *.cpp -o executavel -std=c++11 && ./executavel 
// g++ *.cpp -o executavel -std=c++11 && ./executavel MosaicoA_Pallet1.dat 4


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

vector<string> split_string(std::string tokenString,string delim){
  vector<string> tokens;
  std::regex delimiters {delim};
  sregex_token_iterator tokens_begin { tokenString.begin(), tokenString.end(), delimiters, -1 };
  auto tokens_end = sregex_token_iterator {};
  for (auto token_it = tokens_begin; token_it != tokens_end; token_it++)tokens.push_back(*token_it);
  return tokens;
}
std::string split_string(std::string tokenString,string delim,int saida){
  vector<string> tokens;
  std::regex delimiters {delim};
  sregex_token_iterator tokens_begin { tokenString.begin(), tokenString.end(), delimiters, -1 };
  auto tokens_end=sregex_token_iterator {};
  for (auto token_it=tokens_begin; token_it != tokens_end; token_it++)tokens.push_back(*token_it);
  return tokens[saida];
}
std::string ponto_remove_turn(std::string entrada)
{
  std::string aux = split_string(entrada,",T")[0] + "}";
  return aux;
}
void tudo(std::ifstream &inFile,std::string name,std::string T)
{
  std::ofstream ofs (name+"Out.dat", std::ofstream::out);
  // prefixo(ofs,name);
  std::string entrada;
  std::stringstream entrada2;
  vector<string> split;
  int valor;
  while (!inFile.eof())
  {
    getline(inFile,entrada);
    if(entrada.find("E6POS") !=std::string::npos)
    {
      if(T=="r")
      {
        entrada=ponto_remove_turn(entrada)+"\n";
        ofs<<entrada;
      }
      else
      {
        split=split_string(entrada,"[,]+");
        for(int i=0;i<7;i++){
          entrada2<<split[i];
          entrada2<<",";
        }
        entrada2<<"T " << T <<",";
        for(int i=8;i<13;i++){
          entrada2<<split[i];
          entrada2<<",";
        }
        entrada2<<split[13];
        ofs << entrada2.str() << endl;
        entrada2.str("");
        split.clear();
      }
    }
    else
    {
      ofs << entrada;
    }
  }
  // sufixo(ofs);
  ofs.close();
  return;
}

int main(int argc, char **argv)
{
//+-------------------------------------------------------------------------------+
  // variaveis
  int contador=0;
  std::string entrada;
  std::stringstream entrada2;
  bool uma_vez=false;
  std::string name;
  std::vector<std::string> VectorOut;
   
  // Informar o numero de linhas do arquivo 
  // std::ifstream inFile(argv[1]); 
  std::ifstream inFile(argv[1]); 
  if(!inFile) {
    cout << "Arquivo não foi encontrado.\n";
    return 0;
  }

  tudo(inFile,argv[1],argv[2]);
  inFile.clear();
  inFile.seekg(0);

  cout << "FINALIZADO" << endl;

  inFile.close();
  return 0;
}