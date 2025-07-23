# Retro Tiled

Retro Tiled est une biblioth�que C++20 permettant de lire, manipuler et exporter des cartes au format TMX (Tiled Map Editor). Elle vise la simplicit� d'int�gration dans des projets r�tro ou modernes, tout en offrant des fonctionnalit�s avanc�es pour la gestion des tuiles et des calques.

## Fonctionnalit�s

- Lecture et parsing des fichiers TMX (XML)
- Acc�s aux propri�t�s des cartes, calques, tuiles et objets
- Exportation et manipulation des donn�es TMX
- Int�gration facile avec CMake (g�n�rateur Visual Studio 2022)
- Tests unitaires avec Boost Test

## Installation

1. **Pr�requis** :
   - CMake >= 3.21
   - Un compilateur compatible C++20 (Visual Studio 2022 recommand�)
   - Boost (pour les tests)

2. **Clonage du d�p�t** :

git clone <url-du-depot> cd retro-tiled

3. **G�n�ration du projet** :

cmake -S . -B build -G "Visual Studio 17 2022"

4. **Compilation** :

cmake --build build --config Release

## Utilisation

Inclure le header principal dans votre projet :

```cpp
#include <retro/tiled.h>

retro::tiled::File tmxFile("chemin/vers/carte.tmx"); if (tmxFile.isValid()) { // Acc�s aux calques, tuiles, etc. }
```

## Tests

Pour ex�cuter les tests unitaires :

ctest --test-dir build

## Licence

Ce projet est distribu� sous licence CeCILL.

## Ressources

- [Tiled Map Editor](https://www.mapeditor.org/)
- [Documentation TMX](https://doc.mapeditor.org/en/stable/reference/tmx-map-format/)
