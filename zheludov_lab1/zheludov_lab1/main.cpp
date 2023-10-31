#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>

using namespace std;

vector <string> tube_atribute{ "Название","Длинна","Диаметр","В ремонте" };
vector <string> KS_atribute{ "Название","Кол-во цехов","Кол-во цехов в работе","Эфективность" };

int menu_input() {
    int choise;
    try
    {
        cin >> choise;
    }
    catch (...)
    {
        cout << "Введено не верное значение (строка)" << endl;
        return menu_input();
    }
    return choise;
}

string check_parametr(string text_message, int tipe, int restriction = 0)
{
    string user_message;
    int int_check;
    cout << text_message << endl;
    cin >> user_message;

    if (tipe == 12 || tipe == 13 || tipe == 22) {
        tipe = 1;
    }

    switch (tipe) {
    case 1:
        try
        {
            int_check = stoi(user_message);
            if (int_check <= 0) {
                cout << "Введено не верное значение (Отрицательное число)" << endl;
                return check_parametr(text_message, tipe);
            }
        }
        catch (...)
        {
            cout << "Введено не верное значение (строка)" << endl;
            return check_parametr(text_message, tipe);
        }
        break;
    case 14:
        if (user_message != "y" && user_message != "n") {
            cout << "Введено не верное значение (Должно быть значение y/n)" << endl;
            return check_parametr(text_message, tipe);
        }
        break;
    case 23:
        try
        {
            int_check = stoi(user_message);
            if (int_check < 0) {
                cout << "Введено не верное значение (Отрицательное число)" << endl;
                return check_parametr(text_message, tipe, restriction);
            }
            if (int_check > restriction && restriction != 0) {
                cout << "Введено не верное значение (Слишком большое число)" << endl;
                return check_parametr(text_message, tipe, restriction);
            }
        }
        catch (...)
        {
            cout << "Введено не верное значение (строка)" << endl;
            return check_parametr(text_message, tipe);
        }
        break;
    case 24:
        try
        {
            int_check = stoi(user_message);
            if (int_check < 0) {
                cout << "Введено не верное значение (Отрицательное число)" << endl;
                return check_parametr(text_message, tipe);
            }
        }
        catch (...)
        {
            cout << "Введено не верное значение (строка)" << endl;
            return check_parametr(text_message, tipe);
        }
        break;
    default:
        break;
    }
    return user_message;
}


vector<string> input_pipeline()
{
    vector<string> result{ "Труба" };
    string enterr;
    
    enterr = check_parametr("Введите Километровую отметку (название)",11);
    result.push_back(enterr);

    enterr = check_parametr("Введите длинну",12);
    result.push_back(enterr);

    enterr = check_parametr("Введите диаметр",13);
    result.push_back(enterr);

    enterr = check_parametr("Введите признак 'в ремонте' (y/n)",14);
    result.push_back(enterr);
    


    return result;
}


vector<string> input_KS()
{
    vector<string> result{ "КС" };
    string enterr;

    enterr = check_parametr("Введите название", 21);
    result.push_back(enterr);

    enterr = check_parametr("Введите количество цехов", 22);
    result.push_back(enterr);

    enterr = check_parametr("Введите количество цехов в работе", 23, stoi(result[result.size() - 1]));
    result.push_back(enterr);

    enterr = check_parametr("Введите эффективность", 24);
    result.push_back(enterr);

    return result;
}

vector <vector < string >> edit_object(vector <vector < string >> objects)
{

    int objects_count = objects.size();
    int i,object_number,paremetr_number;

    if (objects_count == 0){
        cout << "У вас нет заданных объектов" << endl;
        return objects;
    }

    cout << "\nКакой объект вы хотите редоктировать?"<<endl;
    for (i = 0; i < objects_count; i++) {
        cout << i + 1 << ") Название: " << objects[i][1] << endl;
    }
    cout << "0) Выход"<<endl;

    object_number = stoi(check_parametr("", 23, objects_count))-1;
    if (object_number == -1){ return objects; }

    cout << "\nКакой параметр вы хотите изменить?" << endl;

    if (objects[object_number][0] == "Труба") {
        for (i = 1; i < 5; i++) {
            cout << i << ")" << tube_atribute[i - 1] << ": " << objects[object_number][i] << endl;
        }
    }
    else {
        for (i = 1; i < 5; i++) {
            cout << i << ")" << KS_atribute[i - 1] << ": " << objects[object_number][i] << endl;
        }
    }
    cout << "0) Удалить объект" << endl;

    paremetr_number = stoi(check_parametr("", 23, 4));

    if (paremetr_number == 0) {
        if (check_parametr("Вы уверены ? (y / n)", 14) == "n") {
            return edit_object(objects);
        }
        else {
            objects.erase(objects.begin() + object_number);
            return edit_object(objects);
        }
    }
    if (objects[object_number][0] == "Труба") {



        objects[object_number].erase(objects[object_number].begin() + paremetr_number);

        objects[object_number].emplace(objects[object_number].begin() + paremetr_number, check_parametr("", 10 + paremetr_number));
        return edit_object(objects);
    }
    else {

        objects[object_number].erase(objects[object_number].begin() + paremetr_number);
        if (paremetr_number == 3) {
            objects[object_number].emplace(objects[object_number].begin() + paremetr_number, check_parametr("", 20 + paremetr_number, stoi(objects[object_number][paremetr_number - 1])));
            return edit_object(objects);
        }
        else {
            objects[object_number].emplace(objects[object_number].begin() + paremetr_number, check_parametr("", 20 + paremetr_number));
            return edit_object(objects);
        }
        
    }
    return objects;
    

}

pair<vector <vector < string >>, vector <vector < string >> > from_file() {
    vector <vector < string >> tubes, KSes;
    vector < string > object;
    string line,parametr;


    ifstream file("saves.txt");

    if (file.is_open())
    {
        while (getline(file, line))
        {
            object = {};
            istringstream iss(line, istringstream::in);
            while (iss >> parametr)
            {
                object.push_back(parametr);
            }
            if (object[0] == "Труба") {
                tubes.push_back(object);
            }
            else {
                KSes.push_back(object);
            }
        }
    }
    file.close();
    cout << "Файл упешно прочитан" << endl;
    return make_pair(tubes, KSes);
}

int to_file(vector <vector < string >> tubes, vector <vector < string >>KSes) {
    ofstream file;
    int i;

    if (check_parametr("Хотите перезаписать сохранение?(y/n)\n(если нет то данные запишутся в конец файла)", 14) == "y") {
        file.open("saves.txt");
    }
    else {
        file.open("saves.txt", ios::app);
    }
         
    if (file.is_open())
    {
        for (const vector < string >& object : tubes) {
            for (i = 0; i < 5; i++) {
                file << object[i] << " ";
            }
            file << endl;
        }
        for (const vector < string >& object : KSes) {
            for (i = 0; i < 5; i++) {
                file << object[i] << " ";
            }
            file << endl;
        }
    }
    file.close();
    cout << "Файл успешно перезаписан" << endl;
    return 0;
}


int output(vector <vector < string >> tubes, vector <vector < string >>KSes)
{
    int i;
    if (tubes.size() == 0 && KSes.size() == 0) {
        cout << "У вас нет объектов" << endl;
        return 0;
    }
    for (const vector < string >& object : tubes) {
        cout << object[0] << endl;
        for (i = 1; i < 5; i++) {
            cout << tube_atribute[i-1] << ": " << object[i] << endl;
        }
        cout << "\n";
    }
    for (const vector < string >& object : KSes) {
        cout << object[0] << endl;
        for (i = 1; i < 5; i++) {
            cout << KS_atribute[i - 1] << ": " << object[i] << endl;
        }
        cout << "\n";
    }
    return 0;
}






int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Лабораторная работа 1 Желудов АС-22-05\n";
    
    vector <vector < string >> objects_tube;
    vector <vector < string >> objects_KS;
    
    pair<vector <vector < string >>, vector <vector < string >> > file_objects;

    int exit = 1;
    int choise;
    
    while (exit !=0)
    {
        cout << "_________________________" << endl << endl;
        cout << "Главное меню:" <<  endl;
        cout << "1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход" << endl;
        choise = menu_input();
        cout << "_________________________" << endl << endl;
        switch (choise) {
        case 1:
            cout << "---Добавление Трубы---" << endl << endl;
            objects_tube.push_back(input_pipeline());
            break;
        case 2:
            cout << "---Добавление КС---" << endl << endl;
            objects_KS.push_back(input_KS());
            break;
        case 3:
            cout << "---Просмотр всех объектов---" << endl << endl;
            output(objects_tube, objects_KS);
            break;
        case 4:
            cout << "---Редактор труб---" << endl << endl;
            objects_tube = edit_object(objects_tube);
            break;
        case 5:
            cout << "---Редактор КС---" << endl << endl;
            objects_KS = edit_object(objects_KS);
            break;
        case 6:
            cout << "---Запись в файл---" << endl;
            to_file(objects_tube, objects_KS);
            break;
        case 7:
            cout << "---Чтение из файла---" << endl;
            file_objects = from_file();
            objects_tube = file_objects.first;
            objects_KS = file_objects.second;
            break;
        case 0:
            cout << "Выход" << endl;
            exit = 0;
            break;
        default:
            cout << "Введено не верное значение" << endl;
            break;
        }

    }


    cout << "Завершение работы..." << endl;


    return 0;
}
