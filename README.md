# Minishell

> *As beautiful as a shell*

Un shell Unix personnalisé écrit en C dans le cadre du cursus de l'école 42. Minishell reproduit les comportements essentiels de bash — de l'analyse des commandes à leur exécution, en passant par les pipes, les redirections et l'expansion des variables d'environnement.

---

## Fonctionnalités

### Commandes intégrées (builtins)

| Commande | Description |
|----------|-------------|
| `echo [-n]` | Affiche du texte sur stdout, avec suppression optionnelle du saut de ligne |
| `cd <chemin>` | Change de répertoire (chemin relatif ou absolu) |
| `pwd` | Affiche le répertoire de travail courant |
| `export` | Définit des variables d'environnement |
| `unset` | Supprime des variables d'environnement |
| `env` | Affiche l'environnement courant |
| `exit` | Quitte le shell |

### Comportements du shell

- **Prompt** affiché en attente d'une commande
- **Résolution des exécutables** via `PATH`, ou chemin relatif/absolu
- **Guillemets** : simple `'` et double `"` (sauf multilignes)
- **Redirections** : `<`, `>`, `>>`
- **Pipes** : `|` pour chaîner les commandes
- **Séparateur de commandes** : `;`
- **Variables d'environnement** : expansion `$VAR`
- **Code de retour** : expansion `$?`
- **Signaux** : `ctrl-C`, `ctrl-D`, `ctrl-\` se comportent comme dans bash
- **Historique** : navigation avec les flèches via termcap

---

## Structure du projet

```
minishell/
├── include/
│   └── minishell.h
├── libft/
├── srcs/
│   ├── main.c
│   ├── builtins/       # echo, cd, pwd, export, unset, env, exit
│   ├── executor/       # pipeline, commande simple, heredoc, redirections
│   ├── parser/         # tokenizer → liste de commandes
│   ├── signals/        # gestion des signaux
│   ├── tokens/         # lexer / tokenizer
│   └── utils/          # mémoire, chemins, env, parseur
├── Makefile
└── README.md
```

---

## Installation

### Prérequis

- GCC ou Clang
- GNU Make
- `libreadline` (ou termcap pour l'historique)

### Compilation

```bash
git clone git@github.com:tristan24217/minishell.git minishell
cd minishell
make
```

### Lancement

```bash
./minishell
```

### Règles du Makefile

| Règle | Description |
|-------|-------------|
| `make` / `make all` | Compile le projet |
| `make clean` | Supprime les fichiers objets |
| `make fclean` | Supprime les objets et le binaire |
| `make re` | Recompile entièrement |

---

## Exemples d'utilisation

```bash
# Commandes de base
minishell$ echo "Bonjour le monde !"
minishell$ ls -la | grep ".c" | wc -l

# Redirections
minishell$ cat < entree.txt > sortie.txt
minishell$ echo "ajout" >> log.txt

# Variables d'environnement
minishell$ export MA_VAR=42
minishell$ echo $MA_VAR
minishell$ unset MA_VAR

# Enchaînement de commandes
minishell$ cd srcs ; pwd ; ls

# Code de retour
minishell$ ls inexistant; echo $?
```