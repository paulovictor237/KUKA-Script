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

// split_string(outt,"[_=]+",true);
// [0]-> DECL E6POS XPick
// [1]-> E
// [2]-> 1
// [3]-> P
// [4]-> 3
// [5]-> {X 490.63656,Y 71.25504,Z 1342.80037,A -90,B 0,C -180,S 2,T 2,E1 0,E2 0,E3 0,E4 0,E5 0,E6 0}

std::vector<std::string> pick_esteira_ordenado;

bool myfunction (std::string i,std::string j) {
  int ii  = stoi(split_string(i,"[_=]+",2))*1000 + stoi(split_string(i,"[_=]+",4));
  int jj  = stoi(split_string(j,"[_=]+",2))*1000 + stoi(split_string(j,"[_=]+",4));
  return (ii<jj); 
}

std::string funcao_pick_esteira_src(string PickName){
  //Pick_E_2_P_1
  string pallet = split_string(PickName,"[_=]+",2);
  string pickop = split_string(PickName,"[_=]+",4);

  int aux_pallet = stoi(pallet);
  int aux_pickop = stoi(pickop);

  num_pallet = (aux_pallet>num_pallet)?aux_pallet:num_pallet;
  num_pickop = (aux_pickop>num_pickop)?aux_pickop:num_pickop;

  std::string aux_pick_name= "pick_esteira[Pallet_"+pallet+","+pickop+"] = "+PickName+"\n";

  return aux_pick_name;
}

void def_pick_esteira(vector<string> vetor,int &NumEsteiras,int &NumPicks) {
  int NumEsteiras_aux,NumPicks_aux;
  for(auto outt:vetor){
    NumEsteiras_aux  = stoi(split_string(outt,"[_=]+",2));
    NumEsteiras = (NumEsteiras_aux>NumEsteiras?NumEsteiras_aux:NumEsteiras);
    NumPicks_aux  = stoi(split_string(outt,"[_=]+",4));
    NumPicks = (NumPicks_aux>NumPicks?NumPicks_aux:NumPicks);
  }
  return ; 
}


int funcao_pick_esteira_dat(std::ifstream &My_Job_dat,int &NumEsteiras,int &NumPicks)
{
  std::ofstream pick_esteira_src("file_out/Pick/Tpick_esteira.src",std::ofstream::out);
  std::ofstream pick_esteira_dat("file_out/Pick/Tpick_esteira.dat",std::ofstream::out);
  
  pick_esteira_src << "DEF "   << "Tpick_esteira" << "()" << endl;
  pick_esteira_dat << "DEFDAT "<< "Tpick_esteira" << " PUBLIC" << endl;

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

  //pick_esteira_dat << ";OPCOES DE PICK" << endl;
  while (!My_Job_dat.eof())
  {
    getline(My_Job_dat,entrada);
    if (!My_Job_dat.good())break;
    
    if(entrada.find("Data for Pick") !=std::string::npos){
      ERROR_pick=true;
      PickName=split_string(entrada,"[ |\r\n|\r|\n]",3);
      if(split_string(PickName,"[_]+").size() == 5){
        while(entrada.find("ENDDAT") ==std::string::npos)
        {
          getline(My_Job_dat,entrada);
          if(entrada.find("E6POS") !=std::string::npos && entrada.find(PickName) !=std::string::npos)
          {
            ERROR_pick=false;
            pick_esteira_ordenado.push_back(entrada);
          }
        }
        if(ERROR_pick) cout << "<span style=\"color:red\">**ERROR: " << PickName << "**</span>"<<endl;
      }
    }
  }
  //ordena vetor
  std::sort (pick_esteira_ordenado.begin(),pick_esteira_ordenado.end(), myfunction); 

  def_pick_esteira(pick_esteira_ordenado,NumEsteiras,NumPicks);

  for (auto &outt : pick_esteira_ordenado){
    PickName=split_string(outt,"[ =]",2);
    posicao=split_string(outt,"[_=]+",5);
    cout << "Pick encontrado: " << PickName <<endl;
    pick_esteira_dat<<"DECL GLOBAL E6POS "<<PickName<<"="<<posicao<<endl;
    pick_esteira_src << funcao_pick_esteira_src(PickName);
  }
  //---- END ----
  pick_esteira_src << "END";
  pick_esteira_dat << "ENDDAT";

  pick_esteira_src.close();
  pick_esteira_dat.close();
  return NumPontos;
}