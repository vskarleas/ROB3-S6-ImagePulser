# Suivre une couleur / Documentation utilisateur

## Description

Ce projet, développé dans le cadre de l'unité "Projet en langage C" du semestre 6 en robotique, implémente un système de suivi dynamique de couleur à l'aide d'une caméra contrôlée par deux servomoteurs. L'algorithme conçu permet de détecter et de suivre une couleur spécifique, ajustant automatiquement la caméra pour maintenir cette couleur au centre du champ de vision. Le but était de créer un système autonome qui, grâce à des compétences avancées en programmation C et en traitement d'image, illustre notre capacité à développer des applications robotiques interactives et intuitives.
Cette structure de README fournit une explication claire de la manière de configurer et utiliser notre code.

## Prérequis

Assurez-vous d'avoir installé l'Arduino IDE et que vous avez les droits nécessaires pour accéder aux ports USB (dialout)) sur votre machine. De plus, il faut verifier que vous avez OpenCV installé sur votre machine.

## Installation

1. **Cloner le projet** : Clonez ce dépôt sur votre machine locale.

   ```bash
   git clone URL_DU_DEPOT
   ```
2. **Installation des dépendances** : Si nécessaire, installez les librairies requises mentionnées dans un file_input `requirements.txt` ou un document similaire.

## Configuration

1. **Port Arduino** : Ouvrez le file_input `code_arduino.ino` avec l'Arduino IDE.
2. **Paramètres de la caméra** : Mettez à jour les paramètres de la caméra dans la fonction principale du file_input code source principal.

## Démarrage

Suivez ces étapes pour lancer le projet :

1. **Ouvrir le programme** : Ouvrez `code_arduino.ino` via l’application Arduino IDE.
2. **Connecter la caméra** : Branchez la caméra à un port USB de votre ordinateur.
3. **Préparer Arduino** : Connectez la carte Arduino à votre ordinateur et téléchargez le code sur la carte. Assurez-vous de sélectionner la bonne porte et le bon modèle de carte (Arduino UNO) dans les paramètres de l'Arduino IDE.
4. **Configuration du terminal** : Dans un terminal, déplacez-vous dans le répertoire du code.
   ```bash
   cd Impose
   ```
5. **Mise à jour des paramètres** :
   - Mettez à jour la porte USB d'Arduino, par exemple `/dev/ttyACMx` (remplacez `x` par le numéro de votre porte).
   - Ajustez les paramètres de la caméra nécessaires pour la lecture.
6. **Compilation** : Compilez le projet avec la commande `make`.
   ```bash
   make
   ```
7. **Exécution** : Lancez le programme.
   ```bash
   ./main
   ```
8. **Visualisation** : Les données envoyées au robot peuvent être visualisées via le moniteur série de l'Arduino IDE. Des fenêtres d'images s'ouvriront pour faciliter la visualisation.
9. **Arrêt du programme** : Pour arrêter le programme, appuyez sur n'importe quelle touche du clavier lorsque vous êtes sur l'une des fenêtres d'images.

## Copyright

Vasileios Filippos Skarleas, Evanthia Virginia Anastasopoulou, Yanis Sadoun | 2023 - 2024 All rights reserved
