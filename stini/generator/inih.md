# inih.pl 使用说明

该脚本将一个 ini 配置文件转换成映射的 cpp 结构体定义头文件。
其生成的 .h 头文件可再由 inic.pl 脚本生成为 .hpp 实现文件。
故该脚本的输出格式请参考 inic.pl 的相关说明。

```bash
$ ./inih.pl sample.ini
$ ./inih.pl sample.ini | ./inic.pl
$ cat sample.ini | ./inih.pl | ./inic.pl
$ cat sample.ini | ./inih.pl | ./inic.pl > sample.ini.hpp
```

可以利用脚本从 .ini 生成 .h 与 .hpp 文件，但手动按例子写 .h 或 .hpp 也是简
单的。

关键点：

* `[SectionName]` 每个段生成一个 struct ，类型名加前缀 `Se` ，即 `struct
  SeSectionName`
* `key = val` 每个键值对项生成为该段 struct 下的一个成员，其类型根据 val 的特
  征匹配设定为 int/double/string 这三者其一，默认是 string 。且 val 可作为该成
  员的默认初始值。
* 最后为整个 ini 定义一个 root struct ，类型名默认为 `StIni` ，其成员就是之前
  为各个段定义 struct 的类型，成员名就是段名字。

注意点：

* ini 段名键名须是有效的标识符，不与 C++ 关键字冲突。
* 键值若是字符串，不须加引号，转 C++ 的成员初值时会加双引号，但未作可能复杂的
  转义。即字符串值本身不宜再有引号 `"` 反斜杠 `\` 这些。
* 脚本开头部分有全局常量配置，可修改一些默认行为。

为减少对 perl 模块依赖，可配置参数通过环境变量传入。具体环境变量及默认值如下：

* `INIH_LIBSTINI` 需引用依赖的库 "stini.hpp"
* `INIH_OHPPFILE` 输出的用户头文件 "config.ini.hpp" (仅用于头文件保护宏)
* `INIH_INDENT`   缩进字符，4 空格
* `INIH_ENDMACRO` 标记扩展宏 `END_INI_KEY`
* `INIH_STRTYPE`  字符串类型 `std::string`
* `INIH_INIROOT`  表示整个 ini 的根类型名，`StIni`
* `INIH_SECPREFIX`  段类型名前缀 `Se`
* `INIH_SECPOINTER` 是否将每段表示成指针
