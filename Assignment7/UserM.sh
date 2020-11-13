
#!/bin/bash


userFile=$1
groupName=$2
opflag=$3

echo "Passed in $opFlag"

if [[ $opFlag != "-a" && $opFlag != "-r" ]]; then

	echo "Argument will need to add or remove users flag."
	exit

fi

if [[ $# -ne 3 ]]; then
	echo "Command line contains $# arguments." 
		echo "Pass in three arguments: (user, group and operation flag)"

else

	echo "Checking for group"

	if echo "OUTPUT" | grep -q  $groupName /etc/group; then

	echo "User group exists"
		if [[ $opFlag == "-r" ]]; then
			echo "Delete user group"
			groupdel $groupName

		fi

	else
		if [[ $opFlag == "-a" ]]; then
		echo "creating user group" 
		groupadd $groupName
		fi
	fi

cat "${userFile}" | whileIFS=" " read username password
do

	[[ $opFlag == "-a" ]] && echo "user '$username' will now be created if they don't  exist..." 
	[[ $opFlag == "-r" ]] && user "user '$username' will now be deleted if it exists..."
	cat /etc/passwd | grep ${username} >/dev/null 2>&1 
	if [[ $? -eq 0 ]] ; then
		echo "$username Exists" 
	[[ $opFlag == "-a" ]] & userdel -r $username
	else 
		echo "User not found"
	[[ $opFlag == "-r" ]] && useradd -m -G $groupName - p $password $username
	fi
done
echo "*** User M completed. ***"  
