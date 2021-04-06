#pragma once

#pragma region STDINCLUDE

#include <unordered_map>

#pragma endregion

#pragma region NOSTDINCLUDE

#include <API/Identifier.h>
#include <API/Utils.h>

#pragma endregion

template <class T>
class Repository
{
public:
	Repository(const Identifier& ownerID);
	~Repository();

	bool contains(const std::string &key) const;

	bool store_optional(const std::string& key, const T& value);
	void store(const std::string& key, const T& value);

	const T& get_optional(const std::string& key, bool& exists);
	const T& get(const std::string& key);

	Identifier::numeric_type count() const;

private:
	Identifier __ownerID;
	std::unordered_map<std::string, T> __keymap;
};

template<class T>
inline Repository<T>::Repository(const Identifier& ownerID) : __ownerID(ownerID)
{
}

template<class T>
inline Repository<T>::~Repository()
{
}

template<class T>
inline bool Repository<T>::contains(const std::string& key) const
{
	auto it = __keymap.find(key);

	return it != __keymap.end();
}

template<class T>
inline bool Repository<T>::store_optional(const std::string& key, const T& value)
{
	if (contains(key)) {
		return false;
	}

	__keymap[key] = value;

	return true;
}

template<class T>
inline void Repository<T>::store(const std::string& key, const T& value)
{
	__keymap[key] = value;
}

template<class T>
inline const T& Repository<T>::get_optional(const std::string& key, bool& exists)
{
	if (!contains(key)) {
		exists = false;
		return T();
	}

	exists = true;
	return __keymap[key];
}

template<class T>
inline const T& Repository<T>::get(const std::string& key)
{
	if (!contains(key)) {
		throw std::runtime_error("No key-value found.");
	}

	return __keymap[key];
}

template<class T>
inline Identifier::numeric_type Repository<T>::count() const
{
	return (Identifier::numeric_type)__keymap.size();
}
