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

**API文档将在后续版本更新**