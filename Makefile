SFMLLink=game
SFMLLib= -lsfml-graphics -lsfml-window -lsfml-system 
linux:
	g++ main.cpp Player.cpp WorldChunk.cpp World.cpp Tile.cpp -o $(SFMLLink) $(SFMLLib)
  
