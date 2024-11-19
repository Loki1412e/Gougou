# Gougou - Sujet

Intitulé : C programming

## Chronologie :

> ### Debut (25/10/2024)
>  * Choix du sujet,
>  * Soumis à validation
> ### Etape intermédiaire (Date Limite : Non définie)
> * Point d'avancement du projet
> * Prototype de l'application fonctionnel (50% des features)
> * Librairie graphique au minimum testée et fonctionnelle dans un proof of concept
> ### Rendu final (Date Limite : Non définie)
>  * Rendu du code source et documents

## Attendus obligatoires :
> - Projet C structuré avec fonctions et fichiers
> - Un fichier de configuration pour paramétrer les fonctionnement du programme
> - Une interface graphique (librairie au choix) -> ici `CSFML` version `2.6.1`
> - Traitement de fichiers
> - Traitement de chaînes de caractères
> - Stockage de données vers des fichiers
> - Traitements algorithmiques

## Optionnel :
> - Traitement de son
> - Connexion à une api web
> - Connexion à une base de donnée (plutôt que stockage sur fichiers)
> - Un installer pour un setup user-friendly du programme (type “setup.exe”)

## Rendu :
> - Code zippé
> - Installeur
> - Document descriptif

## Soutenance :
> - 15-20 minutes de présentation.
> - 50% Lancement et présentation du programme, parcours des fonctionnalités
> - 50% Présentation du code, de l’organisation de travail, questions techniques


| <img src="https://i.ibb.co/RQZWfsP/die-wand.jpg" alt="image trop cool" width="400"> |
| :-: |


# Gougou - Projet

Projet en C sous windows utilisant : 
- la librairie `CSFML` v`2.6.1`, `gcc`, `make`
- `python`, `gdown`

## Setup le projet :

### Rejoindre le projet git
```bash
git clone git@github.com:Loki1412e/Gougou.git
```

### Installer les assets via vscode
> Lien Google Drive : [Gougou/assets](https://drive.google.com/drive/folders/1eYqVpx6OT2iBl6RiNMA0K5kwdwIUOAKj?usp=sharing)

Il faut entrer les commandes dans la racine du projet.

Prérequis :
- python
- la lib gdown

```bash
pip install gdown
```

> les fichiers deja existant en local ne seront PAS remplacés
> donc si besoin : supprime le dossier ./assets puis entre la commande pour recharger les assets

```bash
python -m gdown --folder https://drive.google.com/drive/folders/1eYqVpx6OT2iBl6RiNMA0K5kwdwIUOAKj?usp=sharing
```

## ALORS ptit pbl

J'ai été raciste pcque j'utilise `make` sous windows mdr, donc soit faut installer msys2 comme moi, soit un autre truc raciste.
Faut juste pas oublié d'ajouter le chemin dans les variables d'environement (pour moi : `C:\msys64\usr\bin\`).

> Sur MSYS2
```bash
pacman -S mingw-w64-x86_64-gcc
pacman -S make
```

## Utilisation

> Compile uniquement .\gougou.exe (en mode terminal)
```bash
make
```

> Compile tout le projet (en mode sans terminal)
```bash
make gougou
```

## Aide CSFML :

* <a href="https://www.sfml-dev.org/download/csfml/" target="blank">CSFML Download</a>
* <a href="https://26.customprotocol.com/csfml/index.htm" target="blank">CSFML Documentation</a>
* <a href="https://csfml.1l.is/" target="blank">CSFML Handbook</a> <- (\*)
* <a href="https://epitech-2022-technical-documentation.readthedocs.io/en/latest/csfml.html" target="blank">CSFML : Graphical Programming — EPITECH 2022</a> <- (\*)
* <a href="https://github.com/Nerzouille/my_rpg" target="blank">Nerzouille/my_rpg</a> <- (\*)
