#!/bin/bash

if [[ "`ps | grep server`" == "" ]]
then
	./server &
	sleep 1
fi
