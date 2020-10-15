#include <windows.h>
#include <gdiplus.h>
#include <iostream>

int GetEncoderClsid(const WCHAR *format, CLSID *pClsid) {
    using namespace Gdiplus;
    UINT num = 0;
    UINT size = 0;

    ImageCodecInfo *pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;

    pImageCodecInfo = (ImageCodecInfo *) (malloc(size));
    if (pImageCodecInfo == NULL)
        return -1;

    GetImageEncoders(num, size, pImageCodecInfo);
    for (UINT j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }
    }
    free(pImageCodecInfo);
    return 0;
}

bool analyze_screen() {
    bool sameColor = TRUE;

    using namespace Gdiplus;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    {
        SetProcessDPIAware();

        HDC scrdc, memdc;
        HBITMAP membit;
        scrdc = ::GetDC(0);
        int height = GetSystemMetrics(SM_CYSCREEN);
        int width = GetSystemMetrics(SM_CXSCREEN);
        memdc = CreateCompatibleDC(scrdc);
        membit = CreateCompatibleBitmap(scrdc, width, height);
        HBITMAP hOldBitmap = (HBITMAP) SelectObject(memdc, membit);
        BitBlt(memdc, 0, 0, width, height, scrdc, 0, 0, SRCCOPY);
        Gdiplus::Bitmap bitmap(membit, NULL);

        Color currPixel(0, 255, 255, 255);
        int y = height - 1;
        for (int x = 0; x < width; x++) {
            bitmap.GetPixel(x, y, &currPixel);
            if (
                    (currPixel.GetR() != 1) ||
                    (currPixel.GetG() != 1) ||
                    (currPixel.GetB() != 1)
                    ) {
                sameColor = false;
                break;
            }
        }

        DeleteObject(memdc);
        DeleteObject(membit);
        ::ReleaseDC(0, scrdc);
    }
    GdiplusShutdown(gdiplusToken);
    return sameColor;
}

inline const char *const boolToString(bool b) {
    return b ? "1" : "0";
}

void toClipboard(HWND hwnd, const std::string &s) {
    OpenClipboard(hwnd);
    EmptyClipboard();
    HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
    if (!hg) {
        CloseClipboard();
        return;
    }
    memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
    GlobalUnlock(hg);
    SetClipboardData(CF_TEXT, hg);
    CloseClipboard();
    GlobalFree(hg);
}

int main() {
    bool b = analyze_screen();
    std::string result = boolToString(b);
    toClipboard(NULL, result);

    std::cout << boolToString(b) << std::endl;

    return 0;
}