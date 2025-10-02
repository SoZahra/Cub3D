<h1 align="center">
 🎮 Cub3D 🎮
</h1>

<p align="center">
Une réinterprétation moderne de Wolfenstein 3D utilisant le ray-casting
</p>

<p align="center">
  <img src="./assets/Screenshot from 2025-10-02 20-52-11.png" alt="Cub3D Demo" width="1000"/>
</p>


________________________________________________________________________________________________________________________________________
📖 **À propos du projet**<br></br>
Cub3D est un projet qui consiste à créer un moteur graphique 3D minimaliste inspiré du légendaire Wolfenstein 3D. En utilisant la technique du ray-casting, ce projet transforme une carte 2D en environnement 3D immersif depuis une perspective à la première personne.<br></br>
🎯 **Objectifs pédagogiques**

Comprendre les principes fondamentaux du ray-casting
Maîtriser la bibliothèque graphique MiniLibX
Gérer les événements clavier et souris
Implémenter un parser robuste pour les fichiers de configuration
Optimiser les performances graphiques en temps réel

________________________________________________________________________________________________________________________________________

✨ **Fonctionnalités**
🔧 **Partie obligatoire**

- Moteur 3D : Rendu temps réel d'un environnement 3D à partir d'une carte 2D
- Textures murales : Support de différentes textures selon l'orientation des murs
- Contrôles fluides : Déplacement avec WASD et rotation avec les flèches directionnelles
- Couleurs personnalisables : Sol et plafond configurables via RGB
- Gestion d'erreurs : Validation complète des fichiers de carte et textures

🌟 **Partie bonus (si implémentée)**

- Collisions : Détection et gestion des collisions avec les murs
- Minimap : Vue aérienne en temps réel de la position du joueur
- Contrôle souris : Rotation de la caméra avec la souris
- Portes : Mécanisme d'ouverture/fermeture des portes
- Sprites animés : Éléments animés dans l'environnement

________________________________________________________________________________________________________________________________________

🚀 **Installation & Compilation**
Prérequis
# macOS
brew install make
xcode-select --install

# Linux
sudo apt-get install make gcc libbsd-dev libx11-dev libxext-dev libtool-bin

Compilation
bash# Cloner le repository
git clone https://github.com/SoZahra/Cub3D.git
cd Cub3D

# Compiler la partie obligatoire
make

# Compiler la partie bonus (si disponible)
make bonus

# Nettoyer les fichiers objets
make clean

# Nettoyer complètement
make fclean

# Recompiler
make re

_______________________________________________________________________________________________________________________________________

🎹 **Contrôles**

![controle![Uploading Screenshot from 2025-06-18 11-15-40.png…]()
s]
