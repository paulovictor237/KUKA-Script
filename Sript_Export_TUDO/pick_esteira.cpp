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
#include "pick_esteira.h"

int num_pallet = 0;
int num_pickop = 0;

void funcao_pick_esteira_src(std::ofstream &pick_esteira_src,string name){
  //Pick_E_2_P_1
  string pallet = split_string(name,"[_]+",2);
  string pickop = split_string(name,"[_]+",4);

  int aux_pallet = stoi(pallet);
  int aux_pickop = stoi(pickop);

  num_pallet = (aux_pallet>num_pallet)?aux_pallet:num_pallet;
  num_pickop = (aux_pickop>num_pickop)?aux_pickop:num_pickop;

  pick_esteira_src << "pick_esteira[Pallet_"+pallet+","+pickop+"] = "+name+"\n";

  return;
}


int funcao_pick_esteira_dat(std::ifstream &My_Job_dat)
{
  std::ofstream pick_esteira_dat("out/Pick/pick_esteira.dat",std::ofstream::out);
  std::ofstream pick_esteira_src("out/Pick/pick_esteira.src",std::ofstream::out);
  cout <<  "# >> Rotina Pick << " << endl;
  //error
  bool ERROR_pick=true;

  My_Job_dat.clear();
  My_Job_dat.seekg(0);
  // prefixo(ofs,name);
  std::string entrada;
  std::string posicao;
  std::string PickName;
  int tipo_place=1;
  int NumPontos=0;
  int contador=1;

  pick_esteira_dat << ";FOLD OPCOES DE PICK" << endl;
  while (!My_Job_dat.eof())
  {
    getline(My_Job_dat,entrada);
    if (!My_Job_dat.good())break;
    
    if(entrada.find("Data for Pick") !=std::string::npos){
      ERROR_pick=true;
      PickName=split_string(entrada,"[ |\r\n|\r|\n]",3);
      pick_esteira_dat<<";"<<PickName<<endl;
      while(entrada.find("ENDDAT") ==std::string::npos)
      {
        getline(My_Job_dat,entrada);
        if(entrada.find("E6POS") !=std::string::npos && entrada.find(PickName) !=std::string::npos)
        {
          ERROR_pick=false;
          cout << "Pick encontrado: " << PickName <<endl;
          // cout << entrada<<endl;
          posicao=split_string(entrada,"[=]+",1);
          //posicao = ponto_remove_turn(posicao);
          pick_esteira_dat<<"DECL GLOBAL E6POS "<<PickName<<"="<<posicao<<endl;
        }
      }
      if(ERROR_pick) cout << "<span style=\"color:red\">**ERROR: " << PickName << "**</span>"<<endl;
      pick_esteira_dat<<endl;
    }
  }
  pick_esteira_dat << ";ENDFOLD \n" << endl;
  return NumPontos;
}