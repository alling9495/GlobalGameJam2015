SFMLLink=game
SFMLLib= -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system 
linux:
	g++ -g main.cpp Camera.cpp Player.cpp LinearBullet.cpp Tile.cpp WorldChunk.cpp World.cpp Particle.cpp  -o $(SFMLLink) $(SFMLLib)
