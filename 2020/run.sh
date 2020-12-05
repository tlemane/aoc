#!/bin/bash

NB=$(ls | grep day | wc -l)
for (( i=1; i<=${NB}; i++))
do
    ex="day${i}/day${i}.out"
    data="day${i}/input"
    if [[ -f "${ex}" && -f ${data} ]]; then
        ${ex} ${data}
        echo
    fi
done