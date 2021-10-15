#!/bin/bash

export VAR1="sneg"
export VAR2="padaet"
env | grep VAR*
NEW_VAR="$VAR1 $VAR2"
echo $NEW_VAR
echo ${NEW_VAR:0:${#VAR1}}
echo ${NEW_VAR/$VAR1/"kaplya"}

