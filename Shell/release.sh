#!/usr/bin/bash

# REDEDA代码根目录
REDEDA_SOURCE="D:/Repos/RedEDA"

# REDEDA安装bin目录
REDEDA_INSTALL_BIN="D:/Repos/rededa-lib/bin"

# NSIS的full目录，打包脚本及打包软件本体在此目录下
NSIS_FULL_ROOT="D:/Repos/rededa-installer/win/full"

NSIS_SOURCE_BIN="${NSIS_FULL_ROOT}/package/RedPCB/bin/"

NSIS_SCRIPT="${NSIS_FULL_ROOT}/nsis/install.nsi"

# NSIS可执行文件目录
MAKENSIS="D:/NSIS"

# 没用的文件列表，复制到打包环境后需要删除

rm_useless_file(){
	for sub in `ls $1`; do
		if [ -d $1"/"${sub} ]
	   	then
			rm_useless_file $1"/"${sub} $2
		else
			if [ ${sub} == $2 ] 
		   	then
				echo "delete file ${sub}"
				rm $1"/"${sub}
			fi
		fi
	done
}

# 检查是否存在build文件夹，没有就创建一个
if [-d "./build"]; then 
	mkdir build
fi

# cmake开始构建项目
# 有Debug Release RelWithDebInfo MinSizeRel四种模式
cmake -S ${REDEDA_SOURCE} -B ./build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo

cd ./build

cmake --build . -j 20

cmake --install .
# cmake构建结束

for file in pingme.txt route.log redtest.exe rededa-examples.exe
do
	rm_useless_file ${REDEDA_INSTALL_BIN} ${file}
done

# 移动程序到打包环境
cp -r ${REDEDA_INSTALL_BIN}/* ${NSIS_SOURCE_BIN}

ls ${REDEDA_INSTALL_BIN} -la
