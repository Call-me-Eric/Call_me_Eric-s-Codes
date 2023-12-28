while [ true ]
do
	python3 data.py
	./bf
	./eq
	if diff -w eq.out eq.ans
	then
		echo AC
	else
		echo WA
		exit
	fi
done
