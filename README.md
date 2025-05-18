# Maze generator
A simple maze generator written in  C. It can generate a random maze, solve it, and display it to the command prompt. 
This was done as a small for fun project.

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
Make a build folder
```
$ mkdir build
```
then simply call the makefile
```
$ make
```