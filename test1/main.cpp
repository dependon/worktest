
#include <QApplication>
#include <iostream>
#include "exam.h"
void back(std::string str,int start,std::set<std::string> &res)
{
    if(str.size()==start){
        res.insert(str);
        return ;
    }
    for(int i=0;i<str.size();i++)
    {
        std::swap(str[i],str[start]);
        back(str,start+1,res);
        std::swap(str[i],str[start]);
    }
}


std::vector<std::string> test2(std::string s1)
{
    std::set <std::string>set;
    back(s1,0,set);
    return std::vector<std::string>(set.begin(),set.end());

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::string S1="qwe";
    std::vector<std::string> vector1=test2(S1);

    std::string S2="ad";
    std::vector<std::string> vector2=test2(S2);
    vector2.size();

    return 0;
}
