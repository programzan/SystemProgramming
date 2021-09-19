// lab1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND Btn1;                                      // большая кнопка
HWND Btn2;                                      // малая кнопка
HWND EditTxt;                                   // поле ввода (EDIT)
HWND StaticTxt;                                 // поле вывода (STATIC) 

const static int idBtn1 = 1;                    // идентификаторы кнопок и полей
const static int idBtn2 = 2;
const static int idEditTxt = 3;
const static int idStaticTxt = 4;

const static int idTimer = 5;                   // идентификатор таймера
static int Counter = 0;                         // счетчик

int WWidth = 800;
int WHeight = 600;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                WRedrawRgn(HWND);

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
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));           // иконка в панели задач
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MYICON));     // иконка в левом верхнем углу окна

    return RegisterClassExW(&wcex);
}

void WRedrawRgn(HWND hWnd) {
    HRGN cutRgn, outRgn;
    RECT WRect;
    GetWindowRect(hWnd, &WRect);
    WWidth = WRect.right - WRect.left; // новая ширина окна
    WHeight = WRect.bottom - WRect.top; // новая высота окна
    outRgn = CreateEllipticRgn(-10, -WHeight, WWidth + 10, WHeight);
    int r = 100; // радиус вырезанного круга
    cutRgn = CreateEllipticRgn(WWidth / 2 - r, WHeight - 200 - r, WWidth / 2 + r, WHeight - 200 + r);
    CombineRgn(cutRgn, cutRgn, outRgn, RGN_XOR);
    SetWindowRgn(hWnd, cutRgn, true);
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

   //SetWindowPos(hWnd, HWND_TOPMOST, 200, 200, WWidth, WHeight, SWP_SHOWWINDOW);   // варианты изменения размера окна
   MoveWindow(hWnd, 200, 200, WWidth, WHeight, true);                               
   
   WRedrawRgn(hWnd);


   Btn1 = CreateWindow(L"BUTTON", L"Вывести текст из EDIT в STATIC", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 250, 150, 300, 50, hWnd, (HMENU)idBtn1, hInstance, NULL);
   Btn2 = CreateWindow(L"BUTTON", L"Вывести заголовок в STATIC", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 280, 100, 240, 25, hWnd, (HMENU)idBtn2, hInstance, NULL);
   EditTxt = CreateWindow(L"EDIT", L"Some text in EDIT", WS_VISIBLE|WS_CHILD|WS_BORDER, 25, 25, 200, 50, hWnd, (HMENU)idEditTxt, hInstance, NULL);
   StaticTxt = CreateWindow(L"STATIC", L"Some text in STATIC", WS_VISIBLE|WS_CHILD, 575, 25, 200, 50, hWnd, (HMENU)idStaticTxt, hInstance, NULL);

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
        MessageBox(hWnd, L"Окно было успешно создано!", L"Message", MB_OK);
        break;
    case WM_LBUTTONDOWN: // Нажатие на левую кнопку мыши
        SetWindowText(StaticTxt, L"Нажатие левой кнопки мыши!");
        break;
    case WM_RBUTTONDOWN: // Нажатие на правую кнопку мыши
        SetWindowText(StaticTxt, L"Нажатие правой кнопки мыши!");
        KillTimer(hWnd, idTimer);
        if (GetParent(Btn1) != hWnd) {
            SetParent(Btn1, hWnd);
            MoveWindow(Btn1, 250, 150, 300, 50, true);
        }
        break;
    case WM_INITMENUPOPUP: // Сообщение перед раскрытием меню
        SetWindowText(StaticTxt, L"Открыто меню!");
        break;
    case WM_TIMER:
        {
            ++Counter;
            MoveWindow(Btn1, Counter, Counter, 300, 50, true);
        }
        break;
    case WM_SIZE:
        {
            WRedrawRgn(hWnd);
        }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case idBtn1: // нажатие на большую кнопку - вставляем в STATIC текст из EDIT
            {
                TCHAR editTextContent[MAX_LOADSTRING];
                GetWindowText(EditTxt, editTextContent, MAX_LOADSTRING);
                SetWindowText(StaticTxt, editTextContent);
            }
            break;
            case idBtn2: // нажатие на маленькую кнопку - вставляем в STATIC заголовок окна
            {
                TCHAR editTextContent[MAX_LOADSTRING];
                GetWindowText(hWnd, editTextContent, MAX_LOADSTRING);
                SetWindowText(StaticTxt, editTextContent);
            }
            break;
            case IDM_CHANGEPARENT:
            {
                Counter = 0; 
                SetTimer(hWnd, idTimer, 30, (TIMERPROC)NULL); 
                if (GetParent(Btn1) == hWnd) {  
                    SetParent(Btn1, NULL);
                }
                else {
                    KillTimer(hWnd, idTimer); 
                    SetParent(Btn1, hWnd); 
                    MoveWindow(Btn1, 250, 150, 300, 50, true);
                }
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
        MessageBox(hWnd, L"Окно было успешно закрыто!", L"Message", MB_OK);
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
