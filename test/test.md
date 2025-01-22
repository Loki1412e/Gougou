## Dossier `./test/`

Depuis le dossier `./test/` on peut compiler des mini projtes permettant ainsi d'effectuer des tests sans impacter le vrai projet.

Pour cela il suffit de faire :
```bash
make -B test
```

*Tout les fichiers dans le dossier, exceptés `./test/test.md`, ne seront pas considérés par GIT (voir `.gitignore`)*