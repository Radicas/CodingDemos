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
    TA(){}
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
        std::cout << "TA fake function thread start\t" << "thread_adress:" << this<<"\t"<< "thread_id:" << std::this_thread::get_id() << std::endl;
        std::cout << "modify m_i_:" << this->m_i_ << std::endl;
        /*
         *
         */
        std::cout << "TA fake function thread end  " << this << std::endl;
    }
    int get_m_i() const {
        return m_i_;
    }
    void set_m_i(int& i) const {
        this->m_i_ = i;
    }
private:
    mutable int m_i_ = 0;
};
/*
 * 参数中的引用，不是真正的原参数，实际上是值传递--》子线程中用主线程中的引用是安全的
 * 子线程中的指针还是原参数的地址--》子线程不能使用指针！！
 */
//void thread_demo_1(const int& ti, char* tbuffer)
void thread_demo_1(const int ti, const std::string& tbuffer)    //字符数组指针，转换成string类型。
{
    std::cout << "thread_demo_1 start\t" <<"thread_id:" << std::this_thread::get_id() << std::endl;
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
    std::cout << "thread_demo_2 start\t" << "thread_id:" << std::this_thread::get_id() << std::endl;
    std::cout << "m_i_:" << ta.get_m_i() << std::endl;
    std::cout << "thread_demo_2 end" << std::endl;
}

void send_temp_arguments2()
{
    int i = 20;
    std::thread t_demo_2(thread_demo_2,i,TA(i));    //主线程结束前会构造出TA类型，不用担心传递空内容

    t_demo_2.join();                                   //构造临时对象传参是安全的
}

void thread_demo_3(const TA& ta)
{
    int i = 255;
    std::cout << "thread_demo_3 start\t" << "thread_id:" << std::this_thread::get_id() << std::endl;
    ta.set_m_i(i);
    std::cout << "3 m_i:" << ta.get_m_i() << std::endl;
    std::cout << "thread_demo_3 end" << std::endl;
}
void ref_test(const TA& ta)
{
    //std::thread t_demo_3(thread_demo_3,ta);   //假引用，复制出一个新的ta，主线程中的ta没有变化
    std::thread t_demo_3(thread_demo_3,std::ref(ta));   //std::ref() 传入真正的引用而不是复制一份，此时可以将const去掉
    t_demo_3.join();
}

int main()
{
    std::cout << "mian thread id:" << std::this_thread::get_id() << std::endl;
    TA ta;
    std::cout << "init m_i_:" << ta.get_m_i() << std::endl;
    std::thread t_thread(ta);   //t_thread括号中要传入"可调用对象",传入一个类对象
    /*
     * t_thread.detach()    //和主线程分开，主线程结束，当前进程将在后台运行(不稳定，尽量不用)
     * t_thread.join()  //使主线程阻塞，等待t_thread线程执行结束
     * t_thread.joinable()  //判断是否能和主线程合并
     */
    t_thread.join();
    send_temp_arguments();
    send_temp_arguments2();
    ref_test(ta);
    std::cout << "ta mi:" << ta.get_m_i();
    return 0;
}



/*
 * 多线程总结：
 * 1.创建线程时若传递int之类的简单类型参数，建议值传递，避免用引用防止节外生枝
 * 2.如果参数要传递类对象，不要隐式转换，直接在创建线程时构造出临时对象，函数参数里用引用去接，因为值接会再构造出一个对象，浪费资源。
 */