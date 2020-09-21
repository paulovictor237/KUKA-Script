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

void Cilindro::atribuir(std::string entrada){
  std::string numero=split_string(entrada,"[^0-9]+",1);
  valor=split_string(entrada,"[=]+",1);
  if (numero == "200" ){
    avanca = "Abre_Gar_Triplo_Lado_A";
    recua = "Fecha_Gar_Triplo_Lado_A";
    SensorAvanca = "Cil_Comp_Triplo_A_Ava";
    SensorRecua = "Cil_Comp_Triplo_A_Rec";
  }
  else if (numero == "201" ){
    avanca = "Abre_Gar_Triplo_Lado_B";
    recua = "Fecha_Gar_Triplo_Lado_B";
    SensorAvanca = "Cil_Comp_Triplo_B_Ava";
    SensorRecua = "Cil_Comp_Triplo_B_Rec";
  }
  else if (numero == "202" ){
    avanca = "Ava_Comp_Indiv_Gar_1";
    recua = "Rec_Comp_Indiv_Gar_1";
    SensorAvanca = "Cil_Comp_Indiv_Gr_1_Ava";
    SensorRecua = "Cil_Comp_Indiv_Gr_1_Rec";
  }
  else if (numero == "203" ){
    avanca = "Ava_Comp_Indiv_Gar_3";
    recua = "Rec_Comp_Indiv_Gar_3";
    SensorAvanca = "Cil_Comp_Indiv_Gr_3_Ava";
    SensorRecua = "Cil_Comp_Indiv_Gr_3_Rec";
  }
  else if (numero == "204" ){
    avanca = "Ava_Comp_Indiv_Gar_4";
    recua = "Rec_Comp_Indiv_Gar_4";
    SensorAvanca = "Cil_Comp_Indiv_Gr_4_Ava";
    SensorRecua = "Cil_Comp_Indiv_Gr_4_Rec";
    }
  else if (numero == "205" ){
    avanca = "Ava_Comp_Indiv_Gar_6";
    recua = "Rec_Comp_Indiv_Gar_6";
    SensorAvanca = "Cil_Comp_Indiv_Gr_6_Ava";
    SensorRecua = "Cil_Comp_Indiv_Gr_6_Rec";
    }
  else if (numero == "302" ){
    avanca = "Ava_Cil_2_Gar_1";
    recua = "Rec_Cil_2_Gar_1";
    SensorAvanca = "Cil_2_Gar_1_Ava";
    SensorRecua =  "";
    }
  else if (numero == "304" ){
    avanca = "Ava_Cil_2_Gar_2";
    recua = "Rec_Cil_2_Gar_2";
    SensorAvanca = "Cil_2_Gar_2_Ava";
    SensorRecua =  "";
    }
  else if (numero == "306" ){
    avanca = "Ava_Cil_2_Gar_3";
    recua = "Rec_Cil_2_Gar_3";
    SensorAvanca = "Cil_2_Gar_3_Ava";
    SensorRecua =  "";
    }
  else if (numero == "308" ){
    avanca = "Ava_Cil_2_Gar_4";
    recua = "Rec_Cil_2_Gar_4";
    SensorAvanca = "Cil_2_Gar_4_Ava";
    SensorRecua =  "";
    }
  else if (numero == "310" ){
    avanca = "Ava_Cil_2_Gar_5";
    recua = "Rec_Cil_2_Gar_5";
    SensorAvanca = "Cil_2_Gar_5_Ava";
    SensorRecua =  "";
    }
  else if (numero == "312" ){
    avanca = "Ava_Cil_2_Gar_6";
    recua = "Rec_Cil_2_Gar_6";
    SensorAvanca = "Cil_2_Gar_6_Ava";
    SensorRecua =  "";
    }
  else if (numero == "301" ){
    avanca = "Ava_Cil_1_Gar_1";
    recua = "Rec_Cil_1_Gar_1";
    SensorAvanca = "Cil_1_Gar_1_Ava";
    SensorRecua =  "";
    }
  else if (numero == "303" ){
    avanca = "Ava_Cil_1_Gar_2";
    recua = "Rec_Cil_1_Gar_2";
    SensorAvanca = "Cil_1_Gar_2_Ava";
    SensorRecua =  "";
    }
  else if (numero == "305" ){
    avanca = "Ava_Cil_1_Gar_3";
    recua = "Rec_Cil_1_Gar_3";
    SensorAvanca = "Cil_1_Gar_3_Ava";
    SensorRecua =  "";
    }
  else if (numero == "307" ){
    avanca = "Ava_Cil_1_Gar_4";
    recua = "Rec_Cil_1_Gar_4";
    SensorAvanca = "Cil_1_Gar_4_Ava";
    SensorRecua =  "";
    }
  else if (numero == "309" ){
    avanca = "Ava_Cil_1_Gar_5";
    recua = "Rec_Cil_1_Gar_5";
    SensorAvanca = "Cil_1_Gar_5_Ava";
    SensorRecua =  "";
    }
  else if (numero == "311" ){
    avanca = "Ava_Cil_1_Gar_6";
    recua = "Rec_Cil_1_Gar_6";
    SensorAvanca = "Cil_1_Gar_6_Ava";
    SensorRecua =  "";
    }
  return;
}
void Cilindro::imprime(std::ofstream &ofs){
  ofs<<"            "<<avanca<<" = " << valor<< endl;
  ofs<<"            "<<recua<<" = " << (!valor.find("T")?"FALSE":"TRUE") << endl;
  ofs << endl;
  return;
}

void tudo(std::ifstream &My_Job_src,std::fstream &signal,std::vector<std::string> &VectorOut,std::string name){
  std::ofstream ofs ("out/"+name+".src", std::ofstream::out);
  prefixo(ofs,name);
  signal<<";"<<name<<endl;
  class Cilindro cilindro;
  std::string entrada;
  int valor;
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
        if(My_Job_src.eof())
        {
          break;
        }
        if(entrada.find("$OUT") !=std::string::npos)
        {
          valor=std::stoi(split_string(entrada,"[^0-9]+",1));
          if(valor>150){
            cilindro.atribuir(entrada);
            cilindro.imprime(ofs);
            if(cilindro.SensorAvanca.size()>0){
              cilindro.SensorAvanca+=" == ";
              cilindro.SensorAvanca+=(!cilindro.valor.find("T")?"TRUE":"FALSE");
              waitfor.push_back(cilindro.SensorAvanca);
            }
            if(cilindro.SensorRecua.size()>0){
              cilindro.SensorRecua+= " == ";
              cilindro.SensorRecua+=(!cilindro.valor.find("T")?"FALSE":"TRUE");
              waitfor.push_back(cilindro.SensorRecua);
            }
            if(std::find(VectorOut.begin(), VectorOut.end(),cilindro.avanca)== VectorOut.end())
            {
              VectorOut.push_back(cilindro.avanca);
              signal<<"SIGNAL Cilindro"<<cilindro.avanca<<" "<<split_string(entrada,"[=]+",0)<<endl;
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

int garra_exe(std::ifstream &My_Job_src)
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
  // std::ifstream My_Job_src(argv[1]); 
  if(!My_Job_src) {
    cout << "Arquivo não foi encontrado.\n";
    return 0;
  }
  std::fstream signal("out/signal.dat",std::ofstream::out | std::ofstream::trunc);
  signal << "DEF "<< "signal" <<"( )" << endl;
  // std::ofstream OutConfGarra ("ConfGarra.src", std::ofstream::out);
  // std::ofstream OutAbreGarra ("AbreGarra.src", std::ofstream::out);
  // std::ofstream OutFechaGarra ("FechaGarra.src", std::ofstream::out);
  // std::ofstream ofs ("FileOut.src", std::ofstream::out);
  tudo(My_Job_src,signal,VectorOut,"ConfGarra");
  My_Job_src.clear();
  My_Job_src.seekg(0);
  tudo(My_Job_src,signal,VectorOut,"AbreGarra");
  My_Job_src.clear();
  My_Job_src.seekg(0);
  tudo(My_Job_src,signal,VectorOut,"FechaGarra");

  cout << "FINALIZADO GARRAS" << endl;

  signal << "END";
  signal.close();
  return 0;
}