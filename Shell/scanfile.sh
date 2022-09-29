#!/usr/bin/bash

# 需要遍历的根目录
ROOT_DIR="/Users/radica/Work/Repos/CodingDemos"

scanDir(){
	for sub in `ls $1`; do
		if [ -d $1"/"$sub ]
		then
			scanDir $1"/"$sub			
		else
			echo $1"/"${sub}
		fi
	done
}

scanDir ${ROOT_DIR}
