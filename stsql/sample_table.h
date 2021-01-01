#include "sttable.h"

struct table_sample : public table_base
{
    int id;
    int content;
    std::string createTime;

public:
    sql::table_meta_base* getTableMeta()
    {
        return sql::table_meta<table_sample>::getInstance();
    }
};

