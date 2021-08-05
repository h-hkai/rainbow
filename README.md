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


配置的事件机制

当一个配置项发生修改的时候，可以反向通知对应的代码，回调

## 日志系统整合配置系统

```cpp
logs:
    - name: root
      level: (debug, info, warn, error, fatal)
      formatter: '%d%T%p%T%t%m%n'
      appender:
        - type: (StdoutLogApender, FileLogAppender)
          level: (debug, ...)
          file: /logs/xxx.log
```

```cpp
    rainbow::Logger g_logger = 
        rainbow::LoggerMgr::GetInstance()->getLogger(name);
    RAINBOW_LOG_INFO(g_logger) << "xxx log";

    怎么将日志写到我们定义的日志里面去？
```

```cpp
保证 logger 的唯一性
static Logger::ptr g_log = RAINBOW_LOG_NAME("system");
// 如果 system 中没有东西，则返回 m_root（当 logger 的 appenders 为空时）
// 如果 system 中有东西，则返回 system （当 logger 的 appenders 不为空时）

```

```cpp
// 定义 LoggerDefine LogAppenderDefine，偏特化 LexicalCast，
// 实现日志配置解析
```

## 线程库

Thread, Mutex

互斥量 mutex

信号量 semaphore

> 为什么不使用C++提供的信号量而选择自己来实现？
> 在实际的应用中（大并发的情况下），大部分操作都会涉及到读操作，只有少部分会涉及到写操作。
> 如果能够把读写分离的话那么性能就会提高很多。

和 log 整合
Logger, Appender

Spinlock, 替换Mutex

写文件，周期性，reopen

Config,
