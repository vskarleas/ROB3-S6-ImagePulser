# Vasileios Filippos Skarleas Rapport

Au cours de ce projet, j'ai appris à contrôler une carte Arduino via des données envoyées au port série de la carte. De plus, la découverte de la librairie OpenCV était très intéressante car je vois déjà les différents potentiels d'utilisation dans de nombreux projets en domaine de la robotique. J'avais déjà utilisé OpenCV dans le cadre de la robotique expérimentale lorsque nous avons essayé d'utiliser une caméra pour cadrer au centre un point (proche des exigences du projet imposé) et par extension, contrôler les vitesses du robot Baxter pour suivre l'objet. Cette fois, une meilleure recherche sur les différentes fonctionnalités m'a permis de mieux comprendre comment les objets d'OpenCV (par exemple Mat) peuvent appliquer différents filtres sur les images traitées.

### Fonctionnement du système

Notre projet est composé de plusieurs programmes principaux qui fonctionnent de manière autonome. Certains d'entre eux nécessitent des arguments spécifiques pour être lancés, tandis que d'autres peuvent fonctionner sans interactions supplémentaires. Effectivement, il s'agit d'une méthode indirecte pour appeler des fonctionalités via le UI, mais vue le temps limités, j'ai preferé de me concentrer sur la finalisations des fonctions très importants pour le fonctionement du program. De plus il faut noter que l'implementation de l'interface graphique a commencé au milieu du projet et déjà beaucoup des fonctionalités de base etaient déjà implementés sur le source code. Maintenant la question est comment ça marche ?

### Comment ça marche ?

Pour améliorer la réactivité et l'efficacité du système, je suis basé sur le principe de sous-processing. Cette méthode permet d'avoir un program principal qui tourne tout en lancant des sous-processus (d'autres programmes princiaples au fond) qui effectuent pleines differents choses telles que:

* Processing de l;image de le rendre en format PBM
* Simplification de l'image selon defferentes méthods
* Mettre l'image comme un cartoon
* etc.

Donc, les interactions via l'interface graphique déclenchent ces sous-processus. Par exemple, lorsqu'une action requiert un traitement d'image, le système lance un sous-processus via une commande :

```bash
system("./image_processing");
```

Ce script traite l'image capturée et la convertit en format PBM, tout cela en arrière-plan, ce qui permet de garder l'interface utilisateur active et prête à de nouvelles interactions.

## Conception des Structures de Données

### **Les doubles listes chanees**

Effectivement, dans le projet libre, pour etre capable de simplifier l'image, il faut la lire puis socker ces informations à un endroit donné. Une image est composé des pixels qu'on lit et qu'on regroupe en differents contours. Ensuite, un ensemble des contrours construit l'image. Un contour est une liste chainée et une liste de contours est une double liste chainée dans notre cas.

### **Remplacement des listes chaînées par des tableaux statiques**

Le choix de remplacer les structures de données de listes chaînées par des tableaux statiques s'est avéré nécessaire afin d'accéder rapidement aux données lors des multiples itérations de l'algorithme de simplification.

Personnellement, j'ai trouvé cette partie du projet particulièrement complexe en raison des subtilités de gestion de la mémoire et d'optimisation des performances en langage C. En effet, comme nous l'avons vu en cours d'algorithmique ce semestre, parcourir une liste chaînée dans toutes les directions consomme beaucoup de ressources.

```c
// Conversion d'une liste chaînée en tableau statique
Point* convertListToArray(Node* head) {
    int size = 0;
    for (Node* curr = head; curr != NULL; curr = curr->next) size++;
    Point* array = new Point[size];
    Node* current = head;
    int i = 0;
    while (current) {
        array[i++] = current->data;
        current = current->next;
    }
    return array;
}
```

Le dévelopment de cette fonction qui rendre une liste chainé vers ume structure de donnés statique (un tableau), a renforcé ma compréhension des pointeurs et des structures dynamiques en C. En outre, l'utilisation correct de liberation de la memoire aux endorits corrects tout en maintenant la fonctionaléte du code, étais aussi un des points assez intéresants et important.

## Simplification par Courbes de Bézier

L'objectif du projet global était de trouver une manière de maintenir le plus grand nombre d'informations possibles tout en simplifiant l'image originale. La méthode la plus adoptée est celle de simplification par courbes de Bézier, car après plusieurs recherches, on a découvert que ce système est utilisé surtout pour les fichiers vectoriels tels que SVG, PNG, etc. et surtout parce qu'on avait suivi un cours de mathématiques appliquées aux courbes de Bézier.

J'ai travaillé à implémenter la simplification des formes en utilisant des courbes de Bézier de degré 2 et de degré 3, ce qui permet de modéliser les courbes avec seulement trois points ou 4 points de controle respectivement.

1. **Définition des Points de Contrôle :** Le choix des points de contrôle détermine la forme de la courbe.
2. **Optimisation des Points :** Les points de contrôle sont optimisés pour minimiser l'écart entre la courbe de Bézier et les données d'origine, tout en maximisant la réduction de la complexité des données.

## Le potentiel du codec PostScript

Dans le cadre du projet, j'étais également très intéressé par la création de fichiers PostScript (EPS) pour la représentation simplifiée des images. Dès que j'ai découvert que les courbes de Bézier étaient déjà prédéfinies dans la structure PostScript d'Adobe, j'ai réalisé qu'elles font partie intégrante des différents systèmes graphiques, et ce même dans des endroits insoupçonnés. Il existe d'autres technologies bien plus performantes que les courbes de Bézier, mais ces dernières demeurent néanmoins pertinentes.

Le codec PostScript et sa manière de codage m'ont permis d'approfondir la technologie sous-jacente aux fichiers que des programmes spécifiques développent. Déjà, au cours du premier semestre de cette année, j'avais créé mon propre codec pour sauvegarder les données du jeu de bataille navale, permettant ainsi aux joueurs de reprendre leur partie ultérieurement. Ce projet m'a permis de découvrir de nouvelles manières de compacter des informations au sein d'un codec.

## Conclusion

Ce projet m'a permis de développer pour la première fois en utilisant le principe des doubles listes chaînées. J'ai également eu la chance d'appliquer mes connaissances en mathématiques appliquées aux courbes de Bézier, tout en comparant des données réelles grâce au système interactif de capture d'image utilisé avec le robot miniature. De plus, il m'a permis de découvrir de nouvelles manières de compacter des informations au sein d'un codec.
