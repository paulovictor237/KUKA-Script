//+-------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-------------------------------------------------------------------------------+
// BIBLIOTECAS C++

// COMPILAR
// g++ *.cpp -o executavel -std=c++11 && ./executavel 

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

std::fstream TReceita_src("TReceita.src",std::ofstream::out | std::ofstream::trunc);
std::fstream TReceita_dat("TReceita.dat",std::ofstream::out | std::ofstream::trunc);
std::fstream TMatriz_src("TMatriz.src",std::ofstream::out | std::ofstream::trunc);
std::fstream TMatriz_dat("TMatriz.dat",std::ofstream::out | std::ofstream::trunc);
std::fstream TPallet_src("TPallet.src",std::ofstream::out | std::ofstream::trunc);
std::fstream TPallet_dat("TPallet.dat",std::ofstream::out | std::ofstream::trunc);

void init(void){
  prefixo(TReceita_src,"TReceita",false);
  prefixo(TReceita_dat,"TReceita",true);
  prefixo(TMatriz_src,"TMatriz",false);
  prefixo(TMatriz_dat,"TMatriz",true);
  prefixo(TPallet_src,"TPallet",false);
  prefixo(TPallet_dat,"TPallet",true);
}

void end(void){
  sufixo(TReceita_src,false);
  sufixo(TReceita_dat,true);
  sufixo(TMatriz_src,false);
  sufixo(TMatriz_dat,true);
  sufixo(TPallet_src,false);
  sufixo(TPallet_dat,true);
}

int NumPick=3;
int esteiras=2;
int Camadas=3;

int main(int argc, char **argv)
{
//+-------------------------------------------------------------------------------+
  // variaveis
  std::string name;
   
  // Informar o numero de linhas do arquivo 
  // std::ifstream inFile(argv[1]); 
  std::ifstream inFile("My_Job.src"); 
  if(!inFile) {
    cout << "Arquivo não foi encontrado.\n";
    return 0;
  }
  init();
  std::vector<class Receita> receitas;
  class Receita aux_receita("A");
  receitas.push_back(aux_receita);
  aux_receita.nome = "B";
  receitas.push_back(aux_receita);
  aux_receita.nome = "C";
  receitas.push_back(aux_receita);
  aux_receita.nome = "D";
  receitas.push_back(aux_receita);
  for (auto &outt : receitas)outt.imprime(TReceita_src,esteiras,Camadas,NumPick);
  end();

  // ## Garra
  // cria todos os arquivos de garra

  // ## TMatriz -> cria a matriz dat e src
  // começa procurando os MatrizPontos
  // !encontra o Produto
  // PlacesCamada++;
  // layers++;

  // ## TReceita -> cria o Receita src e dat
  // antes de imprimir (PlacesCamada/layers)

  // ## TPallet -> cria o Pallet src e dat
  // coloca as testeiras e os pallets

  // ## Extras
  // Imprime os valores 
  // ;---------- StrPallet[MaxPallets] ----------
  // CONST INT MaxPallets=2
  // DECL GLOBAL DefPallet StrPallet[2];[MaxPallets]
  // ;---------- StrReceita[MaxReceitas] ----------
  // CONST INT MaxReceitas=21 ; 21
  // CONST INT MaxCamadas=12 ; 8
  // DECL GLOBAL DefStrReceita StrReceita[21];[MaxReceitas]
  // INT  StrReceitaLayer[21,12];[MaxReceitas,MaxCamadas]
  // ;---------- MatrizPontos[MaxMatrizI,MaxMatrizJ,MaxMatrizK] ----------
  // CONST INT MaxMatrizI=2  ;[numero de pallets por receita]
  // CONST INT MaxMatrizJ=21 ;[acompanha o MaxReceitas]
  // CONST INT MaxMatrizK=25 ;[numero Maximo de Pontos]
  // DECL GLOBAL DefMatriz MatrizPontos[2,21,25];[MaxMatrizI,MaxMatrizJ,MaxMatrizK]

  TReceita_dat.close();
  TReceita_src.close();
  TMatriz_dat.close();
  TMatriz_src.close();
  TPallet_dat.close();
  TPallet_src.close();
  inFile.close();
  return 0;
}