#ifndef SAMPLE_PARSER_HPP__
#define SAMPLE_PARSER_HPP__

#include <regex>
#include <fstream>
#include "../ini_parser_base.hpp"

class CSection // : public SectionInterface
{
public:
    const string* get_key(const string& key) const
    {
        auto it = m_mapItems.find(key);
        return it != m_mapItems.end()
            ? &(it->second)
            : nullptr;
    }

    void add_item(const string& key, const string& val)
    {
        m_mapItems[key] = val;
    }

private:
    map<string, string> m_mapItems;
};

class CIni // : public IniInterface
{
public:
    const CSection* get_key(const string& key) const
    {
        auto it = m_mapSections.find(key);
        return it != m_mapSections.end()
            ? &(it->second)
            : nullptr;
    }

    bool load_file(const char* file)
    {
        std::regex reEmpty("^\\s*$");
        std::regex reComment("^\\s*[#;]");
        std::regex reSection("\\[(\\w+)\\]");
        std::regex reItem("^\\s*(\\w+)\\s*=\\s*(\\w+)");

        std::ifstream in(file);
        if (!in)
        {
            return false;
        }

        CSection* pSection = nullptr;
        std::smatch matches;
        std::string line;
        std::string section;
        std::string key;
        std::string val;
        while (std::getline(in, line))
        {
            if (line.empty() || std::regex_search(line, reEmpty))
            {
                continue;
            }
            if (std::regex_search(line, reComment))
            {
                continue;
            }
            if (std::regex_search(line, matches, reSection))
            {
                section = matches[1];
                add_section(section);
                pSection = const_cast<CSection*>(get_key(section));
                if (pSection == nullptr)
                {
                    return false;
                }
            }
            else if(std::regex_search(line, matches, reItem))
            {
                key = matches[1];
                val = matches[2];
                if (!section.empty() && pSection != nullptr)
                {
                    pSection->add_item(key, val);
                }
            }
            else
            {
                // ignore
            }
        }

        return true;
    }

    void add_section(const string& section)
    {
        if (m_mapSections.find(section) == m_mapSections.end())
        {
            m_mapSections[section]; // auto insert non-existed item
        }
    }

    void add_item(const string& section, const string& key, const string& val)
    {
        m_mapSections[section].add_item(key, val);
    }

    void clear()
    {
        m_mapSections.clear();
    }
private:
    map<string, CSection> m_mapSections;
};
#endif /* end of include guard: SAMPLE_PARSER_HPP__ */
