#pragma once

#include <string>

#define RES_DIR        "Resources\\"
#define RES_SHADER_DIR "Resources\\Shaders\\"
#define RES_IMAGE_DIR  "Resources\\Images\\"


//All types  passed to template should have a static member ResourceMap
template <typename T>
class ResourceManager {
public:
	//This will only load if does not exist, otherwise will return looked up element
	static T* Load(std::string   name);
	//Will simply unload resource if exists
	static void Unload(std::string name);
	//Will load or delete existing and load new
	static T* Reload(std::string name);
};

template <typename T>
inline T* ResourceManager<T>::Load(std::string   name) {
	auto iter = T::ResourceMap.find(name);
	if (iter != T::ResourceMap.end())
		return &iter->second;
	auto ret = T::ResourceMap.insert(std::make_pair(name, T(name)));
	return &ret.first->second;
};

template <typename T>
inline void ResourceManager<T>::Unload(std::string name) {
	T::ResourceMap.erase(name);
};

template<typename T>
inline T* ResourceManager<T>::Reload(std::string name) {
	T::ResourceMap.erase(name);
	auto ret = T::ResourceMap.insert(std::make_pair(name, T(name)));
	return &ret.first->second;
};