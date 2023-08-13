#pragma once
#include "imemory.h"
#include <vector>
#include <map>
#include <unordered_map>

//Using Allocator to manage container memory distribution.
namespace is {
	template<class T>			using vector	= std::vector<T, is::memory::Allocator<T>>;
	template<class K, class V>	using map		= std::map<K, V, std::less<K>, is::memory::Allocator<std::pair<const K, V>>>;
	template<class K, class V>	using hash_map	= std::unordered_map<K, V, std::hash<K>, std::equal_to<K>, is::memory::Allocator<std::pair<const K, V>>>;
}
