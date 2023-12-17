#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>


using namespace std;

#define DIV (1024 * 1024)
#define MEMSIZE (100 * 1024 * 1024)
#define WIDTH 7

void VMStatus(MEMORYSTATUSEX& statex) {
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    cout << "There are " << setw(WIDTH) << statex.ullTotalVirtual / DIV
        << " total MB of virtual memory." << endl;
    cout << "There are " << setw(WIDTH) << statex.ullAvailVirtual / DIV
        << " free MB of virtual memory." << endl;
}

void AllocateVM(vector<void*>& cells, MEMORYSTATUSEX& statex) {
    void* p = nullptr;
    int i = 0;

    do {
        p = VirtualAlloc(nullptr, MEMSIZE, MEM_COMMIT | MEM_RESERVE, PAGE_NOACCESS);
        i++;

        if (p != nullptr) {
            if (i % 10 == 0) {
                cout << setw(2) << i << ": " << p << "\n" << endl;
                VMStatus(statex);
            }

            cells.push_back(p);
        }
        else {
            cout << i << ": NULL" << endl;
            break;
        }

    } while (true);
    VMStatus(statex);
}

void Reserve1(MEMORYSTATUSEX& statex) {
    void* p = VirtualAlloc(nullptr, statex.ullAvailVirtual, MEM_COMMIT | MEM_RESERVE, PAGE_NOACCESS);
    if (p != nullptr) {
        cout << p << endl;
        VMStatus(statex);
        cout << endl;
    }
    else {
        cout << "NULL" << endl;
    }
    cout << endl;
    VMStatus(statex);
    cout << endl << endl;
}

void Reserve2(MEMORYSTATUSEX& statex, const int& freeVM) {
    void* p = VirtualAlloc(nullptr, freeVM, MEM_RESERVE, PAGE_NOACCESS);
    if (p != nullptr) {
        cout << p << endl;
        VMStatus(statex);
        cout << endl;
    }
    else {
        cout << "NULL" << endl;
    }
    cout << endl;
    VMStatus(statex);
    cout << endl << endl;
}

int main() {
    MEMORYSTATUSEX statex;
    vector<void*> cells;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "1. Доступная и общая ВП" << endl;
    VMStatus(statex);
    getchar();

    cout << "2. Выделяем блоки по 100 MB пока возможно" << endl;
    AllocateVM(cells, statex);
    getchar();

    cout << "3. Освобождаем каждый второй из выделенных в п.2" << endl;
    int freeVM = 0;
    for (size_t i = 1; i < cells.size(); i += 2) {
        VirtualFree(cells[i], 0, MEM_RELEASE);
        freeVM += MEMSIZE;
    }
    cout << freeVM << endl;
    VMStatus(statex);
    cout << endl << endl;
    getchar();

    cout << "4. Попытаемся выделить блок памяти с размером с доступную" << endl;
    Reserve1(statex);
    cout << endl << endl;

    getchar();

    cout << "5. Освободим оставшуюся выделенную память" << endl;

    for (auto i : cells) {
        VirtualFree(i, 0, MEM_RELEASE);
    }
    cout << endl;
    VMStatus(statex);
    cout << endl << endl;

    getchar();

    cout << "6. Зарезервировать область памяти того же размера, что и вп. 4 только с флагом RESERVE " << endl;
    Reserve2(statex, freeVM);

    getchar();

    return 0;
}
