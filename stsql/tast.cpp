#include "../tast/tast_util.hpp"
#include "stsql.hpp"
#include "sample_table.h"

struct SSample
{
    char c;
    short s;
    int i;
    float f;
    double d;
};

void tast_offset()
{
    COUT(MEMBER_OFFSET_OF(SSample, c));
    COUT(MEMBER_OFFSET_OF(SSample, s));
    COUT(MEMBER_OFFSET_OF(SSample, i));
    COUT(MEMBER_OFFSET_OF(SSample, f));
    COUT(MEMBER_OFFSET_OF(SSample, d));
}

void tast_base_size()
{
    using namespace sql;

    COUT(sizeof(std::string));
    COUT(sizeof(size_t));

    COUT(sizeof(value_encoder<int>));
    COUT(sizeof(value_encoder<double>));
    COUT(sizeof(value_encoder<std::string>));

    COUT(sizeof(field_meta_base));
    COUT(sizeof(field_meta<int>));

    COUT(sizeof(table_meta_base));
    COUT(sizeof(table_meta<SSample>));
}

void tast_table_meta()
{
    table_sample st;
    st.id = 1001;
    st.content = 1234;
    st.createTime = "now()";

    sql::table_meta_base* pTmeta = st.getTableMeta();
    COUT(pTmeta->name());

    const sql::table_meta_base::FieldListT& vecFmeta = pTmeta->fields();
    sql::table_meta_base::FieldListT::const_iterator it = vecFmeta.begin();
    DESC("iterate field:");
    while (it != vecFmeta.end())
    {
        sql::field_meta_base* pFmeta = *it;
        COUT(pFmeta->name());
        COUT(pFmeta->offset());
        std::string strFieldValue;
        pFmeta->decode_to_string(strFieldValue, &st);
        COUT(strFieldValue);
        ++it;
    }
}

void tast_table_sample()
{
    table_sample st;
    st.id = 1001;
    st.content = 1234;
    st.createTime = "now()";

    std::string strSql = st.insert();
    COUT(strSql);
}

int main(int argc, char* argv[])
{
    TAST(tast_offset);
    TAST(tast_base_size);
    TAST(tast_table_meta);
    TAST(tast_table_sample);
    return 0;
}
