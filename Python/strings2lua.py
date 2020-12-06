#coding=utf-8
import re
import os

OUTPUT_PATH = "../frameworks/runtime-src/proj.ios_mac/ios/strings2lua/"
'''
读取源文件
'''
def readFile(sourceFilePath,savePath):
    languageSourceFile = open(sourceFilePath, mode="r")  # 只读方式打开文件
    fileName = getFileName(sourceFilePath)
    line = languageSourceFile.readline()
    while line:
        str = r'\"(.*?)\"'
        if "\"" in line:
            target = re.findall(str, line)  # 截取" "之间内容，返回list
            if len(target) == 2:
                content = target[0] + " = \"" + target[1] + "\"," #每行内容
                outPutFile(fileName,savePath,content) #输出给文件
        line = languageSourceFile.readline()
    languageSourceFile.close()

'''
输出为lua文件
'''
def outPutFile(fileName,savePath,content):
        dir = savePath.split('/')[-1]
        outPutFilePath = OUTPUT_PATH + dir  #在当前目录创建新目录
        file = open(outPutFilePath+"/"+fileName,mode='a')
        file.write(content+"\n")
        file.close()
'''
获取输出文件路径
'''
def getFileName(sourcePath):
    name = sourcePath.split('/')[-1]
    fileName = re.findall(name,sourcePath)
    str = fileName[0]
    forePart = str.split('.')[0]
    foreName = re.findall(forePart,str)
    newName = foreName[0]+".lua"
    return newName
'''
判断lua文件是否存在
'''
def isExits(path,sourceFileName):
    print(path)
    if not os.path.exists(path):
        os.mkdir(path)
    fileName = getFileName(sourceFileName)
    file = open(path+"/"+fileName,mode="w")
    file.write("return {\n")
    file.close()
def addTail(path,sourceFileName):
    fileName = getFileName(sourceFileName)
    file = open(path+"/"+fileName,mode='a')
    file.write("}")
    file.close()
'''
开始转换
'''
def transStart():
    homePath = "../frameworks/runtime-src/proj.ios_mac/ios"
    fileList = os.listdir(homePath)
    for dir in fileList:
        dirPath = homePath + "/"+dir
        if os.path.isdir(dirPath):
            if "strings2lua" in dir:
                continue
            sourceFile = os.listdir(dirPath)
            for file in sourceFile:
                sourceFilePath = dirPath + "/" + file
                isExits(OUTPUT_PATH+dir,file)
                readFile(sourceFilePath,dirPath)#传递文件路径，及文件父文件夹路径
                addTail(OUTPUT_PATH+dir,file)
if __name__ == '__main__':
    transStart()
