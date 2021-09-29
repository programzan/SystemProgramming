// lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab2.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND Btn1;                                      // большая кнопка
HWND Btn2;                                      // малая кнопка
HWND InputTxt;                                  // поле ввода
HWND OutputTxt;                                 // поле вывода
HWND LogTxt;                                    // вывод событий
HWND MouseTracker;                              // поле для вывода кол-ва изменений состояния мыши
TCHAR EventList[1000];                          // строковая переменная

const static int idBtn1 = 1;                    // идентификаторы кнопок и полей
const static int idBtn2 = 2;
const static int idInputTxt = 3;
const static int idOutputTxt = 4;
const static int idLogTxt = 5;
const static int idMouseTracker = 6;

int WWidth = 800;
int WHeight = 600;
int Counter = 0;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2);
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
      CW_USEDEFAULT, WWidth, CW_USEDEFAULT, WHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   MoveWindow(hWnd, 200, 200, WWidth, WHeight, true);

   Btn1 = CreateWindow(L"BUTTON", L"Запустить программу", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 250, 150, 300, 50, hWnd, (HMENU)idBtn1, hInstance, NULL);
   Btn2 = CreateWindow(L"BUTTON", L"Возвести в квадрат", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 280, 100, 240, 25, hWnd, (HMENU)idBtn2, hInstance, NULL);
   InputTxt = CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 175, 25, 200, 50, hWnd, (HMENU)idInputTxt, hInstance, NULL);
   OutputTxt = CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD, 425, 25, 200, 50, hWnd, (HMENU)idOutputTxt, hInstance, NULL);
   LogTxt = CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 250, 600, 100, hWnd, (HMENU)idLogTxt, hInstance, NULL);
   MouseTracker = CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 0, 50, 25, hWnd, (HMENU)idMouseTracker, hInstance, NULL);

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
    case WM_RBUTTONDOWN:
    {
        POINTS MousePos = MAKEPOINTS(lParam);
        TCHAR strx[10], stry[10];
        _itot_s(MousePos.x, strx, 10);
        _itot_s(MousePos.y, stry, 10);
        TCHAR res[30] = TEXT("X: ");
        _tcscat_s(res, strx);
        _tcscat_s(res, TEXT(" Y: "));
        _tcscat_s(res, stry);
        SetWindowText(OutputTxt, res);
    }
    break;
    case WM_LBUTTONDOWN:
        _tcscat_s(EventList, _T("Нажата ЛКМ! "));
        SetWindowText(LogTxt, EventList);
        SendMessage(hWnd, WM_SYSCOMMAND, SC_MOVE | HTCLIENT, 0);
        SendMessage(hWnd, WM_LBUTTONUP, 0, 0);
        break;
    case WM_NCLBUTTONDOWN:
        if (wParam == HTCAPTION)
            return 0;
        else
            return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    case WM_LBUTTONUP:
        _tcscat_s(EventList, _T("Отпущена ЛКМ! "));
        SetWindowText(LogTxt, EventList);
        break;
    case WM_LBUTTONDBLCLK:
        _tcscat_s(EventList, _T("Двойной щелчок ЛКМ! "));
        SetWindowText(LogTxt, EventList);
        break;
    case WM_NCHITTEST:
        TCHAR str[10];
        _itot_s(Counter++, str, 10);
        SetWindowText(MouseTracker, str);
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case idBtn1: // нажатие на большую кнопку - заставляем нажаться маленькую
            {
                // 1 способ
                //SendMessage(hWnd, WM_COMMAND, idBtn2, 0);
                // 2 способ
                SendMessage(Btn2, BM_CLICK, 0, 0);
            }
            break;
            case idBtn2: // нажатие на маленькую кнопку - возводим число в квадрат
            {
                TCHAR InputTxtContent[MAX_LOADSTRING];
                int x;
                GetWindowText(InputTxt, InputTxtContent, 100);
                x = _tstoi(InputTxtContent);
                x = x * x;
                _itot_s(x, InputTxtContent, _countof(InputTxtContent), 10);
                SetWindowText(OutputTxt, InputTxtContent);
            }
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
