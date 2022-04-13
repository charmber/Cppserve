



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

### 支持路由分发功能

通过router对象调用AddUrl方法即可添加不同路由对应处理的业务逻辑函数

### 增加线程池功能：

可选择是否使用多线程功能，在创建路由函数时候传入创建线程对象
多线程使用了一个线程池进行管理，实现了一个任务队列对任务进行处理
明显提高了io请求的并发能力，

### 增加epoll多路复用-边缘(ET)非阻塞模式

### 性能测试结果

![img.png](./res/img.png)
在并发量为800的情况下也能稳定全部请求成功，并且每分钟可以接收10万以上请求

#### 路由相关api
实现类为router，
例如添加一个http请求：
```c++
//添加GET请求
    router.Get("index",test);   //第二个参数即为调用接口
//添加POST请求
    router.POST("login",login);
```

然后即可启动一个服务：
```c++
//创建一个服务对象，传入需要开启的端口号，调用run即可
int main()
{
    chamber c(8080);
    c.run();
    return 0;
}
```
如果需要开启多线程则需要调用路由对象方法以及创建线程池对象
```c++
int main()
{
    ThreadPool pool(8);     //选择需要开启的最大线程数量，默认为4个
    pool.init();
    router.StartThreadPool(&pool);
    RouterManage();
    chamber c(8080);
    c.run();
    return 0;
}
```

调用接口函数响应时候则可以
```c++
//传入一个Header对象，封装json成字符串传入SendRequestHeader，以及选择响应状态码即可
void test(Header hea){
    ChJson te;
    te["测试"]="成功";
    te["测试2"]="哈哈哈";
    std::string st= Json(te);
    hea.SendRequestHeader(200,st);
}
```