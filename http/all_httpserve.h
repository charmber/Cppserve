#include "./router/router.h"


class chamber
{
public:
    chamber(int p);
    void init();
    int run();


private:
    //分界线
    int Port=8080;         //端口号
    static Router* router;
    std::vector<std::string> t;

};
chamber::chamber(int p) {
    Port=p;
}

//socket运行
int chamber::run() {

    while (1) {

    }

}

void chamber::init() {
    t.push_back("test1");
    t.push_back("test2");
    t.push_back("test3");
    t.push_back("test4");
}
