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
#include "pallet.h"

void data_tool(std::ifstream &My_Job_src,std::ofstream &TPallet_src){
  int bases=0;
  int tools=0;
  My_Job_src.clear();
  My_Job_src.seekg(0);
  std::string entrada;
  while (!My_Job_src.eof())
  {
    getline(My_Job_src,entrada);
    if(entrada.find("Tools and Bases")!=std::string::npos){
      getline(My_Job_src,entrada);
      while(entrada.find("endfold")==std::string::npos)
      {
        if(entrada.find("BASE_DATA")!=std::string::npos){
          TPallet_src<<"       "<<split_string(entrada,"[;]+",1) << endl;
          bases++;
        }
        if(entrada.find("TOOL_DATA")!=std::string::npos){
          TPallet_src<<"       "<<split_string(entrada,"[;]+",1) << endl;
          tools++;
        }
        getline(My_Job_src,entrada);
      }
      break;
      }
  }
  cout << "numero de bases: " << bases << endl;
  cout << "numero de bases: " << tools << endl;
}

void pallet_src(std::ifstream &My_Job_src,std::ofstream &TPallet_src,int MaxPallets){
  cout <<  "# >> Rotina Pallet << " << endl;  
  int i=1;
  int j=1;

  TPallet_src << "    ;FOLD RobRoot, Tools and Bases used" << endl;
  data_tool(My_Job_src,TPallet_src);
  TPallet_src << "    ;ENDFOLD\n" << endl;

  TPallet_src << "    ;FOLD Iniciar Opcoes de Pallet" << endl;
  for (i=1;i<MaxPallets+1;i++){
    TPallet_src << "       StrPallet["<< i <<"].BasePoint=BASE_DATA["<< i <<"]" << endl;
  }
  TPallet_src << "    ;ENDFOLD\n" << endl;

  TPallet_src << "    ;FOLD Iniciar Opcoes de Esteira" << endl;
  j=i;
  for (i=1;i<MaxPallets+1;i++){
    TPallet_src << "       BaseEsteira"<< i <<"=BASE_DATA["<< j++ <<"]" << endl;
  }
  TPallet_src << "    ;ENDFOLD\n" << endl;

  TPallet_src << "    ;FOLD OffSetPallet" << endl;
  for (i=1;i<MaxPallets+1;i++){
    TPallet_src << "       StrPallet[" << i << "].OffSetPallet.X=0" << endl;
    TPallet_src << "       StrPallet[" << i << "].OffSetPallet.Y=0" << endl;
    TPallet_src << "       StrPallet[" << i << "].OffSetPallet.Z=0" << endl;
    TPallet_src << "       StrPallet[" << i << "].OffSetPallet.A=0" << endl;
    TPallet_src << "       StrPallet[" << i << "].OffSetPallet.B=0" << endl;
    TPallet_src << "       StrPallet[" << i << "].OffSetPallet.C=0" << endl;
    TPallet_src << endl;
  }
  TPallet_src << "    ;ENDFOLD\n" << endl;

  TPallet_src << "    ;FOLD OffsetEsteira" << endl;
  for (i=1;i<MaxPallets+1;i++){
    TPallet_src << "       OffsetEsteira"<< i <<".X=0" << endl;
    TPallet_src << "       OffsetEsteira"<< i <<".Y=0" << endl;
    TPallet_src << "       OffsetEsteira"<< i <<".Z=0" << endl;
    TPallet_src << "       OffsetEsteira"<< i <<".A=0" << endl;
    TPallet_src << "       OffsetEsteira"<< i <<".B=0" << endl;
    TPallet_src << "       OffsetEsteira"<< i <<".C=0" << endl;
    TPallet_src << endl;
  }
  TPallet_src << "    ;ENDFOLD\n" << endl;
  return;
}



