#include <windows.h>
#include <math.h>

#include "drawing/drawing.c"
#include "matrix/matrix.c"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Lab 3";
boolean isDirect = 1;
double k = 0.67;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
    WNDCLASS window;
    window.lpszClassName = ProgName;
    window.hInstance = hInstance;
    window.lpfnWndProc = WndProc;
    window.hCursor = LoadCursor(NULL, IDC_ARROW);
    window.hIcon = 0;
    window.lpszMenuName = 0;
    window.hbrBackground = WHITE_BRUSH;
    window.style = CS_HREDRAW|CS_VREDRAW;
    window.cbClsExtra = 0;
    window.cbWndExtra = 0;

    if (!RegisterClass(&window)) return 0;

    HWND hWnd;
    MSG lpMsg;

    hWnd = CreateWindow(
            ProgName,
            "Lab 3 by Lev Bereza",
            WS_OVERLAPPEDWINDOW,
            100, 100, 1000, 800,
            (HWND) NULL,
            (HMENU) NULL,
            (HINSTANCE) hInstance,
            (HINSTANCE) NULL);

    HWND button1 = CreateWindow("BUTTON",
                                "Direct graph",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                850, 175,
                                110, 30,
                                hWnd, (HMENU)1, NULL, NULL);
    HWND button2 = CreateWindow("BUTTON",
                                "Indirect graph",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                850, 215,
                                110, 30,
                                hWnd, (HMENU)2, NULL, NULL);
    HWND button3 = CreateWindow("BUTTON",
                                "First koef",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                850, 250,
                                110, 30,
                                hWnd, (HMENU)3, NULL, NULL);
    HWND button4 = CreateWindow("BUTTON",
                                "Second koef",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                850, 290,
                                110, 30,
                                hWnd, (HMENU)4, NULL, NULL);
    HWND button5 = CreateWindow("BUTTON",
                                "Condensation",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                850, 350,
                                110, 30,
                                hWnd, (HMENU)5, NULL, NULL);

    ShowWindow(hWnd, nCmdShow);

    int flag;
    while((flag = GetMessage(&lpMsg, hWnd, 0, 0)) != 0) {
        if (flag == -1) return lpMsg.wParam;
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return lpMsg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC handle;
    PAINTSTRUCT ps;
    RECT rect;

    switch(message) {
        case WM_PAINT :
            drawGraph(handle, hWnd, ps, isDirect, k);
            EndPaint(hWnd, &ps);
            break;

        case WM_COMMAND:
        {
            GetClientRect(hWnd, &rect);
            InvalidateRect(hWnd, &rect, TRUE);
            handle = GetDC(hWnd);
            UpdateWindow(hWnd);
            SetBkMode(handle, TRANSPARENT);

            switch (LOWORD(wParam))
            {
                case 1:
                    isDirect = 1;
                    FillRect(handle, &rect, (HBRUSH) (COLOR_WINDOW + 1));
                    InvalidateRect(hWnd, NULL, TRUE);
                    break;
                case 2:
                    isDirect = 0;
                    FillRect(handle, &rect, (HBRUSH) (COLOR_WINDOW + 1));
                    InvalidateRect(hWnd, NULL, TRUE);
                    break;
                case 3:
                    k = 0.67;
                    FillRect(handle, &rect, (HBRUSH) (COLOR_WINDOW + 1));
                    InvalidateRect(hWnd, NULL, TRUE);
                    break;
                case 4:
                    k = 0.715;
                    FillRect(handle, &rect, (HBRUSH) (COLOR_WINDOW + 1));
                    InvalidateRect(hWnd, NULL, TRUE);
                    break;
                case 5:
                    k = 0.715;
                    FillRect(handle, &rect, (HBRUSH) (COLOR_WINDOW + 1));
                    InvalidateRect(hWnd, NULL, TRUE);
                    drawCondensationGraph(handle, hWnd, ps);
                    break;
                default:
                    printf("other\n");
                    break;
            }
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, message, wParam, lParam));
    }
}