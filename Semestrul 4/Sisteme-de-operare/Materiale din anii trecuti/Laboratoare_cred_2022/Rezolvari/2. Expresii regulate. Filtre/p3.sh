result=$(echo $1 | sed 's/[0-9A-F]\{2\}/&:/g' | sed 's/.$//g')
echo $result