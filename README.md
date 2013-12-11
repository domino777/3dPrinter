3dPrinter
=========

3dPrinter for Atmel XMEGA


This is a project for develop an open-source 3dPrinter provided by a SD card reader with easy browsing user interface. It is possible to select a g-code file in the SD-Card for launch the printing process.

SD card's file system supported format is EXT2 with 1kB block and maximum readable file's size is 274432byte
The maximum number of storable inode table is set to 512. Library work only in read-only mode without control of root data, file privilege and only files which are seen and read by the system are regular file and directory.

There is a library for axes control (not finished yet), axes control is similar to PLC ( not a stop-'n-wait ) control system and 4 interpolated axes can be moved all together. Axes are activated in a WHILE loop and CPU CYCLE is computed in real-time mode with a non-wait timer control. 

( see the code, is more easy to understand :) ) my english is arrrrrrrrr......... >.<

In the source code there are a lot of comments and waste-code. This project isn't finish and it is an open-work.

All the source codes are under GPLv3.

Copy if you want, use if you want, help if you want but pleas give me a feedback about bugs, ideas and other stuff that you think is good for the implementation
