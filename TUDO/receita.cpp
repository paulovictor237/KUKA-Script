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

int pick(std::ifstream &My_Job_dat,std::fstream &TReceita_dat)
{
  My_Job_dat.clear();
  My_Job_dat.seekg(0);
  // prefixo(ofs,name);
  std::string entrada;
  std::string posicao;
  std::string PickName;
  int tipo_place=1;
  int NumPontos=0;
  int contador=1;

  TReceita_dat << ";FOLD PICK" << endl;
  while (!My_Job_dat.eof())
  {
    getline(My_Job_dat,entrada);
    if (!My_Job_dat.good())break;
    
    if(entrada.find("Data for Pick") !=std::string::npos){
      PickName=split_string(entrada,"[ |\r\n|\r|\n]",3);
      TReceita_dat<<";"<<PickName<<endl;
      while(entrada.find("ENDDAT") ==std::string::npos)
      {
        getline(My_Job_dat,entrada);
        if(entrada.find("E6POS") !=std::string::npos && entrada.find(PickName) !=std::string::npos)
        {
          // cout << entrada<<endl;
          posicao=split_string(entrada,"[=]+",1);
          TReceita_dat<<"E6POS "<<PickName<<" = "<<posicao<<endl;
        }
      }
      TReceita_dat<<endl;
    }
  }
  TReceita_dat << ";ENDFOLD \n" << endl;
  return NumPontos;
}