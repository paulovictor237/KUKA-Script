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

void ERROR_messege(std::string mensagem)
{
  cout << "<span style=\"color:red\">**ERROR: " << mensagem << "**</span>"<<endl;
}

std::string split_string(std::string tokenString,string delim,int saida)
{
  vector<string> tokens;
  std::regex delimiters {delim};
  sregex_token_iterator tokens_begin { tokenString.begin(), tokenString.end(), delimiters, -1 };
  auto tokens_end=sregex_token_iterator {};
  for (auto token_it=tokens_begin; token_it != tokens_end; token_it++)tokens.push_back(*token_it);
  return tokens[saida];
}

vector<string> split_string(std::string tokenString,std::string delim)
{
  vector<string> tokens;
  std::regex delimiters {delim};
  sregex_token_iterator tokens_begin { tokenString.begin(), tokenString.end(), delimiters, -1 };
  auto tokens_end=sregex_token_iterator {};
  for (auto token_it=tokens_begin; token_it != tokens_end; token_it++)tokens.push_back(*token_it);
  return tokens;
}

void imprime_vetor(vector<string> tokens)
{
  int i=0;
  for (const string& token: tokens)
{
    cout << "[" << i << "]"<< "-> " << token << "\n";
    i++;
  }
}


double valor(std::string entrada)
{
  return stod(split_string(entrada,"[^0-9]+",1));
}

void init_files(std::ofstream &src,std::ofstream &dat,std::string name)
{
  src << "DEF " << name <<"()"<< endl;
  dat << "DEFDAT " << name << endl;
  return;
}

void end_files(std::ofstream &src,std::ofstream &dat)
{
  src << "END";
  dat << "ENDDAT";
  return;
}


std::string Pose::kuka(void)
{
  std::stringstream aux;
  aux << "{X " << X << ",Y " << Y << ",Z " << Z << ",A " << A << ",B 0,C 180,S 2,T 2}";
  return aux.str();
}

std::ostream &operator<<(std::ostream &os, Pose const &m)
{
  os << "{ X " << m.X;
  os << ", Y " << m.Y;
  os << ", Z " << m.Z;
  os << ", A " << m.A;
  os << ", B " << m.B;
  os << " }";
  return os;
}

std::ostream &operator<<(std::ostream &os, Objeto const &m)
{
  // os << "width : "  << m.width << endl;
  // os << "length : " << m.length << endl;
  // os << "height : " << m.height << endl;
  os << "Dimensoes : "  << m.width << " x " << m.length << " x " << m.height << endl;
  os << "Peso : " << m.weight << endl;

  return os;
}

void Receita::imprime(std::ofstream &ofs)
{
  std::stringstream aux;
  ofs<<";FOLD Produto "    << nome << endl;

  ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.X=0"<< endl;
  ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.Y=0"<< endl;
  ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.Z=0"<< endl;
  ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.A=0"<< endl;
  ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.B=0"<< endl;
  ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.C=0"<< endl;

  ofs<<"  StrReceita[Prdt_"<< nome << "].AlturaCaixa="<<AlturaCaixa << endl;
  ofs<<"  StrReceita[Prdt_"<< nome << "].PlacesCamada=" << PlacesCamada << endl;
  ofs<<"  StrReceita[Prdt_"<< nome << "].Layers="<< Layers << endl;
  ofs<<"  StrReceita[Prdt_"<< nome << "].Camadas="<< Camadas << endl;

  int i=1;
  for (auto &outt : LayersVector)
  {
    ofs<<"  StrReceitaLayer[Prdt_"<< nome <<","<<i<<"]="<< outt << endl;
    i++;
  }
  ofs<<";ENDFOLD\n" << endl;
  
  return;
}
bool buscar_chave(std::string entrada,std::string chave)
{
  return entrada.find(chave) !=std::string::npos;
}


