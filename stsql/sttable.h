#ifndef STTABLE_H__
#define STTABLE_H__

#include "stsql.hpp"

struct table_base
{
    table_base() {}
    virtual ~table_base() {}
    virtual sql::table_meta_base* getTableMeta() = 0;

    std::string insert();
    bool insert(std::string& strSql);
};


#endif /* end of include guard: STTABLE_H__ */
