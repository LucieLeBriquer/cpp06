#!/bin/bash

CONVERT_PATH='./convert'

## colors

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

function display_help()
{
	printf "usage:\t./tester.sh\n"
	exit
}

if [ "$#" -ne "0" ]
then
	display_help
fi


## check if ./convert is here

convert_ok=$(ls $CONVERT_PATH 2>/dev/null | wc -l)
if [ "$convert_ok" -eq "0" ]
then
	printf "converter needed, please update CONVERT_PATH\n"
	exit
fi

## test

function test()
{
	printf "\n$YELLOW$CONVERT_PATH $1$NC\n"
	$CONVERT_PATH $1
}

test "0"
test "0.0f"
test ".0f"
test "0.f"
test "0."
test "nan"
test "inf"
test "+inff"
test "-inf"
test "42.00001f"
test "42.12"
test "-42.5"
test "42000000000000000000000000000000000000.17"
test "420000000000000000000000000000000000000.17"
test "420000000000000000000000000000000000000.17f"
test "2147483648"
test "2147483648.1"
test "-2147483649"
test "-2147483648"

## not supposed to work
test ".f"
test "-.f"
test "7f"
test "7.77.7"
test "-7.12f1"
test