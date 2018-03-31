
#ps -ef | grep $1 | head -n1 | awk '{ print $2 }' | xargs ./symbolmap $1 
pgrep $1 | head -n1 | xargs ./symbolmap $1 

