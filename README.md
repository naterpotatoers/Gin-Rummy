# Gin Rummy
Class Assignment for Fall 2018. Added win condition checking over winter break. 

![](GinRummyTerminal.png)
gin_rummy.h and main.cpp contain just the basic game functionality without any win condition checking.

#### main_full.cpp is the complete game.
Over winter break I implemented win condition checking using the bitset library. I mapped playing cards to a binary value and preformed BitWise operations to check for melds and runs. The initial implementation of the game lacks reusability so I had started rewriting the project with better object oriented design practice.
