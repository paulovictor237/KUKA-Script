#include "parse.h"

int main(int argc, char** argv) 
{
    Parse my_parse;
    my_parse.initialCheck(argc, argv);
    my_parse.call();
    return 0;
}