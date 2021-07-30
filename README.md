# rainbow

## 开发环境

Ubuntu

gcc

cmake

## 项目目录

- bin --> 二进制
- Makefile 
- rainbow --> 源代码路径
- tests --> 测试代码路径

## 日志系统
```
Log4J

Logger（定义日志类别）
  |
  |-------------Formatter（日志格式）
  |
Appender（日志输出的地方）
```

## 配置系统

Config --> Yaml

```cpp
YAML::Node node = YAML::LoadFile(filename);
node.IsMap()
for (auto it = node.begin(); it != node.end(); ++it) {

}

node.IsSequence()
for (size_t i = 0; i < node.size(); ++i) {

}

node.IsScalar()
```

配置系统的原则：约定优于配置

```cpp
template<T, FromStr, ToStr>
class ConfigVar;

template<F, T>
LexicalCast;
```

//容器序列化
//支持 vector, list, set, map, unordered_set, unordered_map
//map/unordered_map 支持 key = std::string

自定义类型，需要实现rainbow::LexicalCast，片特化

实现后，就可以支持Config解析自定义类型，自定义类型可以和常规STL容器一起使用。

一个复杂的类型可以嵌套的很深。


##






