#include <jni.h>
#include <android/log.h>
#include "hooks.h"

#define LOG_TAG "Menu7Bypass"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Java_com_Menu7Bypass_Native_initNative
//      (package)         (classe) (método)
extern "C" JNIEXPORT void JNICALL
Java_com_Menu7Bypass_Native_initNative(JNIEnv* env, jclass clazz) {
    LOGI("initNative() chamado");
    Hooks::Init();
}

extern "C" JNIEXPORT void JNICALL
Java_com_Menu7Bypass_Native_installAnogsBypass(JNIEnv* env, jclass clazz) {
    Hooks::InstallAnogsBypass();
}

extern "C" JNIEXPORT void JNICALL
Java_com_Menu7Bypass_Native_installAnortBypass(JNIEnv* env, jclass clazz) {
    Hooks::InstallAnortBypass();
}

extern "C" JNIEXPORT void JNICALL
Java_com_Menu7Bypass_Native_setAimbot(JNIEnv* env, jclass clazz, jboolean on) {
    LOGI("setAimbot: %d", on);
}

extern "C" JNIEXPORT void JNICALL
Java_com_Menu7Bypass_Native_setEsp(JNIEnv* env, jclass clazz, jboolean on) {
    LOGI("setEsp: %d", on);
}