# Evanthia Virginia Anastasopoulou Rapport

## Exploration et Application d'OpenCV dans un Projet Innovant de Traitement d'Images

Au cours de ce projet, j’ai appris comment utiliser OpenCV, une bibliothèque très large et puissante pour le traitement d'images. Utiliser OpenCV pour la première fois m’a donné la chance de beaucoup apprendre, m'ouvrant la porte à de nombreuses fonctionnalités et me permettant de découvrir les différentes possibilités offertes par le traitement d'images.

## Projet de Simplification d'Images

Notre équipe a pris la décision de se concentrer sur la simplification des images, que nous capturons en temps réel ou chargeons depuis un ordinateur. Nous avons employé deux techniques distinctes : la simplification par segments et la simplification par courbes de Bézier. Cette phase de simplification nécessitait une série d'étapes préliminaires qui impliquait non seulement la manipulation des images pour les préparer à la simplification mais aussi l'affinement des paramètres pour optimiser les résultats. Ce processus détaillé m'a permis de mettre en pratique mes compétences en manipulation d'images.

## Intégration de la Caméra Externe

Une partie intéressante que nous avons implémenté à notre projet est la possibilité de pouvoir utiliser une caméra externe pour prendre des photos. Cette caméra est capable de se mettre en mouvement grâce à ses deux servomoteurs, avec l'appui sur des touches du clavier (W, A, S, D). La programmation de cette interaction impliquait de traduire les pressions sur les touches du clavier en coordonnées spécifiques pour chaque moteur, ajoutant une couche de complexité technique intéressante.

## Gestion de la Communication Série et du Mouvement

La mise en mouvement de la caméra a été rendue possible grâce à une communication série entre l'ordinateur et l'Arduino. À chaque fois qu'une touche est pressée, le système calculait les nouvelles positions basées sur les commandes précédentes et les transmettait via le port série à l'Arduino. L'Arduino, programmé pour écouter et interpréter les signaux reçus, traduisait ces données en mouvements physiques des servomoteurs.

Le programme affiche le flux vidéo en direct dans une fenêtre sur l'écran de l'ordinateur. L'utilisateur peut interagir avec ce flux en utilisant la souris pour cliquer sur le bouton de capture d'une image.

## Simplification par segments

La simplification par segments commence par prendre une image au format PBM, un format d'image simple qui facilite la manipulation des données binaires.

Le traitement de l'image en identifiant ses contours et en les simplifiant avec l'algorithme de Douglas-Peucker s'est révélé être une démarche particulièrement intéressante et instructive. Ce processus m’a permis d'aborder plusieurs aspects de la vision par ordinateur et du traitement d'images.

D'abord, la détection des contours est une étape cruciale car elle permet d'isoler les éléments essentiels de l'image en se concentrant uniquement sur les limites qui définissent les formes et structures. Cette étape a été assez complexe à implémenter étant donné qu’il fallait trouver une méthode adaptée à notre problématique.

Ensuite, la simplification des contours avec l'algorithme de Douglas-Peucker a ajouté une dimension supplémentaire au projet de notre équipe. Cet algorithme est très apprécié pour sa capacité à réduire le nombre de points dans une courbe tout en conservant son allure générale, ce qui est parfait pour alléger les données sans perdre de l'information critique.

## Défis et Implications Techniques

Ce projet a souligné l'importance de la maîtrise des interfaces entre le logiciel et le matériel. La coordination entre les programmes écrits pour OpenCV et les commandes de l'Arduino a exigé une compréhension nuancée de la communication série, ainsi qu'une capacité à résoudre des problèmes complexes de synchronisation et de contrôle des dispositifs.

## Conclusion

Personnellement, ce que j'ai trouvé particulièrement gratifiant dans ce projet, c'est la conception et la mise en œuvre d'un algorithme complet qui guide l'image depuis sa capture initiale jusqu'à son résultat final transformé. Cette capacité à influencer le processus de traitement de l'image de A à Z m'a non seulement permis de renforcer ma compréhension des principes de la programmation orientée objet, mais a aussi illustré de manière concrète l'impact de notre travail sur le produit final. Chaque étape, de la simplification des contours à l'optimisation de l'algorithme pour des performances efficaces, a été une opportunité d'apprentissage. À mon avis, ce projet était une introduction très nécessaire à un style de programmation assez différent de celui auquel j'étais habituée. Le caractère libre de la deuxième partie du projet nous a permis, en tant que groupe, de rechercher et d'implémenter une idée qui nous intéressait.  Cela a rendu l'expérience non seulement éducative mais aussi extrêmement satisfaisante.
