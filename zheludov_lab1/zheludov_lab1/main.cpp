
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct pipline {
    string tag = "pl";
    string name;
    int length;
    int diameter;
    string repair;
};
struct compressor_station {
    string tag = "ks";
    string name;
    int workshops;
    int workshops_in_operation;
    int efficiency;
};


int isint(int min, int max) {
    int num;
    cout << "\n";
    while ((cin >> num).fail() || (num < min) || (num > max)) {
        cout << "Введено не верное значение" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n";
    }
    cout << endl;
    return num;
}

string y_or_n() {
    string result;
    cin >> result;
    if (result != "y" && result != "n") {
        cout << "Введено не верное значение (Должно быть значение y/n)" << endl;
        return y_or_n();
    }
    return result;
}
int menu_input() {
    int result;

    cout << "_________________________" << endl << endl;
    cout << "Главное меню:" << endl;
    cout << "1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход" << endl;
    cout << "_________________________" << endl << endl;

    result = isint(0, 7);
    return result;
}
/*
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
}*/


pipline input_pipeline()
{
    pipline result;
    string enterr;
    
    cout << "Введите Километровую отметку (название)"<<endl;
    cin >> enterr;
    result.name = enterr;

    cout << "Введите длинну" << endl;
    result.length = isint(1,INT_MAX);

    cout << "Введите диаметр" << endl;
    result.diameter = isint(1,INT_MAX);

    cout << "Введите признак 'в ремонте' (y/n)" << endl;
    result.repair = y_or_n();
    


    return result;
}


compressor_station  input_KS()
{
    compressor_station result;
    string enterr;

    cout << "Введите название" << endl;
    cin >> enterr;
    result.name = enterr;

    cout << "Введите количество цехов" << endl;
    result.workshops = isint(1,INT_MAX);

    cout << "Введите количество цехов в работе" << endl;
    result.workshops_in_operation = isint(0,result.workshops);

    cout << "Введите эффективность" << endl;
    result.efficiency = isint(0,100);

    return result;
}

vector <pipline>  edit_pipeline(vector <pipline> objects)
{

    int objects_count = objects.size();
    int i,object_number;
    string user_message;
    
    if (objects_count != 0) {

        cout << "Выберите объект который хотите изменить" << endl;
        i = 1;
        for (const pipline& object : objects) {
            cout << i << ") " << object.name << endl;
            i++;
        }
        cout << "0) Выход" << endl;

        object_number = isint(0,objects_count);

        if (object_number != 0) {
            if (objects[object_number - 1].repair == "n") {
                cout << "Хотите ремонтировать трубу?" << endl;
            }
            else {
                cout << "Хотите Выпустить из ремонта трубу?" << endl;
            }
            user_message = y_or_n();
            if (user_message == "y") {
                if (objects[object_number-1].repair == "n") {
                    objects[object_number-1].repair = "y";
                }
                else {
                    objects[object_number-1].repair = "n";
                }
            }
            else {
                return edit_pipeline(objects);
            }
        }
    }
    else {
        cout << "У вас нет заданных объектов" << endl;
    }
    return objects;
    

}

vector <compressor_station>  edit_KS(vector <compressor_station> objects)
{

    int objects_count = objects.size();
    int i, object_number;
    int user_message;
    if (objects_count != 0) {
        cout << "Выберите объект который хотите изменить" << endl;
        i = 1;
        for (const compressor_station& object : objects) {
            cout << i << ") " << object.name << endl;
            i++;
        }
        cout << "0) Выход" << endl;
        object_number = isint(0,objects_count);
        if (object_number != 0) {
            cout << "Введите новое число запущеных цехов (Всего цехов: " << objects[object_number - 1].workshops << ")" << endl;
            user_message = isint(0,objects[object_number - 1].workshops);
            objects[object_number - 1].workshops_in_operation = user_message;
        }
    }
    else {
        cout << "У вас нет заданных объектов" << endl;
    }
    return objects;


}



pair<vector <pipline>, vector <compressor_station> > from_file() {
    vector <pipline> tubes; 
    pipline tube;
    vector <compressor_station> KSes;
    compressor_station KS;
    vector <string> object;
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
            if (object[0] == "pl") {
                tube.name = object[1];
                tube.length = stoi(object[2]);
                tube.diameter = stoi(object[3]);
                tube.repair = object[4];
                tubes.push_back(tube);
            }
            else {
                KS.name = object[1];
                KS.workshops = stoi(object[2]);
                KS. workshops_in_operation = stoi(object[3]);
                KS.efficiency = stoi(object[4]);
                KSes.push_back(KS);
            }
        }
    }
    file.close();
    cout << "Файл упешно прочитан" << endl;
    return make_pair(tubes, KSes);
}

int to_file(vector <pipline> tubes, vector <compressor_station> KSes) {
    ofstream file;
    int i;
    cout << "Хотите перезаписать сохранение?(y/n)\n(если нет то данные запишутся в конец файла)" << endl;
    if (y_or_n() == "y") {
        file.open("saves.txt");
    }
    else {
        file.open("saves.txt", ios::app);
    }
         
    if (file.is_open())
    {
        for (const pipline& object : tubes) {
            file << object.tag << " " << object.name << " " << object.length << " " << object.diameter << " " << object.repair << endl;
        }
        for (const compressor_station& object : KSes) {
            file << object.tag << " " << object.name << " " << object.workshops << " " << object.workshops_in_operation << " " << object.efficiency << endl;
        }
    }
    file.close();
    cout << "Файл успешно перезаписан" << endl;
    return 0;
}


int output(vector <pipline> tubes, vector <compressor_station>KSes)
{
    int i;
    if (tubes.size() == 0 && KSes.size() == 0) {
        cout << "У вас нет объектов" << endl;
        return 0;
    }
    for (const pipline& object : tubes) {
        cout << "Труба" << ": " << object.name << "\nДлинна: " << object.length << "\nДиаметр: " << object.diameter << "\nПризнак в ремонте: " << object.repair << "\n" << endl;
    }
    for (const compressor_station& object : KSes) {
        cout << "КС" << ": " << object.name << "\nЦеха: " << object.workshops << "\nЦеха в работе: " << object.workshops_in_operation << "\nЭфективность: " << object.efficiency << "\n" << endl;
    }
    return 0;
}






int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Лабораторная работа 1 Желудов АС-22-05\n";
    
    vector <pipline>  objects_tube;
    vector <compressor_station>  objects_KS;
    
    pair<vector <pipline>, vector <compressor_station> > file_objects;

    int exit = 1;
    int choise;
    
    while (exit !=0)
    {
        choise = menu_input();
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
            objects_tube = edit_pipeline(objects_tube);
            break;
        case 5:
            cout << "---Редактор КС---" << endl << endl;
            objects_KS = edit_KS(objects_KS);
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
