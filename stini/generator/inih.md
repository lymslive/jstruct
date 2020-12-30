# inih.pl ʹ��˵��

�ýű���һ�� ini �����ļ�ת����ӳ��� cpp �ṹ�嶨��ͷ�ļ���
�����ɵ� .h ͷ�ļ������� inic.pl �ű�����Ϊ .hpp ʵ���ļ���
�ʸýű��������ʽ��ο� inic.pl �����˵����

```bash
$ ./inih.pl sample.ini
$ ./inih.pl sample.ini | ./inic.pl
$ cat sample.ini | ./inih.pl | ./inic.pl
$ cat sample.ini | ./inih.pl | ./inic.pl > sample.ini.hpp
```

�������ýű��� .ini ���� .h �� .hpp �ļ������ֶ�������д .h �� .hpp Ҳ�Ǽ�
���ġ�

�ؼ��㣺

* `[SectionName]` ÿ��������һ�� struct ����������ǰ׺ `Se` ���� `struct
  SeSectionName`
* `key = val` ÿ����ֵ��������Ϊ�ö� struct �µ�һ����Ա�������͸��� val ����
  ��ƥ���趨Ϊ int/double/string ��������һ��Ĭ���� string ���� val ����Ϊ�ó�
  Ա��Ĭ�ϳ�ʼֵ��
* ���Ϊ���� ini ����һ�� root struct ��������Ĭ��Ϊ `StIni` �����Ա����֮ǰ
  Ϊ�����ζ��� struct �����ͣ���Ա�����Ƕ����֡�

ע��㣺

* ini ��������������Ч�ı�ʶ�������� C++ �ؼ��ֳ�ͻ��
* ��ֵ�����ַ�������������ţ�ת C++ �ĳ�Ա��ֵʱ���˫���ţ���δ�����ܸ��ӵ�
  ת�塣���ַ���ֵ�������������� `"` ��б�� `\` ��Щ��
* �ű���ͷ������ȫ�ֳ������ã����޸�һЩĬ����Ϊ��

Ϊ���ٶ� perl ģ�������������ò���ͨ�������������롣���廷��������Ĭ��ֵ���£�

* `INIH_LIBSTINI` �����������Ŀ� "stini.hpp"
* `INIH_OHPPFILE` ������û�ͷ�ļ� "config.ini.hpp" (������ͷ�ļ�������)
* `INIH_INDENT`   �����ַ���4 �ո�
* `INIH_ENDMACRO` �����չ�� `END_INI_KEY`
* `INIH_STRTYPE`  �ַ������� `std::string`
* `INIH_INIROOT`  ��ʾ���� ini �ĸ���������`StIni`
* `INIH_SECPREFIX`  ��������ǰ׺ `Se`
* `INIH_SECPOINTER` �Ƿ�ÿ�α�ʾ��ָ��
