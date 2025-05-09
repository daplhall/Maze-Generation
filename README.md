# Maze generator
A simple maze generator written in, with a visualizer for the command prompt.  

Here is an example generated ascii maze with it solution starting at `S` and ending at `E`
```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@S@  ***@      *****@           @  *****@ @     @
@*@@@*@*@@@@@@@*@@@*@@@@@@@ @@@ @ @*@@@*@ @ @ @ @
@*****@*********@ @*@*****@   @   @*@***@ @ @ @ @
@@@@@@@@@@@@@@@@@ @*@*@@@*@@@@@@@@@*@*@@@ @ @ @@@
@   @         @ @***@*@  ***********@***@   @   @
@ @@@ @@@@@ @ @ @*@@@*@@@@@@@@@@@@@@@@@*@@@@@@@ @
@   @   @   @   @*@  *****@     @     @*****@***@
@ @ @@@ @ @ @@@@@*@ @@@@@*@@@ @ @ @ @@@@@@@*@*@*@
@ @     @ @ @   @*@ @*****@   @ @ @     @***@*@E@
@ @@@@@@@ @@@ @ @*@@@*@@@@@ @@@@@ @@@ @@@*@@@*@ @
@       @     @  *****@             @    *****@ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
```
# Building
Make a build folder eg.
```
$ mkdir build
```
then simply call the makefile, given you have gcc installed.
```
$ make
```