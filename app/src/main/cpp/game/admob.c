#include "admob.h"
#include "jni.h"

static JavaVM* jvm = NULL;
static jobject nativeLoaderInstance;

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;

    if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    jvm = vm;

    jclass nativeLoaderClass = (*env)->FindClass(env, "com/bigfoot/raymob/NativeLoader");
    jmethodID getInstanceMethod = (*env)->GetStaticMethodID(env, nativeLoaderClass, "getInstance", "()Lcom/bigfoot/raymob/NativeLoader;");
    jobject instance = (*env)->CallStaticObjectMethod(env, nativeLoaderClass, getInstanceMethod);
    nativeLoaderInstance = (*env)->NewGlobalRef(env, instance);

    return JNI_VERSION_1_6;
}

void ReleaseNativeLoader(void) {
    JNIEnv* env;
    (*jvm)->AttachCurrentThread(jvm, &env, NULL);

    if (nativeLoaderInstance != NULL) {
        (*env)->DeleteGlobalRef(env, nativeLoaderInstance);
        nativeLoaderInstance = NULL;
    }

    (*jvm)->DetachCurrentThread(jvm);
}

void RequestInterstitialAd(void) {
    JNIEnv* env;
    (*jvm)->AttachCurrentThread(jvm, &env, NULL);

    if (nativeLoaderInstance != NULL) {
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, nativeLoaderInstance);
        jmethodID method = (*env)->GetMethodID(env, nativeLoaderClass, "requestInterstitialAd", "()V");
        (*env)->CallVoidMethod(env, nativeLoaderInstance, method);
    }

    (*jvm)->DetachCurrentThread(jvm);
}

bool IsInterstitialAdLoaded(void) {
    JNIEnv* env;
    (*jvm)->AttachCurrentThread(jvm, &env, NULL);

    if (nativeLoaderInstance != NULL) {
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, nativeLoaderInstance);
        jmethodID method = (*env)->GetMethodID(env, nativeLoaderClass, "isInterstitialAdLoaded", "()Z");
        jboolean loaded = (*env)->CallBooleanMethod(env, nativeLoaderInstance, method);

        (*jvm)->DetachCurrentThread(jvm);

        return (bool)loaded;
    }

    (*jvm)->DetachCurrentThread(jvm);

    return false;
}

void ShowInterstitialAd(void) {
    JNIEnv* env;
    (*jvm)->AttachCurrentThread(jvm, &env, NULL);

    if (nativeLoaderInstance != NULL) {
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, nativeLoaderInstance);
        jmethodID method = (*env)->GetMethodID(env, nativeLoaderClass, "showInterstitialAd", "()V");
        (*env)->CallVoidMethod(env, nativeLoaderInstance, method);
    }

    (*jvm)->DetachCurrentThread(jvm);
}
