#include "istring.h"
#include "iassert.h"
#include "imemory.h"
#include <cstring>

ISL_BEGIN


inline usize lengthof(cstring str) {
	isl_assert(str != nullptr);
	usize len = 0;
	for (; str[len]; ++len);
	return len;
}


cstring StringMeta::get_data() { return data; }

usize StringMeta::get_length() { return length; }

cstring StringMeta::operator~() { return data; }

char& StringMeta::operator[](usize idx) {
	isl_assert(data != nullptr);
	isl_assert(idx < length);
	return data[idx];
}

bool StringMeta::operator==(const StringMeta& another) {
	if (another.length != length) return false;
	if (another.data == data) return true;
	for (usize i = 0; i < length; ++i)
		if (another.data[i] != data[i]) return false;
	return true;
}


RefString::RefString(lstring lit) {
	data = (cstring)lit;
	length = lengthof(data);
}

RefString::RefString(lstring lit, usize len) {
	data = (cstring)lit;
	length = len;
}

RefString::RefString(StringMeta meta) {
	data = meta.get_data();
	length = meta.get_length();
}

void RefString::clear() {
	data = nullptr;
	length = 0;
}

RefString& RefString::operator=(StringMeta& meta) {
	data = meta.get_data();
	length = meta.get_length();
	return *this;
}

RefString& RefString::operator=(lstring str) {
	data = (cstring)str;
	length = lengthof(data);
	return *this;
}


String::String(lstring lit) {
	copy((cstring)lit, lengthof((cstring)lit), true);
}

String::String(lstring lit, usize len) {
	copy((cstring)lit, len, true);
}

String::String(StringMeta meta) {
	copy(meta.get_data(), meta.get_length(), true);
}

String::String(const String& str) {
	copy(str.data, str.length, true);
}

String::String(String&& str) noexcept {
	this->operator=(is::move(str));
}

void String::clear() {
	length = 0;
	if (data) isl_free_ary(data);
	data = nullptr;
}

void String::copy(cstring str, usize len, bool is_init) {
	if (!is_init) clear();
	length = len;
	data = (cstring)memcpy(isl_malloc_ary(char, length + 1), str, length);
	data[length] = '\0';
}

String& String::operator=(String&& str) noexcept {
	clear();
	length = str.length;
	data = str.data;
	str.data = nullptr;
	str.length = 0;
	return *this;
}

String& String::operator=(StringMeta& meta) {
	copy(meta.get_data(), meta.get_length());
	return *this;
}

String& String::operator=(lstring str) {
	copy((cstring)str, lengthof((cstring)str));
	return *this;
}

String& String::operator=(const String& str) {
	copy(str.data, str.length);
	return *this;
}

String::~String() {
	clear();
}

ISL_END