# C++web框架

### 简介

目前框架准备取名为chamber，具体功能正在逐渐完善，文档当中出现的目录均为可用接口，如有改进或者提议的地方欢迎指导

### 文件结构

```
----http        //tcp请求响应逻辑部分
	---httpheader.h
	---httpserve.h
	⌙--router
	    ---router.h
----str        //字符串以及json序列化和反序列化
	---json.h
----test       //框架测试代码
        ---controller
        ---router.cpp
        ---main.cpp
        
        
Cmdouble.h
```

**文件目录：**

- **http**：该目录为存放网络通行建立以及路由选择之类功能目录
- **router**：该目录为进行路由选择等功能处理目录
- **str**：该目录为字符串相关处理目录
- **test**：该目录为框架测试代码

**文件名：**

- **httpheader.h**:处理http请求头部以及响应解析等函数
- **httpserve.h**:处理http通信服务相关工作
- **router.h**:处理url解析等工作
- **json.h**:处理json格式序列化和反序列化操作
- **Cmdoble.h**:c++标准库头文件存放文件

<<<<<<< Updated upstream
=======

### 支持路由分发功能

通过router对象调用AddUrl方法即可添加不同路由对应处理的业务逻辑函数

>>>>>>> Stashed changes

### 增加线程池功能：

可选择是否使用多线程功能，在创建路由函数时候传入创建线程对象
多线程使用了一个线程池进行管理，实现了一个任务队列对任务进行处理
明显提高了io请求的并发能力，

<<<<<<< Updated upstream

**API文档将在后续版本更新**
=======

### 增加epoll多路复用-边缘(ET)非阻塞模式


**API文档将在后续版本更新**
