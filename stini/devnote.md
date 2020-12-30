# stini: ini 配置映射结构体方案

参考之前 jstruct 映射 json 的思路。ini 更简单，只有两层结构，不支持数组。

debug 踩坑：

* 模板成员函数也只能写在头文件中，可以写在类外，但不能写在另一个 cpp 文件。想
  把依赖的 ini parser 做成泛型，也就内置或代理两层 map。
* 如果约定从 parser 取某 key 的 val 为 const & ，就不能直接用 map 的 [] 操作符
  ，后者是非 const 的，可能自动插入原不存在的值至 map 。所以返回指针会更好。

目录说明：

* sample/ : 一份可执行的代码，包括 ini 样本、解析器与使用 stini.hpp 库的例和。
  + `sample_parser.hpp` 用 c++11 正则库写的简易ini解析器
  + `sample.ini.hpp` 与 `sample.ini` 映射的 cpp 结构体定义及实现一起。
* generator/ : perl 脚本，从 ini 的定义 .h 写义文件转成 .hpp 文件。
* tmp/ : 更原始的测试文件，不一定删
