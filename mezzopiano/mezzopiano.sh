#$/bin/bash

#.CONFIG file to initialize a default directory for the 

printf "\n\t\t++++++++++++++++\n\t\t| JPLabsystems |\n\t\t++++++++++++++++\n\n\t\t  *mezzopiano*  \n\ncopyright(c) 2025 Justinas Petkauskas\nmezzopiano.sh script\n\n"

cd /run/media/justinas

printf "Select player directory: \n\n"
ls
printf "\n"

#read -p "Enter path: " path
#cd ./$path/player

cd ./JPLMP3/player

printf "WELCOME TO mezzopiano! CURRENT LIBRARY:\n\n"
sqlite3 ./playerdb.db3 "SELECT composer, piecename FROM library LIMIT 10;"

printf "\n"
read -p "options: 1 = add files. selection: " selection
if [ "$selection" -eq 1 ]; then
    printf "\n\tADDING FILE TO LIBRARY\n\n"
fi 
