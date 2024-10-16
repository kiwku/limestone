#include <jni.h>
#include <string>

#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>


extern "C" JNIEXPORT jstring JNICALL
Java_com_kiwku_limestone_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Kocham babije";
    return env->NewStringUTF(hello.c_str());
}