#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_kiwku_limestone_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Kocham babije";
    return env->NewStringUTF(hello.c_str());
}