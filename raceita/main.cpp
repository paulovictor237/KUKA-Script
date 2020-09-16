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

using namespace std;

void preenche(string entrada, string &IndexacaoVH, string &NumCaixas, string &ConfGarraPick, string &PickOp, string &FechaGarraOp, string &AbreGarraOp, string &SkipGoHome, string &SkipSobeRelativo, string &PlacePos){
  if(entrada.find("IndexacaoVH") !=std::string::npos){
    IndexacaoVH = entrada;
  }
  else if(entrada.find("NumCaixas") !=std::string::npos){
    NumCaixas = entrada;
  }
  else if(entrada.find("ConfGarraPick") !=std::string::npos){
    ConfGarraPick = entrada;
  }
  else if(entrada.find("PickOp") !=std::string::npos){
    PickOp = entrada;
  }
  else if(entrada.find("FechaGarraOp") !=std::string::npos){
    FechaGarraOp = entrada;
  }
  else if(entrada.find("AbreGarraOp") !=std::string::npos){
    AbreGarraOp = entrada;
  }
  else if(entrada.find("SkipGoHome") !=std::string::npos){
    SkipGoHome = entrada;
  }
  else if(entrada.find("SkipSobeRelativo") !=std::string::npos){
    SkipSobeRelativo = entrada;
  }
  else if(entrada.find("PlacePos") !=std::string::npos){
    PlacePos = entrada;
  }
}



void imprimir(std::ofstream &ofs,int contador, string IndexacaoVH, string NumCaixas, string ConfGarraPick, string PickOp, string FechaGarraOp, string AbreGarraOp, string SkipGoHome, string SkipSobeRelativo, string PlacePos){
  ofs << "MatrizPontos[1," << contador << "]." << IndexacaoVH << endl;
  ofs << "MatrizPontos[1," << contador << "]." << NumCaixas << endl;
  ofs << "MatrizPontos[1," << contador << "]." << ConfGarraPick << endl;
  ofs << "MatrizPontos[1," << contador << "]." << PickOp << endl;
  ofs << "MatrizPontos[1," << contador << "]." << FechaGarraOp << endl;
  ofs << "MatrizPontos[1," << contador << "]." << AbreGarraOp << endl;
  ofs << "MatrizPontos[1," << contador << "]." << SkipGoHome << endl;
  ofs << "MatrizPontos[1," << contador << "]." << SkipSobeRelativo << endl;
  ofs << "MatrizPontos[1," << contador << "]." << PlacePos << endl;
  ofs << endl;
  return;
}

int main(int argc, char **argv)
{
//+-------------------------------------------------------------------------------+
  // variaveis
  string IndexacaoVH;
  string NumCaixas;
  string ConfGarraPick;
  string PickOp;
  string FechaGarraOp;
  string AbreGarraOp;
  string SkipGoHome;
  string SkipSobeRelativo;
  string PlacePos;  
  
  // Informar o numero de linhas do arquivo 
  std::ifstream inFile("MosaicoA_Pallet1.src"); 
  if(!inFile) {
    cout << "Arquivo não foi encontrado.\n";
    return 0;
  }
  std::ofstream ofs ("MosaicoA_Pallet1_out.src", std::ofstream::out);

  int contador=0;
  
  ofs << "DEF TMatriz( )" << endl;
  // MatrizPontos[ProdutoA,1].Indexacao
  char leitura;

  std::string entrada;
  std::stringstream entrada2;
  bool uma_vez=false;
  while (!inFile.eof()){
    getline(inFile,entrada);
    if((
      (entrada.find("IndexacaoVH") !=std::string::npos)||
      (entrada.find("NumCaixas") !=std::string::npos)||
      (entrada.find("ConfGarraPick") !=std::string::npos)||
      (entrada.find("PickOp") !=std::string::npos)||
      (entrada.find("FechaGarraOp") !=std::string::npos)||
      (entrada.find("AbreGarraOp") !=std::string::npos)||
      (entrada.find("SkipGoHome") !=std::string::npos)||
      (entrada.find("SkipSobeRelativo") !=std::string::npos)||
      (entrada.find("PlacePos") !=std::string::npos)) && 
      (entrada.find("()") == std::string::npos))
    {
      uma_vez=true;
      preenche(entrada,IndexacaoVH,NumCaixas,ConfGarraPick,PickOp,FechaGarraOp,AbreGarraOp,SkipGoHome,SkipSobeRelativo,PlacePos);
      entrada2 << entrada;
      // cout << entrada[1]        << endl;
      cout << entrada2.str() << endl;
      entrada2.str("");
    }
    else
    {
      if(uma_vez){
        imprimir(ofs,contador,IndexacaoVH,NumCaixas,ConfGarraPick,PickOp,FechaGarraOp,AbreGarraOp,SkipGoHome,SkipSobeRelativo,PlacePos);
        contador++;
        uma_vez=false;
      }
    }
    // cout << entrada << endl;
    // if(entrada.find("IndexacaoVH")!=std::string::npos)cout << entrada << enld;
  }

  ofs << "END"<< endl;
  ofs.close();

  cout << "Numero de pontos: " << contador-1 << endl;

  inFile.close();
  return 0;
}