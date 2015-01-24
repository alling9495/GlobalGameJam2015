SFMLLink=game
SFMLLib= -lsfml-graphics -lsfml-window -lsfml-system 
linux:
	g++ main.cpp Player.cpp -o $(SFMLLink) $(SFMLLib)
