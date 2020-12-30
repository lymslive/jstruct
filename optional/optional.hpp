#ifndef OPTIONAL_HPP__
#define OPTIONAL_HPP__
#include <string>
#include <iostream>

// fake std::optional<T> in C++17 for berfore C++11
// only for scalar value: int/double/string etc
template <typename T, bool ZERO = false>
class optional
{
public:
    typedef T valueType;
    typedef optional selfType;

    optional()
    {
        reset();
    } 
    optional(const T& val) : m_val(val), m_has(true) {}
    optional(const selfType& that)
    {
        m_val = that.m_val;
        m_has = that.m_has;
    }
    selfType& operator=(const selfType& that)
    {
        if (this != &that)
        {
            m_val = that.m_val;
            m_has = true;
        }
        return *this;
    }
    selfType& operator=(const valueType& val)
    {
        m_val = val;
        m_has = true;
        return *this;
    }

    T& value()
    {
        return m_val;
    }
    const T& value() const
    {
        return m_val;
    }
    operator T() const
    {
        return m_val;
    }
    T value_or(const T& defVal) const
    {
        if (m_has)
        {
            return m_val;
        }
        else
        {
            return defVal;
        }
    }

    const T& get() const
    {
        return m_val;
    }
    const T& get(const T& defVal) const
    {
        if (m_has)
        {
            return m_val;
        }
        else
        {
            return defVal;
        }
    }
    T& set(const T* pVal = nullptr)
    {
        if (nullptr != pVal)
        {
            m_val = *pVal;
        }
        return m_val;
    }
    T& set(const T& val)
    {
        m_val = val;
        return m_val;
    }

    bool has_value() const
    {
        return m_has;
    }
    bool valid() const
    {
        return m_has;
    }
    bool invalid() const
    {
        return !m_has;
    }
#if 0
    operator bool() const
    {
        return has_value();
    }
#endif

    void reset()
    {
        m_has = false;
        if (ZERO)
        {
            m_val = T(0);
        }
    }
    void clear()
    {
        reset();
    }

private:
    T    m_val;
    bool m_has;
};

template <typename T, bool ZERO>
std::ostream& operator<<(std::ostream &out, const optional<T, ZERO>& op)
{
    out << op.value();
    return out;
}

typedef optional<int, true> Int;
typedef optional<double, true> Double;
typedef optional<std::string> String;
#endif /* end of include guard: OPTIONAL_HPP__ */
