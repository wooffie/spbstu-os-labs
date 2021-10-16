#!/bin/bash
 
(cd $1 && ls -Ggh1 | awk '{print $1, $3, $7}') > "tmp1.out"
(cd $2 && ls -Ggh1 | awk '{print $1, $3, $7}') > "tmp2.out"
while IFS= read -r line2
do
	while IFS= read -r line1
	do
		foundEq=false
		if [[ "$line1" == "$line2" ]]; then
			foundEq=true
			break
		fi
	done < "./tmp1.out"
	if [[ "$foundEq" != "true" ]]; then
		echo "no pair found for :"
		echo "$line2 from dir2"
		echo ""
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
		echo "no pair found for :"
		echo "$line1 from dir1"
		echo ""
	fi
done < "./tmp1.out"
 
rm "tmp1.out"
rm "tmp2.out"
