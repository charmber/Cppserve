#include <iostream>

void test(Header hea){
    ChJson te;
    te["测试"]="成功";
    te["测试2"]="哈哈哈";
    std::string st= Json(te);
    char *Hea= hea.StrChangeChar(hea.initHeader()+st,1024);
    //std::cout<<Hea<<std::endl;
    send(hea.serverID, Hea, strlen(Hea), 0);//发送响应
    std::cout<<"success!:"<<hea.HttpRequestUrl<<std::endl;
    close(hea.serverID);
}

void login(Header hea){
    ChJson te;
    te["测试"]="成功";
    std::string st= Json(te);
    char *Hea= hea.StrChangeChar(hea.initHeader()+st,1024);
    send(hea.serverID, Hea, strlen(Hea), 0);//发送响应
    close(hea.serverID);
    std::cout<<"login success"<<std::endl;
}
void fin(Header hea){
    std::cout<<"查找成功"<<std::endl;
}