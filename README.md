# Retro Tiled

Retro Tiled est une bibliothèque C++20 permettant de lire, manipuler et exporter des cartes au format TMX (Tiled Map Editor). Elle vise la simplicité d'intégration dans des projets rétro ou modernes, tout en offrant des fonctionnalités avancées pour la gestion des tuiles et des calques.

## Fonctionnalités

- Lecture et parsing des fichiers TMX (XML)
- Accès aux propriétés des cartes, calques, tuiles et objets
- Exportation et manipulation des données TMX
- Intégration facile avec CMake (générateur Visual Studio 2022)
- Tests unitaires avec Boost Test

## Installation

1. **Prérequis** :
   - CMake >= 3.21
   - Un compilateur compatible C++20 (Visual Studio 2022 recommandé)
   - Boost (pour les tests)

2. **Clonage du dépôt** :

git clone <url-du-depot> cd retro-tiled

3. **Génération du projet** :

cmake -S . -B build -G "Visual Studio 17 2022"

4. **Compilation** :

cmake --build build --config Release

## Utilisation

Inclure le header principal dans votre projet :

```cpp
#include <retro/tiled.h>

retro::tiled::File tmxFile("chemin/vers/carte.tmx"); if (tmxFile.isValid()) { // Accès aux calques, tuiles, etc. }
```

## Tests

Pour exécuter les tests unitaires :

ctest --test-dir build

## Licence

Ce projet est distribué sous licence CeCILL.

## Ressources

- [Tiled Map Editor](https://www.mapeditor.org/)
- [Documentation TMX](https://doc.mapeditor.org/en/stable/reference/tmx-map-format/)
