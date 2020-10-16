#ifndef comum_h
#define comum_h

class Pose{
public:
    double X=0,Y=0,Z=0,A=0,B=0;
public:
    std::string kuka(void);
    friend std::ostream &operator<<(std::ostream &os, Pose const &m);
};

class Objeto{
public:
    double width=0,height=0,length=0,weight=0;
public:
    friend std::ostream &operator<<(std::ostream &os, Objeto const &m);
};

class Receita{
public:
  std::string nome;
  int PlacesCamada=0,AlturaCaixa=0,Camadas=0,Layers=0;
  std::vector <int> LayersVector;
public:
  void imprime(std::ofstream &ofs);
};

std::string split_string(std::string tokenString,std::string delim,int saida);
vector<string> split_string(std::string tokenString,std::string delim);
void imprime_vetor(vector<string> tokens);

double valor(std::string entrada);
bool buscar_chave(std::string entrada,std::string chave);

void init_files(std::ofstream &src,std::ofstream &dat,std::string name);
void end_files(std::ofstream &src,std::ofstream &dat);

#endif