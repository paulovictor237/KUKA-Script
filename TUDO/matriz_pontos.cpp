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
# include "matriz_pontos.h"

int matriz_pontos_str(std::ifstream &My_Job_src,std::fstream &TMatriz_src,std::string pallet,std::string produto)
{
  // variaveis  
  int contador=0;
  int NumLayers=1;

  std::string entrada="";

  TMatriz_src << ";FOLD " <<pallet<<" "<< produto << endl;

  while(entrada.find("END")!=0){
    getline(My_Job_src,entrada);
    if (!My_Job_src.good())break;

    if(entrada.find("NumLayers") !=std::string::npos)
    {
      NumLayers=std::stoi(split_string(entrada,"[^0-9]+",1));
      // cout << "NumLayers: "<< NumLayers << endl;
    }

    if(entrada.find("PontoPlace") !=std::string::npos)
    {
      contador++;
      getline(My_Job_src,entrada);
      getline(My_Job_src,entrada);
      while(entrada.find("FOLD")==std::string::npos){
        TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "]." << entrada << endl;
        getline(My_Job_src,entrada);
        if (!My_Job_src.good())break;
      }
      TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
      TMatriz_src<<"App1Place = "<<pallet<<"_"<<produto<<"_"<<contador<<"_"<<"App1"<<endl;
      TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
      TMatriz_src<<"App2Place = "<<pallet<<"_"<<produto<<"_"<<contador<<"_"<<"App2"<<endl;
      TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
      TMatriz_src<<"Place = "<<pallet<<"_"<<produto<<"_"<<contador<<"_"<<"Place"<<endl;
      TMatriz_src<< endl;
      // ofs << "MatrizPontos[1," << contador << "]." << IndexacaoVH << endl;
    }
    // cout << entrada << endl;
  }
  TMatriz_src << ";ENDFOLD \n" << endl;
  // // cout << "Numero de pontos: " << contador << endl;

  return contador/NumLayers;
}

int matriz_pontos_dat(std::ifstream &My_Job_dat,std::fstream &TMatriz_dat,std::string pallet,std::string produto,std::string produto_cmplt)
{
  My_Job_dat.clear();
  My_Job_dat.seekg(0);
  // prefixo(ofs,name);
  std::string entrada;
  std::string posicao;
  int tipo_place=1;
  int NumPontos=0;
  int contador=1;

  TMatriz_dat << ";FOLD " <<pallet<<" "<< produto << endl;
  while (!My_Job_dat.eof())
  {
    getline(My_Job_dat,entrada);
    if (!My_Job_dat.good())break;
    if(entrada.find(produto_cmplt) !=std::string::npos){
      contador=1;
      while(entrada.find("ENDDAT") ==std::string::npos)
      {
        getline(My_Job_dat,entrada);
        if(entrada.find("E6POS") !=std::string::npos)
        {
          posicao=split_string(entrada,"[=]+",1);
          TMatriz_dat<<"E6POS ";
          TMatriz_dat<<pallet<<"_"<<produto<<"_"<<contador<<"_";
          switch(tipo_place) {
            case 1:
              TMatriz_dat<<"App1"; 
              tipo_place++;
              break;
            case 2:
              TMatriz_dat<<"App2";
              tipo_place++;
              break;
            case 3:
              TMatriz_dat<<"Place";
              tipo_place=1;
              contador++;
              NumPontos++;
              break;
          }
          TMatriz_dat<<" = "<<posicao<<(tipo_place==1?"\n":"")<<endl; 
        }
      }
    }
  }
  TMatriz_dat << ";ENDFOLD \n" << endl;
  return NumPontos;
}