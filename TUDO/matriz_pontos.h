#ifndef matriz_pontos_h
#define matriz_pontos_h

int matriz_pontos_str(std::ifstream &My_Job_src,std::ofstream &TMatriz_src,std::string pallet,std::string produto,int &NumLayers);
int matriz_pontos_dat(std::ifstream &My_Job_src,std::ofstream &TMatriz_dat,std::string pallet,std::string produto,std::string produto_cmplt);

#endif