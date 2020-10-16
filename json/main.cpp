//# +---------------------------------------------------------------------------------------------------------------------------------------------------<< 
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//# +---------------------------------------------------------------------------------------------------------------------------------------------------<< 
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

#include "comum.h"
#include "simulacao.h"
#include "matriz_pontos.h"

int main(int argc, char **argv)
{
//+------------------------------------------------------------<< 
  //system("clear");
  // system("cls");
//+------------------------------------------------------------<< 
  // cout << "# PROGRAMA INICIADO #"<<endl;
  // std::ofstream Relatorio("Relatorio/Relatorio.md");
  // std::streambuf *coutbuf=std::cout.rdbuf(); //save old buf
  // std::cout.rdbuf(Relatorio.rdbuf()); //redirect std::cout to out.txt!
  // cout << "Relatorio gerado em [ Relatorio/Relatorio.md ]"<<endl;
//+------------------------------------------------------------<< 
  cout << "# $ >> PROGRAMA INICIADO << $"<<endl;
  cout << "Valores de inicializacao" << endl; 
//+------------------------------------------------------------<< 
  std::ifstream file_in("in/My_Job.json"); 

  std::ofstream simulacao_src("simulacao/simulacao.src",std::ofstream::out);
  std::ofstream simulacao_dat("simulacao/simulacao.dat",std::ofstream::out);

  std::ofstream TReceita_src("out/INIT/TReceita.src",std::ofstream::out);
  std::ofstream TReceita_dat("out/INIT/TReceita.dat",std::ofstream::out);

  std::ofstream TMatriz_src ("out/INIT/TMatriz.src", std::ofstream::out);
  std::ofstream TMatriz_dat ("out/INIT/TMatriz.dat", std::ofstream::out);

  std::ofstream TPallet_src ("out/INIT/TPallet.src", std::ofstream::out);
  std::ofstream TPallet_dat ("out/INIT/TPallet.dat", std::ofstream::out);


  if((!file_in)||(!simulacao_src)||(!simulacao_dat))
  {
    //MaxPallets=atoi(argv[1]);
    cout << "Erro ao abrir os arquivos.\n";
    return 0;
  }
  init_files(simulacao_src,simulacao_dat,"simulacao");
  init_files(TReceita_src,TReceita_dat,"TReceita");
  init_files(TMatriz_src,TMatriz_dat,"TMatriz");
  init_files(TPallet_src,TPallet_dat,"TPallet");
  //padrao_move(simulacao_src);
//+------------------------------------------------------------<< 
  

  std::string entrada;
  int NumPontos=0;
  int NumLayers=0;
  bool aux_name=false;

  class Pose pose;
  class Objeto Pallet,Caixa;
  class Receita receita;
  
  while (!file_in.eof())
  {
    if (!file_in.good())break;
    getline(file_in,entrada);
    //coleta o nome da receita
    if(buscar_chave(entrada,"name") && aux_name==false)
    {
      aux_name=true;
      //imprime_vetor(split_string(entrada,"[\"]+"));
      receita.nome = split_string(entrada,"[\"]+",3);
    }
    //pegar valor de paller
    if(buscar_chave(entrada,"dimensions"))
    {
      getline(file_in,entrada);
      Pallet.height = valor(entrada);
      getline(file_in,entrada);
      Pallet.length = valor(entrada);
      getline(file_in,entrada);
      Pallet.width = valor(entrada);
      cout << "Pallet\n" << Pallet << endl;
    }
    //pega valor de caixa
    if(buscar_chave(entrada,"productDimensions"))
    {
      getline(file_in,entrada);
      Caixa.width = valor(entrada);
      getline(file_in,entrada);
      Caixa.height = valor(entrada);
      getline(file_in,entrada);
      Caixa.length = valor(entrada);
      getline(file_in,entrada);
      Caixa.weight = valor(entrada);
      cout << "Caixa\n" << Caixa << endl;
    }
    //coleta os layers
    if(buscar_chave(entrada,"layers"))
    {
      while (entrada.find("]")!=0)
      {
        getline(file_in,entrada);
        if (!file_in.good()||buscar_chave(entrada,"]"))break;
        receita.LayersVector.push_back(valor(entrada));
      }
    }
    //captura os pontos
    if(buscar_chave(entrada,"pattern"))
    {
      NumLayers++;
      while (entrada.find("        }")!=0)
      {
        getline(file_in,entrada);
        if (!file_in.good())break;

        if(buscar_chave(entrada,"x"))
        {
          NumPontos ++;
          pose.X=valor(entrada);
          getline(file_in,entrada);
          pose.Y=valor(entrada);
          getline(file_in,entrada);
          getline(file_in,entrada);
          pose.A=valor(entrada);
          getline(file_in,entrada);
          //pose.B=valor(entrada);
          //cout << pose << endl;
          simulacao_ponto(simulacao_src,simulacao_dat,NumPontos+20,pose,false);
        }
      }
      pose.Z=Caixa.height*NumLayers;
    }
  }
//+------------------------------------------------------------<< 
  //preenche a receita
  receita.PlacesCamada=NumPontos/NumLayers;
  receita.AlturaCaixa=Caixa.height;
  receita.Camadas=receita.LayersVector.size();
  receita.Layers=NumLayers;
  receita.imprime(TReceita_src);
//+------------------------------------------------------------<< 
  end_files(simulacao_src,simulacao_dat);
  end_files(TReceita_src,TReceita_dat);
  end_files(TMatriz_src,TMatriz_dat);
  end_files(TPallet_src,TPallet_dat);
  simulacao_src.close();
  simulacao_dat.close();
  TReceita_src.close();
  TReceita_dat.close();
  TMatriz_src.close();
  TMatriz_dat.close();
  TPallet_src.close();
  TPallet_dat.close();
  file_in.close();
  //Relatorio.close();
  cout << "# $ >> FIM << $"<<endl;
  return 0;
}