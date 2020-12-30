#include "sample.ini.hpp"
#include "sample_parser.hpp"
#include <cstdio>

int main(int argc, char* agrv[])
{
    SIni ini;
    CIni parser;

    printf("load normal ini struct\n");
    bool bRet = load_ini(ini, "sample.ini", parser);
    if (bRet)
    {
        printf("ini: SectionA.keya = %d\n", ini.SectionA.keya);
        printf("ini: SectionA.keyb = %d\n", ini.SectionA.keyb);
        printf("ini: SectionA.keyc = %d\n", ini.SectionA.keyc);
        printf("ini: SectionB.keya = %s\n", ini.SectionB.keya.c_str());
        printf("ini: SectionB.keyb = %s\n", ini.SectionB.keyb.c_str());
        printf("ini: SectionB.keyc = %s\n", ini.SectionB.keyc.c_str());
    }
    printf("\n");

    PSIni inip;
    parser.clear();
    printf("load ini struct with optional pointer section\n");
    bRet = load_ini(inip, "sample.ini", parser);
    if (bRet)
    {
        printf("ini: SectionA.keya = %d\n", ini.SectionA.keya);
        printf("ini: SectionA.keyb = %d\n", ini.SectionA.keyb);
        printf("ini: SectionA.keyc = %d\n", ini.SectionA.keyc);
        printf("ini: SectionB.keya = %s\n", ini.SectionB.keya.c_str());
        printf("ini: SectionB.keyb = %s\n", ini.SectionB.keyb.c_str());
        printf("ini: SectionB.keyc = %s\n", ini.SectionB.keyc.c_str());
    }
    printf("\n");

    PSIni* inipp = nullptr;
    parser.clear();
    printf("load ini struct with optional pointer section, and root ini also in heap\n");
    bRet = load_ini(inipp, "sample.ini", parser);
    if (bRet && inipp)
    {
        printf("ini: SectionA.keya = %d\n", ini.SectionA.keya);
        printf("ini: SectionA.keyb = %d\n", ini.SectionA.keyb);
        printf("ini: SectionA.keyc = %d\n", ini.SectionA.keyc);
        printf("ini: SectionB.keya = %s\n", ini.SectionB.keya.c_str());
        printf("ini: SectionB.keyb = %s\n", ini.SectionB.keyb.c_str());
        printf("ini: SectionB.keyc = %s\n", ini.SectionB.keyc.c_str());
        delete inipp;
    }

    return 0;
}
