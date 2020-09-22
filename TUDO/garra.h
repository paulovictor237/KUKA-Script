//+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+
// BIBLIOTECAS C++

// COMPILAR
// g++ *.cpp -o executavel -std=c++11 && ./executavel 
#ifndef garra_h
#define garra_h

class Cilindro{
public:
  std::string numero;
  std::string valor;
  std::string avanca;
  std::string recua;
  std::string SensorAvanca;
  std::string SensorRecua;
public:
  void atribuir(std::string entrada);
  void imprime(std::ofstream &ofs);
};

int garra_exe(std::ifstream &My_Job_src);


#endif