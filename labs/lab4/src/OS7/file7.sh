#!/bin/bash
 
(cd $1 && ls -Ggh1 | awk '{print $7}') > "tmp1.out"
(cd $2 && ls -Ggh1 | awk '{print $7}') > "tmp2.out"
while IFS= read -r line2
do
	lmt2=$(date +%s -r "$2/$line2")
	while IFS= read -r line1
	do
		foundEq=false
		lmt1=$(date +%s -r "$1/$line1")
		if [[ "$lmt1" < "$lmt2" ]] && [[ "$line1" == "$line2" ]]; then
			cp "$2/$line2" $1
			break
		fi
		if [[ "$line1" == "$line2" ]]; then
			foundEq=true
			break
		fi
	done < "./tmp1.out"
	if [[ "$foundEq" != "true" ]]; then
		cp "$2/$line2" $1
	fi
done < "./tmp2.out"
 
while IFS= read -r line1
do
	while IFS= read -r line2
	do
		foundEq=false
		if [[ "$line1" == "$line2" ]]; then
			foundEq=true
			break
		fi
	done < "./tmp2.out"
	if [[ "$foundEq" != "true" ]]; then
		rm "$1/$line1"
	fi
done < "./tmp1.out"
 
rm "tmp1.out"
rm "tmp2.out"
