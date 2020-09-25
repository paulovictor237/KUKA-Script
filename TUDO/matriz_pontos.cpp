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

int contador_places(std::ifstream &My_Job_src,int &NumLayers)
{
  std::string entrada="";
  int contador=0;
  bool ERROR_NumLayers=true;
  while(entrada.find("END")!=0)
  {
    getline(My_Job_src,entrada);
    if (!My_Job_src.good())break;

    if(entrada.find("NumLayers") !=std::string::npos && ERROR_NumLayers==true)
    {
      ERROR_NumLayers=false;
      NumLayers=std::stoi(split_string(entrada,"[^0-9]+",1));
      // cout <<"1@@@@@@@@@@NumLayers: "<<NumLayers << endl;
    }

    if(entrada.find(";FOLD ; ## PontoPlace ##") !=std::string::npos)
    {
      contador++;
      getline(My_Job_src,entrada);
    }
  }
  return contador;
}



int matriz_pontos_str(std::ifstream &My_Job_src,std::ofstream &TMatriz_src,std::string pallet,std::string produto,int &NumLayers,int &AlturaCaixa,int &Camadas)
{
  //erros
  bool ERROR_NumLayers=true;
  bool ERROR_AlturaCaixa=true;
  bool ERROR_Camadas=true;
  bool layer1 = false;
  bool layer2;
  int i=0;
  //outras
  //int NumLayers = 2;
  NumLayers=1;
  AlturaCaixa = 0;
  Camadas = 12;
  // variaveis  
  int contador=0;
  std::string entrada="";

  TMatriz_src << ";FOLD Pallet " <<pallet[1]<<" - Produto "<< produto << endl;
  cout << "Pallet:  " << pallet << endl;
  cout << "Produto: " << produto << endl;

  // contador de places e numero de Layers
  std::streampos  length = My_Job_src.tellg();
  int FinalContador =  contador_places(My_Job_src,NumLayers);
  My_Job_src.seekg (length);

  //FOLD Layer
  // TMatriz_src << ";FOLD [ Layer INFO ]"<< endl;
  // for (int i=0;i<NumLayers;i++){
  //   TMatriz_src << ";LAYER "<<i+1<<": "<<FinalContador/NumLayers*i+1 << " ate " << FinalContador/NumLayers*(i+1) << endl;
  // }
  // TMatriz_src << ";ENDFOLD" << endl;
  // TMatriz_src << endl;
  //FOLD Layer
  i=0;
  TMatriz_src << ";FOLD LAYER "<<i+1<<": PLACE "<<FinalContador/NumLayers*i+1 << " ate " << FinalContador/NumLayers*(i+1) << endl;
  i++;
  while(entrada.find("END")!=0){
    getline(My_Job_src,entrada);
    if (!My_Job_src.good())break;

    if(entrada.find("NumLayers") !=std::string::npos && ERROR_NumLayers==true)
    {
      ERROR_NumLayers=false;
      NumLayers=std::stoi(split_string(entrada,"[^0-9]+",1));
      // cout <<"NumLayers: "<<NumLayers << endl;
    }
    if(entrada.find("AlturaCaixa") !=std::string::npos && ERROR_AlturaCaixa==true)
    {
      ERROR_AlturaCaixa=false;
      AlturaCaixa=std::stoi(split_string(entrada,"[^0-9]+",1));
      // cout <<"AlturaCaixa: "<<AlturaCaixa << endl;
    }
    if(entrada.find("Camadas") !=std::string::npos && ERROR_Camadas==true)
    {
      ERROR_Camadas=false;
      Camadas=std::stoi(split_string(entrada,"[^0-9]+",1));
      // cout <<"Camadas: "<<Camadas << endl;
    }

    if(entrada.find(";FOLD ; ## PontoPlace ##") !=std::string::npos)
    {
      contador++;
      if (contador==(FinalContador/NumLayers*i+1)&& NumLayers>1){
        TMatriz_src << ";ENDFOLD"<< endl;
        TMatriz_src << ";FOLD LAYER "<<i+1<<": PLACE "<<FinalContador/NumLayers*i+1 << " ate " << FinalContador/NumLayers*(i+1) << endl;
        i++;
      }
      TMatriz_src<<";FOLD PLACE " << contador << endl;
      getline(My_Job_src,entrada);
      getline(My_Job_src,entrada);
      //cabesalho
      TMatriz_src<<";FOLD PROPRIEDADES " << endl;
      while(entrada.find("FOLD")==std::string::npos){
        TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "]." << entrada << endl;
        getline(My_Job_src,entrada);
        if (!My_Job_src.good())break;
      }
      TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
      TMatriz_src<<"XApp1Place = "<<pallet<<"_"<<produto<<"_"<<contador<<"_"<<"App1"<<endl;
      TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
      TMatriz_src<<"XApp2Place = "<<pallet<<"_"<<produto<<"_"<<contador<<"_"<<"App2"<<endl;
      TMatriz_src<<"MatrizPontos[Pallet_"<<pallet[1]<<",Prdt_"<<produto << "," << contador << "].";
      TMatriz_src<<"XPlace = "<<pallet<<"_"<<produto<<"_"<<contador<<"_"<<"Place"<<endl;
      TMatriz_src<<";ENDFOLD" << endl;

      OffsetPlace(TMatriz_src,pallet,produto,contador);

      TMatriz_src<<";ENDFOLD" << endl;
      TMatriz_src<< endl;
      // ofs << "MatrizPontos[1," << contador << "]." << IndexacaoVH << endl;
    }
    // cout << entrada << endl;
  }
  TMatriz_src << ";ENDFOLD" << endl;
  TMatriz_src << ";ENDFOLD\n" << endl;

  if(ERROR_AlturaCaixa){
    cout << "<span style=\"color:red\">**ERROR: " << "AlturaCaixa" << "**</span>"<<endl;
  }else{
    cout << "AlturaCaixa: " << AlturaCaixa<< endl;
  }
  if(ERROR_Camadas){
    cout << "<span style=\"color:red\">**ERROR: " << "Camadas" << "**</span>"<<endl;
  }else{
    cout << "Camadas: " << Camadas<< endl;
  }
  if(ERROR_NumLayers){
    cout << "<span style=\"color:red\">**ERROR: " << "NumLayers" << "**</span>"<<endl;
  }else{
    cout <<"NumLayers: "<<NumLayers << endl;
    // cout << "NumPlaces/NumLayers: " << contador/NumLayers<< endl;
  }
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
  if(ConfereDOUBLE!=ConfereINT) cout << "<span style=\"color:red\">**ERROR: " << "Pontos incompletos" << "**</span>"<<endl;
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