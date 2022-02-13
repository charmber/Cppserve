#include "../Cmdoule.h"
//const std::string Hearder="HTTP/1.1 200 ok\r\ncontent-type: application/json;charset=utf-8\r\nconnection: close\r\n\r\n";
//const std::string buf="{\n\"user\":\"1234567890\",\n\"name\":\"梦\",\n\"title\":\"哈哈哈哈哈了\",\n\"news_type\":\"科技\"\n}";//HTTP响应
//字符串转换char*

//查找键值对
void FindKeyValue(std::unordered_map<std::string,std::string>&Te,std::string s,int start,std::string Key);

//查找Json
void FindJson(std::string &json,std::string s,int start);


class Header
{
public:
    std::string Http;
    std::string HttpRequestWay;
    std::string HttpRequestUrl;
    std::unordered_map<std::string,std::string> HttpUserAgent;
    std::unordered_map<std::string,std::string> HttpAccept;
    std::unordered_map<std::string,std::string> HttpConnection;
    std::unordered_map<std::string,std::string> HttpAcceptEncoding;
    std::unordered_map<std::string,std::string> HttpAcceptLanguage;
    std::unordered_map<std::string,std::string> HttpCookie;
    std::string HttpBody;
    std::string initHeader();
    char* StrChangeChar(std::string str,int len);//字符串转char类型
    std::string SendRequestHeader(int code,std::string Type);//封装响应头部
    void SerializationHeader(char res[]);//反序列化请求头

private:
    const std::string Header="HTTP/1.1 200 ok\r\n";
    const std::string ContentTypeJson="content-type: application/json;charset=utf-8\r\n";
    const std::string connection="connection: close\r\n\r\n";
};
char * Header::StrChangeChar(std::string str, int len) {
    char p[len];
    str.copy(p,str.length(),0);
    return p;
}

std::string Header::initHeader() {
    return Header+ContentTypeJson+connection;
}

std::string Header::SendRequestHeader(int code,std::string Type){
    if(Type=="json"){
        return "HTTP/1.1 "+std::to_string(code)+" "+"ok\r\n"+ContentTypeJson+connection;
    }
}


//解析请求头
void Header::SerializationHeader(char res[]) {
    int p=0;
    int start=0;
    std::string str(res);
    for(int i=0;i<str.size();i++){
        if(str[i]==' '){
            HttpRequestWay.assign(str,0,i);
            break;
        }
    }
    int lock=0;
    for (int i = HttpRequestWay.size()-1; i < str.size(); ++i) {
        if(str[i]=='/'){
            lock=1;
            start=i;
        }
        if(lock){
            if(str[i]==' '){
                HttpRequestUrl.assign(str,start+1,i-1-start);
                for(int j=i+1;j<str.size();j++){
                    if(str[j]=='\r'){
                        Http.assign(str,i+1,j-i);
                        break;
                    }
                }
                break;
            }
        }
    }
    std::cout<<"url:"<<HttpRequestUrl<<std::endl;
    int l=HttpRequestWay.size()+HttpRequestUrl.size()+Http.size();
    //序列化头部键值对
    int conn=str.find("Connection",l);
    int ua=str.find("User-Agent",l);
    int acc=str.find("Accept",l);
    int ae=str.find("Accept-Encoding",l);
    int al=str.find("Accept-Language",l);
    int coo=str.find("Cookie",l);
    FindKeyValue(HttpConnection,str,conn,"Connection");
    FindKeyValue(HttpAccept,str,acc,"Accept");
    FindKeyValue(HttpUserAgent,str,ua,"User-Agent");
    FindKeyValue(HttpAcceptEncoding,str,ae,"Accept-Encoding");
    FindKeyValue(HttpAcceptLanguage,str,al,"Accept-Language");
    FindKeyValue(HttpCookie,str,coo,"Cookie");
    FindJson(HttpBody,str,coo);
}


void FindKeyValue(std::unordered_map<std::string,std::string>&Te,std::string s,int start,std::string Key){
    int lock=0,begin=0;
    for(int i=start+Key.size();i<s.size();i++){
        if(s[i]==' '&&!lock){
            lock=1;
            begin=i;
        }
        if(lock){
            if(s[i]=='\r'){
                Te[Key].assign(s,begin+1,i-begin);
                break;
            }
        }
    }
    //std::cout<<Key<<":"<<Te[Key]<<std::endl;
}

void FindJson(std::string &json,std::string s,int start){
    if(s.find("{",start)==std::string::npos&&s.rfind("}",s.size())==std::string::npos){
        return;
    }
    int l=s.find("{",start);
    int b=s.rfind("}",s.size());
    json.assign(s,l,b-l+1);
    //std::cout<<"json:"<<json<<std::endl;
}


