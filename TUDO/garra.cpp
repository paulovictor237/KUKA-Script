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

#include "garra.h"
#include "comum.h"


void prefixo(std::ofstream &ofs,std::string name){
  ofs << "&ACCESS RVO1" << endl;
  ofs << "&PARAM EDITMASK = *" << endl;
  ofs << "DEF "<< name <<"( )" << endl;
  ofs << "   IF (OperarVazio==FALSE) THEN" << endl;
  ofs << "      SWITCH "<< name <<"Op" << endl;
  return;
}
void sufixo(std::ofstream &ofs){
  ofs << "      ENDSWITCH" << endl;
  ofs << "      WAIT SEC 1" << endl;
  ofs << "   ENDIF" << endl;
  ofs << "END";
  return;
}

void Cilindro::imprime(std::ofstream &ofs){
  ofs<<"            "<<avanca<<" = " << valor<< endl;
  ofs<<"            "<<recua<<" = " << (!valor.find("T")?"FALSE":"TRUE") << endl;
  ofs << endl;
  return;
}

class Cilindro atribuir(std::vector<class Cilindro> Vcilindro,std::string entrada){
  for (class Cilindro out : Vcilindro){
    if(entrada.find(out.numero) !=std::string::npos){
      out.valor=split_string(entrada,"[=]+",1);
      return out;
    }
  }
  class Cilindro out;
  out.numero="ERROR";
  return out;
}

void tudo(std::ifstream &My_Job_src,std::vector<class Cilindro> &Vcilindro,std::string name){
  std::ofstream ofs ("out/"+name+".src", std::ofstream::out);
  prefixo(ofs,name);
  class Cilindro cilindro;
  std::string entrada;
  std::string numero;
  vector<string> waitfor;
  while (!My_Job_src.eof())
  {
    getline(My_Job_src,entrada);
    if(entrada.find("DEF "+name) !=std::string::npos)
    {
      ofs << "         " << "CASE " << split_string(entrada,"[^0-9]+",1) << endl;
      while(entrada.find("END")!=0)
      {
        getline(My_Job_src,entrada);
        if(My_Job_src.eof())break;

        if(entrada.find("$OUT") !=std::string::npos)
        {
          cilindro=atribuir(Vcilindro,entrada);
          if(cilindro.numero!="ERROR"){
            cilindro.imprime(ofs);
          if(cilindro.SensorAvanca!="X"){
            cilindro.SensorAvanca+=" == ";
            cilindro.SensorAvanca+=(!cilindro.valor.find("T")?"TRUE":"FALSE");
            waitfor.push_back(cilindro.SensorAvanca);
          }
          if(cilindro.SensorRecua!="X"){
            cilindro.SensorRecua+= " == ";
            cilindro.SensorRecua+=(!cilindro.valor.find("T")?"FALSE":"TRUE");
            waitfor.push_back(cilindro.SensorRecua);
          }
          }
        }
      }
      //  WAIT FOR  ( SensorGarraAberta1 )
      for (auto &outt : waitfor)ofs<<"            WAIT FOR ( "<<outt<<" )" << endl;
      ofs<<"            WAIT SEC 0.5"<< endl;
      waitfor.clear();
    }
  }
  sufixo(ofs);
  ofs.close();
  return;
}
void mapear(std::vector<class Cilindro> &cilindro){

  std::ifstream inFile("My_Job/mapa.md"); 
  if(!inFile) {
    cout << "Arquivo não foi encontrado.\n";
    return;
  }
  string descartar;
  string entrada;
  class Cilindro aux;
  getline(inFile,entrada);
  getline(inFile,entrada);
  while (!inFile.eof())
  { 
    inFile >> descartar >> aux.numero;
    inFile >> descartar >> aux.avanca;
    inFile >> descartar >> aux.recua;
    inFile >> descartar >> aux.SensorAvanca;
    inFile >> descartar >> aux.SensorRecua;
    inFile >> descartar;
    cilindro.push_back(aux);
  }
  // for (auto &out : cilindro){
  //   cout << out.numero << endl;
  // }
  inFile.close();
  return;
}

int garra_exe(std::ifstream &My_Job_src)
{
//+-------------------------------------------------------------------------------+
  // variaveis
  int contador=0;
  std::string entrada;
  std::stringstream entrada2;
  bool uma_vez=false;
  std::string name;
   
  // Informar o numero de linhas do arquivo 
  // std::ifstream My_Job_src(argv[1]); 
  if(!My_Job_src) {
    cout << "Arquivo não foi encontrado.\n";
    return 0;
  }
  std::vector<class Cilindro> cilindro;
  mapear(cilindro);
  tudo(My_Job_src,cilindro,"ConfGarra");
  My_Job_src.clear();
  My_Job_src.seekg(0);
  tudo(My_Job_src,cilindro,"AbreGarra");
  My_Job_src.clear();
  My_Job_src.seekg(0);
  tudo(My_Job_src,cilindro,"FechaGarra");

  cout << "FINALIZADO GARRAS" << endl;
  return 0;
}

