// lab7.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab7.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HBITMAP hBackImg;                               // картинка-фон
HBITMAP hPlaneImg;                              // картинка самолета
HWND hAnimateBtn;                               // кнопка запуска анимации
HWND hMetaBtn;                                  // кнопка создания метафайла

const static int idAnimateBtn = 0;
const static int idMetaBtn = 1;
const static int idTimer = 2;
bool is_animate = false, is_meta = false;
RECT mainRect = { -10, 300, 360, 440 };
int x_plane = 0;
int hWidth = 1200, hHeight = 800;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID                DrawBitmap(HDC, int, int, HBITMAP);

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
    LoadStringW(hInstance, IDC_LAB7, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB7));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB7));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB7);
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
      CW_USEDEFAULT, 0, hWidth, hHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   hAnimateBtn = CreateWindow(L"BUTTON", L"Запустить анимацию", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
       0, 0, 200, 25, hWnd, (HMENU)idAnimateBtn, hInstance, NULL);
   hMetaBtn = CreateWindow(L"BUTTON", L"Создать метафайл", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
       210, 0, 200, 25, hWnd, (HMENU)idMetaBtn, hInstance, NULL);


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
    {
        hBackImg = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BACK));
        hPlaneImg = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PLANE));
    }
    break;
    case WM_TIMER:
    {
        if (x_plane < hWidth) {
            x_plane += 15;
            mainRect.left += 15;
            mainRect.right += 15;
            InvalidateRect(hWnd, &mainRect, FALSE);
            UpdateWindow(hWnd);
        }
        else {
            x_plane = -360;
            mainRect.left = -370;
            mainRect.right = 0;
        }
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case idAnimateBtn:
            {
                is_animate = !is_animate;
                if (is_animate)
                    SetTimer(hWnd, idTimer, 200, NULL);
                else
                    KillTimer(hWnd, idTimer);
            }
            break;
            case idMetaBtn:
            {
                HDC metaDC = CreateMetaFile(L"metafile.wmf");
                if (metaDC != NULL) {
                    HBRUSH rb = CreateSolidBrush(RGB(255, 0, 0));
                    HBRUSH gb = CreateSolidBrush(RGB(0, 255, 0));
                    SelectObject(metaDC, rb);
                    Rectangle(metaDC, 0, 0, 300, 300);
                    SelectObject(metaDC, gb);
                    Ellipse(metaDC, 0, 0, 300, 300);
                    SelectObject(metaDC, rb);
                    RoundRect(metaDC, 100, 100, 200, 200, 10, 10);
                    CloseMetaFile(metaDC);
                    DeleteDC(metaDC);
                }
                else
                    MessageBox(hWnd, L"Не удалось создать metafile.wmf ", L"Error", MB_OK | MB_ICONEXCLAMATION);
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
            DrawBitmap(hdc, 0, 0, hBackImg);
            DrawBitmap(hdc, x_plane, mainRect.top, hPlaneImg);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        DeleteObject(hBackImg);
        DeleteObject(hPlaneImg);
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

VOID DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap) {
    HBITMAP old_bitmap;
    HDC hImgDC;
    BITMAP bitmap;
    POINT  ptSize, ptOrg;
    hImgDC = CreateCompatibleDC(hDC);
    old_bitmap = (HBITMAP)SelectObject(hImgDC, hBitmap);
    if (old_bitmap)
    {
        SetMapMode(hImgDC, GetMapMode(hDC));
        GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bitmap);
        ptSize.x = bitmap.bmWidth;
        ptSize.y = bitmap.bmHeight;
        DPtoLP(hDC, &ptSize, 1);
        ptOrg.x = 0;
        ptOrg.y = 0;
        DPtoLP(hImgDC, &ptOrg, 1);
        BitBlt(hDC, x, y, ptSize.x, ptSize.y,
            hImgDC, ptOrg.x, ptOrg.y, SRCCOPY);
        SelectObject(hImgDC, old_bitmap);
    }
    DeleteDC(hImgDC);
}