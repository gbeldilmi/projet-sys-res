BELDILMI Guillaume
GAUGUET Guillaume

# Systèmes et Réseaux : Projet

## Enoncé du sujet

Créer un jeu du "6 qui prend" en réseau.

## Structure du projet

Nous avons choisi de diviser le projet en 3 parties :

- Une partie client : elle s'occupera d'interagir avec l'utilisateur et de lui afficher les informations qui lui seront transmises par le serveur.
- Une partie serveur : elle s'occupera de gérer les connexions et de gérer les parties (lobby).
- Une partie jeu : c'est notre jeu à proprement parler, il s'occupera de gérer le déroulement de la partie.

## Notre client

Afin de créer notre client, nous avons choisi d'utiliser une structure assez simple. Il s'agit d'un script bash qui va se charger d'interagir avec l'utilisateur : de lui afficher une partie des informations qui lui seront transmises par le serveur et de récupérer les saisies de l'utilisateur pour les envoyer au serveur.

### Fonctionnement

Ce script nécessite la présence d'arguments pour fonctionner :

- L'adresse IP du serveur (`--server <server>`)
- L'intention du client (`--create` ou `--join <lobby>`)

Le script va ensuite se connecter au serveur, puis rediriger le flux d'entrée et de sortie vers le serveur. Toutes les entrées de d'utilisateur seront donc envoyées au serveur. Cependant, seules les informations commançant par les tags `@everyone` ou `@<user_id>` (où `<user_id>` représente l'identifiant de l'utilisateur choisi aléatoirement par le client avant de se connecter) seront affichées à l'utilisateur.

## Notre serveur

La structure de notre serveur est, elle aussi, assez simple. Il s'agit d'un script bash qui va se charger de gérer les connexions et de lancer les parties (lobby) dans de nouveaux processus.

### Fonctionnement

Ce script est composé d'une boucle infinie qui va se charger d'accepter les connexions des clients. Selon la requête du client, il va soit créer un nouveau lobby, soit le connecter à un lobby existant.

- Si le client demande à créer un lobby, le serveur va connecter le client à un pipe et lancer un nouveau processus qui va se charger de gérer la partie en interagissant avec le pipe.
- Si le client demande à rejoindre un lobby, le serveur va connecter le client au pipe du lobby demandé.

## Notre jeu

La partie jeu, à l'instar des deux parties précedentes, est plus complexe. Il s'agit d'un programme écrit en C qui va se charger de gérer le déroulement de la partie en communiquant avec les clients via un pipe.

### Fonctionnement

#### Le pipe

Les interactions entre les clients et le jeu se font via un pipe. Le jeu va se charger d'ouvrir le pipe et de le fermer à la fin de la partie. Chaque client pourra donc écrire dans le pipe pour envoyer des informations au jeu (avec le tag `~<user_id>`) et lire dans le pipe afin d'afficher les informations qui lui sont destinées (avec les tag `@<user_id>` ou `@everyone`) à l'utilisateur. Le jeu écrira dans le pipe pour envoyer des informations aux clients (avec le tag `@everyone` ou `@<user_id>` où `<user_id>` représente l'identifiant du client concerné).

#### Le déroulement de la partie

Le jeu va se charger de gérer le déroulement de la partie. Il va donc se charger de :

- Gérer les joueurs (nombre, identifiants, bots, etc.)
- Gérer les cartes (nombre, distribution, etc.)
- Gérer le déroulement de la partie (tour par tour, etc.)