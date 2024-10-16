#pragma once
#define _CRT_NONSTDC_NO_DEPRECATE
/* #ifdef TESSERACT_VERSION // 3.03 API */
/* #include <tesseract/renderer.h> */
/* #endif // TESSERACT_VERSION */
/* #if (TESSERACT_MAJOR_VERSION < 5) */
/* #include <tesseract/strngs.h> */
/* #endif */

#include <QPainter>
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

#if (LIBLEPT_MAJOR_VERSION > 1) || (LIBLEPT_MINOR_VERSION > 82)
#include <leptonica/pix_internal.h>
#endif

// Thanks to Stackoverflow user "user898678":
// https://stackoverflow.com/a/10019508
// https://github.com/zdenop/qt-box-editor/blob/master/src/TessTools.cpp
// LICENSE: https://github.com/zdenop/qt-box-editor/blob/master/LICENSE
// modified version

class TesseractTool
{
public:
    static PIX* qImageToPIX(const QImage& qImage)
    {
        PIX* pixs;
        l_uint32* lines;

        QImage qImageCopy = qImage.copy();

        qImageCopy = qImageCopy.rgbSwapped();
        int width = qImageCopy.width();
        int height = qImageCopy.height();
        int depth = qImageCopy.depth();
        int wpl = qImageCopy.bytesPerLine() / 4;

        pixs = pixCreate(width, height, depth);
        pixSetWpl(pixs, wpl);
        pixSetColormap(pixs, NULL);
        l_uint32* datas = pixs->data;

        for (int y = 0; y < height; y++) {
            lines = datas + y * wpl;
            QByteArray a((const char*)qImageCopy.scanLine(y),
                         qImageCopy.bytesPerLine());
            for (int j = 0; j < a.size(); j++) {
                *((l_uint8*)lines + j) = a[j];
            }
        }
        return pixEndianByteSwapNew(pixs);
    }
};
