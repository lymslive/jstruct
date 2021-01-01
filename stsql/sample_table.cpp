#include "sample_table.h"

struct table_sample_meta_builder : public sql::table_meta_builder<table_sample>
{
    table_sample_meta_builder()
    {
        table_sample sample;
        // sql::table_meta_base* pMeta = sql::table_meta<table_sample>::getInstance();
        sql::table_meta_base* pMeta = sample.getTableMeta();
        pMeta->setName("table_sample");
        pMeta->addField(sample.id, "id", MEMBER_OFFSET_OF(table_sample, id));
        pMeta->addField(sample.content, "content", MEMBER_OFFSET_OF(table_sample, content));
        pMeta->addField(sample.createTime, "createTime", MEMBER_OFFSET_OF(table_sample, createTime));
    }
} s_table_sample_meta_built;

// static table_sample_meta_builder s_table_sample_meta_built;
