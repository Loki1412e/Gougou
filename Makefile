# Nom du projet
NAME = googoo.exe

# Drapeaux de compilation
CFLAGS = -Wdeprecated-declarations

# Dossier contenant les fichiers sources
SRC = $(wildcard ./src/*.c)

# Chemins vers CSFML (ajuste-les en fonction de l'endroit exact de tes fichiers)
INCLUDE_DIR = ./lib/CSFML_2.6.1/include/
LIB_DIR = ./lib/CSFML_2.6.1/lib/gcc

# Bibliothèques nécessaires pour la liaison
CSFML = -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window

# Permet à GCC de compiler ton programme en une application graphique, sans associer un terminal à l'exécutable.
NO_TERMINAL = -mwindows

# Compilation et Liaison du projet
all:
	gcc $(SRC) -o $(NAME) -I$(INCLUDE_DIR) -L$(LIB_DIR) $(CFLAGS) $(CSFML) $(NO_TERMINAL)

# Débogage : ajout de l'option -g pour inclure les symboles de débogage
debug: CFLAGS += -g3 -W -Wall -Wextra
debug: all

# Profilage : ajout de l'option -pg pour le profilage (gprof)
perf: fclean
perf: CFLAGS += -pg
perf: all

# Nettoyage de l'exécutable
clean:
	rm ./$(NAME)

# Suppression de l'exécutable et autres fichiers temporaires
fclean: clean

# Recompilation complète (nettoie et reconstruit)
re: fclean all

# Lancement du débogage avec GDB
gdb: debug
	"$(shell where gdb)" ./$(NAME)

# Cibles génériques
.PHONY: all clean fclean debug perf re gdb
