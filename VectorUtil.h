#ifndef __VECTOR_UTIL_H__
#define __VECTOR_UTIL_H__ value
class VectorUtil{
public: 
	static sf::Vector2f offset(const sf::Vector2f & a, const sf::Vector2f & off){
	return sf::Vector2f(a.x+off.x,a.y+off.y);
	}

};
#endif