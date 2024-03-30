#include <iostream>
#include <string>
#include <vector>

class AddressEntry
{
public:
	void setContactName() {
		std::string strName;
		std::cout << "Enter name of contact: ";	//Для упрощения только имя
		std::cin >> strName;
		contactName = strName;
	}
	void setPhoneNumber() {
		std::string strNumber;
		bool validNumber = false;

		while (!validNumber) {
			std::cout << "Enter phone number of contact (+7**********): ";
			std::cin >> strNumber;
			if (strNumber.length() != 12 || strNumber[0] != '+' || strNumber[1] != '7') {
				std::cout << "Invalid phone number format!\n\n";
				continue;
			}
			else {
				validNumber = true;
				for (int i = 2; i < 12; i++) {
					if (strNumber[i] < '0' || strNumber[i] > '9') {
						std::cout << "Invalid phone number format!\n\n";
						validNumber = false;
						break;
					}
				}
			}
		}
		phoneNumber = strNumber;
	}
	std::string getContactName() {
		return contactName;
	}
	std::string getPhoneNumber() {
		return phoneNumber;
	}
private:
	std::string contactName = "Unknown";
	std::string phoneNumber = "+70000000000";
};

class Phone
{
public:
	void addEntry(AddressEntry entry) {
		vecAddressBook.push_back(entry);
	}
	std::string findContact(std::string strInput) {
		std::string strPhoneNumber;
		bool bCall = false;

		if (strInput[0] == '+') {	//Если введён номер телефона и он имеется в адресной книге
			for (int i = 0; i < vecAddressBook.size(); i++) {
				if (vecAddressBook[i].getPhoneNumber() == strInput) {
					strPhoneNumber = strInput;
					bCall = true;
					break;
				}
			}
		}
		else {	//Если введено имя контакта и оно имеется в адресно книге
			for (int i = 0; i < vecAddressBook.size(); i++) {
				if (vecAddressBook[i].getContactName() == strInput) {
					strPhoneNumber = vecAddressBook[i].getPhoneNumber();
					bCall = true;
					break;
				}
			}
		}
		if (bCall)	//Если контакт не найден
			return strPhoneNumber;
		else
			return "";
	}
	void calling(std::string strInput) {
		std::string strPhoneNumber = findContact(strInput);
		if (strPhoneNumber == "")
			std::cout << "Contact is missing!" << std::endl << std::endl;
		else
			std::cout << "Call " << strPhoneNumber << std::endl << std::endl;
	}
	void smsing(std::string strInput, std::string strMsessage) {
		std::string strPhoneNumber = findContact(strInput);
		if (strPhoneNumber == "")
			std::cout << "Contact is missing!" << std::endl << std::endl;
		else {
			std::cout << "SMS to: " << strPhoneNumber << std::endl;
			std::cout << strMsessage << std::endl << std::endl;
		}
	}
private:
	std::vector<AddressEntry> vecAddressBook{};
};

int main()
{
	std::cout << "***************** Implementation of a mobile phone simulation program *****************\n\n";

	std::string command = "";
	Phone myPhone;
	
	while (true) {
		std::cout << "Enter the command for the mobile phone (add, call, sms) or 'exit' to exit the program: ";
		std::cin >> command;

		if (command == "add") {
			AddressEntry entry;	
			entry.setPhoneNumber();
			entry.setContactName();
			myPhone.addEntry(entry);
		}
		else if (command == "call") {
			std::string strInput;
			std::cout << "Enter name or number phone of contact: ";
			std::cin >> strInput;
			myPhone.calling(strInput);
		}
		else if (command == "sms") {
			std::string strMessage, strInput;
			std::cout << "Enter the text of the message: ";
			std::cin.ignore();
			std::getline(std::cin,strMessage);
			
			std::cout << "Enter name or number phone of contact: ";
			std::cin >> strInput;
			myPhone.smsing(strInput, strMessage);
		}
		else if (command == "exit") {
			return 0;
		}
		else {
			std::cerr << "Invalid command!\n\n";
		}
	}
}