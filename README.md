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


##





