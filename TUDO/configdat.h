#ifndef configdat_h
#define configdat_h


class Config{
public:

std::vector<std::string> ENUM_RECEITA;

// ;------------------ StrPallet[MaxPallets] ------------------
int MaxPallets=0;
// DECL GLOBAL DefPallet StrPallet[2];[MaxPallets]

// ;------------------ StrReceita[MaxReceitas] ------------------
int MaxReceitas=0;
int MaxCamadas=0;
// DECL GLOBAL DefStrReceita StrReceita[21];[MaxReceitas]
// INT  StrReceitaLayer[21,12];[MaxReceitas,MaxCamadas]

// ;------------------ MatrizPontos[MaxMatrizI,MaxMatrizJ,MaxMatrizK] ------------------
int MaxMatrizI=0  ;//[numero de pallets por receita]
int MaxMatrizJ=0 ;//[acompanha o MaxReceitas]
int MaxMatrizK=0 ;//[numero Maximo de Pontos]
// DECL GLOBAL DefMatriz MatrizPontos[2,21,25];[MaxMatrizI,MaxMatrizJ,MaxMatrizK]

public:
  Config(void){};
  void imprime(std::ofstream &config_dat);
  void cout_print(void);
};

#endif