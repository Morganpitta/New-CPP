#include <windows.h>
#include <iostream>
#include <vector>

typedef HWND WindowHandleId;
typedef HDC DeviceContextHandleId;

int main()
{
    DeviceContextHandleId context = GetDC(NULL);

    POINT point;
    while ( true )
    {
        if ( GetKeyState('Z') & 0x8000 ) { 
            GetCursorPos(&point); 
            COLORREF colour = GetPixel(context,point.x,point.y+30); 
            std::cout << std::hex << colour << std::endl; 
            SelectObject( context, GetStockObject(DC_BRUSH) );
            SetDCBrushColor(context,colour); 
            Ellipse( context, 0, 0, 10, 10 );
        }
    }

    return 0;
}