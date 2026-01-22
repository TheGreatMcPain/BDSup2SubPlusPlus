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

#ifndef SUBPICTUREBD_H
#define SUBPICTUREBD_H

#include "subpicture.h"
#include "imageobject.h"
#include "paletteinfo.h"
#include "../types.h"

#include <QList>
#include <QMap>

class ImageObject;
class PaletteInfo;

struct PCS
{
    long pts = -1;
    int videoWidth;
    int videoHeight;
    int frameRate;
    int compositionNumber;
    CompositionState compositionState;
    bool paletteUpdate = false;
    int paletteId;
    int numberOfCompositionObjects;
    QList<int> objectIds;
    QMap<int, int> windowIds;       // map of object id to window id
    QMap<int, int> forcedFlags;     // map of object id to forced flag
    QMap<int, int> xPositions;      // map of object id to x position
    QMap<int, int> yPositions;      // map of object id to y position
};

struct WDS
{
    int numberOfWindows;
    QList<int> windowIds;
    QMap<int, QRect> windows;
};

struct PDS
{
    int paletteId = -1;
    int paletteVersion = -1;
    int paletteSize = -1;
    PaletteInfo paletteInfo;
};

struct ODS
{
    int objectId;
    int objectVersion;
    int objectSequence;
    int rleLength;
    int width;
    int height;
    ImageObjectFragment fragment;
};

class SubPictureBD : public SubPicture
{
public:
    SubPictureBD();
    SubPictureBD(const SubPictureBD* other);
    SubPictureBD(const SubPictureBD& other);
    ~SubPictureBD() override { }

    SubPicture* copy() override;

    int imageWidth() override
    {
        int width;
        if (numberCompObjects == 1)
        {
            width = scaledImageRects[objectIds[0]].width();
        }
        else
        {
            int left = scaledImageRects[objectIds[0]].x() < scaledImageRects[objectIds[1]].x() ?
                       scaledImageRects[objectIds[0]].x() : scaledImageRects[objectIds[1]].x();
            int right = scaledImageRects[objectIds[0]].right() > scaledImageRects[objectIds[1]].right() ?
                        scaledImageRects[objectIds[0]].right() : scaledImageRects[objectIds[1]].right();
            width = (right - left) + 1;
        }
        return width;
    }

    int imageHeight() override
    {
        if (numberCompObjects == 1)
        {
            return scaledImageRects[objectIds[0]].height();
        }
        else if (scaledImageRects[objectIds[0]].y() < scaledImageRects[objectIds[1]].y())
        {
            return ((scaledImageRects[objectIds[1]].y() + scaledImageRects[objectIds[1]].height()) - scaledImageRects[objectIds[0]].y());
        }
        else
        {
            return ((scaledImageRects[objectIds[0]].y() + scaledImageRects[objectIds[0]].height()) - scaledImageRects[objectIds[1]].y());
        }
    }

    int x() override
    {
        if (numberCompObjects == 1)
        {
            return scaledImageRects[objectIds[0]].x();
        }
        return scaledImageRects[objectIds[0]].x() < scaledImageRects[objectIds[1]].x() ?
                scaledImageRects[objectIds[0]].x() : scaledImageRects[objectIds[1]].x();
    }

    int y() override
    {
        if (numberCompObjects == 1)
        {
            return scaledImageRects[objectIds[0]].y();
        }
        return scaledImageRects[objectIds[0]].y() < scaledImageRects[objectIds[1]].y() ?
                scaledImageRects[objectIds[0]].y() : scaledImageRects[objectIds[1]].y();
    }

    CompositionState compositionState() { return compState; }
    void setCompositionState(CompositionState compositionState) { compState = compositionState; }

    int paletteId() { return paletteID; }
    void setPaletteId(int paletteId) { paletteID = paletteId; }

    bool paletteUpdated() { return paletteUpdate; }
    void setPaletteUpdated(bool paletteUpdated) { paletteUpdate = paletteUpdated; }

    int numberOfWindows() { return numWindows; }
    void setNumberOfWindows(int numberOfWindows) { numWindows = numberOfWindows; }

    int subPictureType() { return type; }
    void setSubPictureType(int subPictureType) { type = subPictureType; }

    bool isForced() override
    {
        bool isForced = false;

        for (auto& imageObject : imageObjectList)
        {
            if (!imageObject.fragmentList().empty())
            {
                isForced |= imageObject.isForced();
            }
        }
        return isForced;
    }

    void setForced(bool isForced) override
    {
        for (auto key : imageObjectList.keys())
        {
            auto& imageObject = imageObjectList[key];
            if (!imageObject.fragmentList().empty())
            {
                imageObject.setForcedFlags(isForced ? 0x40 : 0);
                forcedFlags[key] = imageObject.forcedFlags();
            }
        }
    }

    void setData(const PCS &pcs, QMap<int, QList<ODS>> ods, QMap<int, QVector<PaletteInfo>> pds, const WDS &wds);

    QMap<int, ImageObject> imageObjectList;

    QMap<int, QList<PaletteInfo>> palettes;

private:
    int type = 0;
    bool paletteUpdate = false;
    CompositionState compState;
    int paletteID = -1;
};

#endif // SUBSPICTUREBD_H
