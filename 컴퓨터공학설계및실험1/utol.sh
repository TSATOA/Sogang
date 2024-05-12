#!/bin/bash

echo 'Working directory:' #/sogang/under/cse20191583/shell
read dirname #dirctory 이름을 입력을 저장

if [ -n "$dirname" ]
then
	if [ -d "$dirname" ]
	then
		cd $dirname
		for dir in *
		do
			newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
			mv $dir $newname
		done
	else
		echo "error message : no available directory"
	fi
else
	for dir in *
	do
		newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"`
		mv $dir $newname
	done
fi


#	for dir in *
#	do
#		newname=`echo $dir | tr "[a-z] [A-Z]" "[A-Z] [a-z]"` #변수 newname은 dir의 대소분자 tr을 이용해서 바꾼 것
#	mv $dir $newname #dir을 newname으로 바꾼다.
#	done



