#ifndef STSQL_HPP__
#define STSQL_HPP__

#include <cstdlib>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#define MEMBER_OFFSET_OF(type, field) reinterpret_cast<size_t>(&(static_cast<type*>(0)->field))

namespace sql
{

// quote string in single ''
// todo: escape special char
inline
std::string to_string(const std::string& val)
{
    std::string out("'");
    out += val;
    out += "'";
    return out;
}

template <typename T>
std::string to_string(const T& val)
{
    std::ostringstream out;
    out << val;
    return out.str();
}

template <typename T>
struct value_encoder
{
    void encode(void* ptr, const T& val)
    {
        if (nullptr == ptr)
        {
            return;
        }
        *(reinterpret_cast<T*>(ptr)) = val;
    }

    T decode(void* ptr)
    {
        // return (nullptr == ptr) ? 0 : *(reinterpret_cast<const T*>(ptr));
        return (nullptr == ptr) ? T() : *(reinterpret_cast<const T*>(ptr));
    }

    // will fail throw when ptr is null
    T& reference(void* ptr)
    {
        return *(reinterpret_cast<T*>(ptr));
    }
};

struct field_meta_base
{
    field_meta_base() {}
    field_meta_base(const char* name, size_t offset)
    {
        _name = name;
        _offset = offset;
    }
    virtual ~field_meta_base() {}
    
    virtual void decode_to_string(std::string& dest, void* obj) = 0;

private:
    std::string _name;
    size_t _offset;

public:
    const std::string& name() { return _name; }
    size_t offset() { return _offset; }
};

template <typename fieldT>
struct field_meta : public field_meta_base, public value_encoder<fieldT>
{
    field_meta() {}
    field_meta(const char* name, size_t offset)
        : field_meta_base(name, offset)
    {}

    virtual void decode_to_string(std::string& dest, void* obj)
    {
        char* pThisBase = static_cast<char*>(obj);
        char* pThisField = pThisBase + offset();
        dest = to_string(value_encoder<fieldT>::reference(pThisField));
    }
};

enum EFieldFlag
{
    FIELD_NORMAL = 0,
    FIELD_PRIKEY = 1,
    FIELD_INDEX = 2,
    FIELD_UNIQUE = 4,
    FIELD_NOTNULL = 8,
};

struct table_meta_base
{
    table_meta_base() {}
    virtual ~table_meta_base()
    {
        size_t nField = _fields.size();
        for (size_t i = 0; i < nField; ++i)
        {
            field_meta_base* pFmeta = _fields[i];
            if (nullptr != pFmeta)
            {
                delete pFmeta;
                _fields[i] = nullptr;
            }
        }
    }

    void setName(const std::string& name)
    {
        _name = name;
    }

    template <typename fieldT>
    void addField(fieldT& field, const char* name, size_t offset, uint32_t flag = 0, const char* idx = nullptr)
    {
        field_meta<fieldT>* fmeta = new field_meta<fieldT>(name, offset);
        _fields.push_back(fmeta);
        if ((flag & FIELD_PRIKEY) != 0)
        {
            _prikey.push_back(fmeta);
        }
        if (idx != nullptr && (flag & FIELD_INDEX) != 0)
        {
            _index[idx].push_back(fmeta);
        }
    }

    typedef std::vector<field_meta_base*> FieldListT;
private:
    std::string _name;
    FieldListT _fields;
    FieldListT _prikey;
    std::map<std::string, FieldListT> _index;

public:
    const std::string& name() { return _name; }
    const FieldListT& fields() { return _fields; } 
    const FieldListT& prikey() { return _prikey; } 
};

template <typename tableT>
struct table_meta : public table_meta_base
{
    typedef tableT     tableType;
    typedef table_meta selfType;

    static table_meta_base* getInstance()
    {
        static selfType instance;
        return &instance;
    }

    tableType createRow()
    {
        tableType row;
        return row;
    }

private:
    // static selfType s_instance;
};
// template <typename tableT>
// table_meta<tableT> table_meta<tableT>::s_instance;

template <typename tableT>
struct table_meta_builder
{
};

} //< end of namespace sql

#endif /* end of include guard: STSQL_HPP__ */
