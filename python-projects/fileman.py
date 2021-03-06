#!/usr/bin/python3
#
# fileman.py, A simple server-side file manager
# (c) 2021 pocketlinux32, Under GPLv3
#
# This script should be ran as root.
#
import os, sys, shutil

def commandParser(command, option):
	statFile = open("/run/server-process/stat", "w+")
	driveList = open("/run/server-process/drives", "r")
	currentDrive = statFile.readline()
	currentPath = statFile.readline()
	if currentDrive == "" or currentPath == "":
		currentDrive = driveList.readline()
		currentPath = "/"
		driveList.seek(0)
	currentRoot = "/mnt" + currentDrive

	if option[0] == "/":
		os.chdir(currentRoot)
		option = option[1:]
	else:
		os.chdir(currentRoot + currentPath)

	if str(command) == "cd":
		if os.path.exists(option) && option == "":
			os.chdir(option)
		else:
			exit(2)
	elif str(command) == "chdrive":
		drives = "start"
		while drives:
			drives = driveList.readline()
			if option == drives:
				currentDrive = option
				break
	elif str(command) == "mkdir":
		if os.path.exists(option):
			os.mkdir(option)
		else:
			exit(2)
	elif str(command) == "del" or str(command) == "rm":
		if os.path.exists(option):
			if os.isfile(option):
				os.remove(option)
			elif os.isdir(option):
				shutil.rmtree(option)
	statFile.seek(0)
	if statFile.readline() == "" or currentRoot + currentPath[:currentPath.rfind("/") - 1] != os.getcwd():
		

if __name__ == "__main__":
	if len(sys.argv) < 3:
		print("Usage: " + sys.argv[0] + " [cd | chdrive | mkdir | del | rm] {path}")
		exit(1)
