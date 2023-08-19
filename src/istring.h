#pragma once
#include "imemory.h"
#include "itypes.h"

ISL_BEGIN


usize lengthof(cstring str);

//string-meta was the common part of reference-string and string
class StringMeta {
protected:
	cstring data{ nullptr };
	usize length{ 0 };
public:
	_ISL_GEN_DEFAULT_NEW_AND_DELETE_FN(StringMeta);

	//default construction
	StringMeta() = default;

	//just the getter
	cstring get_data();
	usize get_length();

	//get char value of this string
	char& operator[](usize idx);

	//compare data and length of this and another string
	bool operator==(const StringMeta& another);

	//get data of this StringMeta
	cstring operator~();
};

//islang reference string
class RefString : public StringMeta {
public:
	_ISL_GEN_DEFAULT_NEW_AND_DELETE_FN(RefString);

	//public the string-meta member: data & length
	using StringMeta::data;
	using StringMeta::length;

	//default construction
	RefString() = default;

	//init by literal string
	explicit RefString(lstring lit);

	//init by literal string and length
	explicit RefString(lstring lit, usize len);

	//init by string-meta
	explicit RefString(StringMeta meta);

	//clear set data to nullptr, set length to zero
	void clear();

	//assignment was just the shallow copy
	RefString& operator=(StringMeta& meta);
	RefString& operator=(lstring str);
};

//islang string
class String : public StringMeta {
public:
	_ISL_GEN_DEFAULT_NEW_AND_DELETE_FN(String);

	//default construction
	String() = default;

	//init by literal string
	String(lstring lit);

	//init by literal string and length
	String(lstring lit, usize len);

	//init by string-meta
	String(StringMeta meta);

	//init by lvalue-string
	String(const String& str);

	//init by rvalue-string
	String(String&& str) noexcept;

	//clear free data to nullptr, set length to zero
	void clear();

	//deepth copy
	void copy(cstring str, usize len, bool is_init = false);

	//assignment was the deepth copy
	String& operator=(lstring str);
	String& operator=(const String& str);
	String& operator=(String&& str) noexcept;
	String& operator=(StringMeta& meta);

	//destructor
	~String();

};


ISL_END