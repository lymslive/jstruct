#include "sample.ini.h"

IniSectionA::IniSectionA()
{
}

IniSectionA::~IniSectionA()
{
}

template <typename mapType>
void IniSectionA::ReadIni(const mapType& iniMap)
{
    READ_INI_KEY(keya, iniMap);
    READ_INI_KEY(keyb, iniMap);
    READ_INI_KEY(keyc, iniMap);
}

IniSectionB::IniSectionB()
{
}

IniSectionB::~IniSectionB()
{
}

template <typename mapType>
void IniSectionB::ReadIni(const mapType& iniMap)
{
    READ_INI_KEY(keya, iniMap);
    READ_INI_KEY(keyb, iniMap);
    READ_INI_KEY(keyc, iniMap);
}

SIni::SIni()
{
}

SIni::~SIni()
{
}

template <typename mapType>
void SIni::ReadIni(const mapType& iniMap)
{
    READ_INI_KEY(SectionA, iniMap);
    READ_INI_KEY(SectionB, iniMap);
}

PSIni::PSIni()
{
    SectionA = nullptr;
    SectionB = nullptr;
}

PSIni::~PSIni()
{
    delete SectionA;
    delete SectionB;
}

template <typename mapType>
void PSIni::ReadIni(const mapType& iniMap)
{
    READ_INI_KEY(SectionA, iniMap);
    READ_INI_KEY(SectionB, iniMap);
}
