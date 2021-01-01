#include "sttable.h"

bool table_base::insert(std::string& strSql)
{
    sql::table_meta_base* pTmeta = getTableMeta();
    const std::string& strTableName = pTmeta->name();

    strSql.clear();
    strSql += ("INSERT INTO ");
    strSql += strTableName;
    strSql += " SET ";

    int iCount = 0;
    const sql::table_meta_base::FieldListT& vecFmeta = pTmeta->fields();
    sql::table_meta_base::FieldListT::const_iterator it = vecFmeta.begin();
    while (it != vecFmeta.end())
    {
        sql::field_meta_base* pFmeta = *it;
        const std::string& strFieldName = pFmeta->name();
        std::string strFieldValue;
        pFmeta->decode_to_string(strFieldValue, this);
        if (iCount > 0)
        {
            strSql += ", ";
        }
        strSql += strFieldName;
        strSql += " = ";
        strSql += strFieldValue;

        ++iCount;
        ++it;
    }

    strSql += ";";
    return true;
}

std::string table_base::insert()
{
    std::string strSql;
    insert(strSql);
    return strSql;
}
