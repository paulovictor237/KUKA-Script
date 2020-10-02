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
#include "configdat.h"

void Config::imprime(std::ofstream &config_dat){
  //adicionar numero a mais por seguranca
  MaxCamadas=MaxCamadas + 3;
  MaxReceitas=MaxReceitas + 3;

  //inicia prints
  config_dat<<";FOLD ENUM E DECLARACAO DAS STRUCS\n"<<endl;
  
  config_dat<<";FOLD ENUM Pallet"<<endl; 
  for (int i=0;i<MaxPallets;i++)config_dat<< "CONST INT Pallet_"<<i+1<<"="<<i+1<<endl;
  config_dat<<";ENDFOLD\n"<<endl; 


  int contador=1;
  config_dat<<";FOLD ENUM RECEITA"<<endl; 
  for (auto &outt : ENUM_RECEITA)config_dat<< "CONST INT Prdt_"<<outt<<"="<<(contador++)<<endl;
  config_dat<<";ENDFOLD\n"<<endl; 


  config_dat<<";FOLD STR"<<endl; 
  config_dat<<";---------- StrPallet[MaxPallets] ----------"<<endl;
  config_dat<<"CONST INT MaxPallets="<<MaxPallets<<endl;
  config_dat<<"DECL GLOBAL DefPallet StrPallet["<<MaxPallets<<"];[MaxPallets]"<<endl;
  config_dat<<";---------- StrReceita[MaxReceitas] ----------"<<endl;
  config_dat<<"CONST INT MaxReceitas="<<MaxReceitas<<endl;
  config_dat<<"CONST INT MaxCamadas="<<MaxCamadas<<endl;
  config_dat<<"DECL GLOBAL DefStrReceita StrReceita["<<MaxReceitas<<"];[MaxReceitas]"<<endl;
  config_dat<<"DECL GLOBAL INT StrReceitaLayer["<<MaxReceitas<<","<<MaxCamadas<<"];[MaxReceitas,MaxCamadas]"<<endl;
  config_dat<<";---------- MatrizPontos[MaxMatrizI,MaxMatrizJ,MaxMatrizK] ----------"<<endl;
  config_dat<<"CONST INT MaxMatrizI="<<MaxMatrizI<<";[numero de pallets por receita]"<<endl;
  config_dat<<"CONST INT MaxMatrizJ="<<MaxMatrizJ<<";[acompanha o MaxReceitas]"<<endl;
  config_dat<<"CONST INT MaxMatrizK="<<MaxMatrizK<<";[numero Maximo de Pontos]"<<endl;
  config_dat<<"DECL GLOBAL DefMatriz MatrizPontos["<<MaxMatrizI<<","<<MaxMatrizJ<<","<<MaxMatrizK<<"];[MaxMatrizI,MaxMatrizJ,MaxMatrizK]"<<endl;
  config_dat<<";ENDFOLD\n"<<endl;

  config_dat<<";ENDFOLD\n"<<endl;
}

void Config::cout_print(void){
  cout <<  "# >> Rotina config.dat  <<" << endl;
  cout <<  "\n-----------------------------\n" << endl;
  cout<<"CONST INT MaxPallets="<<MaxPallets<<endl;
  cout<<"StrPallet[MaxPallets]"<<endl;
  cout <<  "\n-----------------------------\n" << endl;
  cout<<"CONST INT MaxReceitas="<<MaxReceitas<<endl;
  cout<<"CONST INT MaxCamadas="<<MaxCamadas<<endl;
  cout<<"StrReceita[MaxReceitas]"<<endl;
  cout<<"StrReceitaLayer[MaxReceitas,MaxCamadas]"<<endl;
  cout <<  "\n-----------------------------\n" << endl;
  cout<<"CONST INT MaxMatrizI="<<MaxMatrizI<<";[numero de pallets por receita]"<<endl;
  cout<<"CONST INT MaxMatrizJ="<<MaxMatrizJ<<";[acompanha o MaxReceitas]"<<endl;
  cout<<"CONST INT MaxMatrizK="<<MaxMatrizK<<";[numero Maximo de Pontos]"<<endl;
  cout<<"MatrizPontos[MaxMatrizI,MaxMatrizJ,MaxMatrizK]"<<endl;
  cout <<  "\n-----------------------------\n" << endl;
}

