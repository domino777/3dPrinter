3dPrinter
=========

C code
-------

3dPrinter for Atmel XMEGA or other MCU if you adapt the code


This is a project for develop an open-source 3dPrinter provided by a SD card reader with easy browsing user interface. It is possible to select a g-code file in the SD-Card for launch the printing process.

SD cards EXT2 file system are supported with 1kB block and maximum readable file size is 274432byte
The maximum number of storable inode table is up to 512. Library work only in read-only mode without control of root data, file privilege and only files which are seen and read by the system are regular files and directorys.

There is a library for axes control (not finished yet), axes control is similar to PLC ( not a stop-'n-wait ) control system and 4 interpolated axes can be moved all together. Axes are activated in a WHILE loop and CPU CYCLE is computed in real-time mode with a non-wait timer control. 

In the source code there are a lot of comments and waste-code. This project isn't finish and it is an open-work.

All the source codes are under GPLv3.

Copy if you want, use if you want, help if you want but pleas give me a feedback about bugs, ideas and other stuff that you think is good for the implementation


drawings
--------

Inside the folder "drawings" there are all mechanical 3d drawing parts necessary for build the printer. Software used for draw all parts is SOLIDWORK.

Everything is under the TAPR Open Hardware License and are property of Sabrina Schiavinato
