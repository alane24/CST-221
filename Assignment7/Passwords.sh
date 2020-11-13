#!/bin/bash

rxContainsDigit="(\d)."

rxContainsDigitNonAlphaNumeric="[@#\$%|&\*\+-=]."

pass=$1


if [ $# -ne 1 ]; then

	echo "Command line contains $# arguments. "
		echo  "Pass single password as string."

else

	echo "Passed in: $pass"
	size=${#pass}
	if [  $size -lt 8 ]; then
		echo "Password needs to be longer."
	exit

fi

if ! [[ $pass =~ $rxContainsNonAlphaNumeric ]]; then
	echo "Password needs to have one non-alphanumeric character!"
	echo "Characters that are accepted are: (@, #, $, $, %, &, *, +, -, =)"
exit

fi

echo "*** Password is secured. ***"

fi
