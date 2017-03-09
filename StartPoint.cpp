#include "StartPoint.h"
#include <math.h>
using namespace std;
StartPoint::StartPoint(sf::Vector2f chunk):
	x((int)chunk.x),
	y((int)chunk.y)
{
	
	position=sf::Vector2f(
		chunk.x*CHUNK_SIZE*TILE_SIZE + CHUNK_SIZE*TILE_SIZE*0.5f ,
		chunk.y*CHUNK_SIZE*TILE_SIZE + CHUNK_SIZE*TILE_SIZE*0.5f);	

	square1 = sf::RectangleShape();
	square2 = sf::RectangleShape();
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
	fadeDir = true;
	alpha = 0;
	angle = 0;
};
StartPoint::~StartPoint(){

}
void StartPoint::setChunk(sf::Vector2f chunk){
	position=sf::Vector2f(
		chunk.x*CHUNK_SIZE*TILE_SIZE + CHUNK_SIZE*TILE_SIZE*0.5f ,
		chunk.y*CHUNK_SIZE*TILE_SIZE + CHUNK_SIZE*TILE_SIZE*0.5f);
	square1.setPosition(position);
	square2.setPosition(position);
	
}
void StartPoint::fadeIn(){
	fadeDir=true;
}
void StartPoint::fadeOut(){
	fadeDir = false;
}
void StartPoint::update(sf::Time elapsed){
	if(fadeDir){
		alpha = (int)min(255,alpha+10);
	}
	else{
		alpha = (int)max(0,alpha-10);
	}
	angle += elapsed.asSeconds()*6.28f;
	square1.setRotation(3*angle);
	square2.setRotation(-3*angle);
	square1.move(sf::Vector2f(0,sin(angle)));
	square2.move(sf::Vector2f(0,sin(angle)));
	square1.setOutlineColor(sf::Color(0,255,0,alpha));
	square2.setOutlineColor(sf::Color(0,255,0,alpha));
}
void StartPoint::draw(sf::RenderWindow & window){
	window.draw(square1);
	window.draw(square2);
}
bool StartPoint::pointIn(sf::Vector2f point){
	return (position.x-point.x)*(position.x-point.x) + (position.y-point.y)*(position.y-point.y) < 
		(TILE_SIZE*CHUNK_SIZE/8) * (TILE_SIZE*CHUNK_SIZE/8);
}
bool StartPoint::isActive(){
	return fadeDir;
}