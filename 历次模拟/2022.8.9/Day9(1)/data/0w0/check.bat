:loop
	data
	"(0w0)"
	bf
	C:\Windows\System32\fc output.out bf.out
	if errorlevel==1 pause
goto :loop
