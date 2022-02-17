#include "../Cmdoule.h"

//std::unordered_map<std::string ,std::string >Js;

const std::string quotes="\"";
const std::string enter="\n";
typedef std::unordered_map<std::string,std::string> ChJson;


//json键值对初始化
std::unordered_map<std::string,std::string> JsonInit(std::vector<std::string> jstr){
    std::unordered_map<std::string,std::string>Js;
    for(auto i:jstr){
        Js[i]="0";
    }
    return Js;
}
//对map结构转换为json
std::string Json(std::unordered_map<std::string,std::string>Js){
    std::string json="{\n";
    for(auto iter = Js.begin(); iter != Js.end(); ++iter){
        auto it=iter;
        if(++it==Js.end()){
            json+=quotes+iter->first+quotes+":"+quotes+iter->second+quotes+enter+"}";
        } else{
            json+=quotes+iter->first+quotes+":"+quotes+iter->second+quotes+","+enter;
        }
    }
    return json;
}

