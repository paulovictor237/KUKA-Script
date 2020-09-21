#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "ConsoleColor.h"

using namespace std;

class Parse
{
  public:
    Parse();
    void call();
    void initialCheck(int argc, char** argv);
  
  private:
    void readFile();
    void Search_and_Save_E6POS();
    void Search_and_Save_SRC();
    void Save_Outputs_E6POS();
    void Save_Outputs_SRC();
    void Define_Default_Values();
    void Store_Last_Values();
    bool Search_Variables(string line);

    string Search_Z(size_t position, int movement);
    string Print_Matrix(int count_pto);

    //size_t Search_Variables(size_t position_to_search);

    //Booleans
    bool store_Three_Zs = true;
    bool mount_matrix = false;
    //Integer
    int count_points, count_local_points;

    //Strings 
    string my_file_name, receita;
    string myfile_src_string, myfile_dat_string; //Input
    string myfile_dat_string_output, myfile_src_string_output; //Output

    string sZ1, sZ2, sZ3;

    //Const Strings
    string Init ="P_";
    const string App_End_1 ="App1Place"; 
    const string App_End_2 = "App2Place";
    const string Place = "Place";
    const string name_matrix = "MatrizPontos";
    const string sufix_prod = "Produto";

    string IndexacaoVH = "IndexacaoVH";
    string IndexacaoVH_val;
    string NumCaixas = "NumCaixas";
    string NumCaixas_val;
    string ConfGarraPick = "ConfGarraPick";
    string ConfGarraPick_val;
    string PickOp = "PickOp";
    string PickOp_val;
    string FechaGarraOp = "FechaGarraOp";
    string FechaGarraOp_val;
    string AbreGarraOp = "AbreGarraOp";
    string AbreGarraOp_val;
    string SkipGoHome = "SkipGoHome";
    string SkipGoHome_val;
    string SkipSobeRelativo = "SkipSobeRelativo";
    string SkipSobeRelativo_val;
    string PlacePos = "PlacePos";
    string PlacePos_val;

};