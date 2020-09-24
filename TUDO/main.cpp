//+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+
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
#include "pallet.h"
#include "receita.h"
#include "configdat.h"
#include "receita.h"
#include "comum.h"
#include "garra.h"

std::ofstream TReceita_src("out/TReceita.src",std::ofstream::out);
std::ofstream TReceita_dat("out/TReceita.dat",std::ofstream::out);
std::ofstream TMatriz_src ("out/TMatriz.src", std::ofstream::out);
std::ofstream TMatriz_dat ("out/TMatriz.dat", std::ofstream::out);
std::ofstream TPallet_src ("out/TPallet.src", std::ofstream::out);
std::ofstream TPallet_dat ("out/TPallet.dat", std::ofstream::out);

std::ofstream Aux1TMatriz_src ("auxiliar/aux1TMatriz.src", std::ofstream::out);
std::ofstream Aux1TMatriz_dat ("auxiliar/aux1TMatriz.dat", std::ofstream::out);
std::ofstream Aux2TMatriz_src ("auxiliar/aux2TMatriz.src", std::ofstream::out);
std::ofstream Aux2TMatriz_dat ("auxiliar/aux2TMatriz.dat", std::ofstream::out);

std::ofstream config_dat("out/config.dat", std::ofstream::out);

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

int MaxPallets=2;
int MaxCamadas=12;

int main(int argc, char **argv)
{
//+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+
  system("clear");
  // system("cls");
  cout << "\033[1;44m" <<  "╔═══════════════════════════════════════════════════════╗" << "\033[0m"<<endl;
  cout << "\033[1;44m" <<  "║                   PROGRAMA INICIADO                   ║" << "\033[0m"<<endl;
  cout << "\033[1;44m" <<  "╚═══════════════════════════════════════════════════════╝" << "\033[0m"<<endl;
  
  cout << "Valores de inicializacao" << endl; 
  if(argc==3){
    MaxPallets=atoi(argv[1]);
    MaxCamadas=atoi(argv[2]);
  }
  cout << "MaxPallets = " << MaxPallets << endl;
  cout << "MaxCamadas = " << MaxCamadas << endl;
  
  // variaveis
  int MaxMatrizK;
  int PlacesCamada;
  int contador_src;
  int contador_dat;
  int NumLayers;
  std::vector<class Receita> receitas;
  class Receita aux_receita("A");
  class Config config;
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
  cout <<  "+--------------- Rotina Receitas ---------------+" << endl;
  cout << "=========================" << endl;
  while (!My_Job_src.eof())
  {
    getline(My_Job_src,entrada);
    if (!My_Job_src.good()) {
      // cout << "ponteiro nulo" << endl;
      break;
    }
    if(entrada.find("DEF Mtrz") !=std::string::npos)
    {
      cout << entrada << endl;
      pallet=split_string(entrada,"[_()]+",1);//pallet
      produto=split_string(entrada,"[_()]+",2);//produto
      entrada=split_string(entrada,"[ ()]+",1);//produto
      if(pallet[1]=='1')
      {
        contador_src =matriz_pontos_str(My_Job_src,Aux1TMatriz_src,pallet,produto,NumLayers);
        contador_dat =matriz_pontos_dat(My_Job_dat,Aux1TMatriz_dat,pallet,produto,entrada);
      }
      else
      {
        contador_src =matriz_pontos_str(My_Job_src,Aux2TMatriz_src,pallet,produto,NumLayers);
        contador_dat =matriz_pontos_dat(My_Job_dat,Aux2TMatriz_dat,pallet,produto,entrada);
      }
      PlacesCamada = contador_dat/NumLayers;
      MaxMatrizK = contador_dat;
      cout << "NumPlaces/NumLayers: " << PlacesCamada<< endl;
      if(contador_src!=contador_dat) cout << "\033[1;31m" <<  "ERROR: " << "NumPlaces SRC != NumPlaces DAT" << "\033[0m"<<endl;
      config.MaxMatrizK=MaxMatrizK>config.MaxMatrizK?MaxMatrizK:config.MaxMatrizK;
      if(std::find(config.ENUM_RECEITA.begin(), config.ENUM_RECEITA.end(),produto) == config.ENUM_RECEITA.end())
      {
        // ## TPallet -> cria o receita src e dat
        // coloca as testeiras e os pallets
        config.ENUM_RECEITA.push_back(produto);
        aux_receita.nome = produto;
        aux_receita.PlacesCamada=PlacesCamada;
        receitas.push_back(aux_receita);
        config.MaxReceitas++;
        config.MaxMatrizJ++;
      }
      cout << "=========================" << endl; 
    }
  }
  //SEPARA OS PALLETS NA MATRIZ
  Aux1TMatriz_src.close();
  Aux1TMatriz_dat.close();
  Aux2TMatriz_src.close();
  Aux2TMatriz_dat.close();
  copy_file(TMatriz_src,"auxiliar/aux1TMatriz.src","auxiliar/aux2TMatriz.src");
  copy_file(TMatriz_dat,"auxiliar/aux1TMatriz.dat","auxiliar/aux2TMatriz.dat");

  pallet_src(My_Job_src,TPallet_src,MaxPallets);
  pick(My_Job_dat,TReceita_dat);
  config.MaxCamadas=MaxCamadas;
  config.MaxPallets=MaxPallets;
  config.MaxMatrizI=MaxPallets;
  config.imprime(config_dat);
  config.cout_print();
  for (auto &outt : receitas)outt.imprime(TReceita_src,MaxCamadas);

  end_all();
  config_dat.close();
  TReceita_dat.close();
  TReceita_src.close();
  TMatriz_dat.close();
  TMatriz_src.close();
  TPallet_dat.close();
  TPallet_src.close();
  My_Job_src.close();
  My_Job_dat.close();
  
  cout << "\033[1;44m" <<  "╔═══════════════════════════════════════════════════════╗" << "\033[0m"<<endl;
  cout << "\033[1;44m" <<  "║                          FIM                          ║" << "\033[0m"<<endl;
  cout << "\033[1;44m" <<  "╚═══════════════════════════════════════════════════════╝" << "\033[0m"<<endl;

  return 0;
}