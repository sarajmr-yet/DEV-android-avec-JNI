package com.sara.jnidemo;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

/**
 * JNIDemo — LAB JNI / NDK
 *
 * FLUX GÉNÉRAL :
 * MainActivity.java → déclare des méthodes "native"
 *      → Android charge libnative-lib.so au démarrage
 *      → JNI transmet les appels au code C++ (native-lib.cpp)
 *      → C++ exécute le traitement et retourne le résultat
 *      → Java affiche le résultat dans l'UI
 *
 * RÈGLE DE NOMMAGE JNI (côté C++) :
 * Java_<package>_<classe>_<méthode>
 * Ex : Java_com_sara_jnidemo_MainActivity_helloFromJNI
 */
public class MainActivity extends AppCompatActivity {

    // ── Chargement de la bibliothèque native ────────────────────────────────
    // Cette ligne charge libnative-lib.so au démarrage de la classe.
    // Si le .so est absent → UnsatisfiedLinkError au runtime.
    static {
        System.loadLibrary("native-lib");
    }

    // ── Déclarations des méthodes natives ───────────────────────────────────
    // "native" = implémentées en C++ dans native-lib.cpp

    // Fonction 1 : message simple
    public native String helloFromJNI();

    // Fonction 2 : calcul factoriel (long pour éviter overflow)
    public native long computeFactorial(int n);

    // Fonction 3 : inversion de chaîne
    public native String reverseString(String input);

    // Fonction 4 : traitement d'un tableau int[]
    public native String processArray(int[] arr);

    // ── UI ──────────────────────────────────────────────────────────────────
    private TextView tvResult1, tvResult2, tvResult3, tvResult4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvResult1 = findViewById(R.id.tvResult1);
        tvResult2 = findViewById(R.id.tvResult2);
        tvResult3 = findViewById(R.id.tvResult3);
        tvResult4 = findViewById(R.id.tvResult4);

        // ── Démo 1 : helloFromJNI() ─────────────────────────────────────────
        String hello = helloFromJNI();
        tvResult1.setText(hello);

        // ── Démo 2 : computeFactorial() ─────────────────────────────────────
        int n = 10;
        long fact = computeFactorial(n);
        if (fact == -1) {
            tvResult2.setText("Erreur : valeur hors limites !");
        } else {
            tvResult2.setText(n + "! = " + fact);
        }

        // ── Démo 3 : reverseString() ────────────────────────────────────────
        String original = "Android JNI";
        String reversed = reverseString(original);
        tvResult3.setText("\"" + original + "\"  →  \"" + reversed + "\"");

        // ── Démo 4 : processArray() ─────────────────────────────────────────
        int[] tableau = {3, 17, 8, 42, 5, 99, 11};
        String arrayResult = processArray(tableau);
        tvResult4.setText(arrayResult);
    }
}
