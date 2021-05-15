#include <string>
#include <vector>
#include <fstream>
#include <forward_list>
using namespace std;

struct datetime
{
	int day = 0;
	int	month = 0;
	int year = 0;
	int hour = 0;
	int	min = 0;
	int sec = 0;
};

struct message_info
{
	datetime date;
	string username;
	string message;

	void print() {
		cout << date.day << "." << date.month << "." << date.year << " " << date.hour << ":"
			<< date.min << ":" << date.sec << " " << username << ": " << message << endl;
	}

	void clear() {
		date.day = 0;
		date.month = 0;
		date.year = 0;
		date.hour = 0;
		date.month = 0;
		date.sec = 0;
		username.clear();
		message.clear();
	}
};

void read_file(ifstream &instream, forward_list<message_info> &flist);
bool check_datetime(const message_info& minfo);
bool is_digit_string(const string& str);
bool get_datatime(message_info& minfo, const string& str);
bool get_message_info(message_info& minfo, const string& buf);
void split_words(vector<string>& vec, const string& src);
void split_to_vector(vector<string>& vec, string dlm, const string& src);

void read_file(ifstream &in, forward_list<message_info> &flist)
{
	message_info m_info;
	string string_buf;

	while (getline(in, string_buf)) {
		if (!get_message_info(m_info, string_buf))
			continue;
		flist.push_front(m_info);
		string_buf.clear();
	}
}


bool is_digit_string(const string &str)
{
	for (int i = 0; i < str.length(); i++)
		if (!isdigit(str[i]))
			return false;
	return true;
}

bool check_datetime(const message_info &m_info)
{
	if ((m_info.date.day < 1 || m_info.date.day > 30) &&
		(m_info.date.month == 4 || m_info.date.month == 6 ||
			m_info.date.month == 9 || m_info.date.month == 11))
		return false;
	else if ((m_info.date.day < 1 || m_info.date.day > 31) &&
		(m_info.date.month == 1 || m_info.date.month == 3 ||
			m_info.date.month == 5 || m_info.date.month == 7 ||
			m_info.date.month == 8 || m_info.date.month == 10 ||
			m_info.date.month == 12))
		return false;
	else if (m_info.date.month == 2) {
		if (m_info.date.year % 4 == 0)
			if (m_info.date.day < 1 || m_info.date.day > 29)
				return (false);
			else if (m_info.date.year % 4 != 0)
				if (m_info.date.day < 1 || m_info.date.day > 28)
					return (false);
	}
	return (true);
}

bool get_datetime(message_info &m_info, const string &str)
{
	vector<string> datetime_vec;
	int number;

	split_to_vector(datetime_vec, " .:", str); // заносим в вектор разбивая по указанным символам
	if (datetime_vec.size() != 6)
		return false;
	if (is_digit_string(datetime_vec[5])) {
		number = atoi(datetime_vec[5].c_str());
		if (number < 0 || number > 60)
			return false;
		m_info.date.sec = number;
	}
	if (is_digit_string(datetime_vec[4])) {
		number = atoi(datetime_vec[4].c_str());
		if (number < 0 || number > 60)
			return false;
		m_info.date.min = number;
	}
	if (is_digit_string(datetime_vec[3])) {
		number = atoi(datetime_vec[3].c_str());
		if (number < 0 || number > 24)
			return false;
		m_info.date.hour = number;
	}
	if (is_digit_string(datetime_vec[2])) {
		number = atoi(datetime_vec[2].c_str());
		if (number < 1973 || number > 3000)
			return false;
		m_info.date.year = number;
	}
	if (is_digit_string(datetime_vec[1])) {
		number = atoi(datetime_vec[1].c_str());
		if (number < 1 || number > 12)
			return false;
		m_info.date.month = number;
	}
	if (is_digit_string(datetime_vec[0])) {
		m_info.date.day = atoi(datetime_vec[0].c_str());
		if (!check_datetime(m_info))
			return false;
	}
	return true;
}

bool get_message_info(message_info& m_info, const string &buf)
{
	vector<string> vec_info;

	split_words(vec_info, buf);
	if (vec_info.size() != 3)
		return false;
	if (!get_datetime(m_info, vec_info[0]))
		return false;
	m_info.username = vec_info[1];
	m_info.message = vec_info[2];
	return true;
}

void split_words(vector<string> &vec, const string &src)
{
	string temp_buf;

	for (int i = 0; i < src.length(); i++) {
		if (src[i] == '<') {
			i++;
			while (src[i] && src[i] != '>') {
				temp_buf += src[i];
				i++;
			}
			vec.push_back(temp_buf);
			temp_buf.clear();
		}
	}
}

void split_to_vector(vector<string> &vec, string dlm, const string &src)
{
	size_t p;
	size_t start = 0;
	size_t len = src.length();

	vec.clear();
	start = src.find_first_not_of(dlm);
	p = src.find_first_of(dlm, start);
	while (p != string::npos) {
		vec.push_back(src.substr(start, p - start));
		start = src.find_first_not_of(dlm, p);
		p = src.find_first_of(dlm, start);
	}
	if (len > start)
		vec.push_back(src.substr(start, len - start));
}
