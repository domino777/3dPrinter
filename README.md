3dPrinter
=========

3dPrinter for Atmel XMEGA


This a project for develop a 3dPrinter, provided by SD card reader with easy browsing where select a g-code file for launch the printing procedure.

SD card file system format supported is EXT2 with 1kB block and maximum readable file's size is 274432byte
The maximum number of storable inode table is set to 512. Library work only in read-mode without control of root data, file privilege and onyl files which are seen and read by the system are regular file and directory.

There is a library for axes control (not finished yet), the control of the axes is similar to PLC ( not a stop-to-wait ) control system and 4 interpolated axes can be moved all together. Axes are activated in a WHILE loop and CPU CYCLE is computed in real-time mode with and a non-wait timer control when axes are allowd to move. 

( see the code, is more easy to understand :) ) my english is arrrrrrrrr......... >.<

In the source code there are a lot of comments and waste-code. This project isn't finish and it is open-work.

All the source codes are under GPLv3.

Copy if you want, use if you want, help if you want but pleas give me a feedback about bugs, ideas and other stuff that you think is good for implementation
