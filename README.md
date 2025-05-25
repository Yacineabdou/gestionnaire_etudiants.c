# Gestionnaire de Dossiers Étudiants en C

Ce projet est un simple gestionnaire de dossiers étudiants implémenté en langage C, fonctionnant via une interface en ligne de commande (CLI). Il permet de gérer une liste d'étudiants en les ajoutant, affichant, triant, et en sauvegardant/chargeant leurs données dans un fichier.

---

## Fonctionnalités

* **Ajout d'étudiant :** Permet d'enregistrer de nouvelles informations d'étudiants (ID, nom, prénom, âge, moyenne, filière).
* **Affichage des étudiants :** Affiche la liste complète de tous les étudiants enregistrés avec leurs détails.
* **Tri par ID :** Trie la liste des étudiants par leur identifiant numérique.
* **Sauvegarde des données :** Sauvegarde toutes les données des étudiants dans un fichier texte (`etudiants.txt`).
* **Chargement des données :** Charge automatiquement les données existantes depuis `etudiants.txt` au démarrage du programme.
* **Interface interactive :** Un menu simple permet à l'utilisateur de choisir l'action à effectuer.

---

## Comment compiler et exécuter

1.  **Sauvegarder le code :** Copiez le code C fourni (celui avec tous les commentaires en ligne) dans un fichier nommé `gestionnaire_etudiants.c` (ou tout autre nom avec l'extension `.c`).

2.  **Compiler :** Ouvrez un terminal ou une invite de commande et utilisez un compilateur C (comme **GCC**) pour compiler le code :

    ```bash
    gcc gestionnaire_etudiants.c -o gestionnaire_etudiants
    ```

    Cette commande créera un fichier exécutable nommé `gestionnaire_etudiants` (ou `gestionnaire_etudiants.exe` sous Windows).

3.  **Exécuter :** Lancez le programme depuis le terminal :

    ```bash
    ./gestionnaire_etudiants
    ```

    (Ou `gestionnaire_etudiants.exe` sous Windows).

---

## Utilisation

Au démarrage, le programme tentera de charger les données existantes. Ensuite, un menu s'affichera :

--- Gestionnaire de Dossiers Étudiants ---

Ajouter un étudiant
Afficher tous les étudiants
Trier les étudiants par ID
Sauvegarder les données
Quitter
Entrez votre choix :


Suivez les instructions à l'écran pour interagir avec le gestionnaire. Les données sont automatiquement sauvegardées lors de la sélection de l'option "Sauvegarder" ou lors de la sortie du programme via l'option "Quitter".

---

## Structure du Code

Le code est organisé en plusieurs fonctions pour une meilleure modularité :

* `main()` : La fonction principale qui gère le menu et la boucle d'exécution.
* `afficherMenu()` : Affiche les options disponibles.
* `ajouterEtudiant()` : Gère la saisie et l'ajout d'un nouvel étudiant.
* `afficherEtudiants()` : Parcourt et affiche les détails de chaque étudiant.
* `trierEtudiantsParId()` : Implémente un tri par sélection pour classer les étudiants par leur ID.
* `sauvegarderDonnees()` : Écrit les données des étudiants dans `etudiants.txt`.
* `chargerDonnees()` : Lit les données depuis `etudiants.txt` au démarrage.
* `viderBufferClavier()` : Une fonction utilitaire pour gérer les problèmes de buffer après la lecture d'entiers avec `scanf`.

---

## Limitations

* **Taille statique :** Le nombre maximal d'étudiants est fixé à `MAX_ETUDIANTS` (100 par défaut). Pour un usage plus flexible, l'allocation dynamique de mémoire serait nécessaire.
* **ID non unique garanti :** Bien que l'unicité de l'ID soit vérifiée à l'ajout, la robustesse pourrait être améliorée pour les cas limites ou les manipulations directes du fichier de données.
* **Gestion d'erreurs simple :** La validation des entrées utilisateur et la gestion des erreurs de fichier sont basiques.
* **Fonctionnalités manquantes :** Les options de suppression, de modification ou de recherche d'étudiants spécifiques ne sont pas implémentées dans cette version.
