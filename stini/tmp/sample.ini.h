#include "stini.hpp"

struct IniSectionA
{
    int keya;
    int keyb;
    int keyc;

    END_INI_KEY;
    END_INI_STRUCT(IniSectionA);
};

struct IniSectionB
{
    std::string keya;
    std::string keyb;
    std::string keyc;

    END_INI_KEY;
    END_INI_STRUCT(IniSectionB);
};

struct SIni
{
    IniSectionA SectionA;
    IniSectionB SectionB;

    END_INI_KEY;
    END_INI_STRUCT(SIni);
};

struct PSIni
{
    IniSectionA* SectionA;
    IniSectionB* SectionB;

    END_INI_KEY;
    END_INI_STRUCT(PSIni);
};
