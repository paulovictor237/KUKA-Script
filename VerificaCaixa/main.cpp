//+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+
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

int main(int argc, char **argv)
{
//+-----------------------------------------------------------------------------------------------------------------------------------------------------------------------+
  system("clear");
  // system("cls");
  cout << "\033[1;44m" <<  "╔═══════════════════════════════════════════════════════╗" << "\033[0m"<<endl;
  cout << "\033[1;44m" <<  "║                   PROGRAMA INICIADO                   ║" << "\033[0m"<<endl;
  cout << "\033[1;44m" <<  "╚═══════════════════════════════════════════════════════╝" << "\033[0m"<<endl;
  

  // Dividendo |divisor
  // Resto      Quociente

  // Dividendo = Quociente*divisor + Resto
  // Resto = Dividendo - Quociente*divisor

  int Numero=123456;
  int NumSensores=6;
  int divisor=10;
  int Dividendo;
  int quociente;
  int resto;

  Dividendo = Numero;
  while (Dividendo > 0)
  {
    quociente = Dividendo/divisor;
    resto  = Dividendo - quociente*divisor;
    cout << resto << endl;
    Dividendo = Dividendo/divisor;
  }
  cout  << endl;
  Dividendo = Numero;
  while (Dividendo > 0)
  {
    quociente = Dividendo/divisor;
    resto  = Dividendo - quociente*divisor;
    cout << (NumSensores-resto+1) << endl;
    Dividendo = Dividendo/divisor;
  }

  return 0;
}