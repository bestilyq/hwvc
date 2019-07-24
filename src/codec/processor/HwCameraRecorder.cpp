/*
* Copyright (c) 2018-present, lmyooyo@gmail.com.
*
* This source code is licensed under the GPL license found in the
* LICENSE file in the root directory of this source tree.
*/

#include <Size.h>
#include "../include/HwCameraRecorder.h"
#include "../include/HwMicrophone.h"
#include "../include/HwCameraInput.h"
#include "../include/HwVideoCompiler.h"
#include "HwRender.h"
#include "HwScreen.h"
#include "ObjectBox.h"
#include "NativeWindow.h"

HwCameraRecorder::HwCameraRecorder() : HwAbsProcessor("HwCameraRecorder") {
    registerAnUnit(new HwMicrophone());
    registerAnUnit(new HwCameraInput());
    registerAnUnit(new HwRender());
    registerAnUnit(new HwScreen());
    registerAnUnit(new HwVideoCompiler());
}

HwCameraRecorder::~HwCameraRecorder() {
}

void HwCameraRecorder::onDestroy() {
    HwAbsProcessor::onDestroy();
}

void HwCameraRecorder::prepare(HwWindow *win) {
    Message *msg = new Message(EVENT_COMMON_PREPARE, nullptr);
    msg->obj = new ObjectBox(new NativeWindow(win, nullptr));
    postEvent(msg);
}

void HwCameraRecorder::updateWindow(HwWindow *win) {
    Message *msg = new Message(EVENT_SCREEN_UPDATE_WINDOW, nullptr);
    msg->obj = new ObjectBox(new NativeWindow(win, nullptr));
    postEvent(msg);
}

void HwCameraRecorder::start() {
    postEvent(new Message(EVENT_COMMON_START, nullptr));
}

void HwCameraRecorder::pause() {
    postEvent(new Message(EVENT_COMMON_PAUSE, nullptr));
}

void HwCameraRecorder::invalidate(int textureId, int64_t tsInNs, int w, int h) {
    int width = 320;
    int height = 480;
    Message *msg = new Message(EVENT_RENDER_FILTER, nullptr);
    msg->obj = new ObjectBox(new Size(width, height));
    msg->msg = "RENDER";
    msg->arg1 = textureId;
    msg->arg2 = tsInNs;
    msg->queueMode = Message::QUEUE_MODE_UNIQUE;
    postEvent(msg);
}

void HwCameraRecorder::setOutputFilePath(string filePath) {
    putString("", "path", filePath);
}

void HwCameraRecorder::setOutputSize(int width, int height) {
    putInt32("", "width", width);
    putInt32("", "height", height);
}

void HwCameraRecorder::setFilter(Filter *filter) {
    Message *msg = new Message(EVENT_RENDER_SET_FILTER, nullptr);
    msg->obj = new ObjectBox(filter);
    postEvent(msg);
}