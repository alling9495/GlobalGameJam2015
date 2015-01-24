SFMLLink=game
SFMLLib= -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system 
linux:
	g++ main.cpp Camera.cpp Player.cpp LinearBullet.cpp  -o $(SFMLLink) $(SFMLLib)
