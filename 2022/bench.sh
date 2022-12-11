#!/bin/bash

[ "$#" -eq 1 ] && "./$1_bench" && exit

NB=$(ls | grep cpp | wc -l)
for (( i=1; i<=${NB}; i++))
do
  [ -f ./${i}_bench ] && ./${i}_bench
done

exit 0
