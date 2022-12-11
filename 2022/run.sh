#!/bin/bash

[ "$#" -eq 1 ] && "./$1" && exit

NB=$(ls | grep cpp | wc -l)
for (( i=1; i<=${NB}; i++))
do
  [ -f ./${i} ] && ./${i}
done

exit 0
