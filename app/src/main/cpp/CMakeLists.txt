cmake_minimum_required(VERSION 3.22.1)

project("jnidemo")

# Créer la bibliothèque native partagée (.so)
add_library(
        native-lib      # Nom de la lib → libnative-lib.so
        SHARED          # Partagée (chargée dynamiquement)
        native-lib.cpp  # Fichier source C++
)

# Lier avec les bibliothèques Android système
find_library(log-lib log)

target_link_libraries(
        native-lib
        ${log-lib}      # Pour android_log_print (Logcat depuis C++)
)
