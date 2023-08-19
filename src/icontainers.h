#pragma once
#include "imemory.h"
#include <vector>
#include <map>
#include <unordered_map>

ISL_BEGIN

//Using Allocator to manage container memory distribution.

template<class T>			using Vector	= std::vector<T, is::Allocator<T>>;
template<class K, class V>	using Map		= std::map<K, V, std::less<K>, is::Allocator<std::pair<const K, V>>>;
template<class K, class V>	using HashMap	= std::unordered_map<K, V, std::hash<K>, std::equal_to<K>, is::Allocator<std::pair<const K, V>>>;

ISL_END
