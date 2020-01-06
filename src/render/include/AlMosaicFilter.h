/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#ifndef HWVC_ANDROID_ALMOSAICFILTER_H
#define HWVC_ANDROID_ALMOSAICFILTER_H

#include "HwAbsFilter.h"
#include "AlPointF.h"

///马赛克
al_class_ex(AlMosaicFilter, HwAbsFilter) {
public:
    AlMosaicFilter();

    ~AlMosaicFilter();

    void updatePath(std::vector<AlPointF> *vec);

    HwProgram *createProgram() override;

    void draw(HwAbsTexture *src, HwAbsTexture *dest) override;

private:
    AlMosaicFilter(const AlMosaicFilter &o) : HwAbsFilter() {}

    void drawFirst(HwProgram *program, HwAbsTexture *src, HwAbsTexture *dest) override;

private:
    int32_t uRadius = 0;
    int32_t uPaintRadius = 0;
    int32_t uPaths = 0;
    AlVec2 radius;
    float *path = nullptr;
};


#endif //HWVC_ANDROID_ALMOSAICFILTER_H
