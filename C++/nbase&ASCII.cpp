#include <iostream>
using namespace std;

class funManage{

public:
    int optionNum;
    char tmpC;
    int tmpNum;
    void queryASCII(char c){
        //system("clear");//问题点
        cout << "请输入要查询的ASCII码:";
    }

    void transASCII(char c){
        cout << int(c) << endl;
    }

    void ten2N(){
        if (1==tmpNum){
            int ten;
            cout << "请输入" << endl;
            cin >> ten;
            cout << bitset<8>(ten) << endl;
        }else if(2==tmpNum){
            int oct;
            cout << "请输入" << endl;
            cin >> oct;
            cout << "0x";
            cout << std::oct << oct << endl;
        }else if(3==tmpNum){
            int hex;
            cout << "请输入" << endl;
            cin >> hex;
            cout << std::hex << hex << endl;
        }
    }

    void showMenu(){
        cout << "1.ASCII码查询\t";
        cout << "2.进制转换" <<endl;
    }

    void actionFun(){
        if (1==optionNum){
            cout << "请输入字符:" << endl;
            cin >> tmpC;
            transASCII(tmpC);

        } else if (2==optionNum){
            cout << "1.转二进制\t" ;
            cout << "2.转八进制\t" ;
            cout << "3.转十六进制\n" ;
            cin >> tmpNum;
            ten2N();
        } else{
          printf("请输入字符");
        }
    }
};

void start(){
    funManage fm;
    //while (true){
    fm.showMenu();
    cin >> fm.optionNum;
    fm.actionFun();
    //}
}

int main(){
    cout << "************字符转换系统************" << endl;
    //cout << "按back键返回主菜单\n" << endl;
    cout << "请选择功能:" <<endl;
    start();
}

