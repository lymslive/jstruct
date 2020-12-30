#include "sample_gen.hpp"
#include "sample_parser.hpp"
#include <cstdio>

int main(int argc, char* agrv[])
{
    StIni ini;
    CIni parser;

    bool bRet = load_ini(ini, "sample.ini", parser);
    if (bRet)
    {
        printf("ini: SectionA.keya = %d\n", ini.SectionA->keya);
        printf("ini: SectionA.keyb = %d\n", ini.SectionA->keyb);
        printf("ini: SectionA.keyc = %d\n", ini.SectionA->keyc);
        printf("ini: SectionB.keya = %s\n", ini.SectionB->keya.c_str());
        printf("ini: SectionB.keyb = %s\n", ini.SectionB->keyb.c_str());
        printf("ini: SectionB.keyc = %s\n", ini.SectionB->keyc.c_str());
    }
    printf("\n");

    return 0;
}
