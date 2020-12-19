#include <iostream>
#include <thread>
#include <string>

class TA
{
public:
    /*
     * 此处构造函数中的引用参数不安全，当主线程结束时，引用变量的内存会被回收从而导致bug
     * 多线程中传参数时，用引用和指针要小心，最好传递实参
     */
    TA(int& i):m_i_(i){
        //std::cout << "TA constructor call  " << this << std::endl;
    }
    TA(const TA& ta):m_i_(ta.m_i_){
        //std::cout << "TA copy constructor call  " << this << std::endl;
    }
    ~TA(){
        //std::cout << "~TA distructor call  " << this << std::endl;
    }
    void operator()(){  //仿函数，使类对象成为可调用对象
        std::cout << "TA fake function thread start  " << this << std::endl;
        /*
         *
         */
        std::cout << "TA fake function thread end  " << this << std::endl;
    }

private:
    int m_i_;
};
/*
 * 参数中的引用，不是真正的原参数，实际上是值传递--》子线程中用主线程中的引用是安全的
 * 子线程中的指针还是原参数的地址--》子线程不能使用指针！！
 */
//void thread_demo_1(const int& ti, char* tbuffer)
void thread_demo_1(const int ti, const std::string& tbuffer)    //字符数组指针，转换成string类型。
{
    std::cout << "thread_demo_1 start" << std::endl;
    std::cout << "thread_demo_1 ti address: " << &ti << " differ from i" << std::endl;
    std::cout << "thread_demo_1 end" << std::endl;
}

void send_temp_arguments()
{
    int i = 10;
    std::cout << "main thread i address: " << &i << std::endl;
    char buffer[] = {"this is thread demo 1"};
    /*
     * thread <name>[函数名，函数参数1,2,3...]
     * 创建线程时，字符数组存在主线程执行完还未转换成string的可能性，所以在传值之前要强转为string类型，保证安全
     */
    std::thread t_demo_1(thread_demo_1,i,std::string(buffer));
    t_demo_1.join();
}

void thread_demo_2(const int ti, const TA& ta)    //参数含有类类型，构造函数可以将int类型转换为TA类型，强转后传递过来
{
    std::cout << "thread_demo_2 start" << std::endl;
    std::cout << "thread_demo_2 end" << std::endl;
}

void send_temp_arguments2()
{
    int i = 20;
    std::thread t_demo_2(thread_demo_2,i,TA(i));    //主线程结束前会构造出TA类型，不用担心传递空内容
    t_demo_2.join();                                   //构造临时对象传参是安全的
}

int main()
{
    int reference_test_i = 6;
    TA ta(reference_test_i);
    std::thread t_thread(ta);   //t_thread括号中要传入"可调用对象",传入一个类对象
    /*
     * t_thread.detach()    //和主线程分开，主线程结束，当前进程将在后台运行(不稳定，尽量不用)
     * t_thread.join()  //使主线程阻塞，等待t_thread线程执行结束
     * t_thread.joinable()  //判断是否能和主线程合并
     */
    t_thread.join();
    send_temp_arguments();
    send_temp_arguments2();
    return 0;
}
