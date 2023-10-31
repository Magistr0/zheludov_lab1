#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>

using namespace std;

vector <string> tube_atribute{ "��������","������","�������","� �������" };
vector <string> KS_atribute{ "��������","���-�� �����","���-�� ����� � ������","������������" };

int menu_input() {
    int choise;
    try
    {
        cin >> choise;
    }
    catch (...)
    {
        cout << "������� �� ������ �������� (������)" << endl;
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
                cout << "������� �� ������ �������� (������������� �����)" << endl;
                return check_parametr(text_message, tipe);
            }
        }
        catch (...)
        {
            cout << "������� �� ������ �������� (������)" << endl;
            return check_parametr(text_message, tipe);
        }
        break;
    case 14:
        if (user_message != "y" && user_message != "n") {
            cout << "������� �� ������ �������� (������ ���� �������� y/n)" << endl;
            return check_parametr(text_message, tipe);
        }
        break;
    case 23:
        try
        {
            int_check = stoi(user_message);
            if (int_check < 0) {
                cout << "������� �� ������ �������� (������������� �����)" << endl;
                return check_parametr(text_message, tipe, restriction);
            }
            if (int_check > restriction && restriction != 0) {
                cout << "������� �� ������ �������� (������� ������� �����)" << endl;
                return check_parametr(text_message, tipe, restriction);
            }
        }
        catch (...)
        {
            cout << "������� �� ������ �������� (������)" << endl;
            return check_parametr(text_message, tipe);
        }
        break;
    case 24:
        try
        {
            int_check = stoi(user_message);
            if (int_check < 0) {
                cout << "������� �� ������ �������� (������������� �����)" << endl;
                return check_parametr(text_message, tipe);
            }
        }
        catch (...)
        {
            cout << "������� �� ������ �������� (������)" << endl;
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
    vector<string> result{ "�����" };
    string enterr;
    
    enterr = check_parametr("������� ������������ ������� (��������)",11);
    result.push_back(enterr);

    enterr = check_parametr("������� ������",12);
    result.push_back(enterr);

    enterr = check_parametr("������� �������",13);
    result.push_back(enterr);

    enterr = check_parametr("������� ������� '� �������' (y/n)",14);
    result.push_back(enterr);
    


    return result;
}


vector<string> input_KS()
{
    vector<string> result{ "��" };
    string enterr;

    enterr = check_parametr("������� ��������", 21);
    result.push_back(enterr);

    enterr = check_parametr("������� ���������� �����", 22);
    result.push_back(enterr);

    enterr = check_parametr("������� ���������� ����� � ������", 23, stoi(result[result.size() - 1]));
    result.push_back(enterr);

    enterr = check_parametr("������� �������������", 24);
    result.push_back(enterr);

    return result;
}

vector <vector < string >> edit_object(vector <vector < string >> objects)
{

    int objects_count = objects.size();
    int i,object_number,paremetr_number;

    if (objects_count == 0){
        cout << "� ��� ��� �������� ��������" << endl;
        return objects;
    }

    cout << "\n����� ������ �� ������ �������������?"<<endl;
    for (i = 0; i < objects_count; i++) {
        cout << i + 1 << ") ��������: " << objects[i][1] << endl;
    }
    cout << "0) �����"<<endl;

    object_number = stoi(check_parametr("", 23, objects_count))-1;
    if (object_number == -1){ return objects; }

    cout << "\n����� �������� �� ������ ��������?" << endl;

    if (objects[object_number][0] == "�����") {
        for (i = 1; i < 5; i++) {
            cout << i << ")" << tube_atribute[i - 1] << ": " << objects[object_number][i] << endl;
        }
    }
    else {
        for (i = 1; i < 5; i++) {
            cout << i << ")" << KS_atribute[i - 1] << ": " << objects[object_number][i] << endl;
        }
    }
    cout << "0) ������� ������" << endl;

    paremetr_number = stoi(check_parametr("", 23, 4));

    if (paremetr_number == 0) {
        if (check_parametr("�� ������� ? (y / n)", 14) == "n") {
            return edit_object(objects);
        }
        else {
            objects.erase(objects.begin() + object_number);
            return edit_object(objects);
        }
    }
    if (objects[object_number][0] == "�����") {



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
            if (object[0] == "�����") {
                tubes.push_back(object);
            }
            else {
                KSes.push_back(object);
            }
        }
    }
    file.close();
    cout << "���� ������ ��������" << endl;
    return make_pair(tubes, KSes);
}

int to_file(vector <vector < string >> tubes, vector <vector < string >>KSes) {
    ofstream file;
    int i;

    if (check_parametr("������ ������������ ����������?(y/n)\n(���� ��� �� ������ ��������� � ����� �����)", 14) == "y") {
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
    cout << "���� ������� �����������" << endl;
    return 0;
}


int output(vector <vector < string >> tubes, vector <vector < string >>KSes)
{
    int i;
    if (tubes.size() == 0 && KSes.size() == 0) {
        cout << "� ��� ��� ��������" << endl;
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

    cout << "������������ ������ 1 ������� ��-22-05\n";
    
    vector <vector < string >> objects_tube;
    vector <vector < string >> objects_KS;
    
    pair<vector <vector < string >>, vector <vector < string >> > file_objects;

    int exit = 1;
    int choise;
    
    while (exit !=0)
    {
        cout << "_________________________" << endl << endl;
        cout << "������� ����:" <<  endl;
        cout << "1. �������� �����\n2. �������� ��\n3. �������� ���� ��������\n4. ������������� �����\n5. ������������� ��\n6. ���������\n7. ���������\n0. �����" << endl;
        choise = menu_input();
        cout << "_________________________" << endl << endl;
        switch (choise) {
        case 1:
            cout << "---���������� �����---" << endl << endl;
            objects_tube.push_back(input_pipeline());
            break;
        case 2:
            cout << "---���������� ��---" << endl << endl;
            objects_KS.push_back(input_KS());
            break;
        case 3:
            cout << "---�������� ���� ��������---" << endl << endl;
            output(objects_tube, objects_KS);
            break;
        case 4:
            cout << "---�������� ����---" << endl << endl;
            objects_tube = edit_object(objects_tube);
            break;
        case 5:
            cout << "---�������� ��---" << endl << endl;
            objects_KS = edit_object(objects_KS);
            break;
        case 6:
            cout << "---������ � ����---" << endl;
            to_file(objects_tube, objects_KS);
            break;
        case 7:
            cout << "---������ �� �����---" << endl;
            file_objects = from_file();
            objects_tube = file_objects.first;
            objects_KS = file_objects.second;
            break;
        case 0:
            cout << "�����" << endl;
            exit = 0;
            break;
        default:
            cout << "������� �� ������ ��������" << endl;
            break;
        }

    }


    cout << "���������� ������..." << endl;


    return 0;
}
