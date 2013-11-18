#!/usr/bin/bash

sudo avrdude -c jtag3 -p x256a3bu -e -U flash:w:main.hex 
