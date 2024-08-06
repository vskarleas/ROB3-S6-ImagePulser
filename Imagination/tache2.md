# Tâche 2 : Intégration des fonctions de base de la géométrie en 2D

Cette tâche implique la création d'un module de géométrie pour manipuler divers éléments géométriques en deux dimensions, tels que les vecteurs, les points et les segments de droite. Voici un résumé des éléments clés de ce module :

## 2.1 - Géométrie dans le plan 2D

### Définitions des types

- **Point** : Représenté par un couple de coordonnées (x, y) dans l'espace bidimensionnel.
- **Vecteur** : Décrit par des coordonnées (x, y) représentant un déplacement à partir de l'origine O.
- **Vecteur bi-point** : Décrit par la différence entre deux points, où le vecteur AB est défini par C - A, avec C et A étant des points.

### Opérations de base

- **Somme de vecteurs** : La somme de deux vecteurs V1 et V2 est donnée par (x1 + x2, y1 + y2).
- **Somme de points** : La somme de deux points P1 et P2 est représentée par (x1 + x2, y1 + y2), ce qui équivaut à la somme vectorielle de leurs positions.
- **Produit d'un réel par un vecteur** : Le produit d'un scalaire a par un vecteur V est donné par (a * x, a * y).
- **Produit scalaire entre deux vecteurs** : Le produit scalaire de deux vecteurs V1 et V2 est donné par x1 * x2 + y1 * y2.

### Propriétés métriques

- **Norme euclidienne (longueur) d'un vecteur** : La norme d'un vecteur V est donnée par la racine carrée de la somme des carrés de ses composants, soit √(x^2 + y^2).
- **Distance entre deux points** : La distance entre deux points A et B est donnée par la norme du vecteur AB, soit la racine carrée de la somme des carrés des différences de leurs coordonnées respectives, √((xA - xB)^2 + (yA - yB)^2).

Ce module permet de manipuler et d'appliquer des transformations géométriques de base sur des éléments graphiques en 2D, facilitant ainsi les opérations de simplification et de vectorisation dans le cadre du projet.

## 2.2 - Les Types

Dans le cadre de notre module de géométrie en 2D, nous avons défini les types de base nécessaires pour manipuler les points et les vecteurs. Voici les déclarations de ces types :

- **Vecteur** : Un vecteur est défini comme une structure contenant deux coordonnées de type double, représentant ses composantes x et y dans le plan.

```c
typedef struct Vecteur_ {
    double x, y; // Coordonnées du vecteur
} Vecteur;
```

- **Point** : De manière similaire, un point dans le plan est représenté par une structure contenant deux coordonnées de type double, x et y.

```c
typedef struct Point_ {
    double x, y; // Coordonnées du point
} Point;
```

**IMPORTANT :** Les coordonnées des points et des vecteurs sont déclarées avec le type `double` pour assurer une précision suffisante lors des calculs de simplification. La précision des doubles, avec environ 15 chiffres décimaux, est essentielle pour maintenir l'exactitude dans les transformations et manipulations géométriques.


