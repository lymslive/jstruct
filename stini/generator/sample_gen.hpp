#ifndef CONFIG_INI_HPP__
#define CONFIG_INI_HPP__

#include "stini.hpp"

struct SeSectionA
{
    int keya;
    int keyb;
    int keyc;

    END_INI_KEY;
    SeSectionA()
    {
        keya = 1;
        keyb = 2;
        keyc = 3;
    }
    ~SeSectionA()
    {
    }
    template <typename mapType>
    void ReadIni(const mapType& iniMap)
    {
        READ_INI_KEY(keya, iniMap);
        READ_INI_KEY(keyb, iniMap);
        READ_INI_KEY(keyc, iniMap);
    }
};

struct SeSectionB
{
    std::string keya;
    std::string keyb;
    std::string keyc;

    END_INI_KEY;
    SeSectionB()
    {
        keya = "1s";
        keyb = "2s";
        keyc = "3s";
    }
    ~SeSectionB()
    {
    }
    template <typename mapType>
    void ReadIni(const mapType& iniMap)
    {
        READ_INI_KEY(keya, iniMap);
        READ_INI_KEY(keyb, iniMap);
        READ_INI_KEY(keyc, iniMap);
    }
};

struct StIni
{
    SeSectionA* SectionA;
    SeSectionB* SectionB;

    END_INI_KEY;
    StIni()
    {
        SectionA = nullptr;
        SectionB = nullptr;
    }
    ~StIni()
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

#endif
