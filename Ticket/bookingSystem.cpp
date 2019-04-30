#include "bookingSystem.h"


const int numOfCommands = 16;


const std::string CMD[numOfCommands] = {
	"register","query_profile","modify_profile","modify_privilege",
	"query_ticket,", "query_transfer",
	"buy_ticket", "query_order", "refund_ticket",
	"add_train", "sale_train", "query_train","delete_train","modify_train",
	"clean","exit"
};

void ticketBookingSystem::process
(const std::string &cmd, const vector<token> &V) {
	int idx = 0;
	while (idx < numOfCommands && cmd != CMD[idx]) idx++;
	if (idx == numOfCommands) throw wrong_command();
	switch (idx){

	case 0:	Register(V); break;
	case 1:	profile(V); break;
	case 2: modifyProfile(V); break;
	case 3: modifyType(V); break;
	case 4: queryTicket(V); break;
	case 5: transfer(V); break;
	case 6: buy(V); break;
	case 7: queryOrder(V); break;
	case 8: refund(V); break;
	case 9: addTrain(V); break;
	case 10: sale(V); break;
	case 11: queryTrain(V); break;
	case 12: remove(V); break;
	case 13: modifyTrain(V); break;
	case 14: clear(); break;
	case 15: exit(0);
	default: break;

	}
} 

void ticketBookingSystem::Register(const vector<token> &V) {
	if (User.add(V) == -1) {

	}
}

void ticketBookingSystem::profile(const vector<token> &V) {
	if (V.size() != 1 || V[0].first != INT) throw wrong_parameter();
	auto result = User.query(V[0].second.asint());
	if (result.first) os << result.second << endl;
	else os << 0 << endl;
}

void ticketBookingSystem::modifyProfile(const vector<token> &V) {
	os << (User.modify(V)) << endl;
}

void ticketBookingSystem::modifyType(const vector<token> &V) {
	if (V.size() != 3) throw wrong_parameter();
	for (int i = 0; i < 3; i++)
		if (V[i].first != INT) throw wrong_parameter();
	os << User.modifyPrivilege(V[0].second.asint(), V[1].second.asint, V[2].second.asint()) << endl;
}

void  ticketBookingSystem::queryTicket(const vector<token> &V) {
	if (V.size() != 4 || V[2].first != DATE ||
		V[0].first != STRING || V[1].first != STRING || V[3].first != STRING)
		throw wrong_parameter();
	auto U = Ticket.query(V[0].second, V[1].second, V[2].second.asdate(),V[3].second);
	for (int i = 0; i < U.size(); i++)
		os << U[i] << endl;
}

void ticketBookingSystem::transfer(const vector<token> &V) {
	if (V.size() != 4 || V[2].first != DATE ||
		V[0].first != STRING || V[1].first != STRING || V[3].first != STRING)
		throw wrong_parameter();
	auto t = Ticket.transfer(V[0].second, V[1].second, V[2].second.asdate(), V[3].second);
	if (t.first.valid()) os << t.first << '\n' << t.second << endl;
	else os << -1 << endl;
}

void ticketBookingSystem::buy(const vector<token> &V) {
	if (V.size() != 7 ||
		V[0].first != INT || V[1].first != INT || V[5].first != DATE)
		throw wrong_parameter();
	if (!Train.modifyTicket(&Log, V))
		throw wrong_parameter();
}

void ticketBookingSystem::queryOrder(const vector<token> &V) {
	auto U = Log.query(V);
	os << U.size() << endl;
	for (int i = 0; i < U.size(); i++) os << U[i] << endl;
}

void ticketBookingSystem::refund(const vector<token> &V) {
	if (V.size() != 7 ||
		V[0].first != INT || V[1].first != INT || V[5].first != DATE)
		throw wrong_parameter();
	Train.modifyTicket(&Log, V, -1);
}

void ticketBookingSystem::sale(const vector<token> &V) {
	if (V.size() != 1 || V[0].first != STRING) throw wrong_parameter();
	os << Train.sale(V[0].second) << endl;
}

void ticketBookingSystem::remove(const vector<token> &V) {
	if (V.size() != 1 || V[0].first != STRING) throw wrong_parameter();
	os << Train.remove(V[0].second)<< endl;
}

void ticketBookingSystem::clear() {
	Log.clear();
	Train.clear();
	Ticket.clear();
	User.clear();
}

void ticketBookingSystem::queryTrain(const vector<token> &V) {
	if (V.size() != 1 || V[0].first != STRING) throw wrong_parameter();
	auto result = Train.query(V[0].second);
	if (!result.first) os << 0 << endl;
	else os << result.second << endl;
}