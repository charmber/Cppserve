#include "./router/router.h"
#include <fcntl.h>
#include<arpa/inet.h>
#include<sys/event.h>

Router router;


// 错误退出的工具函数
int quit(const char *msg){
    perror(msg);
    exit(1);
}

void setNonBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

class chamber
{
public:
    chamber(int p);
    void init();
    int run();


private:
    //分界线
    const static int FD_NUM = 2; // 两个文件描述符，分别为标准输入与输出
    const static int BUFFER_SIZE = 1024; // 缓冲区大小
    int Port=8080;         //端口号
    std::vector<std::string> t;

};
chamber::chamber(int p) {
    Port=p;
}

//socket运行
int chamber::run() {
    int  listenfd,connfd,efd,ret;
    char buf[1024];
    struct sockaddr_in cliaddr,servaddr;
    socklen_t clilen = sizeof(cliaddr);
    struct kevent tep[2],ep[1024];


    listenfd = socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(Port);
    bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(listenfd,20);
    struct kevent changes[FD_NUM];
    struct kevent events[FD_NUM];

    // 创建一个kqueue
    int kq;
//    if( (kq = kqueue()) == -1 ) quit("kqueue()");
    kq = kqueue();
    //kqueue(); 对应epoll_create


    // 设置为非阻塞
    setNonBlock(listenfd);

    // 注册监听事件
    int k = 0;
    // EV_SET代替epoll
    //tep.events = EPOLLIN;
    //tep.data.fd = connfd;
    EV_SET(&changes[k++], listenfd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, (void *) (intptr_t)listenfd);
    EV_SET(&changes[k++], listenfd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, (void *) (intptr_t)listenfd);
    kevent(kq, changes, FD_NUM, NULL, 0, NULL);//kevent 可以同时代替epoll_ctl和epoll_wait 生成的实例也就是调用epoll_ctl的时候只需要第2第3 参数 而代替epoll_wait的时候需要第4第5参数
    int nev, nread, nwrote = 0; // 发生事件的数量, 已读字节数, 已写字节数
    char buffer[BUFFER_SIZE];


    int lastActive_;
    const int kMaxEvents = 2000;
    struct kevent activeEvs_[kMaxEvents];


    while(1){
        //lastActive_ 活跃的事件数量
        lastActive_ = kevent(kq, NULL, 0, activeEvs_, kMaxEvents, NULL); // 已经就绪的文件描述符数量 epoll_wait
//        if( nev <= 0 ) quit("kevent()");

        int i;
        for(i=0; i<lastActive_; i++){
            struct kevent event = activeEvs_[i];
            if( event.flags & EV_ERROR ) quit("Event error");

            int ev_fd = (int)(intptr_t)activeEvs_[i].udata;

            if (ev_fd == listenfd )
            {
                connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
                printf("connfd=%d",connfd);
                setNonBlock(connfd);
                EV_SET(&changes[0], connfd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, (void *) (intptr_t)connfd);
                EV_SET(&changes[1], connfd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, (void *) (intptr_t)connfd);
                kevent(kq, changes, 2, NULL, 0, NULL);
            }
                // 否则,读取数据
            else
            {
                recv(ev_fd,buf,1024,0);


                //响应
                Header header;
                header.serverID=ev_fd;
                header.SerializationHeader(buf);
                router.CallRequest(header);
            }
        }
    }

}

void chamber::init() {
    t.push_back("test1");
    t.push_back("test2");
    t.push_back("test3");
    t.push_back("test4");
}
