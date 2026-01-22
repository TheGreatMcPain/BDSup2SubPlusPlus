/*
 * BDSup2Sub++ (C) 2012 Adam T.
 * Based on code from BDSup2Sub by Copyright 2009 Volker Oth (0xdeadbeef)
 * and Copyright 2012 Miklos Juhasz (mjuhasz)
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PALETTE_H
#define PALETTE_H

#include <QtGlobal>
#include <QList>
#include <QColor>

class Palette
{
public:
    Palette();
    Palette(const Palette& other);
    Palette(const Palette* other);
    Palette(int paletteSize, bool use601 = false);
    Palette(QList<uchar> r, QVector<uchar> g, QVector<uchar> b, QVector<uchar> a, bool use601);
    ~Palette();

    void setAlpha(int index, int alpha);
    void setRGB(int index, QRgb rgb);
    void setARGB(int index, QRgb inColor);
    void setColor(int index, const QColor &color)
    {
        setRGB(index, color.rgb());
        setAlpha(index, color.alpha());
    }
    void setYCbCr(int index, int yn, int cbn, int crn);

    int size() { return paletteSize; }
    int alpha(int index) { return qAlpha(colors[index]); }
    int transparentIndex();

    QColor color(int index) { return QColor(qRed(colors[index]), qGreen(colors[index]),
                                               qBlue(colors[index]), qAlpha(colors[index])); }

    QRgb rgb(int index) { return qRgba(qRed(colors[index]), qGreen(colors[index]), qBlue(colors[index]), 0); }
    QRgb rgba(int index) { return colors[index]; }

    QList<uchar> Y() { return y; }
    QList<uchar> Cb() { return cb; }
    QList<uchar> Cr() { return cr; }

    QList<int> YCbCr(int index);

    QList<QRgb> colorTable() { return colors; }

    static QList<int> RGB2YCbCr(QRgb rgb, bool use601);

private:
    int paletteSize = 0;

    bool useBT601 = false;

    QList<QRgb> colors;
    QList<uchar> y;
    QList<uchar> cb;
    QList<uchar> cr;

    QRgb YCbCr2RGB(int y, int cb, int cr, bool useBT601);
};

#endif // PALETTE_H
