#!/bin/bash

if [ "$#" -ne 5 ]; then
    echo "Usage: $0 NB_PHILO TTD TTE TTS NB_EAT"
    exit 1
fi

NB_PHILO=$1
TTD=$2
TTE=$3
TTS=$4
NB_EAT=$5

./philo $NB_PHILO $TTD $TTE $TTS $NB_EAT > /tmp/philo.log

for ((i=1; i<=NB_PHILO; i++))
do
	echo -n "Philo $i eat count: "
	< /tmp/philo.log grep -w "$i is eating" | wc -l
done

rm -f /tmp/philo.log