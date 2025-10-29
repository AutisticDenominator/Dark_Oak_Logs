#include <map>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <ctime>
using namespace std;
//TODO: I guess only the encrypting/decrypting part
class Attributes {
public:
	string title;
	string content;
	string output;
	time_t timestamp;
	char str_timestamp[26];
};

Attributes Attribute;

class Core_Capabilities {
public:
	void Write_New_Log() {
		cout << "Write the title of your new log:\n";
		cin.ignore();
		getline(cin, Attribute.title);
		system("cls");

		cout << "Write the content of your new log:\n(don't press enter unless you want to confirm the log)\n";
		getline(cin, Attribute.content);
		system("cls");

		time(&Attribute.timestamp);
		ctime_s(&Attribute.str_timestamp[0], sizeof(Attribute.str_timestamp), &Attribute.timestamp);
		return;
	}

	bool Store_New_Log() {
		try {
			Attribute.output = "|title|" + Attribute.title + "\n" + "|timestamp|";

			for (int s = 0; s < 24; s++) {
				Attribute.output = Attribute.output + Attribute.str_timestamp[s];
			}

			Attribute.output = Attribute.output + "\n" + "|content|" + Attribute.content + "\n";

			int new_log_number = 0;
			bool found = false;

			while (found == false) {
				ifstream File("C:\\DOLlogs\\log" + to_string(new_log_number) + ".txt");

				if (File.fail()) {
					found = true;
				}
				else {
					new_log_number = new_log_number + 1;
				}

				File.close();
			}

			bool written = false;
			while (written == false) {
				ofstream New_Log("C:\\DOLlogs\\log" + to_string(new_log_number) + ".txt");

				if (New_Log.fail()) {
					system("mkdir C:\\DOLlogs");
				}
				else {
					New_Log << Attribute.output;
					written = true;
				}

				New_Log.close();
			}

			return true;
		}
		catch (...) {
			return false;
		}
	}

	string Read_Log(string name) {
		ifstream File("C:\\DOLlogs\\" + name + ".txt");

		if (File.fail()) {
			File.close();
			return "";
		}

		string line_content;
		string file_content;

		while (getline(File, line_content)) {
			int symbol_count = 0;
			string filtered_line;

			for (int i = 0; i < line_content.size(); i++) {
				if (line_content[i] == '|') {
					symbol_count = symbol_count + 1;
					continue;
				}
				else if ((symbol_count % 2) == 1) {
					continue;
				}
				else {
					filtered_line = filtered_line + line_content[i];
				}
			}

			file_content = file_content + filtered_line + "\n";
		}

		File.close();

		return file_content;
	}

	void Created_Logs() {
		bool failed = false;
		int max_number_log = 0;

		while (failed == false) {
			ifstream File("C:\\DOLlogs\\log" + to_string(max_number_log) + ".txt");

			if (File.fail()) {
				failed = true;
			}
			else {
				max_number_log = max_number_log + 1;
			}

			File.close();
		}

		string all_created;

		for (int c = 0; c < max_number_log; c++) {
			ifstream File("C:\\DOLlogs\\log" + to_string(c) + ".txt");

			string line_content;
			string title;
			string timestamp;

			while (getline(File, line_content)) {
				int symbol_count = 0;
				string filtered_line;

				for (int i = 0; i < line_content.size(); i++) {
					if (line_content[i] == '|') {
						symbol_count = symbol_count + 1;
						continue;
					}
					else if ((symbol_count % 2) == 1) {
						continue;
					}
					else {
						filtered_line = filtered_line + line_content[i];
					}
				}

				if (line_content.size() >= 4) {
					if (line_content[3] == 'm' && line_content[0] == '|') {
						timestamp = filtered_line;
					}
					else if (line_content[3] == 't' && line_content[0] == '|') {
						title = filtered_line;
					}
					else {
						continue;
					}
				}
			}

			File.close();

			all_created = all_created + "log" + to_string(c) + "---" + title + "---" + timestamp + "\n";
		}

		cout << all_created;
	}
};

Core_Capabilities Core;

class Cryptography {
public:
	map<int, int> password_numbers;
	map<int, int> password_int_final;

	string alphabet_lowercase = "abcdefghijklmnopqrstuvwxyz";
	string alphabet_uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int password_map_size = 0;

	bool Password_String_To_Int(string password) {
		password_numbers.clear();

		if (password.size() < 4) {
			return false;
		}

		for (int i = 0; i < password.size(); i++) {
			bool found = false;

			for (int c = 0; c < 26; c++) {
				if (password[i] == alphabet_lowercase[c]) {
					password_numbers[i] = c;
					found = true;
					break;
				}
				else if (password[i] == alphabet_uppercase[c]) {
					password_numbers[i] = c;
					found = true;
					break;
				}
			}

			if (found == false) {
				return false;
			}
		}

		return true;
	}

	bool Password_Modification(string password) {
		password_int_final.clear();

		int multiplier;
		string multiplier_temp;
		string final_password_temp;

		for (int i = 0; i < 4; i++) {
			for (int c = 0; c < 26; c++) {
				if (password[i] == alphabet_lowercase[c]) {
					multiplier_temp = multiplier_temp + to_string(c);
				}
				else if (password[i] == alphabet_uppercase[c]) {
					multiplier_temp = multiplier_temp + to_string(c);
				}
			}
		}

		multiplier = stoi(multiplier_temp);
		multiplier = multiplier * multiplier;

		for (auto it = password_numbers.begin(); it != password_numbers.end(); it++) {
			it->second = it->second * multiplier;

			final_password_temp = final_password_temp + to_string(it->second);
		}

		for (int j = 0; j < final_password_temp.size(); j += 2) {
			char temp_letter = final_password_temp[j];
			char* temp_pointer = &temp_letter;

			if ((j + 1) >= final_password_temp.size()) {
				password_int_final[j / 2] = atoi(temp_pointer);
				break;
			}

			char second_letter = final_password_temp[j + 1];
			char* second_pointer = &second_letter;

			if (atoi(temp_pointer) == 0) {
				password_int_final[j / 2] = atoi(second_pointer);
				continue;
			}

			string temp_add = to_string(temp_letter) + second_letter;
			password_int_final[j / 2] = stoi(temp_add);
		}

		return true;
	}

	void Password_Size() {
		password_map_size = 0;

		for (auto it = password_int_final.begin(); it != password_int_final.end(); it++) {
			password_map_size = password_map_size + 1;
		}
	}

	bool Standard_Check(string password, string name) {
		bool status = Password_String_To_Int(password);

		if (status == false) {
			return false;
		}

		bool status_modifier = Password_Modification(password);

		if (status_modifier == false) {
			return false;
		}

		Password_Size();

		return true;
	}

	bool Replace_Log_Text(string new_content, string name) {
		string temp_line;
		string final_log;
		int counter = 0;
		ofstream File_temp("C:\\DOLlogs\\temp.txt");
		File_temp << new_content;
		File_temp.close();

		ifstream File_Read("C:\\DOLlogs\\temp.txt");

		//this is also wrong by the way
		while (getline(File_Read, temp_line)) {
			bool valid_line = false;

			for (int j = 0; j < 26; j++) {
				if (temp_line[0] == alphabet_lowercase[j]) {
					valid_line = true;
				} 
				else if (temp_line[0] == alphabet_uppercase[j]) {
					valid_line = true;
				}
			}

			if (valid_line == true) {
				counter = counter + 1;
			}
			else {
				continue;
			}

			switch (counter) {
			case 1:
				final_log = final_log + "|title|" + temp_line + "\n";
				break;
			case 2:
				final_log = final_log + "|timestamp|" + temp_line + "\n";
				break;
			case 3:
				final_log = final_log + "|content|" + temp_line + "\n";
				break;
			default:
				final_log = final_log + temp_line + "\n";
				break;
			}
		}
		File_Read.close();
		remove("C:\\DOLlogs\\temp.txt");

		ofstream File("C:\\DOLlogs\\" + name + ".txt");
		File << final_log;

		return true;
	}

	bool Encryption(string password, string name) {
		//bro created 10 letters out of 4. WHYYYYYYY
		string content = Core.Read_Log(name);

		if (content == "") {
			return false;
		}

		bool standard_status = Standard_Check(password, name);

		if (standard_status == false) {
			return false;
		}

		for (int i = 0; i < content.size(); i++) {
			if (content[i] == ' ' /* || content[i] == '' */) {
				continue;
			}

			bool lowercase = true;
			int letter_index = 0;
			bool valid = false;

			for (int c = 0; c < 26; c++) {
				if (content[i] == alphabet_uppercase[c]) {
					lowercase = false;
					letter_index = c;
					valid = true;
					break;
				}
				else if (content[i] == alphabet_lowercase[c]) {
					letter_index = c;
					valid = true;
					break;
				}
				else {
					valid = false;
				}
			}

			if (valid == false) {
				continue;
			}

			if (lowercase) {
				content[i] = alphabet_lowercase[(letter_index + password_int_final[i % password_map_size]) % 26];
			}
			else {
				content[i] = alphabet_uppercase[(letter_index + password_int_final[i % password_map_size]) % 26];
			}
		}

		bool end_status = Replace_Log_Text(content, name);

		return end_status;
	}

	bool Decryption(string password, string name) {
		string content = Core.Read_Log(name);

		bool standard_status = Standard_Check(password, name);

		if (standard_status == false) {
			return false;
		}

		for (int i = 0; i < content.size(); i++) {
			if (content[i] == ' ' /* || content[i] == ''*/) {
				continue;
			}

			bool lowercase = true;
			int letter_index = 0;
			bool valid = false;

			for (int c = 0; c < 26; c++) {
				if (content[i] == alphabet_uppercase[c]) {
					lowercase = false;
					letter_index = c;
					valid = true;
					break;
				}
				else if (content[i] == alphabet_lowercase[c]) {
					letter_index = c;
					valid = true;
					break;
				}
				else {
					valid = false;
				}
			}

			if (valid == false) {
				continue;
			}

			if (lowercase) {
				//the +1040 just so it doesnt go below 0 as the % operator doesnt perform the correct modulo operation as it is only remainder division

				content[i] = alphabet_lowercase[(1040 + letter_index - password_int_final[i % password_map_size]) % 26];
			}
			else {
				content[i] = alphabet_uppercase[(1040 + letter_index - password_int_final[i % password_map_size]) % 26];
			}
		}

		bool end_status = Replace_Log_Text(content, name);

		return end_status;
	}
};

Cryptography Cypher;

class Unifying_Functions {
public:
	void Write_To_Proceed() {
		string useless_input;

		cout << "Write anything and confirm to proceed.\n";
		cin >> useless_input;

		return;
	}

	void Console() {
		system("cls");

		string start_input;
		cout << "What do you wish to do?\n";
		cin >> start_input;

		system("cls");

		if (start_input == "write") {
			Core.Write_New_Log();
			bool stored = Core.Store_New_Log();

			cout << "Process succesful: " + to_string(stored) + "\n";
			Write_To_Proceed();
		}
		else if (start_input == "read") {
			Core.Created_Logs();

			string log_name;
			cout << "\nWrite the full name of the log, which you desire to read\n";
			cin >> log_name;

			system("cls");

			string content = Core.Read_Log(log_name);
			cout << content;
			Write_To_Proceed();
		}
		else if (start_input == "help") {
			cout << "Commands - write, read, help, encrypt, decrypt, exit.\n";
			Write_To_Proceed();
		}
		else if (start_input == "exit") {
			return;
		}
		else if (start_input == "encrypt") {
			Core.Created_Logs();

			string log_name;
			cout << "\nWrite the full name of the log, which you desire to encrypt\n";
			cin >> log_name;

			system("cls");

			string password;
			cout << "\nWrite the password, with which you desire to encrypt\n";
			cin >> password;

			system("cls");

			bool result = Cypher.Encryption(password, log_name);
			cout << "Process succesful: " + to_string(result) + "\n";
			Write_To_Proceed();

		}
		else if (start_input == "decrypt") {
			Core.Created_Logs();

			string log_name;
			cout << "\nWrite the full name of the log, which you desire to decrypt\n";
			cin >> log_name;

			system("cls");

			string password;
			cout << "\nWrite the password, with which you desire to decrypt\n";
			cin >> password;

			system("cls");

			bool result = Cypher.Decryption(password, log_name);
			cout << "Process succesful: " + to_string(result) + "\n";
			Write_To_Proceed();
		}
		else {
			cout << "Invalid input!\n";
			Write_To_Proceed();
		}

		Console();
	}
};

Unifying_Functions Unifier;

int main()
{
	Unifier.Console();
	return 0;
}