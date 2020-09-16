#include <iostream>
#include <fstream>
#include <iomanip>      // std::setprecision & std::setw
#include <algorithm>    // std::count
#include <math.h>       // M_PI
#include <sstream>
#include <string>
#include <vector>
#include <regex>

#include "pevepallet.h"

using namespace std;

std::string split_string(std::string tokenString,string delim,int saida){
  vector<string> tokens;
  std::regex delimiters {delim};
  sregex_token_iterator tokens_begin { tokenString.begin(), tokenString.end(), delimiters, -1 };
  auto tokens_end = sregex_token_iterator {};
  for (auto token_it = tokens_begin; token_it != tokens_end; token_it++)tokens.push_back(*token_it);
  return tokens[saida];
}

void prefixo(std::fstream &ofs,std::string name,bool dat){
  ofs << (dat?"DEFDAT ":"DEF ") << name << (dat?"":"()") << endl;
  return;
}
void sufixo(std::fstream &ofs,bool dat){
  ofs << (dat?"ENDDAT":"END ");
  return;
}

Receita::Receita(std::string nome){
this->nome=nome;
}
void Receita::imprime(std::fstream &ofs,int esteiras,int Camadas,int NumPick){
std::stringstream aux;
ofs<<";FOLD Produto "<< nome << endl;
ofs<<"  StrReceita[Produto_"<< nome << "].OffsetProduto.X = 0"<< endl;
ofs<<"  StrReceita[Produto_"<< nome << "].OffsetProduto.Y = 0"<< endl;
ofs<<"  StrReceita[Produto_"<< nome << "].OffsetProduto.Z = 0"<< endl;
ofs<<"  StrReceita[Produto_"<< nome << "].OffsetProduto.A = 0"<< endl;
ofs<<"  StrReceita[Produto_"<< nome << "].OffsetProduto.B = 0"<< endl;
ofs<<"  StrReceita[Produto_"<< nome << "].OffsetProduto.C = 0"<< endl;
for (int i=0;i<esteiras;i++){
    for (int j=0;j<NumPick;j++){
    aux << "_E_";
    aux << i+1;
    aux << "_P_";
    aux << j+1;
    ofs<<"  StrReceita[Produto_"<< nome << "].Pick"<<aux.str()<<" = Pick_"<<nome<<aux.str()<< endl;
    aux.str("");
    }
}
ofs<<"  StrReceita[Produto_"<< nome << "].PlacesCamada = " << PlacesCamada << endl;
ofs<<"  StrReceita[Produto_"<< nome << "].AlturaCaixa = 0" << endl;
ofs<<"  StrReceita[Produto_"<< nome << "].Camadas = "<< Camadas << endl;
for (int i=0;i<Camadas;i++){
    ofs<<"  StrReceitaLayer[Produto_"<< nome <<","<<i+1<<"] = 1" << endl;
}
ofs<<";ENDFOLD" << endl;
return;
}