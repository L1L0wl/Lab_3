#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

struct Record {
    std::string key;
    std::string data;

    // Добавим оператор сравнения для сортировки записей
    bool operator<(const Record& other) const {
        return key < other.key;
    }
};

// Функция для сохранения записи в файл
void saveRecordToFile(const Record& record, const std::string& filename = "output.txt") {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << record.key << ": " << record.data << std::endl;
        file.close();
    }
    else {
        std::cerr << "Unable to open the file: " << filename << std::endl;
    }
}

// Функция для поиска записи по ключу
void searchRecordByKey(const std::string& key, const std::string& filename = "output.txt") {
    std::ifstream file(filename);
    std::string line;
    bool found = false;

    while (std::getline(file, line)) {
        if (line.find(key) != std::string::npos) {
            std::cout << line << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Record with key '" << key << "' not found." << std::endl;
    }

    file.close();
}

// Функция для сортировки записей в файле по ключу
void sortRecordsByKey(const std::string& filename = "output.txt") {
    std::ifstream file(filename);
    std::vector<Record> records;
    std::string line;

    while (std::getline(file, line)) {
        Record record;
        size_t pos = line.find(":");
        if (pos != std::string::npos) {
            record.key = line.substr(0, pos);
            record.data = line.substr(pos + 1);
            records.push_back(record);
        }
    }

    file.close();

    std::sort(records.begin(), records.end());

    std::ofstream outFile(filename);
    for (const auto& record : records) {
        outFile << record.key << ": " << record.data << std::endl;
    }
    outFile.close();
}

// Функция для добавления новой записи
void addRecord() {
    Record newRecord;
    std::cout << "Enter key (or leave empty to finish): ";
    std::getline(std::cin, newRecord.key);

    if (newRecord.key.empty()) {
        std::cout << "No data entered. Returning to menu." << std::endl;
        return;
    }

    std::cout << "Enter data for key '" << newRecord.key << "': ";
    std::getline(std::cin, newRecord.data);

    saveRecordToFile(newRecord);
    std::cout << "Record added successfully." << std::endl;
}

// Функция для выполнения запроса пользователя
void processUserQuery() {
    std::string query;
    std::cout << "Enter your query: ";
    std::getline(std::cin, query);

    searchRecordByKey(query);
}

// Главное меню
void showMenu() {
    std::cout << "1. Add Record\n"
        << "2. Search Record\n"
        << "3. Sort Records\n"
        << "4. Process User Query\n"
        << "0. Exit\n"
        << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore();  // Очистка буфера ввода

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 2: {
            std::string key;
            std::cout << "Enter key to search: ";
            std::getline(std::cin, key);
            searchRecordByKey(key);
            break;
        }
        case 3:
            sortRecordsByKey();
            std::cout << "Records sorted successfully." << std::endl;
            break;
        case 4:
            processUserQuery();
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }

    } while (choice != 0);

    return 0;
}
