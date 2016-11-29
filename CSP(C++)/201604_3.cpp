#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    int num;
    string curDir;
    vector<string> list;

    cin>>num>>curDir;
	
    cin.ignore();
    for(int i=0; i<num; i++){
        string line;
        getline(cin,line);
        int pos;

        // 添加当前目录
        if(line[0] != '/'){
            line = curDir+"/"+line;
        }
        if(line.size()==0){
            line = curDir;
        }
		
		/*
		string& erase(size_t pos=0,size_t n=npos) -> erase(pos,n) 从pos开始删除n个,算上pos自己
		iterator erase(iterator position) -> erase(str.begin()) 删除position处的一个字符
		iterator erase(iterator first,iterator last) -> erase(str.begin(),str.end()) 删除first和second之间的字符，前闭后？
		*/

        // 除去多个///
        while( (pos=line.find("//"))!=-1 ){
            int count = 2;
            while(line[pos+count]=='/'){
                count++;
            }
            line.erase(pos,count-1);
        }

        // 除去../
        while( (pos=line.find("/../"))!=-1){
            if(pos==0){
                line.erase(pos+1,3);
            }else{
                int spos;
                spos = line.rfind("/",pos-1);
                line.erase(spos,pos-spos+3);
            }
        }

        // 除去./
        while( (pos=line.find("/./"))!=-1){
            line.erase(pos+1,2);
        }
        // 除去最后一个/
        if(line.size()>1 && line[line.size()-1]=='/')
            line.erase(line.size()-1);

        list.push_back(line);
    }
    for(int j=0; j<num; j++){
        cout<<list[j]<<endl;
    }

    return 0;
}