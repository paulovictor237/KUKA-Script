#ifndef matriz_pontos_h
#define matriz_pontos_h

void separa_layers_src(std::ofstream &TMatriz_src,int layer,int inicial,int final);
void matriz_pontos(std::ofstream &TMatriz_src,std::ofstream &TMatriz_dat,int pallet,int NumPlace,class Receita receita);


#endif