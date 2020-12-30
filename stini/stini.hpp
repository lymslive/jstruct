#ifndef STINI_HPP__
#define STINI_HPP__

#include <cstdlib>
#include <string>

namespace
{

using string = std::string;

// read an item in a section:
// input is common string, convert to practical value
// now support int/dobule/string
void read_ini_value(int& val, const string& str)
{
    val = atoi(str.c_str());
}

void read_ini_value(double& val, const string& str)
{
    val = atof(str.c_str());
}

void read_ini_value(string& val, const string& str)
{
    val = str;
}

// read a section, input is like map<string, string> = SectionMap
// or read root ini, input is lie map<string, SectionMap>
// Requirement: the ini struct defined ReadIni() method
template <typename valueType, typename parserType>
void read_ini_value(valueType& val, const parserType& parserMap)
{
    val.ReadIni(parserMap);
}

// the section is pointer instead of embeded member
// the ini struct deconstructor handle to delete the auto new sections
template <typename valueType, typename parserType>
void read_ini_value(valueType*& val, const parserType& parserMap)
{
    if (val == nullptr)
    {
        val = new valueType;
    }
    if (val != nullptr)
    {
        val->ReadIni(parserMap);
    }
}

// read an item or section with key name, support for macro
template <typename valueType, typename parserType>
void read_ini_value(valueType& val, const char* key, const parserType& parserMap)
{
    if (parserMap.get_key(key) != nullptr)
    {
        read_ini_value(val, *(parserMap.get_key(key)));
    }
}

}

#define READ_INI_KEY(key, parserMap) read_ini_value(key, #key, parserMap)

#define END_INI_KEY
#define END_INI_STRUCT(iniST) \
    iniST(); \
    ~iniST(); \
    template <typename mapType> void ReadIni(const parserType& parserMap);

// load the top whole ini struct, with help of another parser
template <typename iniType, typename parserType>
bool load_ini(iniType& ini, const char* file, parserType& parser)
{
    bool bRet = parser.load_file(file);
    if (bRet)
    {
        ini.ReadIni(parser);
    }
    return bRet;
}

// use pointer variable for top ini struct, auto new, but user need delete
template <typename iniType, typename parserType>
bool load_ini(iniType*& ini, const char* file, parserType& parser)
{
    if (ini == nullptr)
    {
        ini = new iniType;
    }
    if (ini != nullptr)
    {
        return load_ini(*ini, file, parser);
    }
    else
    {
        return false;
    }
}

#endif /* end of include guard: STINI_HPP__ */
