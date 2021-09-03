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

## 各模块之间的关系

![](../img/img1.png)

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

Config, RMutex

## 协程库的封装

定义协程接口

ucontext_t的主要用法

macro

```
Thread->main_fiber <-----> sub_fiber
            |
            |
            |
        sub_fiber

每一个线程都会有一个主协程 Fiber::GetThis()
swapIn 可以将主协程挂起，切换到子协程中
swapOut 可以将子协程挂起，切换到主协程中
yield 可以唤醒主协程
```
主协程可以创建协程并且可以调度协程

子协程只能执行完之后，让出执行权回到主协程，然后再由主协程调度其他的子协程

子协程不能够再次创建子协程（简单模型，为什么？）

协程的初始化、swapIn、swapOut

遗留问题：怎么解决最后一个没有析构的协程?

每个线程的第一个协程是主协程，可以在主协程和子协程之间切换，不能由子协程直接切换到另外一个子协程。

完成了简单的线程模块

下一章将介绍，使用调度器来控制要执行的协程————协程的调度

## 协程调度模块 Scheduler

通过之前的几次课程，已经完成了一个服务器的一些基本的功能，但是这些功能还达不到一个高性能服务器的要求

接下来需要实现协程在不同的线程之间切换

```
        1 --> N    1 --> M
scheduler --> thread --> fiber

N : M

1. scheduler 是一个线程池，分配一组线程
2. 协程调度器，将线程，指定到相应的线程上去执行

```
实现一个子类来支持epoll

m_thread

<function<void()>, fiber, threadid> m_fibers;

schedule(func/fiber)

start()

stop()
 
run()

2021-08-10 10:16:39

```
1. 设置当前线程的scheduler
2. 设置当前线程的run，fiber
3. 协程调度循环 while(true)
    1. 协程消息队列里面是否有任务
    2. 无任务，执行idle
```

## IO协程调度器

根据之前的 Scheduler 实现异步调度,底层使用 epoll 来实现

基于epoll的 IO 协程调度

```
IOManager(epoll) ---> Scheduler
        |
        |
      idle(epoll_wait)


      信号量
PutMessage(msg, ) + 信号量 1, single()
message_queue
        |
        |----- Thread
        |----- Thread
            wait() - 信号量1,RecvMessage(msg, )

异步IO,等待数据返回.epoll_wait

epoll_create, epoll_ctl, epoll_wait

通过文件句柄可以得知是否有信号到来,如果有信号到来的话就会唤醒 epoll_wait
```

```
Timer -> addTimer() --> cancel()
获取当前定时器触发离现在的时间差
返回当前需要触发的定时器

循环定时, 间隔定时
```


```
            [Fiber]              [Timer]
               ^                    ^ 
               |                    |
               |                    |
            [Thread]         [TimerManager]
               ^ M                  ^
               |                    |
               |                    |
               | 1                  |
          [Scheduler] <---- [IOManager(epoll)]

```

## Socket IO Hook

系统中的某些库是同步的，我们可以采用 Hook IO 的方式使其变为异步的

Hook 的主要目的是为了让同步的 I/O 转变为异步的I/O

```
sleep,

usleep

读操作

写操作

socket 相关的(socket, connect, accept)
io 相关 (read, write, send, recv)
fd 相关 (fcntl, ioctl, ...)

```

fd_manager 文件句柄识别类

## socket 函数库

            
              [UnixAddress]
                    |
                ---------                     |---[IPv4Address]
                |Address| --- [IPAddress] --- |
                ---------                     |---[IPv6Address]
                    |
                ----------
                | Socket |
                ----------

socket 封装

connect, accept, read, write, close

## 序列化 ByteArray

网络编程会涉及到数据传递,数据传递会涉及到序列化和反序列化

write(int, float, int64, ...)

read(int, float, int64, ...)

socket 封装的时候有 sendmsg 和 readmsg 用的是 iovec 结构体

将 ByteArray 中的可读的数据转成 iovec 方式供 socket 使用

将 ByteArray 中分配的内存也转成 iovec 方式供 socket 往里面填充


## HTTP 协议开发

HTTP/1.1 - API

HttpRequest

HttpResponse

```
GET /dashboard/ HTTP/1.1
host: 192.168.80.1

HTTP/1.1 200 OK
Date: Fri, 27 Aug 2021 06:57:05 GMT
Server: Apache/2.4.48 (Win64) OpenSSL/1.1.1k PHP/7.4.20
Last-Modified: Thu, 27 Aug 2015 09:52:42 GMT
ETag: "1af0-51e47eda3ce80"
Accept-Ranges: bytes
Content-Length: 6896
Content-Type: text/html
-----------------------------------------

utl: http://www.xxxx.top:80/page/xxx?id=10&v=20#fr

http,           协议
www.xxxx.top,   host
80,             端口
/page/xxx,      path
id=10&v=20,     param
fr,             fragment

```

封装了 HTTP request 相关的方法

封装了 HTTP response 相关的方法

协议解析

ragel mongerl2

TcpServer封装,

基于TcpServer实现了一个EchoServer

### Stream 封装

针对文件/socket封装

read/write/readFixSize/writeFixSize

### HttpSession 封装

HttpSession / HttpConnection

接收端

Server.accept, socket -> session

请求端

client connect socket -> Connection

HttpServer : TcpServer

### Servlet

```
        Servlet <---- FunctionServlet
          |
          |
          V
     ServletDispatch
```

有限状态机解析 uri

针对 HttpConnect 设计一个连接池

减少链接创建带来的开销
