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

philo/philo $NB_PHILO $TTD $TTE $TTS $NB_EAT > /tmp/philo.log

if [ $? -ne 0 ]; then
    echo "Error: philo program failed to execute."
	rm -f /tmp/philo.log
    exit 1
fi

if grep -q "died" /tmp/philo.log; then
	echo "A philosopher has died."
	rm -f /tmp/philo.log
	exit 1
fi
for ((i=1; i<=NB_PHILO; i++))
do
	echo -n "Philo $i eat count: "
	grep -w "$i is eating" /tmp/philo.log | wc -l
done

rm -f /tmp/philo.log