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
#include "receita.h"


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
void Receita::imprime(std::fstream &ofs,int Camadas){
std::stringstream aux;
ofs<<";FOLD Produto "<< nome << endl;
ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.X = 0"<< endl;
ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.Y = 0"<< endl;
ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.Z = 0"<< endl;
ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.A = 0"<< endl;
ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.B = 0"<< endl;
ofs<<"  StrReceita[Prdt_"<< nome << "].OffsetProduto.C = 0"<< endl;

ofs<<"  StrReceita[Prdt_"<< nome << "].AlturaCaixa = 0" << endl;
ofs<<"  StrReceita[Prdt_"<< nome << "].PlacesCamada = " << PlacesCamada << endl;
ofs<<"  StrReceita[Prdt_"<< nome << "].Camadas = "<< Camadas << endl;
for (int i=0;i<Camadas;i++){
    ofs<<"  StrReceitaLayer[Prdt_"<< nome <<","<<i+1<<"] = 1" << endl;
}
ofs<<";ENDFOLD" << endl;
return;
}

int pick(std::ifstream &My_Job_src,std::fstream &TReceita_dat,std::string produto)
{
  My_Job_src.clear();
  My_Job_src.seekg(0);
  // variaveis
  int contador=0;
  std::string entrada;
  std::string Prdt_pick;

  while (!My_Job_src.eof())
  {
    getline(My_Job_src,entrada);
    if (!My_Job_src.good())break;
    if(entrada.find("DEF Pick") !=std::string::npos && entrada.find(produto) !=std::string::npos)
    {
      getline(My_Job_src,entrada);
      Prdt_pick=split_string(entrada,"[_()]+",1);
      while(entrada.find("END")!=0)
      {
        getline(My_Job_src,entrada);
        if(My_Job_src.eof())break;
        if(entrada.find("$OUT") !=std::string::npos)
        {

        }
      }
    }
  }

  return 0;
}