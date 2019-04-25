#include "user.h"

int userSystem::add(const vector<parameter> &V) {
	if (V.size() != 4) return false;
	for (int i = 0; i < 4; i++) if (V[i].first != STRING) return false;
	if (names.count(V[1].second)) return -1;
	B.insert(currentID, user(currentID, V[0].second, V[1].second, V[2].second,V[3].second));
	return currentID++;
}

bool userSystem::login(const int &id, const String pswd) const {
	if (!B.count(id)) return false;
	return B.find(id).match(pswd);
}

