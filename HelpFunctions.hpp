#ifndef SFML_HELP_FUNCTIONS_HPP
#define SFML_HELP_FUNCTIONS_HPP

#include <iostream>

#include <SFML/Graphics.hpp>


namespace clever
{


template<typename T, typename U> sf::Vector2<T>
conversion(sf::Vector2<U> const &vec)
{
	return sf::Vector2<T>(T(vec.x), T(vec.y));
}

template<typename T>
std::ostream &operator<<(std::ostream &os, sf::Vector2<T> const &vec)
{
	return os << "(" << vec.x << ", " << vec.y << ")";
}
template<typename T>
std::istream &operator>>(std::ostream &is, sf::Vector2<T> &vec)
{
	return is >> vec.x >> vec.y;
}


template<typename T>
std::ostream &operator<<(std::ostream &os, sf::Rect<T> const &rect)
{
	return os << "(" << rect.left << ", " << rect.top <<
		")&(" << rect.width << ", " << rect.height << ")";
}
template<typename T>
std::istream &operator<<(std::istream &is, sf::Rect<T> &rect)
{
	return is >> rect.left >> rect.top >> rect.width >> rect.height;
}



template<typename T, typename U>
sf::Vector2<decltype(T()+U())> operator+(
	sf::Vector2<T> const &lhs,
	sf::Vector2<U> const &rhs
)
{
	return {lhs.x+rhs.x, lhs.y+rhs.y};
}

template<typename T, typename U>
sf::Vector2<decltype(T()-U())> operator-(
	sf::Vector2<T> const &lhs,
	sf::Vector2<U> const &rhs
)
{
	return {lhs.x-rhs.x, lhs.y-rhs.y};
}

template<typename T, typename U>
sf::Vector2<decltype(T()*U())> operator*(
	sf::Vector2<T> const &lhs,
	sf::Vector2<U> const &rhs
)
{
	return {lhs.x*rhs.x, lhs.y*rhs.y};
}

template<typename T, typename U>
sf::Vector2<decltype(T()/U())> operator/(
	sf::Vector2<T> const &lhs,
	sf::Vector2<U> const &rhs
)
{
	return {lhs.x/rhs.x, lhs.y/rhs.y};
}


}


#endif // SFML_HELP_FUNCTIONS_HPP
