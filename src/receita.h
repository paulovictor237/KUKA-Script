#ifndef receita_h
#define receita_h

// std::string split_string(std::string tokenString,std::string delim,int saida);
int pick(std::ifstream &My_Job_dat,std::ofstream &TReceita_dat);
void prefixo(std::ofstream &ofs,std::string name,bool dat);
void sufixo(std::ofstream &ofs,bool dat);
void init(void);
void end(void);

class Receita{
public:
  std::string nome;
  int PlacesCamada=0;
  int AlturaCaixa=0;
  int Camadas=0;
  int Layers=0;
public:
  void imprime(std::ofstream &ofs);
};

#endif