
import os
'''
输入路径，递归判断是否文件，是文件则判断文件大小，以key、value的形式存放与字典；按value排序。
'''

PATH = "/Users/mybogames/ab-blast"
dict = {}

def isFile(path):
    childList = os.listdir(path)
    for childName in childList:
        childPath = path+'/'+childName
        if os.path.isfile(childPath):
            size = os.path.getsize(childPath)
            dict[childName] = size#convertSize(size)
        elif os.path.isdir(childPath):
            isFile(childPath)

def convertSize(size):
    k = size/1024
    m = k/1024
    g = m/1024
    if k < 1024:
        return str(("%.2f" % k))+"K"
    elif k>1024 and m<1024:
        return str(("%.2f" % m))+"M"
    elif m>1024 and g<1024:
        return str(("%.2f" % g))+"G"
def listDic():
    sortValue = sorted(dict.items(), key=lambda item: item[1],reverse=False)    #按value排序
    for k, v in sortValue:
        v = convertSize(v)
        print(k,v)
    print("一共"+str(len(dict))+"个文件")
    #*********************************************************************************#
    # sortKey = sorted(dict.keys())#按key排序
    # for k in sortKey:
    #     print(k,convertSize(dict[k]))
    # print("一共" + str(len(dict)) + "个文件")

if __name__ == '__main__':
    isFile(PATH)
    listDic()
