#include <iostream> 
#include <fstream> 
#include <vector> 
#include <algorithm> 

// Структура для представления трубы 
struct Pipe {
    std::string id;
    std::string name;
    double length;
    double diameter;
    bool inRepair;

    void readFromConsole() {
        std::cout << "Введите ID трубы: ";
        std::cin >> id;
        std::cout << "Введите название трубы: ";
        std::cin >> name;
        std::cout << "Введите длину трубы (в километрах): ";
        std::cin >> length;
        std::cout << "Введите диаметр трубы: ";
        std::cin >> diameter;
        std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";
        std::cin >> inRepair;
    }

    void printToConsole() {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Название: " << name << std::endl;
        std::cout << "Длина (км): " << length << std::endl;
        std::cout << "Диаметр: " << diameter << std::endl;
        std::cout << "В ремонте: " << (inRepair ? "Да" : "Нет") << std::endl;
    }
};

// Структура для представления КС 
struct CompressorStation {
    std::string id;
    std::string name;
    int workshopCount;
    int activeWorkshops;
    double efficiency;

    void readFromConsole() {
        std::cout << "Введите ID КС: ";
        std::cin >> id;
        std::cout << "Введите название КС: ";
        std::cin >> name;
        std::cout << "Введите количество цехов: ";
        std::cin >> workshopCount;
        std::cout << "Введите количество активных цехов: ";
        std::cin >> activeWorkshops;
        std::cout << "Введите показатель эффективности: ";
        std::cin >> efficiency;
    }

    void printToConsole() {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Название: " << name << std::endl;
        std::cout << "Количество цехов: " << workshopCount << std::endl;
        std::cout << "Активных цехов: " << activeWorkshops << std::endl;
        std::cout << "Эффективность: " << efficiency << std::endl;
    }
};

// Функция для сохранения данных в файл 
void saveData(const std::vector<Pipe>& pipes, const std::vector<CompressorStation>& stations, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << pipes.size() << std::endl;
        for (const auto& pipe : pipes) {
            file << pipe.id << std::endl;
            file << pipe.name << std::endl;
            file << pipe.length << std::endl;
            file << pipe.diameter << std::endl;
            file << pipe.inRepair << std::endl;
        }

        file << stations.size() << std::endl;
        for (const auto& station : stations) {
            file << station.id << std::endl;
            file << station.name << std::endl;
            file << station.workshopCount << std::endl;
            file << station.activeWorkshops << std::endl;
            file << station.efficiency << std::endl;
        }

        file.close();
        std::cout << "Данные сохранены в файл." << std::endl;
    }
    else {
        std::cout << "Не удалось открыть файл для сохранения данных." << std::endl;
    }
}

// Функция для загрузки данных из файла 
void loadData(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        pipes.clear();
        stations.clear();

        int pipeCount;
        file >> pipeCount;
        file.ignore();

        for (int i = 0; i < pipeCount; ++i) {
            Pipe pipe;
            std::getline(file, pipe.id);
            std::getline(file, pipe.name);
            file >> pipe.length;
            file >> pipe.diameter;
            file >> pipe.inRepair;
            file.ignore();
            pipes.push_back(pipe);
        }

        int         stationCount;
        file >> stationCount;
        file.ignore();

        for (int i = 0; i < stationCount; ++i) {
            CompressorStation station;
            std::getline(file, station.id);
            std::getline(file, station.name);
            file >> station.workshopCount;
            file >> station.activeWorkshops;
            file >> station.efficiency;
            file.ignore();
            stations.push_back(station);
        }

        std::cout << "Данные загружены из файла." << std::endl;
    }
    else {
        std::cout << "Не удалось открыть файл для загрузки данных." << std::endl;
    }
}

// Функция для поиска трубы по названию 
std::vector<Pipe> findPipesByName(const std::vector<Pipe>& pipes, const std::string& name) {
    std::vector<Pipe> foundPipes;
    for (const auto& pipe : pipes) {
        if (pipe.name == name) {
            foundPipes.push_back(pipe);
        }
    }
    return foundPipes;
}

// Функция для поиска трубы по признаку "в ремонте" 
std::vector<Pipe> findPipesInRepair(const std::vector<Pipe>& pipes, bool inRepair) {
    std::vector<Pipe> foundPipes;
    for (const auto& pipe : pipes) {
        if (pipe.inRepair == inRepair) {
            foundPipes.push_back(pipe);
        }
    }
    return foundPipes;
}

// Функция для поиска КС по названию 
std::vector<CompressorStation> findStationsByName(const std::vector<CompressorStation>& stations, const std::string& name) {
    std::vector<CompressorStation> foundStations;
    for (const auto& station : stations) {
        if (station.name == name) {
            foundStations.push_back(station);
        }
    }
    return foundStations;
}

// Функция для поиска КС по проценту незадействованных цехов 
std::vector<CompressorStation> findStationsByUnusedWorkshops(const std::vector<CompressorStation>& stations, double unusedPercentage) {
    std::vector<CompressorStation> foundStations;
    for (const auto& station : stations) {
        double unusedWorkshops = station.workshopCount - station.activeWorkshops;
        double percentage = (unusedWorkshops / station.workshopCount) * 100.0;
        if (percentage >= unusedPercentage) {
            foundStations.push_back(station);
        }
    }
    return foundStations;
}

// Функция для пакетного редактирования труб 
void editPipes(std::vector<Pipe>& pipes) {
    std::string name;
    std::cout << "Введите название труб для редактирования: ";
    std::cin >> name;

    std::vector<Pipe> foundPipes = findPipesByName(pipes, name);
    if (foundPipes.empty()) {
        std::cout << "Трубы с указанным названием не найдены." << std::endl;
        return;
    }

    int choice;
    std::cout << "Выберите действие для редактирования:" << std::endl;
    std::cout << "1. Изменить длину" << std::endl;
    std::cout << "2. Изменить диаметр" << std::endl;
    std::cout << "3. Изменить статус ремонта" << std::endl;
    std::cout << "4. Удалить" << std::endl;
    std::cout << "Выберите действие: ";
    std::cin >> choice;

    if (choice == 1) {
        double newLength;
        std::cout << "Введите новую длину: ";
        std::cin >> newLength;

        for (auto& pipe : foundPipes) {
            pipe.length = newLength;
        }
    }
    else if (choice == 2) {
        double newDiameter;
        std::cout << "Введите новый диаметр: ";
        std::cin >> newDiameter;

        for (auto& pipe : foundPipes) {
            pipe.diameter = newDiameter;
        }
    }
    else if (choice == 3) {
        bool newInRepair;
        std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";

        std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";
        std::cin >> newInRepair;

        for (auto& pipe : foundPipes) {
            pipe.inRepair = newInRepair;
        }
    }
    else if (choice == 4) {
        // Удалить найденные трубы 
        pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [&name](const Pipe& pipe) { return pipe.name == name; }), pipes.end());
    }
    else {
        std::cout << "Неверный выбор." << std::endl;
    }
}

int main() {
    std::vector<Pipe> pipes;
    std::vector<CompressorStation> stations;

    int choice;
    while (true) {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить трубу" << std::endl;
        std::cout << "2. Добавить КС" << std::endl;
        std::cout << "3. Просмотр всех объектов" << std::endl;
        std::cout << "4. Редактировать трубу" << std::endl;
        std::cout << "5. Редактировать КС" << std::endl;
        std::cout << "6. Сохранить" << std::endl;
        std::cout << "7. Загрузить" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (choice == 1) {
            Pipe pipe;
            pipe.readFromConsole();
            pipes.push_back(pipe);
        }
        else if (choice == 2) {
            CompressorStation station;
            station.readFromConsole();
            stations.push_back(station);
        }
        else if (choice == 3) {
            // Вывод всех объектов 
            std::cout << "Трубы:" << std::endl;
            for (const auto& pipe : pipes) {
                pipe.printToConsole();
                std::cout << std::endl;
            }

            std::cout << "Компрессорные станции:" << std::endl;
            for (const auto& station : stations) {
                station.printToConsole();
                std::cout << std::endl;
            }
        }
        else if (choice == 4) {
            editPipes(pipes);
        }
        else if (choice == 5) {
            // Редактирование КС 
            // Аналогично пакетному редактированию труб 
        }
        else if (choice == 6) {
            std::string filename;
            std::cout << "Введите имя файла для сохранения: ";
            std::cin >> filename;
            saveData(pipes, stations, filename);
        }
        else if (choice == 7) {
            std::string filename;
            std::cout << "Введите имя файла для загрузки: ";
            std::cin >> filename;
            loadData(pipes, stations, filename);
        }
        else if (choice == 0) {
            break;
        }
        else {
            std::cout << "Неверный выбор." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}