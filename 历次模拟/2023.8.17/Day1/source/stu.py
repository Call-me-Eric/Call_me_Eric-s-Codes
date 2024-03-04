import os
import sys

for s in os.listdir('.'):
    if s[0:3] == "Stu":
        for t in os.listdir(s):
            cmd = f'xcopy /-Y {s}\\{t} {t}'
            print(cmd)
            os.system(cmd)
