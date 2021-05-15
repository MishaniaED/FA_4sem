#include <iostream>
#include <fstream>
#include <forward_list>
#include "parser.h"
#include "relation.h"
using namespace std;

void menu();
void get_date_and_time(message_info &m_info);

int	main(void)
{
	forward_list<message_info> messages_info_flist;

	ifstream in("input.txt");
	if (in.fail())
		return 0;
	read_file(in, messages_info_flist);

	StratagyComparator<message_info *>* cmp_datetime = new Comparator_datetime;
	StratagyComparator<message_info *>* cmp_username = new Comparator_username;
	StratagyComparator<message_info *>* cmp_message = new Comparator_message;
	StratagyComparator<message_info *>* cmp_dt_uname = new Comparator_datetime_username;
	RB_tree<message_info *> rb_username(cmp_username);
	RB_tree<message_info *> rb_dt_and_uname(cmp_dt_uname);
	AVL_tree<message_info *> avl_datetime(cmp_datetime);
	AVL_tree<message_info *> avl_message(cmp_message);
	Relation<message_info> relations;

	relations.insert_index(&avl_datetime);	
	for (auto it = messages_info_flist.begin(); it != messages_info_flist.end(); it++)
		relations.insert_data(*it);
	relations.insert_index(&rb_username);
	relations.insert_index(&avl_message);
	relations.insert_index(&rb_dt_and_uname);
	
	int	operation;
	datetime dt;
	message_info info;

	while (true) {
		menu();
		cin >> operation;
		if (operation == 0)
			break;
		switch (operation) {
		case 0:
			return 0;
		case 1:
			get_date_and_time(info);
			if (relations.search_data(info))
				cout << "\n[SEARCH END SUCCESSFULLY]\n";
			else
				cout << "\n[SEARCH FAILURE]\n";
			break;
		case 2:
			cout << "\nEnter username: ";
			cin.ignore();
			getline(cin, info.username);
			if (relations.search_data(info))
				cout << "\n[SEARCH END SUCCESSFULLY]\n";
			else
				cout << "\n[SEARCH FAILURE]\n";
			break;
		case 3:
			cout << "\nEnter message: ";
			cin.ignore();
			getline(cin, info.message);
			if (relations.search_data(info))
				cout << "\n[SEARCH END SUCCESSFULLY]\n";
			else
				cout << "\n[SEARCH FAILURE]\n";
			break;
		case 4:
			get_date_and_time(info);
			cout << "\nEnter username: ";
			getline(cin, info.username);
			if (relations.search_data(info))
				cout << "\n[SEARCH END SUCCESSFULLY]\n";
			else
				cout << "\n[SEARCH FAILURE]\n";
			break;
		default:
			cout << "\n[Incorrect operation number]\n[Try again]\n";
			break;
		};
		info.clear();
	}
	return 0;
}

void menu()
{
	cout << "\nSearch by:\n";
	cout << "0 - exit\n";
	cout << "1 - date and time\n";
	cout << "2 - username\n";
	cout << "3 - message\n";
	cout << "4 - datetime and username\n";
	cout << "Enter operation number: ";
}

void get_date_and_time(message_info &info)
{
	cout << "\nEnter date (dd mm yyyy): ";
	cin >> info.date.day >> info.date.month >> info.date.year;
	cout << "Enter time (hh mm ss): ";
	cin >> info.date.hour >> info.date.min >> info.date.sec;
}
