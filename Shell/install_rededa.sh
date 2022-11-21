#!/usr/bin/bash

CURR_PATH=`pwd`
REDEDA_SOURCE="D:/Repos/RedEDA"
REDEDA_INSTALL_BIN="D:/Repos/rededa-lib/bin"
NSIS_FULL_ROOT="D:/Repos/rededa-installer/win/full"
NSIS_SOURCE_BIN="${NSIS_FULL_ROOT}/package/RedPCB/bin/"
NSIS_SCRIPT="${NSIS_FULL_ROOT}/nsis/install.nsi"
MAKENSIS="D:/NSIS"
SYSTEM32="C:/Windows/system32"
PYTHON_PATH="C:/Users/Radica/.pyenv/pyenv-win/versions/3.7.0/python.exe"

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

if [-d "./build"]; then 
	mkdir build
fi

cmake -S ${REDEDA_SOURCE} -B ./build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo -DPYTHON_EXECUTABLE=${PYTHON_PATH}
cd ./build
cmake --build . -j 20
cmake --install .

for file in pingme.txt route.log redtest.exe rededa-examples.exe
do
	rm_useless_file ${REDEDA_INSTALL_BIN} ${file}
done

cp -r ${REDEDA_INSTALL_BIN}/* ${NSIS_SOURCE_BIN}
ls ${REDEDA_INSTALL_BIN} -la

${MAKENSIS}/makensis -HDRINFO ${NSIS_FULL_ROOT}/nsis/install.nsi

cd ${CURR_PATH}

start
