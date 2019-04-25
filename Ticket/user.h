#pragma once

#include "bplustree.hpp"
#include "tool.h"

class user {
	String id, name, passwd,email,phone;
public:
	user(const String &i, const String &n, const String &p,
		const String &e, const String &ph)
		:id(i), name(n), passwd(p), email(e), phone(ph) {}

	bool match(String _pswd) { return _pswd == passwd; }
};

class userSystem {
	bplustree<String, user, 4096> B;

};