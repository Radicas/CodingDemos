#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using std::cout;
using std::cin;
using std::endl;

class Sort
{
public:
	void bubbleSort(std::vector<int> vec);	//冒泡排序
	void selectSort(std::vector<int> vec);	//选择排序		
	void insertSort(std::vector<int> vec);	//插入排序
};

void Sort::bubbleSort(std::vector<int> vec)
{
	cout<< "Bubble Sort:" << endl;
	for(int i=0;i<vec.size()-1;i++)
	{
		for(int j=0;j<vec.size()-1-i;j++)
		{
			if(vec[j]>vec[j+1])
			{
				int temp = vec[j+1];
				vec[j+1] = vec[j];	
				vec[j] = temp;
			}
		}
	}
	for(int i=0;i<vec.size();i++)
	{
		cout << vec[i] << "\t";
	}
	cout << "\n" << endl;
}

void Sort::selectSort(std::vector<int> vec)
{
	cout << "Select Sort:" << endl;
	int min_index = 0;
	for(int i=0;i<vec.size()-1;i++)
	{
		for(int j=i+1;j<vec.size();j++)
		{
			if(vec[j]<vec[min_index])
			{
				min_index = j;	
			}
		}		
		int temp = vec[min_index];
		vec[min_index] = vec[i];
		vec[i] = temp;
	}
	for(int i=0;i<vec.size();i++)
	{
		cout << vec[i] << "\t";
	}
	cout << "\n" << endl;
}
void Sort::insertSort(std::vector<int> vec){}

std::vector<int> randomNum(int* min_num, int* max_num, int* target_num)
{
    std::srand(time(nullptr));	//current time as random seed 
    std::vector<int> test;
    for(int i=0;i<*target_num;i++)
    {
        test.push_back((rand()%(*max_num-*min_num)+*min_num));
    }
    return test;
}

int main()
{
	Sort sort;
    int min_num, max_num,target_num;
	cout << "this is sort function tests" << endl;
    cout << "enter minimal number:" << endl;
    cin >> min_num;
    cout << "enter maximal number:" << endl;
    cin >> max_num;
    cout << "enterr target number:" << endl;
    cin >> target_num;
    std::vector<int> out = randomNum(&min_num,&max_num,&target_num);
	for(int i=0;i<out.size();i++)
	{
		cout << out[i] << "\t";
	}
	cout << "\n" <<endl;
	sort.bubbleSort(out);
	sort.selectSort(out);
    return 0;
}
