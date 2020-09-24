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

#include "garra.h"
#include "comum.h"


void prefixo(std::ofstream &ofs,std::string name,std::string SWITCH){
  ofs << "DEF "<< name <<"( )" << endl;
  ofs << "   IF (OperarVazio==FALSE) THEN" << endl;
  ofs << "      SWITCH "<< SWITCH <<"Op" << endl;
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
      return out;
    }
  }
  class Cilindro out;
  out.numero="ERROR";
  return out;
}

int tudo(std::ifstream &My_Job_src,std::vector<class Cilindro> &Vcilindro,std::string name){
  My_Job_src.clear();
  My_Job_src.seekg(0);
  std::ofstream ofs ("out/"+name+".src", std::ofstream::out);
  prefixo(ofs,name,name);
  class Cilindro cilindro;
  std::string entrada;
  std::string numero;
  int contador=0;
  vector<string> waitfor;
  while (!My_Job_src.eof())
  {
    getline(My_Job_src,entrada);
    if(entrada.find("DEF "+name) !=std::string::npos)
    {
      contador++;
      ofs << "         " << "CASE " << split_string(entrada,"[^0-9]+",1) << endl;
      while(entrada.find("END")!=0)
      {
        getline(My_Job_src,entrada);
        if(My_Job_src.eof())break;

        if(entrada.find("$OUT") !=std::string::npos)
        {
          cilindro=atribuir(Vcilindro,entrada);
          if(cilindro.numero!="ERROR"){
            cilindro.valor=split_string(entrada,"[=]+",1); // ?"TRUE":"FALSE"
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
      // ofs<<"            WAIT SEC 0.5"<< endl;
      waitfor.clear();
    }
  }
  sufixo(ofs);
  ofs.close();
  return contador;
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

int GarraNoWait(std::ifstream &My_Job_src,std::vector<class Cilindro> &Vcilindro,std::string name){
  My_Job_src.clear();
  My_Job_src.seekg(0);
  std::ofstream ConfGarra_NoWait("out/"+name+"_NoWait.src", std::ofstream::out);
  std::ofstream ConfGarra_Wait ("out/"+name+"_Wait.src",  std::ofstream::out);
  prefixo(ConfGarra_NoWait,name+"_NoWait",name);
  prefixo(ConfGarra_Wait,name+"_Wait",name);

  class Cilindro cilindro;
  std::string entrada;
  std::string numero;
  int contador=0;
  vector<string> waitfor;
  while (!My_Job_src.eof())
  {
    getline(My_Job_src,entrada);
    if(entrada.find("DEF "+name) !=std::string::npos)
    {
      contador++;
      ConfGarra_NoWait << "         " << "CASE " << split_string(entrada,"[^0-9]+",1) << endl;
      ConfGarra_Wait   << "         " << "CASE " << split_string(entrada,"[^0-9]+",1) << endl;
      while(entrada.find("END")!=0)
      {
        getline(My_Job_src,entrada);
        if(My_Job_src.eof())break;

        if(entrada.find("$OUT") !=std::string::npos)
        {
          cilindro=atribuir(Vcilindro,entrada);
          if(cilindro.numero!="ERROR"){
            cilindro.valor=split_string(entrada,"[=]+",1); // ?"TRUE":"FALSE"
            cilindro.imprime(ConfGarra_NoWait);
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
      for (auto &outt : waitfor)ConfGarra_Wait<<"            WAIT FOR ( "<<outt<<" )" << endl;
      // ConfGarra_Wait<<"            WAIT SEC 0.5"<< endl;
      waitfor.clear();
    }
  }
  sufixo(ConfGarra_NoWait); 
  sufixo(ConfGarra_Wait);
  ConfGarra_NoWait.close();
  ConfGarra_Wait.close();
  return contador;
}

int garra_exe(std::ifstream &My_Job_src)
{
//# +---------------------------------------------------------------------------------------------------------------------------------------------------<< 
  // variaveis
  cout <<  "# >> Rotina Garra << " << endl;
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
  GarraNoWait(My_Job_src,cilindro,"ConfGarra");
  contador = tudo(My_Job_src,cilindro,"ConfGarra");
  cout << "Numero de ConfGarra: " << contador << endl;
  contador = tudo(My_Job_src,cilindro,"AbreGarra");
  cout << "Numero de AbreGarra: " << contador << endl;
  contador = tudo(My_Job_src,cilindro,"FechaGarra");
  cout << "Numero de FechaGarra: " << contador << endl;
  return 0;
}


