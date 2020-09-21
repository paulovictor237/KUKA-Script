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
using namespace std;

#include "matriz_pontos.h"
#include "receita.h"
#include "comum.h"
#include "garra.h"

std::fstream TReceita_src("out/TReceita.src",std::ofstream::out | std::ofstream::trunc);
std::fstream TReceita_dat("out/TReceita.dat",std::ofstream::out | std::ofstream::trunc);
std::fstream TMatriz_src ("out/TMatriz.src",std::ofstream::out | std::ofstream::trunc);
std::fstream TMatriz_dat ("out/TMatriz.dat",std::ofstream::out | std::ofstream::trunc);
std::fstream TPallet_src ("out/TPallet.src",std::ofstream::out | std::ofstream::trunc);
std::fstream TPallet_dat ("out/TPallet.dat",std::ofstream::out | std::ofstream::trunc);

void init_all(void){
  prefixo(TReceita_src,"TReceita",false);
  prefixo(TReceita_dat,"TReceita",true);
  prefixo(TMatriz_src,"TMatriz",false);
  prefixo(TMatriz_dat,"TMatriz",true);
  prefixo(TPallet_src,"TPallet",false);
  prefixo(TPallet_dat,"TPallet",true);
}

void end_all(void){
  sufixo(TReceita_src,false);
  sufixo(TReceita_dat,true);
  sufixo(TMatriz_src,false);
  sufixo(TMatriz_dat,true);
  sufixo(TPallet_src,false);
  sufixo(TPallet_dat,true);
}

int Camadas=8;

int main(int argc, char **argv)
{
//+-------------------------------------------------------------------------------+
  // variaveis
  std::vector<class Receita> receitas;
  class Receita aux_receita("A");
  std::string pallet;
  std::string produto;
  std::string entrada;
   
  // Informar o numero de linhas do arquivo 
  // std::ifstream My_Job_src(argv[1]); 
  std::ifstream My_Job_src("My_Job/My_Job.src"); 
  std::ifstream My_Job_dat("My_Job/My_Job.dat"); 
  if(!My_Job_src) {
    cout << "Arquivo não foi encontrado.\n";
    return 0;
  }
  init_all();
  // ## Garra
  // cria todos os out de garra
  garra_exe(My_Job_src);
  My_Job_src.clear();
  My_Job_src.seekg(0);
  // ## TMatriz -> cria a matriz dat e src
  // começa procurando os MatrizPontos
  // !encontra o Produto
  // PlacesCamada++;
  // layers++;

  // ## TReceita -> cria o Receita src e dat
  // antes de imprimir (PlacesCamada/layers)
  
  while (!My_Job_src.eof())
  {
    getline(My_Job_src,entrada);
    if (!My_Job_src.good()) {
      // cout << "ponteiro nulo" << endl;
      break;
    }
    if(entrada.find("DEF Mtrz") !=std::string::npos)
    {
      pallet=split_string(entrada,"[_()]+",1);//pallet
      produto=split_string(entrada,"[_()]+",2);//produto
      entrada=split_string(entrada,"[ ()]+",1);//produto
      cout << entrada << endl;
      aux_receita.nome = produto;
      aux_receita.PlacesCamada=matriz_pontos_str(My_Job_src,TMatriz_src,pallet,produto);
      matriz_pontos_dat(My_Job_dat,TMatriz_dat,pallet,produto,entrada);
      receitas.push_back(aux_receita);

    }
  }
  for (auto &outt : receitas)outt.imprime(TReceita_src,Camadas);
 
  // ## TPallet -> cria o receita src e dat
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

  end_all();
  TReceita_dat.close();
  TReceita_src.close();
  TMatriz_dat.close();
  TMatriz_src.close();
  TPallet_dat.close();
  TPallet_src.close();
  My_Job_src.close();
  My_Job_dat.close();
  return 0;
}