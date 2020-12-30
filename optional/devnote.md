# 开发笔记

自制 `optional<T>` 提供 `oprator T()` 向与的隐式转换。
则在 `optional<int>` 与 `optional<double>` 等封装基础类型时，则在条件表达式中，
它会优先转化为 `int` 或 `double` 而非调用 `operator bool()` 

当 `optional` 封装对象如 `optional<std::string>` 时，在条件表示式中才优先转换
为 bool 。

权衡之下，只提供 `T()` 的隐式转换，不提供 `bool()` 的隐式转换。要在条件表达式
中判断有效性，调用方法 `valid()` 或 `has_value()` 

互反接口设计：

* T() 转换与构造，隐式替代使用
* get() / set() 显式取值设值
* valid() / invlid() 判断

其他操作符重载需要时另议。

bool flag 只能表示有值无值两个状态，可改用 char 表示多状态，反正也占一字节。
