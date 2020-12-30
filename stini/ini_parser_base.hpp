#ifndef INI_PARSER_BASE_HPP__
#define INI_PARSER_BASE_HPP__

using namespace std;

// the interface describe an abstract ini parser, or an typical implement
// that fit to the templated ini struct mapping.
// a concrete ini parser can derived from the interface while not necessary,
// as minimum requirement is defined the following methods:
// get_key() and load_file()
// 
struct SectionInterface
{
    virtual const string* get_key(const string& key) = 0;
};

struct IniInterface
{
    virtual const SectionInterface* get_key(const string& key) = 0;
    virtual bool load_file(const char* file) = 0;
};

#endif /* end of include guard: INI_PARSER_BASE_HPP__ */
