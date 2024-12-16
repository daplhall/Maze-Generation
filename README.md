# Maze generator
A Maze generator written in C, with a visualizer for the command prompt
# todo
The current setup is a mix of a tree structure and a 2D array. It needs to only be a Tree structure, this way we can generate more interesting maze structures.
1. Start with a single cell
2. create a new cell(on a virtual grid) within the shape you want
3. Connect the two cells
4. focus on new cell, repeat 2 until no new cell can be created, then backtrace and repeat 2
