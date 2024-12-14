## Dossier `./assets/`

Vu que les assets ne sont pas considérés par GIT, on peut mettre ce que l'on veut dedans.

Cependant si il y a besoin de download les assets définis sur le [Google Drive](https://drive.google.com/drive/folders/1eYqVpx6OT2iBl6RiNMA0K5kwdwIUOAKj?usp=sharing), on peut les télécharger soit manuellement soit via `gdown`.

Avec `gdown` il suffit de faire la commande suivante dans la racine du projet :
```bash
py -m gdown --folder https://drive.google.com/drive/folders/1eYqVpx6OT2iBl6RiNMA0K5kwdwIUOAKj?usp=sharing
```

Si la commande ne fonctionne pas, regarde le `README.md` du projet.

*Tout les fichiers dans le dossier, exceptés `./assets/assets.md`, ne seront pas considérés par GIT (voir `.gitignore`)*