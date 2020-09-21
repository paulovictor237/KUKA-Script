#ifndef pallet_h
#define pallet_h

// std::string split_string(std::string tokenString,std::string delim,int saida);
void prefixo(std::fstream &ofs,std::string name,bool dat);
void sufixo(std::fstream &ofs,bool dat);
void init(void);
void end(void);

class Receita{
public:
  std::string nome;
  int PlacesCamada=0;
  int AlturaCaixa = 0;
  int layers=3;
  std::vector<std::string>Pick;
public:
  Receita(std::string nome);
  void imprime(std::fstream &ofs,int Camadas);
};

#endif