# Filler
The Filler (game rools)
* In this game, two players fight each other. They play one after the other.  
* The goal is to collect as many points as possible by placing the highest number of
pieces on the the game board.  
* The board is defined by X columns and N lines, it will then become X*N cells.  
* At the beginning of each turn, you will receive your game piece.  
* A game piece is defined by X columns and N lines, so it will be X*N cells. Inside
each game piece, will be included a shape of one or many cells.  
* To be able to place a piece on the board, it is mandatory that one, and only one
cell of the shape (in your piece) covers the cell of a shape placed previously (your
territory).  
* The shape must not exceed the dimensions of the board.  
* When the game starts, the board already contains one shape.  
* The game stops at the first error: either when a game piece cannot be placed
anymore or it has been wrongly placed.  

The player program (bsausage.filler)
* The goal of this project is to create a filler player. It's goal is to win other filler players.  
* It will read the board and the game pieces placed on the standard output.  
* Each turn the filler rewrites the board map and includes a new piece to be
placed.  
* In order to place the game piece on the board, the player will have to write
it’s coordinates on the standard ouput.  
* Player will collect points each time it place a piece.  
To run:  
```
make
./resources/filler_vm -f resources/maps/<map_file> -p1 ./bsausage.filler -p2 ./resources/players/<player_name.filler>
```
The visualizer program
* Is a graphic visualizer of a game.
* Works only on MacOS  
To run:
```
make vis
./resources/filler_vm -f resources/maps/<map_file> -p1 ./bsausage.filler -p2 ./resources/players/<player_name.filler> |./visualizer
```
