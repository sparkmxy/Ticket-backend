#pragma once

#include "bplustree.hpp"
#include "tool.h"

class purchaseLog;

class keyRecord {
	friend class purchaseLog;
	String userID, Date, catalog, trainID, from, to;
public:

	bool operator < (const keyRecord &k) const {
		if (userID != k.userID) return userID < k.userID;
		if (Date!= k.Date) return Date < k.Date;
		if (catalog != k.catalog) return catalog < k.catalog;
		if (trainID != k.trainID) return trainID < k.trainID;
		if (from != k.from) return from < k.from;
		return to < k.to;
	}
};

class record :public keyRecord {
	static const int maxClassN = 5;
	friend class purchaseLog;
	Time leave, arrive;
	int num[maxClassN];
public:

};

class purchaseLog {
	bplustree<keyRecord, record, 4096> B;
	static bool showOption;
public:
	purchaseLog() {
		B.initialize("logData","logBptFile","logAlloc","logBptAlloc");
	}

	static void showReturned() { showOption = true; }
	void add();
	void refund();
	vector<record> query();

};

