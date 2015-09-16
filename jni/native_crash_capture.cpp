//Copyright 2014 miechalzhao@gmail Authors. All rights reserved.
//Use of this source code is governed by a BSD-style license that can be
//found in the LICENSE file.

#include "include/com_hujiang_crashcapture_NativeCrashCapture_JNI.h"

#include "base/common.h"
#include "breakpad/src/client/linux/handler/exception_handler.h"
#include "breakpad/src/client/linux/handler/minidump_descriptor.h"

JavaVM* g_jvm;

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    g_jvm = vm;
    JNIEnv *env;
    if (JNI_OK != vm->GetEnv(reinterpret_cast<void**> (&env),JNI_VERSION_1_4)) {
        LOGE("JNI_OnLoad could not get JNI env");
        return JNI_ERR;
    }

    return JNI_VERSION_1_4;
}

bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded) {
    LOGE("DumpCallback succeeded %d", succeeded);
    return succeeded;
}

JNIEXPORT jint JNICALL Java_com_hujiang_crashcapture_NativeCrashCapture_nativeInit
(JNIEnv* env, jobject obj, jstring crash_dump_path, jstring version) {
    const char* path = (char *)env->GetStringUTFChars(crash_dump_path, NULL);
    const char* c_version = (char *)env->GetStringUTFChars(version, NULL);
    google_breakpad::MinidumpDescriptor descriptor(path, c_version);
    static google_breakpad::ExceptionHandler eh(descriptor, NULL, DumpCallback, NULL, true, -1);
    env->ReleaseStringUTFChars(crash_dump_path, path);
    env->ReleaseStringUTFChars(version, c_version);
    return 0;
}
