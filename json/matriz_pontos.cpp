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

int OffsetPlace(std::ofstream &TMatriz_src,int pallet,int NumPlace,class Receita receita)
{
  TMatriz_src<<";FOLD OffsetPlace " << endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "].";
  TMatriz_src<<"OffsetPlace.X=0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "].";
  TMatriz_src<<"OffsetPlace.Y=0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "].";
  TMatriz_src<<"OffsetPlace.Z=0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "].";
  TMatriz_src<<"OffsetPlace.A=0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "].";
  TMatriz_src<<"OffsetPlace.B=0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "].";
  TMatriz_src<<"OffsetPlace.C=0"<< endl;
  TMatriz_src<<";ENDFOLD" << endl;
  return 0;
}

void separa_layers_src(std::ofstream &TMatriz_src,int layer,int inicial,int final)
{
  TMatriz_src << ";ENDFOLD"<< endl;
  TMatriz_src << ";FOLD LAYER "<<layer<<": PLACE "<<inicial << " ate " << final << endl;
}

void matriz_pontos(std::ofstream &TMatriz_src,std::ofstream &TMatriz_dat,int pallet,int NumPlace,class Receita receita,class Pose pose)
{
  //+-------------------------- SRC --------------------------+<< 

  //TMatriz_src << ";FOLD Pallet " <<pallet<<" - Produto "<< receita.nome << endl;
  
  TMatriz_src<<";FOLD PLACE " << NumPlace << endl;
    TMatriz_src<<";FOLD PROPRIEDADES " << endl;
      //TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "]." << entrada << endl;
      
      TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "].";
      TMatriz_src<<"XApp1Place="<<pallet<<"_"<<receita.nome<<"_"<<NumPlace<<"_"<<"App1"<<endl;
      
      TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "].";
      TMatriz_src<<"XApp2Place="<<pallet<<"_"<<receita.nome<<"_"<<NumPlace<<"_"<<"App2"<<endl;
      
      TMatriz_src<<"MatrizPontos[Pallet_"<<pallet<<",Prdt_"<<receita.nome << "," << NumPlace << "].";
      TMatriz_src<<"XPlace="<<pallet<<"_"<<receita.nome<<"_"<<NumPlace<<"_"<<"Place"<<endl;
      OffsetPlace(TMatriz_src,pallet,NumPlace,receita);
      TMatriz_src<< endl;
    TMatriz_src << ";ENDFOLD" << endl;
  TMatriz_src << ";ENDFOLD\n" << endl;
  
  //TMatriz_src<<";ENDFOLD" << endl;

  //+-------------------------- DAT --------------------------+<< 

  //TMatriz_dat << ";FOLD Pallet " <<pallet<<" - Produto "<< receita.nome << endl;
  
  TMatriz_dat<<";FOLD PLACE " << NumPlace << endl;
  TMatriz_dat<<"DECL E6POS "<<pallet<<"_"<<receita.nome<<"_"<<NumPlace<<"_"<<"App1"<<"="<<pose.kuka()<<endl;
  TMatriz_dat<<"DECL E6POS "<<pallet<<"_"<<receita.nome<<"_"<<NumPlace<<"_"<<"App2"<<"="<<pose.kuka()<<endl;
  TMatriz_dat<<"DECL E6POS "<<pallet<<"_"<<receita.nome<<"_"<<NumPlace<<"_"<<"Place"<<"="<<pose.kuka()<<endl;
  TMatriz_dat<<";ENDFOLD\n" << endl; 

  return;
}