#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WIDTH 400
#define HEIGHT 300
// C:\Users\evilm\mingw64\bin\gcc.exe dvd_logo.c -o dvd.exe -lgdi32 -luser32

HDC hdc;
HDC hdcMem;
HBITMAP hBitmap;
BITMAPINFO bitmapInfo;
DWORD pixels[WIDTH * HEIGHT] = {0}; // Pixels array

int coordinates[2] = {200, 150}; // centre of logo
int size[2] = {10, 10}; // size of logo
int directionStatic[2] = {1,2};
int directionCurrent[2] = {1,2};

void initLogo(){
    for(int i = coordinates[0]-size[0]; i <= coordinates[0]+size[0]; i++){
        for(int j = coordinates[1]-size[1]; j <= coordinates[1]+size[1]; j++){
            pixels[i + j * WIDTH] = RGB(255,255,255);
        } 
    }
}

// main animation function - 
void animateLogo(){
    //it will loop through the direction current until 0 then refresh to static
    // if a wall is hit the directionc urrent and static are updated
    if(directionCurrent[0]){

    } else if(directionCurrent[1]){

    }
    if(!directionCurrent[0] && !directionCurrent[1]){
        directionCurrent[0] = directionStatic[0];
        directionCurrent[1] = directionStatic[1];
    }
}


// function to handle screen setup
void setupScreen(HWND hwnd, WPARAM wParam, LPARAM lParam){
    hdc = GetDC(hwnd);
    hdcMem = CreateCompatibleDC(hdc);
    hBitmap = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
    SelectObject(hdcMem, hBitmap);

    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = WIDTH;
    bitmapInfo.bmiHeader.biHeight = -HEIGHT;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    GetDIBits(hdcMem, hBitmap, 0, HEIGHT, pixels, &bitmapInfo, DIB_RGB_COLORS);
}

int counter = 0;

void editScreen(HWND hwnd, WPARAM wParam, LPARAM lParam){
    // Main function to animate cars
    animateLogo();
    // Update the bitmap with modified pixel data
    SetDIBits(hdcMem, hBitmap, 0, HEIGHT, pixels, &bitmapInfo, DIB_RGB_COLORS);
    BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hdcMem, 0, 0, SRCCOPY);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT:
            editScreen(hwnd, wParam, lParam);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {

    // Setup window
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.lpszClassName = "Traffic";
    wc.hInstance = GetModuleHandle(NULL);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, wc.lpszClassName, "Traffic",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
                               NULL, NULL, wc.hInstance, NULL);

    setupScreen(hwnd, WIDTH, HEIGHT);
    
    // initialise our cars array and setup roads
    initLogo();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(hwnd, hdc);

    return 0;
}