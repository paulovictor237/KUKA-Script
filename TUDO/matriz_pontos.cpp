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

int OffsetPlace(std::ofstream &TMatriz_src,std::string pallet,std::string produto,int contador)
{
  TMatriz_src<<";FOLD OffsetPlace " << endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
  TMatriz_src<<"OffsetPlace.X = 0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
  TMatriz_src<<"OffsetPlace.Y = 0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
  TMatriz_src<<"OffsetPlace.Z = 0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
  TMatriz_src<<"OffsetPlace.A = 0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
  TMatriz_src<<"OffsetPlace.B = 0"<< endl;
  TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
  TMatriz_src<<"OffsetPlace.C = 0"<< endl;
  TMatriz_src<<";ENDFOLD" << endl;
  return 0;
}



int matriz_pontos_str(std::ifstream &My_Job_src,std::ofstream &TMatriz_src,std::string pallet,std::string produto,int &NumLayers)
{
  //erros
  bool ERROR_NumLayers=true;
  // variaveis  
  int contador=0;
  NumLayers=1;

  std::string entrada="";

  TMatriz_src << ";FOLD Pallet " <<pallet[1]<<" - Produto "<< produto << endl;
  cout << "Pallet:  " << pallet << endl;
  cout << "Produto: " << produto << endl;

  while(entrada.find("END")!=0){
    getline(My_Job_src,entrada);
    if (!My_Job_src.good())break;

    if(entrada.find("NumLayers") !=std::string::npos && ERROR_NumLayers==true)
    {
      ERROR_NumLayers=false;
      NumLayers=std::stoi(split_string(entrada,"[^0-9]+",1));
      cout <<"NumLayers: "<<NumLayers << endl;
      
    }

    if(entrada.find("PontoPlace") !=std::string::npos)
    {
      contador++;
      TMatriz_src<<";FOLD PLACE " << contador << endl;
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
      OffsetPlace(TMatriz_src,pallet,produto,contador);
      TMatriz_src<<";ENDFOLD" << endl;
      TMatriz_src<< endl;
      // ofs << "MatrizPontos[1," << contador << "]." << IndexacaoVH << endl;
    }
    // cout << entrada << endl;
  }
  TMatriz_src << ";ENDFOLD" << endl;

  //FOLD Layer
  TMatriz_src << ";FOLD Pallet " <<pallet[1]<<" - Produto "<< produto  << " [ Layer INFO ]"<< endl;
  for (int i=0;i<NumLayers;i++){
    TMatriz_src << ";LAYER "<<i+1<<": "<<contador/NumLayers*i+1 << " ate " << contador/NumLayers*(i+1) << endl;
  }
  TMatriz_src << ";ENDFOLD" << endl;
  TMatriz_src << endl;
  //FOLD Layer

  if(ERROR_NumLayers) cout << "\033[1;31m" <<  "ERROR: " << "NumLayers" << "\033[0m"<<endl;
  cout << "NumPlaces SRC: " << contador<< endl;
  return contador;
}

int matriz_pontos_dat(std::ifstream &My_Job_dat,std::ofstream &TMatriz_dat,std::string pallet,std::string produto,std::string produto_cmplt)
{
  My_Job_dat.clear();
  My_Job_dat.seekg(0);
  // prefixo(ofs,name);
  std::string entrada;
  std::string posicao;
  int tipo_place=1;
  int NumPontos=0;
  int contador=1;

  int Confere=0;
  int ConfereINT;
  double ConfereDOUBLE;
  TMatriz_dat << ";FOLD Pallet " <<pallet[1]<<" - Produto "<< produto << endl;

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
          Confere++;
          if(tipo_place==1){
            TMatriz_dat<<";FOLD PLACE " << contador << endl;
          }
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
          TMatriz_dat<<" = "<<posicao<<endl;
          if(tipo_place==1){
            TMatriz_dat<<";ENDFOLD\n" << endl; 
          }
        }
      }
    }
  }
  ConfereINT = Confere/3;
  ConfereDOUBLE = Confere*1.0/3;//(double)10/(double)3;
  if(ConfereDOUBLE!=ConfereINT) cout << "\033[1;31m" <<  "ERROR: " << "Pontos incompletos" << "\033[0m"<<endl;
  TMatriz_dat << ";ENDFOLD" << endl;
  TMatriz_dat << endl;
  
  // //FOLD Layer
  // TMatriz_dat << ";FOLD Pallet " <<pallet[1]<<" - Produto "<< produto  << " [ Layer INFO ]"<< endl;
  // for (int i=0;i<NumLayers;i++){
  //   TMatriz_dat << ";LAYER "<<i+1<<": "<<contador/NumLayers*i+1 << " ate " << contador/NumLayers*(i+1) << endl;
  // }
  // TMatriz_dat << ";ENDFOLD" << endl;
  // TMatriz_dat << endl;
  // //FOLD Layer
  
  cout << "NumPlaces DAT: " << NumPontos<< endl;
  return NumPontos;
}