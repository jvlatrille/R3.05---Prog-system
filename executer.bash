#!/bin/bash

# Vérifie si un fichier a été passé en paramètre
if [ -z "$1" ]; then
    echo "Usage: $0 <fichier.c>"
    exit 1
fi

# Récupère le nom du fichier sans l'extension
filename=$(basename -- "$1")
filename="${filename%.*}"

# Compile le fichier C
gcc "$1" -o "$filename"
if [ $? -ne 0 ]; then
    echo "Erreur de compilation"
    exit 1
fi

# Exécute le fichier compilé
./"$filename"