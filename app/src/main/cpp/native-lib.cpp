#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "JNIDemo"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// ─────────────────────────────────────────────────────────────────────────────
// FONCTION 1 : helloFromJNI()
// Retourne un message simple depuis C++ vers Java
// Nom JNI : Java_<package>_<classe>_<méthode>
// ─────────────────────────────────────────────────────────────────────────────
extern "C" JNIEXPORT jstring JNICALL
Java_com_sara_jnidemo_MainActivity_helloFromJNI(JNIEnv *env, jobject /* this */) {
    LOGI("helloFromJNI() appelé depuis Java");
    std::string message = "Bonjour depuis C++ via JNI !";
    return env->NewStringUTF(message.c_str());
}

// ─────────────────────────────────────────────────────────────────────────────
// FONCTION 2 : computeFactorial(int n)
// Calcule le factoriel côté natif avec contrôle d'erreur
// Retourne -1 si n < 0 ou n > 20 (overflow long)
// ─────────────────────────────────────────────────────────────────────────────
extern "C" JNIEXPORT jlong JNICALL
Java_com_sara_jnidemo_MainActivity_computeFactorial(JNIEnv *env, jobject /* this */, jint n) {
    LOGI("computeFactorial(%d) appelé", n);

    if (n < 0 || n > 20) {
        LOGI("Erreur : valeur hors limites (%d)", n);
        return -1; // Erreur : valeur invalide
    }

    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }

    LOGI("Résultat factoriel(%d) = %lld", n, result);
    return (jlong) result;
}

// ─────────────────────────────────────────────────────────────────────────────
// FONCTION 3 : reverseString(String s)
// Reçoit une chaîne Java, l'inverse côté C++, retourne le résultat
// ─────────────────────────────────────────────────────────────────────────────
extern "C" JNIEXPORT jstring JNICALL
Java_com_sara_jnidemo_MainActivity_reverseString(JNIEnv *env, jobject /* this */, jstring input) {

    // Convertir jstring → std::string
    const char *nativeStr = env->GetStringUTFChars(input, nullptr);
    std::string str(nativeStr);
    env->ReleaseStringUTFChars(input, nativeStr); // Libérer la mémoire !

    LOGI("reverseString() reçu : %s", str.c_str());

    // Inverser la chaîne
    std::string reversed(str.rbegin(), str.rend());

    LOGI("reverseString() résultat : %s", reversed.c_str());

    return env->NewStringUTF(reversed.c_str());
}

// ─────────────────────────────────────────────────────────────────────────────
// FONCTION 4 : processArray(int[] arr)
// Reçoit un tableau Java int[], calcule la somme et le max côté C++
// Retourne une String formatée "somme=X, max=Y"
// ─────────────────────────────────────────────────────────────────────────────
extern "C" JNIEXPORT jstring JNICALL
Java_com_sara_jnidemo_MainActivity_processArray(JNIEnv *env, jobject /* this */, jintArray arr) {

    // Obtenir la taille du tableau
    jsize length = env->GetArrayLength(arr);

    if (length == 0) {
        return env->NewStringUTF("Tableau vide !");
    }

    // Accéder aux éléments du tableau
    jint *elements = env->GetIntArrayElements(arr, nullptr);

    long long sum = 0;
    int maxVal = elements[0];

    for (int i = 0; i < length; i++) {
        sum += elements[i];
        if (elements[i] > maxVal) maxVal = elements[i];
        LOGI("arr[%d] = %d", i, elements[i]);
    }

    // Libérer le tableau (obligatoire !)
    env->ReleaseIntArrayElements(arr, elements, JNI_ABORT);

    LOGI("processArray() → somme=%lld, max=%d", sum, maxVal);

    // Construire la réponse
    std::string result = "Somme = " + std::to_string(sum) +
                         "  |  Max = " + std::to_string(maxVal);
    return env->NewStringUTF(result.c_str());
}
