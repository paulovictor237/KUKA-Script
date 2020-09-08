//+-------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-------------------------------------------------------------------------------+
// BIBLIOTECAS C++

// COMPILAR
// g++ *.cpp -o z_peve -std=c++11 && ./z_peve 

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

std::string split_string(std::string tokenString,string delim,int saida){
  vector<string> tokens;
  std::regex delimiters {delim};
  sregex_token_iterator tokens_begin { tokenString.begin(), tokenString.end(), delimiters, -1 };
  auto tokens_end = sregex_token_iterator {};
  for (auto token_it = tokens_begin; token_it != tokens_end; token_it++)tokens.push_back(*token_it);
  return tokens[saida];
}

void prefixo(std::ofstream &ofs,std::string name){
  ofs << "&ACCESS RVO1" << endl;
  ofs << "&PARAM EDITMASK = *" << endl;
  ofs << "DEF "<< name <<"( )" << endl;
  ofs << "   IF (OperarVazio==FALSE) THEN" << endl;
  ofs << "      SWITCH AbreGarra"<<"Op" << endl;
  return;
}
void sufixo(std::ofstream &ofs){
  ofs << "      ENDSWITCH" << endl;
  ofs << "      WAIT SEC 1" << endl;
  ofs << "   ENDIF" << endl;
  ofs << "END";
  return;
}

class Cilindro{
public:
  std::string avanca;
  std::string recua;
  std::string SensorAvanca;
  std::string SensorRecua;
  std::string valor;
public:
  void atribuir(std::string entrada){
    avanca=split_string(entrada,"[^0-9]+",1);
    valor=split_string(entrada,"[=]+",1);
    if (avanca == "200" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "201" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "202" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "203" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "204" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "205" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "302" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "304" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "306" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "308" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "310" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "312" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "301" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "303" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "305" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "307" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "309" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    else if (avanca == "311" ){
      avanca = "VALOR";
      recua = "VALOR";
      SensorAvanca = "VALOR";
      SensorRecua = "VALOR";
      valor = "VALOR";
      }
    return;
  }
  void imprime(std::ofstream &ofs){
    ofs<<"            AvancaCilindro"<<avanca<<" = " << valor<< endl;
    ofs<<"            RecuaCilindro"<<recua<<" = " << (!valor.find("T")?"FALSE":"TRUE") << endl;
    ofs<<"            WAIT FOR  ( "<<"SensorCilindro"<<SensorAvanca<<" )"<< endl;
    return;
  }
};

void tudo(std::ifstream &inFile,std::fstream &signal,std::vector<std::string> &VectorOut,std::string name){
  std::ofstream ofs (name+".src", std::ofstream::out);
  prefixo(ofs,name);
  signal<<";"<<name<<endl;
  class Cilindro cilindro;
  std::string entrada;
  while (!inFile.eof())
  {
    getline(inFile,entrada);
    if(entrada.find(name) !=std::string::npos)
    {
      ofs << "         " << "CASE " << split_string(entrada,"[^0-9]+",1) << endl;
      while(entrada.find("END")!=0)
      {
        getline(inFile,entrada);
        if(inFile.eof())
        {
          break;
        }
        if(entrada.find("$OUT") !=std::string::npos)
        {
          cilindro.atribuir(entrada);
          cilindro.imprime(ofs);
          if(std::find(VectorOut.begin(), VectorOut.end(),cilindro.avanca)== VectorOut.end())
          {
            VectorOut.push_back(cilindro.avanca);
            signal<<"SIGNAL Cilindro"<<cilindro.avanca<<" "<<split_string(entrada,"[=]+",0)<<endl;
          } 
        }
      }
    }
  }
  sufixo(ofs);
  ofs.close();
  return;
}

int main(int argc, char **argv)
{
//+-------------------------------------------------------------------------------+
  // variaveis
  int contador=0;
  std::string entrada;
  std::stringstream entrada2;
  bool uma_vez=false;
  std::string name;
  std::vector<std::string> VectorOut;
   
  // Informar o numero de linhas do arquivo 
  // std::ifstream inFile(argv[1]); 
  std::ifstream inFile("My_Job.src"); 
  if(!inFile) {
    cout << "Arquivo não foi encontrado.\n";
    return 0;
  }
  std::fstream signal("signal.dat",std::ofstream::out | std::ofstream::trunc);
  signal << "DEF "<< "signal" <<"( )" << endl;
  // std::ofstream OutConfGarra ("ConfGarra.src", std::ofstream::out);
  // std::ofstream OutAbreGarra ("AbreGarra.src", std::ofstream::out);
  // std::ofstream OutFechaGarra ("FechaGarra.src", std::ofstream::out);
  // std::ofstream ofs ("FileOut.src", std::ofstream::out);
  tudo(inFile,signal,VectorOut,"ConfGarra");
  inFile.clear();
  inFile.seekg(0);
  tudo(inFile,signal,VectorOut,"AbreGarra");
  inFile.clear();
  inFile.seekg(0);
  tudo(inFile,signal,VectorOut,"FechaGarra");

  cout << "FINALIZADO" << endl;

  signal << "END";
  signal.close();
  inFile.close();
  return 0;
}