# Yanis Sadoun Rapport

## Introduction

Participer à la conception et au développement d'un système de pilotage pour une machine inspirée par l'innovation et la créativité de Pixar a été une expérience  enrichissante et stimulante. Ce projet complexe avait pour objectif de mettre en œuvre une interaction dynamique avec l'environnement à travers une machine capable de suivre automatiquement une couleur spécifique ( figure imposée) et de simplifier les images capturées par une webcam ( projet libre ). Ma contribution a couvert des aspects importants de programmation et de conception systémique, me permettant de mettre en pratique mes compétences en informatique et en robotique .

## Pilotage des Moteurs de Caméra : Intégration du Code C et Arduino

### Contexte et Déroulement du Projet

Dans le cadre de notre projet imposé, j'ai été chargé de développer le système de contrôle des moteurs de notre caméra en utilisant le langage C et Arduino. Cette responsabilité a représenté ma première approche pratique de l'utilisation du code C pour la commande directe de moteurs, un défi à la fois innovant et technique.

### Principe de Fonctionnement

Le processus impliquait d'abord la capture d'images en temps réel à l'aide d'une caméra contrôlée par des servomoteurs. Le contrôle de ces servomoteurs se faisait via des commandes issues d'un clavier, transformées en coordonnées que nous utilisions pour ajuster l'orientation de la caméra en temps réel.

1. **Capture et Traitement des Images :** Nous commencions par capturer des images en couleur, que nous traitions ensuite pour en extraire des éléments spécifiques en fonction de leur couleur à l'aide de la bibliothèque OpenCV. Ce traitement consistait à filtrer l'image par couleur pour isoler des éléments de l'image qui étaient ensuite utilisés pour déterminer la direction dans laquelle orienter la caméra.
2. **Détection de Position :** À partir de l'image traitée, nous déterminions le centre des éléments filtrés pour comprendre où la caméra devait pointer. Cette position était cruciale pour diriger les servomoteurs de manière précise.
3. **Transmission de Commandes via Arduino :** Les coordonnées obtenues étaient ensuite envoyées à un Arduino via une connexion série. L'Arduino, programmé pour interpréter ces commandes, ajustait les positions des servomoteurs en fonction des coordonnées reçues.

### Défis Techniques et Solutions

La complexité de ce projet résidait dans la nécessité de synchroniser parfaitement le traitement d'image avec le contrôle moteur pour obtenir une réponse fluide et précise. Parmi les défis rencontrés :

- **Latence dans la transmission des commandes :** L'un des principaux problèmes était le délai entre la détection d'une position dans l'image et l'ajustement correspondant des servomoteurs. Pour minimiser cette latence, j’ai optimisé le code Arduino et ajusté les paramètres de communication série pour accélérer le transfert des données.
- **Précision de la détection de position :** Assurer la précision de la détection de position dans l'image traitée était essentiel. J’ai  expérimenté avec différents seuils et paramètres de filtrage HSV pour améliorer la fiabilité de la détection des objets.
- **Calibration des servomoteurs :** La calibration précise des servomoteurs était nécessaire pour que les mouvements de la caméra correspondent exactement aux coordonnées calculées. J’ai passé plusieurs heures à ajuster les angles et les limites de mouvement des servomoteurs pour garantir un contrôle fluide et précis.

### Impact Personnel et Professionnel

Ce projet a été l'occasion parfaite de combiner mes compétences en programmation avec des applications pratiques de robotique. Il m'a permis de voir directement l'impact de mon travail sur les opérations physiques d'un dispositif, renforçant mon intérêt pour le domaine de la robotique et me donnant des bases spour de futurs projets où logiciel et matériel interagissent étroitement.

## Résolution de Problèmes Techniques avec les Moteurs de la Caméra

### Contexte et Problématique

Lors du développement de notre  système de pilotage de notre c	améra, nous avons rencontré un problème majeur : malgré un code apparemment correct, les moteurs ne répondaient pas comme prévu. Après une série de tests, il est apparu que le problème n'était pas lié au code, mais à des moteurs défectueux.

### Intervention et Réparation

La découverte des moteurs défectueux nous a orientés vers un défi inattendu de robotique pratique. Remplacer les moteurs a impliqué de démonter la caméra, de sélectionner et installer de nouveaux moteurs adaptés. Ce processus, bien que laborieux, m’a permis  de combiner compétences mécaniques et connaissances techniques.

### Impact et Réflexion Personnelle

Cette expérience m'a  marqué car elle a souligné l'importance de l'interaction entre le logiciel et le matériel. J'ai trouvé particulièrement gratifiant de résoudre un problème concret qui impactait directement le succès de notre projet.

## Défi de la Liberté et Simplification par Segments

### La Paradoxe de la Liberté

Un des défis les plus intrigants de ce projet résidait dans l'immense liberté qui nous était donnée. Ce niveau de liberté, bien que potentiellement libérateur, impliquait également la difficulté de définir un cadre précis et efficace pour notre approche. Inspirés par les avancées présentées lors de la Google IO 2023, notamment la technique de prétraitement des images en valeurs binaires pour leur analyse par des réseaux neuronaux, nous avons choisi de concentrer nos efforts sur la simplification d'images. Cependant, déterminer la méthode optimale pour atteindre cet objectif s'est avéré complexe, nécessitant de vastes recherches et un tri minutieux des techniques disponibles.

### Choix de la Simplification par Segments

Personnellement, j'ai été attiré par la simplification par segments utilisant l'algorithme de Douglas-Peucker. Cette méthode m'a fasciné non seulement par sa capacité à réduire la complexité des données tout en préservant les détails visuels essentiels, mais aussi par les défis mathématiques qu'elle représentait. L'algorithme de Douglas-Peucker est particulièrement adapté pour distiller l'essence des formes dans les images, en éliminant les informations superflues tout en conservant les caractéristiques structurales importantes.

### Processus de Simplification

1. **Initialisation :** Nous commençons par identifier un segment initial reliant les points extrêmes du contour de l'objet à simplifier.
2. **Détermination du Point Critique :** La distance entre chaque point du contour et le segment est calculée. Le point avec la distance maximale est identifié comme le point critique.
3. **Division et Répétition :** Si la distance maximale dépasse un seuil prédéfini, le segment est divisé en deux nouveaux segments au niveau de ce point critique. Le processus est ensuite répété pour chaque nouveau segment, affinant progressivement la représentation jusqu'à atteindre le niveau de simplification souhaité.

### Défis et Réalisations

Le développement de cet algorithme a été un véritable test pour mes compétences en programmation et en gestion de données complexes. Chaque étape, que ce soit le calcul des distances ou la segmentation, demandait une grande précision et une rigueur mathématique.

Intégrer les mathématiques dans ce projet m'a beaucoup apporté personnellement, renforçant mon intérêt pour les mathématiques et démontrant leur valeur pratique dans le monde de la technologie.

## Binarisation de l'Image: Application Pratique des Concepts Théoriques

### Contexte et Intérêt Personnel

Dans la partie libre de notre projet, j'ai  également eu l'opportunité d'appliquer un concept que j'avais étudié lors de mon projet de robotique expérimentale sur le robot Baxter : la binarisation d'image. Ce processus, bien que conceptuel dans le cadre académique, a pris une dimension tout à fait concrète dans ce projet. La binarisation d'image est une étape de prétraitement essentielle dans de nombreux algorithmes de vision par ordinateur.

### Principe de la Binarisation de l'Image

La binarisation transforme une image en niveaux de gris en une image nettement plus simple en noir et blanc, où chaque pixel devient soit noir soit blanc. Cette simplification est cruciale non seulement pour des raisons de traitement ultérieur, comme la détection de contours, mais aussi pour améliorer la clarté visuelle et réduire la complexité des données manipulées.

### Processus de Binarisation

Dans notre projet, la binarisation a été réalisée par le seuillage des pixels. Chaque pixel de l'image en niveaux de gris est comparé à un seuil fixe : ceux ayant une intensité supérieure sont définis comme blancs, et les autres comme noirs. Cette approche réduit significativement la quantité d'information contenue dans l'image originale, permettant une analyse plus rapide et plus efficace dans les étapes subséquentes du traitement.

Importance du Format PBM P4

Pour enregistrer efficacement les images binarisées, nous avons utilisé le format PBM P4. Ce format offre une méthode de stockage compacte, chaque octet du fichier représentant huit pixels de l'image, ce qui est nettement plus efficace que le format texte P1 où chaque pixel est représenté individuellement par un caractère. Cela a permis de réduire la taille des fichiers et d'accélérer leur traitement.

### Réflexions Personnelles et Professionnelles

La binarisation, bien que simple en théorie, requiert une attention minutieuse aux détails lors de sa mise en œuvre, en particulier concernant le choix du seuil et la gestion des formats de fichiers. Cela m'a appris l'importance de la précision et de la rigueur dans la programmation en contexte réel.

## Conclusion

Ce projet a marqué ma première immersion dans l'utilisation d'OpenCV, un outil puissant pour le traitement d'images et la vision par ordinateur. L'exploration d'OpenCV a ouvert un vaste champ de possibilités et m'a permis de découvrir de nombreuses fonctionnalités de cette bibliothèque. Parmi celles-ci, la manipulation d'images, la détection de couleurs, et l'implémentation d'algorithmes de simplification d'images ont été particulièrement captivantes. Chacune de ces fonctionnalités a apporté un éclairage sur la manière dont les concepts théoriques sont appliqués dans des solutions technologiques concrètes.

L'aspect le plus valorisant de ce projet a été la liberté de rechercher et d'explorer ces fonctionnalités par moi-même. Cette démarche autonome m'a non seulement permis de découvrir les vastes capacités d'OpenCV, mais a également posé des bases  pour mes futures études, en particulier pour l'unité d'enseignement sur le traitement du signal que je prévois de suivre l'année prochaine.

Au-delà de l'aspect technique, ce projet m'a fait apprécier la connexion entre le codage informatique et ses applications physiques, comme piloter un mouvement de caméra dans le monde réel. Il est très gratifiant de voir le code non seulement fonctionner sur un ordinateur, mais aussi actionner concrètement des dispositifs mécaniques.
