# iManuel d'Utilisateur - Installation

## Prérequis

> Pour votre simplicité nous avons crée un script `bash installation.sh` qui vous permet d'installer toutes les librairies nécessaires à l'utilisation de notre projet et bien plus encore...

Avant de procéder à l'installation du code source sur votre ordinateur, assurez-vous de disposer des librairies et outils suivants nécessaires à la compilation et à l'exécution du logiciel :

1. **Gestionnaire de paquets Homebrew** :

   - Pour l'installer, exécutez la commande suivante dans votre terminal :
     ```bash
     /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
     ```
2. **Python** :

   - Python est requis pour certains packages. Assurez-vous de l'avoir installé sur votre système.
3. **Librairie OpenCV** :

   - Nécessaire pour le traitement des images. Installez-la via Homebrew en utilisant :
     ```bash
     brew install opencv
     ```
4. **Outil de construction CMake** :

   - Téléchargez et installez CMake pour la compilation des projets. Retrouvez plus d'informations et les liens de téléchargement sur [le site de CMake](https://cmake.org/download/).
5. **Compilateurs C et C++** :

   - Assurez-vous que gcc et g++ sont installés, car ils sont essentiels pour compiler les programmes en C et C++.
6. **Support de C++11 ou supérieur** :

   - Vérifiez que votre compilateur supporte au moins la norme C++11.
7. **Evince** :

   - Installé via Homebrew, cet outil est indispensable pour ouvrir les file_inputs EPS générés par le programme :
     ```bash
     brew install evince
     ```
8. **GTK** :

   - GTK est nécessaire pour l'interface graphique du programme. Installez GTK en suivant les instructions spécifiques à votre système :
     - **Mac/Linux** :
       ```bash
       brew install gtk+
       ```
     - **Windows** :
       ```bash
       pacman -S mingw-w64-x86_64-gtk4
       ```

Ces outils et librairies sont essentiels pour garantir une installation sans problème et le bon fonctionnement du logiciel sur votre ordinateur. Assurez-vous de les installer avant de continuer avec le processus d'installation du code source.

# Exploration du Code Source avec VSCode

Pour les développeurs désirant explorer ou modifier le projet, il est recommandé d'utiliser Visual Studio Code (VSCode), un éditeur de code polyvalent et puissant. Vous pouvez télécharger VSCode à partir de [ce lien](https://code.visualstudio.com/download).

Il est important de noter que l'installation de VSCode n'est pas nécessaire pour compiler le projet, mais elle peut enrichir votre expérience de développement grâce à diverses extensions disponibles.

### Extensions Recommandées pour VSCode

Si vous choisissez d'utiliser VSCode, voici une sélection d'extensions qui peuvent améliorer votre flux de travail de développement :

1. **C/C++ (ms-vscode.cpptools)** :

   - Fournit IntelliSense, débogage, et navigation dans le code C/C++.
   - [Lien VS Marketplace](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
2. **C/C++ Extension Pack (ms-vscode.cpptools-extension-pack)** :

   - Regroupe des extensions populaires pour le développement C/C++ sous VSCode.
   - [Lien VS Marketplace](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)
3. **CMake (twxs.cmake)** :

   - Support pour CMake, un système de build essentiel pour les projets C++.
   - [Lien VS Marketplace](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
4. **CodeLLDB (vadimcn.vscode-lldb)** :

   - Débogueur natif puissant, supportant C++, Rust, et d’autres langues compilées.
   - [Lien VS Marketplace](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb)
5. **HTML CSS Support (ecmel.vscode-html-css)** :

   - Fournit IntelliSense pour CSS dans les documents HTML.
   - [Lien VS Marketplace](https://marketplace.visualstudio.com/items?itemName=ecmel.vscode-html-css)
6. **IntelliCode (VisualStudioExptTeam.vscodeintellicode)** :

   - Développement assisté par IA pour une programmation plus efficace.
   - [Lien VS Marketplace](https://marketplace.visualstudio.com/items?itemName=VisualStudioExptTeam.vscodeintellicode)
7. **Make + LLDB Configuration (perelabat.make-lldb-config)** :

   - Fournit une configuration simple pour exécuter des builds et déboguer avec Make et LLDB.
   - [Lien VS Marketplace](https://marketplace.visualstudio.com/items?itemName=perelabat.make-lldb-config)
8. **Tabnine (TabNine.tabnine-vscode)** :

   - Assistant de codage AI offrant des complétions de code et des discussions de code AI directement dans l'IDE, supportant une multitude de langages.
   - [Lien VS Marketplace](https://marketplace.visualstudio.com/items?itemName=TabNine.tabnine-vscode)

Ces extensions optimisent les fonctionnalités de VSCode, rendant le processus de développement plus intuitif et efficace.

## À propos du Projet

Ce projet est écrit en C et C++. Pour faciliter la compilation et garantir la compatibilité sur différents systèmes d'exploitation, un Makefile est inclus avec le code source. Ce Makefile est conçu pour simplifier le processus de compilation et augmenter la portabilité du projet.

## Guide d'Installation

Pour installer et lancer le programme, suivez ces étapes simples :

1. **Téléchargement :**

   - Téléchargez le dossier "Imagination" contenant le projet.
2. **Préparation :**

   - Ouvrez un terminal et naviguez jusqu'au dossier téléchargé.
3. **Installation des modules (Facultatif)**

   Pour vous faciliter, on a integré un script qui permetra d'installer les modules que le program a besoin. Il faut noter qu'il utiliser Brew package manager. Dans les packages il y a une diversite des outils informatiques qui pouraient etre interessant pour vos projets. Ceux que vous avez besoin pour ce projet sont `"evince" "gtk+" "doxygen" "azure-cli" "opencv" "openexr" "libtiff" "libpng" "jpeg" "gnuplot"`

   Dans le terminal, modifiez les permissions du script pour le rendre exécutable :

   ```bash
   chmod 777 installation.sh
   ```

   Lancez le script avec la commande :

   ```bash
   bash installation.sh
   ```
4. **Exécution du Script :**

   Dans le terminal, modifiez les permissions du script pour le rendre exécutable :

   ```bash
   chmod 777 program.sh
   ```

   Lancez le script avec la commande :

   ```bash
   bash program.sh
   ```

   Le script compile automatiquement l'application et démarre son exécution.
5. **Gestion des file_inputs :**

   - Consultez le file_input *"RepSimplification des images prise avec un webcamertoires"* pour voir les données stockées. Ce file_input vous permet également de charger directement des images PNG ou PBM si nécessaire.
6. **Options de Configuration :**

   - Lorsque le script `program.sh` est exécuté, plusieurs configurations vous sont proposées :
     1. **Mode Automatique :** Lance automatiquement le flux de travail principal utilisant la webcam.
     2. **Mode Manuel :** Permet de sélectionner manuellement les fonctionnalités à utiliser, offrant une flexibilité accrue pour répondre à vos besoins spécifiques.

Ces instructions facilitent la mise en place rapide du programme et vous permettent de personnaliser l'expérience utilisateur selon vos préférences.
