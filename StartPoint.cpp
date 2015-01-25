#include "StartPoint.h"
StartPoint::StartPoint(sf::Vector2f chunk){
	position=sf::Vector2f(
		chunk.x*CHUNK_SIZE*TILE_SIZE + CHUNK_SIZE*TILE_SIZE*0.5f ,
		chunk.y*CHUNK_SIZE*TILE_SIZE + CHUNK_SIZE*TILE_SIZE*0.5f);
	square1.setSize(sf::Vector2f(TILE_SIZE*CHUNK_SIZE/4,TILE_SIZE*CHUNK_SIZE/4));
	square2.setSize(sf::Vector2f(TILE_SIZE*CHUNK_SIZE/4,TILE_SIZE*CHUNK_SIZE/4));
	square1.setPosition(position);
	square2.setPosition(position);
	square1.setOrigin(TILE_SIZE*CHUNK_SIZE/8,TILE_SIZE*CHUNK_SIZE/8);
	square2.setOrigin(TILE_SIZE*CHUNK_SIZE/8,TILE_SIZE*CHUNK_SIZE/8);

	square1.setFillColor(sf::Color(0,0,0,0));
	square2.setFillColor(sf::Color(0,0,0,0));
	square1.setOutlineColor(sf::Color(0,255,0));
	square2.setOutlineColor(sf::Color(0,255,0));
	
	square1.setOutlineThickness(5);
	square2.setOutlineThickness(5);
};
StartPoint::~StartPoint(){

}
void StartPoint::fadeIn(){

}
void StartPoint::fadeOut(){
	
}
void StartPoint::update(sf::Time elapsed){
	angle += elapsed.asSeconds()*6.28f;
	square1.setRotation(3*angle);
	square2.setRotation(-3*angle);
	square1.move(sf::Vector2f(0,sin(angle)));
	square2.move(sf::Vector2f(0,sin(angle)));
}
void StartPoint::draw(sf::RenderWindow & window){
	window.draw(square1);
	window.draw(square2);
}
bool StartPoint::pointIn(sf::Vector2f point){
	return false;
}
