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

using namespace std;

void prefixo(std::ofstream &ofs,std::string name){
  ofs << "&ACCESS RVO1" << endl;
  ofs << "&PARAM EDITMASK = *" << endl;
  ofs << "DEF "<< name <<"( )" << endl;
  ofs << "   IF (OperarVazio==FALSE) THEN" << endl;
  ofs << "      SWITCH AbreGarra"<<"Op" << endl;
  
}
void sufixo(std::ofstream &ofs){
  ofs << "      ENDSWITCH" << endl;
  ofs << "      WAIT SEC 1" << endl;
  ofs << "   ENDIF" << endl;
  ofs << "END"<< endl;
}

void tudo(std::ifstream &inFile,std::fstream &signal,std::vector<std::string> &VectorOut,std::string name){
  std::ofstream ofs (name+".src", std::ofstream::out);
  prefixo(ofs,name);
  std::string entrada;
  while (!inFile.eof()){
    getline(inFile,entrada);
    if(entrada.find(name) !=std::string::npos)
    {
      ofs << "         " << "CASE " << entrada << endl;
      while(entrada.find("END")!=0){
        getline(inFile,entrada);
        if(inFile.eof()){
          break;
        }
        if(entrada.find("$OUT") !=std::string::npos){
          ofs <<  "            " << entrada << endl;
          if(std::find(VectorOut.begin(), VectorOut.end(),entrada)== VectorOut.end()){
            VectorOut.push_back(entrada);
            signal << entrada << endl;
          } 
        }
      }
    }
  }
  sufixo(ofs);
  ofs.close();
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

  signal.close();
  inFile.close();
  return 0;
}