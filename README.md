# Invisible Keylogger in C
This Keylogger with attached Script for installation is designed to silently run in the background of a PC and later upload all the collected files in a designed FTP folder.

#  DISCLAMINER
![]You should not use this Keylogger to spy other person, this is a crime and you might be persecuted. This demo was developed for research puprose only in a collaboration project between Grenoble University, Roma Tre University and Università di Padova.

Structure:

keylib.h 	Libraries
keylib.c 	Keylogger engine
keylogger.c	Main function and initialization

#  HOW TO USE
uni.vbs will run a hidden shell calling test.bat.
test.bat will copy the win32drv.exe into a hidden Windows folder. Windows will save this folder as System folder, making it invisible and protected. Additionally, it will add the keylogger to the automatic startup.

win32drv.exe is the keylogger engine (not included to avoid misuse). 

To stop the keylogger use: ".,m"
To set a deactivation timer of 30 sec use: ".,s"
To activate the "hacked mode" use: ".,x"

The Keylogger will run by default with these settings, is it possible to change settings by editing a setting file in the FTP repository.


I apologize for the horrible documentation, it will be updated.

#  TO BE DONE
![] Retrive command from FTP
![] Self-hide function
![] Shut down detection
![] Screenshot FTP upload
![] Find/delete local file
![] Add polymorfic code