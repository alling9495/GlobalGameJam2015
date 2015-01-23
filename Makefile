SFMLLink=game
SFMLLib= -lsfml-graphics -lsfml-window -lsfml-system 
linux:
	g++ main.cpp -o $(SFMLLink) $(SFMLLib)
