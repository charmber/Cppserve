
class Router{
public:
    Router();
    JudgeRequest();
    JudgeUrl();
    AddUrl();

private:
    char res[];
    std::vect
};



//判断请求
std::string Router::JudgeRequest() {
    int l= sizeof(res);
    for(int i=0;i<l;i++){
        if((res[0]=='G'&&res[1]=='E')||(res[0]=='g'&&res[1]=='e')){
            return "GET";
        }
    }
}

std::string Router::JudgeUrl() {
    int l=sizeof(res);
}
std::string Router::AddUrl() {

}
