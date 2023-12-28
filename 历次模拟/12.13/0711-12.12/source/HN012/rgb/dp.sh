#!/bin/bash

nam="rgb"
for (( i=1 ; ; i++ )) ; do
	echo -n "Case #$i: "
	python3 ./gen.py 10 18 > ./$nam.in
	if ! ./$nam ; then
		echo RE!
		break
	fi
	./bf
	if ! diff <(head -n1 $nam.out) $nam.ans ; then
		echo WA!
		break
	fi
	echo AC!
done
