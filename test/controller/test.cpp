#include <iostream>

void test(Header hea){
    ChJson te;
    te["测试"]="成功";
    te["测试2"]="哈哈哈";
    std::string st= Json(te);
    char msg[1024];
    hea.StrChangeChar(hea.initHeader()+st,msg);
    //std::cout<<Hea<<std::endl;
    send(hea.serverID, msg, strlen(msg), 0);//发送响应
    //std::cout<<"success!:"<<hea.HttpRequestUrl<<std::endl;

    std::cout<<"关闭"<<std::endl;
        //std::lock_guard<std::mutex> tmp(sock_lock);
        //sleep(5);
        close(hea.serverID);
    eventdel(g_efd, hea.ev);                                //从红黑树g_efd中移除
}

void login(Header hea){
    ChJson te;
    te["测试"]="成功";
    std::string st= Json(te);
    char msg[1024];
    hea.StrChangeChar(hea.initHeader()+st,msg);
    send(hea.serverID, msg, strlen(msg), 0);//发送响应

        //std::lock_guard<std::mutex> tmp(sock_lock);
        close(hea.serverID);
    eventdel(g_efd, hea.ev);                                //从红黑树g_efd中移除
    //std::cout<<"login success"<<std::endl;
}
void fin(Header hea){
    //std::cout<<"查找成功"<<std::endl;
    ChJson te;
    te["查找"]="成功";
    std::string st= Json(te);
    char msg[1024];
    hea.StrChangeChar(hea.initHeader()+st,msg);
    send(hea.serverID, msg, strlen(msg), 0);//发送响应

    {
        //std::lock_guard<std::mutex> tmp(sock_lock);
        close(hea.serverID);
        eventdel(g_efd, hea.ev);                                //从红黑树g_efd中移除
    }
}