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
#include "pallet.h"

// &ACCESS RVO1
// &REL 3
// &PARAM EDITMASK = *
// DEF TPallet( )
//    ;DECL FRAME TBASE[5] 
//    ;DECL POS TBASE
   
//    ;fold RobRoot, Tools and Bases used
//       ; $ROBROOT = {x 0,y 0,z 0,a 0,b 0,c 0}
      
//       ;Pallet1
//       BASE_DATA[1] = {x -146.408,y -2681.991,z -822.545,a 0,b 0,c 0}
//       ;Pallet1
//       BASE_DATA[2] = {x -146.408,y 1400.659,z -837.242,a 0,b 0,c 0}

     
//       ;ESTEIRA1
//       ;AJUSTE DE BASES DO PICK
//       ;BASE_DATA[3] = {x 1273.688,y -630.658,z -549.545,a 0,b 0,c 0}
//       ;BASE_DATA[3] = {x  -90.000,y   30.000,z  -55.000,a 0,b 0,c 0}
//       BASE_DATA[3] = {x 1183.688,y -600.658,z -604.545,a 0,b 0,c 0}
      
//       ;ESTEIRA2
//       ;AJUSTE DE BASES DO PICK
//       ;BASE_DATA[4] = {x 1273.688,y 616.142,z -554.945,a 0,b 0,c 0}
//       ;BASE_DATA[4] = {x  -90.000,y  34.000,z  -55.000,a 0,b 0,c 0}
//       BASE_DATA[4] = {x 1183.688,y 650.142,z -609.945,a 0,b 0,c 0}
      
//       ;GlobalTool
//       TOOL_DATA[1] = {x 0,y 0,z 0,a -90,b 0,c 0}
//    ;endfold
   
//    ;FOLD Iniciar Opcoes de Pallet e esteira
//       StrPallet[1].BasePoint=BASE_DATA[1]
//       StrPallet[2].BasePoint=BASE_DATA[2]
//       BaseEsteira1 = BASE_DATA[3]
//       BaseEsteira2 = BASE_DATA[4]
//    ;ENDFOLD
   
//    ;FOLD OffSetPallet
//       StrPallet[1].OffSetPallet.X=130
//       StrPallet[1].OffSetPallet.Y=80
//       StrPallet[1].OffSetPallet.Z=-55
//       StrPallet[1].OffSetPallet.A=0
//       StrPallet[1].OffSetPallet.B=0
//       StrPallet[1].OffSetPallet.C=0
      
//       StrPallet[2].OffSetPallet.X=0
//       StrPallet[2].OffSetPallet.Y=0
//       StrPallet[2].OffSetPallet.Z=60
//       StrPallet[2].OffSetPallet.A=0
//       StrPallet[2].OffSetPallet.B=0
//       StrPallet[2].OffSetPallet.C=0
//    ;ENDFOLD
   
//    ;FOLD OffsetEsteira
//       OffsetEsteira1.X=0
//       OffsetEsteira1.Y=0
//       OffsetEsteira1.Z=0
//       OffsetEsteira1.A=0
//       OffsetEsteira1.B=0
//       OffsetEsteira1.C=0
      
//       OffsetEsteira2.X=0
//       OffsetEsteira2.Y=0
//       OffsetEsteira2.Z=0
//       OffsetEsteira2.A=0
//       OffsetEsteira2.B=0
//       OffsetEsteira2.C=0
//    ;ENDFOLD
   
// END