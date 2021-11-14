// lab5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab5.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND ColorBack;                                 // кнопка для закраски фона преобладающим цветом раб.стола
HWND DrawFlags;                                 // кнопка для отрисовки флагов
HWND MoveCircles;                               // кнопка для движения кругов
HWND ChangeColor;                               // кнопка для смены цвета
HPEN hPen;                                      // перо

POINT pt, old, cur;

const static int idMove = 1;
const static int idMoveCircles = 2;
const static int idColorBack = 3;
const static int idDrawFlags = 4;
const static int idChangeColor = 5;

bool timer = false;
bool is_drawing = false;
bool back_coloring = false;
bool is_moving_circ = false;
bool is_draw_flag = false;
bool is_change_color = false;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID                PaintFlag(HWND hWnd, bool is_client = false);
VOID                MoveCircle(HWND hWnd, RECT& circle, int x, int y);
VOID                MoveOn(HWND hWnd, bool init = false);
VOID                MoveDesktop(bool init = false);
VOID                MoveWinF(bool init = false);

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
    LoadStringW(hInstance, IDC_LAB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB5);
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
      CW_USEDEFAULT, 0, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ColorBack = CreateWindow(L"BUTTON", L"Фон + фигуры", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 570, 10, 200, 30, hWnd, (HMENU)idColorBack, hInstance, NULL);
   DrawFlags = CreateWindow(L"BUTTON", L"Нарисовать флаги", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 570, 50, 200, 30, hWnd, (HMENU)idDrawFlags, hInstance, NULL);
   MoveCircles = CreateWindow(L"BUTTON", L"Запустить круги", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 570, 90, 200, 30, hWnd, (HMENU)idMoveCircles, hInstance, NULL);
   ChangeColor = CreateWindow(L"BUTTON", L"Сменить цвет", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 570, 130, 200, 30, hWnd, (HMENU)idChangeColor, hInstance, NULL);

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
    case WM_TIMER:
        {
            int wmId = wParam;
            switch (wmId)
            {
            case idMove:
                MoveOn(hWnd);
                MoveWinF();
                MoveDesktop();
                break;
            default:
                break;
            }
        }
    break;
    case WM_LBUTTONDOWN:
    {
        is_drawing = true;
        hPen = CreatePen(PS_SOLID, 4, RGB(50, 20, 200));
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        old.x = -1; old.y = -1;
    }
    break;
    case WM_LBUTTONUP:
        is_drawing = false;
    break;
    case WM_MOUSEMOVE:
    {
        if (is_drawing) {
            cur.x = LOWORD(lParam);
            cur.y = HIWORD(lParam);
            HDC hdc = GetDC(hWnd);
            SelectObject(hdc, hPen);
            MoveToEx(hdc, pt.x, pt.y, NULL);
            if (is_change_color)
                SetROP2(hdc, R2_XORPEN);
            else
                SetROP2(hdc, R2_NOTXORPEN);
            if (old.x >= 0)
                LineTo(hdc, old.x, old.y);
            MoveToEx(hdc, pt.x, pt.y, NULL);
            LineTo(hdc, cur.x, cur.y);
            ReleaseDC(hWnd, hdc);
            old.x = cur.x;
            old.y = cur.y;
        }
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case idColorBack:
                back_coloring = !back_coloring;
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case idDrawFlags:
                is_draw_flag = !is_draw_flag;
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case idMoveCircles:
                if (timer) {
                    timer = false;
                    KillTimer(hWnd, idMove);
                }
                else {
                    timer = true;
                    MoveOn(hWnd, true);
                    MoveWinF(true);
                    MoveDesktop(true);
                    SetTimer(hWnd, idMove, 200, NULL);
                }
                break;
            case idChangeColor:
                is_change_color = !is_change_color;
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
            if (back_coloring) {
                RECT rWnd;
                GetWindowRect(hWnd, &rWnd);
                rWnd.bottom = rWnd.bottom - rWnd.top;
                rWnd.right = rWnd.right - rWnd.left;
                rWnd.top = 0;
                rWnd.left = 0;
                COLORREF clrDesktop = GetPixel(hdc, 1000, 1000);
                SetBkColor(hdc, clrDesktop);
                FillRect(hdc, &rWnd, CreateSolidBrush(clrDesktop));
                HPEN pen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
                SelectObject(hdc, pen);
                Rectangle(hdc, 100, 400, 200, 450);
                SetTextColor(hdc, RGB(255, 0, 0));
                TextOut(hdc, 105, 370, TEXT("Прямоугольник"), 14);
                HBRUSH brush1 = CreateHatchBrush(HS_CROSS, RGB(0, 255, 0));
                SelectObject(hdc, brush1);
                Ellipse(hdc, 300, 400, 400, 450);
                TextOut(hdc, 320, 370, TEXT("Эллипс"), 7);
            }
            if (is_draw_flag) {
                PaintFlag(GetDesktopWindow());
                PaintFlag(hWnd);
                PaintFlag(hWnd, true);
            }
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

// Отрисовка флага России
VOID PaintFlag(HWND hWnd, bool is_client) {
    HDC hdc;
    RECT rect;
    if (is_client) {
        hdc = GetDC(hWnd);
        rect.left = 0, rect.top = 0, rect.bottom = 100, rect.right = 200;
        FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 255, 255)));
    }
    else {
        hdc = GetWindowDC(hWnd);
        rect.left = 300, rect.top = 0, rect.bottom = 100, rect.right = 500;
        FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 255, 255)));
    }
    rect.top = 100, rect.bottom = 200;
    FillRect(hdc, &rect, CreateSolidBrush(RGB(0, 0, 255)));
    rect.top = 200, rect.bottom = 300;
    FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 0, 0)));
    ReleaseDC(hWnd, hdc);
}

// Функции движения кружка
VOID MoveCircle(HWND hWnd, RECT& circle, int x, int y) {
    HDC hdc = GetDC(hWnd);
    InvalidateRect(hWnd, &circle, true);
    UpdateWindow(hWnd);
    circle.left += x, circle.right += x;
    circle.top += y, circle.bottom += y;
    SelectObject(hdc, CreateSolidBrush(RGB(200, 100, 0)));
    Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom);
    ReleaseDC(hWnd, hdc);
}

VOID MoveOn(HWND hWnd, bool init) {
    static RECT circle, rect;
    static int x = 5, y = -5;
    if (init) {
        circle.left = 50, circle.right = 200, circle.top = 50, circle.bottom = 200;
    }
    GetWindowRect(hWnd, &rect);
    if (rect.right - rect.left - circle.right <= 0)
        x = -5;
    if (circle.left <= 0)
        x = 5;
    if (circle.top <= 0)
        y = 5;
    if (rect.bottom - rect.top - circle.bottom <= 0)
        y = -5;
    MoveCircle(hWnd, circle, x, y);
}

VOID MoveDesktop(bool init) {
    static RECT circle, rect;
    static int x = 5, y = -5;
    static HWND hDsktp = GetDesktopWindow();
    if (init) {
        circle.left = 50, circle.right = 400, circle.top = 50, circle.bottom = 400;
        GetWindowRect(hDsktp, &rect);
    }
    if (rect.right - rect.left - circle.right <= 0)
        x = -5;
    if (circle.left <= 0)
        x = 5;
    if (circle.top <= 0)
        y = 5;
    if (rect.bottom - rect.top - circle.bottom <= 0)
        y = -5;
    MoveCircle(hDsktp, circle, x, y);
}

VOID MoveWinF(bool init) {
    static RECT circle, rect;
    static int x = 5, y = -5;
    static HWND hWinF = FindWindow(0, L"C#");
    if (hWinF == NULL) {
        return;
    }
    if (init) {
        circle.left = 50, circle.right = 200, circle.top = 50, circle.bottom = 200;
    }
    GetWindowRect(hWinF, &rect);
    if (rect.right - rect.left - circle.right <= 0)
        x = -5;
    if (circle.left <= 0)
        x = 5;
    if (circle.top <= 0)
        y = 5;
    if (rect.bottom - rect.top - circle.bottom <= 0)
        y = -5;
    MoveCircle(hWinF, circle, x, y);
}

