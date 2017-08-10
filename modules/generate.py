import os
import subprocess

for d in os.listdir(os.path.dirname(os.path.realpath(__file__))):
	dirPath = os.path.join(os.path.dirname(os.path.realpath(__file__)), d)
	
	if os.path.isdir(dirPath):
		subprocess.call(["python", "generate.py"], cwd=dirPath)