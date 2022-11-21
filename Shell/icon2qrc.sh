#!/usr/bin/bash
ICON_ROOT="/home/radica" 

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

scanDir ${ICON_ROOT}

