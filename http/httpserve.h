#include "../Cmdoule.h"
#include "httpheader.h"


class chamber:public Header
{
public:
    chamber();
    chamber(int p);
    int SocketInit(const int port);
    void init();
    int run();

private:
    int ChPort;
    int sock;
    int confd;
    char *json;
    std::vector<std::string> t;

};

//构造函数传入端口号
chamber::chamber(int p) {
    init();
    ChPort=p;
    sock= this->SocketInit(ChPort);
}
//socket初始化
int chamber::SocketInit(const int port) {
    int sock1;
    struct sockaddr_in sever_address;
    bzero(&sever_address,sizeof(sever_address));
    sever_address.sin_family = PF_INET;
    sever_address.sin_addr.s_addr = htons(INADDR_ANY);
    sever_address.sin_port = htons(port);

    sock1 = socket(AF_INET,SOCK_STREAM,0);

    assert(sock1>=0);

    int ret = bind(sock1, (struct sockaddr*)&sever_address,sizeof(sever_address));
    assert(ret != -1);

    ret = listen(sock1,1);
    assert(ret != -1);
    return sock1;
}

//socket运行
int chamber::run() {
    while(1)
    {
        struct sockaddr_in client;
        socklen_t client_addrlength = sizeof(client);
        confd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
        if(confd < 0)
        {
            printf("errno\n");
        }
        else{
            char request[1024];
            recv(confd, request, 1024, 0);
            request[strlen(request)+1]='\0';
            SerializationHeader(request);
            //printf("%s\n",request);
            //std::cout<<HttpRequestWay<<std::endl<<Http<<std::endl;
            std::string st= Json(JsonInit(t));
            //std::string http=init();
            char *Hea= StrChangeChar(initHeader()+st,1024);
            int s = send(confd, Hea, strlen(Hea), 0);//发送响应
            //printf("send=%d\n",s);
            close(confd);
        }
    }
}

void chamber::init() {
    t.push_back("test1");
    t.push_back("test2");
    t.push_back("test3");
    t.push_back("test4");
}
