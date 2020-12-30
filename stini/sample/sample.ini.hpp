#include "../stini.hpp"

struct IniSectionA
{
    int keya;
    int keyb;
    int keyc;

    END_INI_KEY;

    template <typename mapType>
    void ReadIni(const mapType& iniMap)
    {
        READ_INI_KEY(keya, iniMap);
        READ_INI_KEY(keyb, iniMap);
        READ_INI_KEY(keyc, iniMap);
    }
};

struct IniSectionB
{
    std::string keya;
    std::string keyb;
    std::string keyc;

    END_INI_KEY;

    template <typename mapType>
    void ReadIni(const mapType& iniMap)
    {
        READ_INI_KEY(keya, iniMap);
        READ_INI_KEY(keyb, iniMap);
        READ_INI_KEY(keyc, iniMap);
    }
};

struct SIni
{
    IniSectionA SectionA;
    IniSectionB SectionB;

    END_INI_KEY;

    template <typename mapType>
    void ReadIni(const mapType& iniMap)
    {
        READ_INI_KEY(SectionA, iniMap);
        READ_INI_KEY(SectionB, iniMap);
    }
};

struct PSIni
{
    IniSectionA* SectionA;
    IniSectionB* SectionB;

    END_INI_KEY;

    PSIni()
    {
        SectionA = nullptr;
        SectionB = nullptr;
    }

    ~PSIni()
    {
        delete SectionA;
        delete SectionB;
    }

    template <typename mapType>
    void ReadIni(const mapType& iniMap)
    {
        READ_INI_KEY(SectionA, iniMap);
        READ_INI_KEY(SectionB, iniMap);
    }
};
