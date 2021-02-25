#pragma once

#include <vector>

/*
  Une optimisation de std::vector.
  Multiplie la capacite du vecteur par 1.5 quand
  la taille depasse la capacite.
  Permet d'eviter de faire trop d'allocations et
  de copies, tout en gaspillant peu de memoire.
*/
template<typename T>
class BetterVector: public std::vector<T>
{
	using std::vector<T>::vector;

public:
	void push_back(const T& value)
	{
		size_t cap = std::vector<T>::capacity();

		if (cap <= std::vector<T>::size())
			std::vector<T>::reserve(cap + cap / 2);

		std::vector<T>::push_back(value);
	}

	void push_back(T&& value)
	{
		size_t cap = std::vector<T>::capacity();

		if (cap <= std::vector<T>::size())
			std::vector<T>::reserve(cap + cap / 2);

		std::vector<T>::push_back(std::move(value));
	}

	template<typename... Args>
	T& emplace_back(Args&&... args)
	{
		size_t cap = std::vector<T>::capacity();

		if (cap <= std::vector<T>::size())
			std::vector<T>::reserve(cap + cap / 2);

		std::vector<T>::emplace_back(std::forward<Args>(args)...);
		return std::vector<T>::back();
	}
};