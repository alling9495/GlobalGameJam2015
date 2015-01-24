#import "World.h"

World::World(int seed)
	seed(seed)
{
	//Do initial world generation
}

World::update(int elapsed){
	bool top = isPlayerNearTop();
	bool bootom = isPlayerNearBottom();
	bool left = isPlayerNearLeft();
	bool right = isPlayerNearRight();


}
World::draw(sf::RenderWindow & window){

}

bool World::isPlayerNearTop(){
	const sf::Vector2f pos = player.getPosition();
	return  ((pos.y%(CHUNK_SIZE * TILE_SIZE))/(CHUNK_SIZE*TILE_SIZE) < 0.5)
}
bool World::isPlayerNearBottom(){
	return !(isPlayerNearTop())
}

bool World::isPlayerNearLeft(){
	const sf::Vector2f pos = player.getPosition();
	return  ((pos.x%(CHUNK_SIZE * TILE_SIZE))/(CHUNK_SIZE*TILE_SIZE) < 0.5)
}
bool World::isPlayerNearRight(){
	return !(isPlayerNearLeft())
}
