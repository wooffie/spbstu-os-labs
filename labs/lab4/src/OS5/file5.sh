grep -Ril $1 $(pwd)  > "./tmp.out"
 
while IFS= read -r line
do
	echo "$line $(cat -b $line | grep $1)" >> "./$2"
done < "./tmp.out"
rm "./tmp.out"
