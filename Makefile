SFMLLink=game
SFMLLib= -lsfml-graphics -lsfml-window -lsfml-system 
linux:
	g++ main.cpp Camera.cpp Player.cpp -o $(SFMLLink) $(SFMLLib)
