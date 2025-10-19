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

			for (int s = 0; s < 26; s++) {
				Attribute.output = Attribute.output + Attribute.str_timestamp[s];
			}

			Attribute.output = Attribute.output + "\n|content|" + Attribute.content + "\n";

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
			return;
		}

		string line_content;
		string file_content;

		while (getline(File, line_content)) {
			int symbol_count = 0;
			string filtered_line;

			for (int i = 0; i < line_content.size(); i++) {
				if (line_content[i] == '|'){
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
	void Encryption(string password, string name) {
		string content = Core.Read_Log(name);
	}

	void Decryption(string password, string name) {
		string content = Core.Read_Log(name);
	}
};

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
			cout << "\nWrite the the full name of the log, which you desire to read\n";
			cin >> log_name;

			system("cls");

			string content = Core.Read_Log(log_name);
			cout << content;
			Write_To_Proceed();
		}
		else if (start_input == "help") {
			cout << "Commands - write, read, help, exit.\n";
			Write_To_Proceed();
		}
		else if (start_input == "exit") {
			return;
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
