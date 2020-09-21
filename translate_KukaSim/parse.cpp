#include "parse.h"

Parse::Parse()      //My Constructor
{
    cout << "Define Initial Configurations" << endl;
    Define_Default_Values();
}

//Read SRC and Dat Files
void Parse::readFile()
{
    //ofstream myfile_src, myfile_dat;
    std::ifstream myfile_src, myfile_dat;
    stringstream str_src, str_dat;

    //Read Src File
    myfile_src.open(my_file_name+".src");
    
    //Check is exists
    if(myfile_src.is_open())
    {
        Color::Modifier def(Color::FG_DEFAULT);
        Color::Modifier blue(Color::FG_BLUE);

        cout << blue << "Arquivo "<< my_file_name+".src" <<" Encontrado"  << def <<endl;
    }
    else
    {
        Color::Modifier def(Color::FG_DEFAULT);
        Color::Modifier red(Color::FG_RED);

        cout << red << "Arquivo "<< my_file_name+".src Nao Encontrado"  << def <<endl;
        exit(EXIT_FAILURE);
    }

    while(myfile_src.peek() != EOF)
    {
        str_src << (char) myfile_src.get();
    }
    myfile_src.close();
    myfile_src_string = str_src.str();
    
    //Read Dat File
    myfile_dat.open(my_file_name+".dat");
    
    //Check if exists
    if(myfile_dat.is_open())
    {
        Color::Modifier def(Color::FG_DEFAULT);
        Color::Modifier blue(Color::FG_BLUE);

        cout << blue << "Arquivo "<< my_file_name+".dat" <<" Encontrado"  << def <<endl;
    }
    else
    {
        Color::Modifier def(Color::FG_DEFAULT);
        Color::Modifier red(Color::FG_RED);

        cout << red << "Arquivo "<< my_file_name+".dat Nao Encontrado"  << def <<endl;
        exit(EXIT_FAILURE);
    }

    while(myfile_dat.peek() != EOF)
    {
        str_dat << (char) myfile_dat.get();
    }
    myfile_dat.close();
    myfile_dat_string = str_dat.str();


    //Exit
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier blue(Color::FG_BLUE);

    cout << blue << "Parse SRC OK"  << def <<endl;
    cout << blue << "Parse DAT OK"  << def <<endl;

}

void Parse::Search_and_Save_E6POS()
{
    count_points = 1;
    count_local_points = 1; 
    string e6pos = "E6POS";
    
    //Att Init

    Init = Init+receita+"_";

    vector<size_t> positions;
    size_t end_of_line;
    size_t pos = myfile_dat_string.find(e6pos);
    
    //Start Dat File
    myfile_dat_string_output = "DEFDAT "+ my_file_name+"\n\n";

 
    //Search in Dat File
    while (pos != string::npos)
    {
        //Search /n
        end_of_line = myfile_dat_string.find('}', pos);
        pos = myfile_dat_string.find('=', pos);

        if (count_local_points==1)   //Write App1
        {           
            if (store_Three_Zs){
                sZ1 = Search_Z(pos, 0);
            }
            else{
                Search_Z(pos, count_local_points);
            }
            
            myfile_dat_string_output = myfile_dat_string_output+ "E6POS " + Init+to_string(count_points)+"_"+App_End_1+myfile_dat_string.substr(pos,end_of_line-pos+1)+"\n"; //+1 because we must include '}'
            count_local_points++;
        }
        else if(count_local_points==2) //Write App2
        {          
            if (store_Three_Zs){
                sZ2 = Search_Z(pos, 0);
            }
            else{
                Search_Z(pos, count_local_points);
            }

            myfile_dat_string_output = myfile_dat_string_output + "E6POS " + Init+to_string(count_points)+"_"+App_End_2+ myfile_dat_string.substr(pos,end_of_line-pos+1)+"\n";  //+1 because we must include '}'
            count_local_points++;
        }
        else if(count_local_points==3) //Write Place
        {
            if (store_Three_Zs){
                store_Three_Zs=false;
                sZ3 = Search_Z(pos, 0);
            }
            else{
                Search_Z(pos, count_local_points);
            }           
            
            myfile_dat_string_output = myfile_dat_string_output + "E6POS " + Init+to_string(count_points)+"_"+Place+ myfile_dat_string.substr(pos,end_of_line-pos+1)+"\n";  //+1 because we must include '}'
            count_local_points=1;
            count_points++;
        }
        

        positions.push_back(pos);
        pos = myfile_dat_string.find(e6pos, end_of_line);
    }
    
    //End Dat File
    myfile_dat_string_output = myfile_dat_string_output + "\nENDDAT\n";
    

    //Exit
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT);
    cout << blue << "Search Finished" << def <<endl;
}

string Parse::Search_Z(size_t position, int movement)
{
    //Found ,Z
    int pos_start_Z = myfile_dat_string.find(",Z", position)+2;

    //Found end of Z
    int pos_end_Z = myfile_dat_string.find(',', pos_start_Z);

    if (movement==1){
        myfile_dat_string.replace(pos_start_Z, pos_end_Z-pos_start_Z, sZ1);
    }
    else if (movement==2){
        myfile_dat_string.replace(pos_start_Z, pos_end_Z-pos_start_Z, sZ2);
    }
    else if (movement==3){
        myfile_dat_string.replace(pos_start_Z, pos_end_Z-pos_start_Z, sZ3);
    }

    return myfile_dat_string.substr(pos_start_Z, pos_end_Z-pos_start_Z);
}

void Parse::Search_and_Save_SRC()
{
    //Start SRC File
    int count_points = 0;

    size_t pos = myfile_src_string.find("CONTINUE"); //Initial position to search
    size_t start_line = 0 ;
    size_t end_line = 0;

    string line;

    myfile_src_string_output =  "DEF "+ my_file_name+"()\n\n";

    start_line = pos;   //Define first Start Line

    while (end_line != string::npos)
    {
        end_line = myfile_src_string.find('\n', start_line);
        line = myfile_src_string.substr(start_line, end_line+1 - start_line);
        
        start_line = end_line+1;
        pos = end_line;

        bool variable_not_found;

        variable_not_found = Search_Variables(line);

        if(variable_not_found==true && mount_matrix==true)
        {
            count_points++;
            mount_matrix=false;
            
            myfile_src_string_output = myfile_src_string_output + Print_Matrix(count_points) + "\n";
        }

    }


    //End SRC File
    myfile_src_string_output = myfile_src_string_output + "\nEND\n";
}

string Parse::Print_Matrix(int count_pto)
{
    string local_string;

    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"]."+IndexacaoVH+" ="+IndexacaoVH_val+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"]."+NumCaixas+" ="+NumCaixas_val+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"]."+ConfGarraPick+" ="+ConfGarraPick_val+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"]."+PickOp+" ="+PickOp_val+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"]."+FechaGarraOp+" ="+FechaGarraOp_val+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"]."+AbreGarraOp+" ="+AbreGarraOp_val+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"]."+SkipGoHome+" ="+SkipGoHome_val+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"]."+SkipSobeRelativo+" ="+SkipSobeRelativo_val+'\n';
    //local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"]."+PlacePos+" ="+PlacePos_val+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"].X"+App_End_1+" = "+Init+to_string(count_pto)+"_"+App_End_1+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"].X"+App_End_2+" = "+Init+to_string(count_pto)+"_"+App_End_2+'\n';
    local_string = local_string+name_matrix+"["+sufix_prod+"_"+receita+","+to_string(count_pto)+"].X"+Place+" = "+Init+to_string(count_pto)+"_"+Place+'\n';

    return local_string;

}

void Parse::Define_Default_Values()
{
    IndexacaoVH_val = "FALSE";
    NumCaixas_val = "0";
    ConfGarraPick_val = "0";
    PickOp_val = "0";
    FechaGarraOp_val = "0";
    AbreGarraOp_val = "0";
    SkipGoHome_val = "FALSE";
    SkipSobeRelativo_val = "FALSE";
    PlacePos_val = "0";

}

void Parse::Store_Last_Values()
{
    IndexacaoVH_val = "FALSE";
    NumCaixas_val = "0";
    ConfGarraPick_val = "0";
    PickOp_val = "0";
    FechaGarraOp_val = "0";
    AbreGarraOp_val = "0";
    SkipGoHome_val = "FALSE";
    SkipSobeRelativo_val = "FALSE";
    PlacePos_val = "0";

}

bool Parse::Search_Variables(string line) //Almost a getline
{
    size_t pos;
    bool variable_not_found = true;
    size_t start_string = 0;
    size_t end_string = 0;

    //Search IndexacaoVH
    pos = line.find(IndexacaoVH);
    
    if(pos!=string::npos)
    {
        start_string = line.find('=')+1;
        end_string = line.find('\n',start_string);
        
        IndexacaoVH_val = line.substr(start_string, end_string-start_string);
        
        variable_not_found=false;
        mount_matrix = true;
        return variable_not_found;
    }
    else
    {
        variable_not_found=true;
    }

    //Search NumCaixas
    pos = line.find(NumCaixas);
    if(pos!=string::npos)
    {
        start_string = line.find('=')+1;
        end_string = line.find('\n',start_string);
        
        NumCaixas_val = line.substr(start_string, end_string-start_string);
        
        variable_not_found=false;
        mount_matrix = true;
        return variable_not_found;
    }
    else
    {
        variable_not_found=true;
    }


    //Search ConfGarraPick
    pos = line.find(ConfGarraPick);
    if(pos!=string::npos)
    {
        start_string = line.find('=')+1;
        end_string = line.find('\n',start_string);
        
        ConfGarraPick_val = line.substr(start_string, end_string-start_string);
        
        variable_not_found=false;
        mount_matrix = true;
        return variable_not_found;
    }
    else
    {
        variable_not_found=true;
    }
    
    //Search PickOp
    pos = line.find(PickOp);
    if(pos!=string::npos)
    {
        start_string = line.find('=')+1;
        end_string = line.find('\n',start_string);
        
        PickOp_val = line.substr(start_string, end_string-start_string);
        
        variable_not_found=false;
        mount_matrix = true;
        return variable_not_found;
    }
    else
    {
        variable_not_found=true;
    }
    
    //Search FechaGarraOp
    pos = line.find(FechaGarraOp);
    if(pos!=string::npos)
    {
        start_string = line.find('=')+1;
        end_string = line.find('\n',start_string);
        
        FechaGarraOp_val = line.substr(start_string, end_string-start_string);
        
        variable_not_found=false;
        mount_matrix = true;
        return variable_not_found;
    }
    else
    {
        variable_not_found=true;
    }
    
    //Search AbreGarraOp
    pos = line.find(AbreGarraOp);
    if(pos!=string::npos)
    {
        pos = line.find("()"); //Check if we found a function
        if(pos==string::npos)
        {
            start_string = line.find('=')+1;
            end_string = line.find('\n',start_string);
            
            AbreGarraOp_val = line.substr(start_string, end_string-start_string);
            
            variable_not_found=false;
            mount_matrix = true;
            return variable_not_found;
        }
    }
    else
    {
        variable_not_found=true;
    }
    
    //Search SkipGoHome
    pos = line.find(SkipGoHome);
    if(pos!=string::npos)
    {
        start_string = line.find('=')+1;
        end_string = line.find('\n',start_string);
        
        SkipGoHome_val = line.substr(start_string, end_string-start_string);
        
        variable_not_found=false;
        mount_matrix = true;
        return variable_not_found;
    }
    else
    {
        variable_not_found=true;
    }
    
    //Search SkipSobeRelativo
    pos = line.find(SkipSobeRelativo);
    if(pos!=string::npos)
    {
        start_string = line.find('=')+1;
        end_string = line.find('\n',start_string);
        
        SkipSobeRelativo_val = line.substr(start_string, end_string-start_string);

        variable_not_found=false;
        mount_matrix = true;
        return variable_not_found;
    }
    else
    {
        variable_not_found=true;
    }
    
    //Search PlacePos
    //pos = line.find(PlacePos);
    //if(pos!=string::npos)
    //{
    //    start_string = line.find('=')+1;
    //    end_string = line.find('\n',start_string);
    //    
    //    PlacePos_val = line.substr(start_string, end_string-start_string);
    //    
    //    variable_not_found=false;
    //    mount_matrix = true;
    //    return variable_not_found;
    //
    //}
    //else
    //{
    //    variable_not_found=true;
    //}

    return variable_not_found;
}

void Parse::Save_Outputs_E6POS()
{
    ofstream out(my_file_name+"E6POS.dat");
    out << myfile_dat_string_output;
    out.close();
    
    //Exit
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT);
    cout << blue << "Save DAT OK" << def <<endl;
}

void Parse::Save_Outputs_SRC()
{
    ofstream out(my_file_name+"_Trans.src");
    out << myfile_src_string_output;
    out.close();
    
    //Exit
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier def(Color::FG_DEFAULT);
    cout << blue << "Save SRC OK" << def <<endl;
}

void Parse::initialCheck(int argc, char** argv)
{
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier blue(Color::FG_BLUE);
    string my_str;
    if (argc==2)
    {
        cout << red << "Necessario 2 entradas (argumentos) para executar o programa."  << def <<endl;
        exit(EXIT_FAILURE);
    }
    else if(argc==3){
        cout << blue << "Quantidade de arquivos OK!"  << def <<endl;
        cout << "Arquivo a ser lido: " << argv[1] << ".dat e "<< argv[1]<< ".src " <<  endl;
        my_file_name = argv[1];
        receita = argv[2];
    }
    else
    {
        cout << red << "Necessario 2 entradas (argumentos) para executar o programa. Verificar a chamada do programa, pois foram passados mais do que 1 arquivo."  << def <<endl;
        exit(EXIT_FAILURE);
    }
}

void Parse::call()      
{   
    readFile();
    
    Search_and_Save_E6POS();
    Search_and_Save_SRC();
    
    Save_Outputs_E6POS();
    Save_Outputs_SRC();

    //Exit
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier blue(Color::FG_BLUE);
    cout << blue << "Parse Finished!!"<< def << endl;
}