SFMLLink=sfml-app
SFMLLib= -lsfml-graphics -lsfml-window -lsfml-system 
linux:
	g++ *.cpp -o $(SFMLLink) $(SFMLLib)
