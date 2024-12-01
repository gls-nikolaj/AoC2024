set -e

today=$(date +'%Y %0d %-d')

yearInt=$(echo -n $today | cut -d' ' -f1)
day=$(echo -n $today | cut -d' ' -f2)
dayInt=$(echo -n $today | cut -d' ' -f3)

if [ ! -d "$day" ] ; then
    mkdir $day
    cp -r template/* $day

    session=$(cat session.txt)
    curl -s -H "Cookie: session=$session" -o "$day/input.txt" "https://adventofcode.com/$yearInt/day/$dayInt/input" 

    git add $day
fi

cd $day
