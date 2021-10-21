// lab3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab3.h"
#include <string>

#define MAX_LOADSTRING 100
using namespace std;

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND BtnHideAuxApp;                             // Кнопка, которая прячет окно вспомогательного приложения
HWND BtnUnavailable;                            // Кнопка, делающая недоступным окно вспомогательного приложения
HWND BtnExitApp3;                               // Кнопка, закрывающая приложение на C#
HWND BtnPressBtn1Lab2;                          // Кнопка, нажимающая кнопку из ЛР №2
HWND BtnAboutLab2;                              // Кнопка, открывающая окно "О программе" из ЛР №2
HWND BtnRBDownLab2;                             // Кнопка-имитатор щелчка ПКМ из ЛР №2
HWND BtnMoveWndLab2;                            // Кнопка для перемещения окна из ЛР №2
HWND BtnRenameWndLab2;                          // Кнопка для переименования дочерних окон
HWND BtnNumerateWnd;                            // Кнопка для нумерации окон
HWND OutTxt;                                    // Поле вывода

HWND lab2;                                      // Окно ЛР №2
HWND Borland;                                   // Окно программы Borland C++
HWND Sharp;                                     // Окно программы на C#

// Идентификаторы кнопок и полей
const static int idBtnHideAuxApp = 1;
const static int idBtnUnavailable = 2;
const static int idBtnExitApp3 = 3;
const static int idBtnPressBtnLab2 = 4;
const static int idBtnAboutLab2 = 5;
const static int idBtnRBDownLab2 = 6;
const static int idBtnRenameWndLab2 = 7;
const static int idBtnNumerateWnd = 8;
const static int idOutTxt = 9;

int WWidth = 800;
int WHeight = 600;

int p = 0;
int param = 0;
int i = 0;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK    Numeration(HWND, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                             100, 100, WWidth, WHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   BtnHideAuxApp = CreateWindow(L"BUTTON", L"Спрятать/показать вспомогательные приложения", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 10, 500, 30, hWnd, (HMENU)idBtnHideAuxApp, hInstance, NULL);
   BtnUnavailable = CreateWindow(L"BUTTON", L"Сделать (не)доступными окна вспомогательных приложений", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 50, 500, 30, hWnd, (HMENU)idBtnUnavailable, hInstance, NULL);
   BtnExitApp3 = CreateWindow(L"BUTTON", L"Закрыть приложение №3 (C#)", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 90, 500, 30, hWnd, (HMENU)idBtnExitApp3, hInstance, NULL);
   BtnPressBtn1Lab2 = CreateWindow(L"BUTTON", L"ЛР №2: нажать кнопку и выполнить команду", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 130, 500, 30, hWnd, (HMENU)idBtnPressBtnLab2, hInstance, NULL);
   BtnAboutLab2 = CreateWindow(L"BUTTON", L"ЛР №2: выполнить команду пункта меню", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 170, 500, 30, hWnd, (HMENU)idBtnAboutLab2, hInstance, NULL);
   BtnRBDownLab2 = CreateWindow(L"BUTTON", L"ЛР №2: выполнить действия как после нажатия ПКМ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 210, 500, 30, hWnd, (HMENU)idBtnRBDownLab2, hInstance, NULL);
   BtnRenameWndLab2 = CreateWindow(L"BUTTON", L"ЛР №2: найти и переименовать все дочерние окна", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 250, 500, 30, hWnd, (HMENU)idBtnRenameWndLab2, hInstance, NULL);
   BtnNumerateWnd = CreateWindow(L"BUTTON", L"Пронумеровать все окна", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 290, 500, 30, hWnd, (HMENU)idBtnNumerateWnd, hInstance, NULL);
   OutTxt = CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 350, 500, 50, hWnd, (HMENU)idOutTxt, hInstance, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        lab2 = FindWindow(0, TEXT("Лабораторная работа №2, Рамазанов Никита, А-13а-19"));
        if (!lab2) MessageBox(hWnd, TEXT("Окно ЛР №2 не найдено!"), TEXT("Ошибка"), MB_OK);
        Borland = FindWindow(0, TEXT("Borland C++"));
        if (!Borland) MessageBox(hWnd, TEXT("Окно Borland C++ не найдено!"), TEXT("Ошибка"), MB_OK);
        Sharp = FindWindow(0, L"C#");
        if (!Sharp) MessageBox(hWnd, TEXT("Окно C# не найдено!"), TEXT("Ошибка"), MB_OK);
        break;
    case WM_LBUTTONDOWN:
    {
        SendMessage(lab2, WM_LBUTTONDOWN, wParam, lParam);
    }
    break;
    case WM_MOUSEMOVE:
    {
        SendMessage(lab2, WM_MOUSEMOVE, wParam, lParam);
    }
    break;
    case WM_LBUTTONUP:
    {
        SendMessage(lab2, WM_LBUTTONUP, wParam, lParam);
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case idBtnHideAuxApp:
                IsWindowVisible(lab2) ? ShowWindow(lab2, SW_HIDE) : ShowWindow(lab2, SW_SHOW);
                IsWindowVisible(Borland) ? ShowWindow(Borland, SW_HIDE) : ShowWindow(Borland, SW_SHOW);
                IsWindowVisible(Sharp) ? ShowWindow(Sharp, SW_HIDE) : ShowWindow(Sharp, SW_SHOW);
                break;
            case idBtnUnavailable:
                IsWindowEnabled(lab2) ? EnableWindow(lab2, false) : EnableWindow(lab2, true);
                IsWindowEnabled(Borland) ? EnableWindow(Borland, false) : EnableWindow(Borland, true);
                IsWindowEnabled(Sharp) ? EnableWindow(Sharp, false) : EnableWindow(Sharp, true);
                break;
            case idBtnExitApp3:
                SendMessage(Sharp, WM_CLOSE, 0, 0);
                break;
            case idBtnPressBtnLab2:
                HWND hBtn;
                hBtn = FindWindowEx(lab2, NULL, TEXT("BUTTON"), TEXT("Возвести в квадрат"));
                if (hBtn)
                    SendMessage(hBtn, BM_CLICK, 0, 0);
                break;
            case idBtnAboutLab2:
                SendMessage(lab2, WM_COMMAND, IDM_ABOUT, 0);
                break;
            case idBtnRBDownLab2:
                POINT pt;
                GetCursorPos(&pt);
                ScreenToClient(lab2, &pt);
                SendMessage(lab2, WM_RBUTTONDOWN, 0, MAKELPARAM(pt.x, pt.y));
                break;
            case idBtnRenameWndLab2:
                EnumChildWindows(lab2, &Numeration, 0);
                break;
            case idBtnNumerateWnd:
                param = 1;
                EnumWindows(&Numeration, 0);
                param = 0;
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Нумерация окон
BOOL CALLBACK Numeration(HWND tW, LPARAM lParam) {
    if (param == 1) {
        TCHAR lpWinTitle[256];
        p++;
        char z[10];
        GetWindowTextW(tW, lpWinTitle, 256 - 1);
        string str = "Window #" + to_string(p);
        wstring s1 = wstring(str.begin(), str.end());
        const wchar_t* s = s1.c_str();
        SendMessage(tW, WM_SETTEXT, 0, (LPARAM)s);
        TCHAR lpWinTitle1[256];
        GetWindowText(tW, lpWinTitle1, 256 - 1);
        param = 0;
        i = 0;
        EnumChildWindows(tW, &Numeration, 0);
        param = 1;
        return true;
    }
    else {
        TCHAR lpWinTitle[256];
        i++;
        char z[10];
        GetWindowText(tW, lpWinTitle, 256 - 1);
        string str = "Child Window #" + to_string(i);
        wstring s1 = wstring(str.begin(), str.end());
        const wchar_t* s = s1.c_str();
        SendMessage(tW, WM_SETTEXT, 0, (LPARAM)s);
        TCHAR lpWinTitle1[256];
        GetWindowText(tW, lpWinTitle1, 256 - 1);
        return true;
    }
}