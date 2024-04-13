#if !defined( BIT_MAP_HPP )
#define BIT_MAP_HPP

    #include <windows.h>
    #include <vector>

    typedef HWND WindowHandleId;
    typedef HDC DeviceContextHandleId;
    typedef HBITMAP BitMapHandleId;

    // https://stackoverflow.com/questions/26233848/c-read-pixels-with-getdibits 
    BitMapHandleId getScreenCaptureBitmap( DeviceContextHandleId context, POINT topLeft, int captureWidth, int captureHeight )
    {
        // Create compatible context, create a compatible bitmap and copy the screen using BitBlt()
        DeviceContextHandleId captureContext  = CreateCompatibleDC(context);
        BitMapHandleId bitMap = CreateCompatibleBitmap(context, captureWidth, captureHeight);
        HGDIOBJ oldBitMap = SelectObject(captureContext, bitMap);
        BitBlt( captureContext, 0, 0, captureWidth, captureHeight, context, topLeft.x, topLeft.y, SRCCOPY | CAPTUREBLT ); 

        // Reselect old bitmap. If we dont do this, when we delete DC it will delete the one we want and leak the old one
        SelectObject(captureContext, oldBitMap);
        DeleteDC(captureContext);
        return bitMap;
    }

    bool getPixels( DeviceContextHandleId context, std::vector<RGBQUAD> &pixels, POINT topLeft, int captureWidth, int captureHeight )
    {
        // Great! We have the data but its not in a usable form.
        BitMapHandleId screenCaptureBitMap = getScreenCaptureBitmap( context, topLeft, captureWidth, captureHeight );

        BITMAPINFO bitMapInfo = {0};
        // It needs to know the size of the header because it takes a pointer reference.
        bitMapInfo.bmiHeader.biSize = sizeof(bitMapInfo.bmiHeader);

        // Passed in NULL for pixelBuffer, so the function will populate bitMapInfo.
        if ( !GetDIBits( context, screenCaptureBitMap, 0, 0, NULL, &bitMapInfo, DIB_RGB_COLORS ) )
            return false;

        // Resize buffer if needed
        if ( pixels.size() != captureWidth*captureHeight )
            pixels.resize(captureWidth*captureHeight);

        // There is a chance that this is BI_BITFIELDS, meaning it can be either RGB 565 or RBG 55.
        // We only want RGB 555, so we specify that using BI_RGB.  
        bitMapInfo.bmiHeader.biCompression = BI_RGB;

        // Now we have all the bitMap info! Lets get the buffer! Copy all data from the start (index 0) to the end of the bitmap (biHeight).
        if ( !GetDIBits( context, screenCaptureBitMap, 0, bitMapInfo.bmiHeader.biHeight, &pixels[0], &bitMapInfo, DIB_RGB_COLORS ) )
            return false;

        DeleteObject( screenCaptureBitMap );

        return true;
    }

    RGBQUAD getBufferValueAt( std::vector<RGBQUAD> &pixels, int screenWidth, int screenHeight, int xIndex, int yIndex )
    {
        return pixels[LONG(xIndex)+screenWidth*LONG(screenHeight-yIndex-1)];
    }

    bool operator<( const RGBQUAD &rgb1, const RGBQUAD &rgb2 )
    {
        return std::tie(rgb1.rgbRed,rgb1.rgbGreen,rgb1.rgbBlue) < std::tie(rgb2.rgbRed,rgb2.rgbGreen,rgb2.rgbBlue);
    }

    std::set<RGBQUAD> getColoursInArea( std::vector<RGBQUAD> &pixels, int screenWidth, int screenHeight, int xIndex, int yIndex )
    {
        std::set<RGBQUAD> colours;
        for ( int xOffset = -2; xOffset <= 2; xOffset++ )
        {
            for ( int yOffset = -2; yOffset <= 2; yOffset++ )
            {
                RGBQUAD colour = getBufferValueAt( pixels, screenWidth, screenHeight, xIndex+xOffset, yIndex+yOffset );
                colours.insert( colour );
            }
        }

        return colours;
    }

#endif /* BIT_MAP_HPP */