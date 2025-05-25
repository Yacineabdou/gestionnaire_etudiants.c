#include <stdio.h>   // Inclut la bibliothèque standard d'entrée/sortie pour printf, scanf, fopen, fclose, etc.
#include <string.h>  // Inclut la bibliothèque pour les fonctions de manipulation de chaînes (strcpy, strcmp, etc.).

// Définition de la taille maximale du tableau d'étudiants, des chaînes de caractères(nom, prénom, filière).
#define MAX_ETUDIANTS 100
#define MAX_NOM_PRENOM 50
#define MAX_FILIERE 30
// Nom du fichier où les données seront sauvegardées.
#define NOM_FICHIER "etudiants.txt"

// Définition de la structure pour représenter un étudiant.
typedef struct {
    int id;
    char nom[MAX_NOM_PRENOM];
    char prenom[MAX_NOM_PRENOM];
    int age;
    float moyenne;
    char filiere[MAX_FILIERE];
} Etudiant;

// Déclaration d'un tableau statique pour stocker les étudiants.
Etudiant listeEtudiants[MAX_ETUDIANTS];
// Variable pour garder une trace du nombre actuel d'étudiants dans le tableau.
int nombreEtudiants = 0;

// --- Prototypes des fonctions ---
void afficherMenu();          // Affiche les options du menu.
void ajouterEtudiant();       // Ajoute un nouvel étudiant à la liste.
void afficherEtudiants();     // Affiche tous les étudiants de la liste.
void trierEtudiantsParId();   // Trie les étudiants par ID.
void sauvegarderDonnees();    // Sauvegarde les données des étudiants dans un fichier.
void chargerDonnees();        // Charge les données des étudiants depuis un fichier.
void viderBufferClavier();    // Fonction utilitaire pour vider le buffer du clavier après scanf.

// --- Fonction principale ---
int main() {
    int choix; // Variable pour stocker le choix de l'utilisateur dans le menu.

    chargerDonnees(); // Tente de charger les données existantes au démarrage du programme.

    do {
        afficherMenu(); // Affiche le menu des options.
        printf("Entrez votre choix : ");
        // La gestion de l'erreur d'entrée est basique ici : si scanf ne lit pas un entier,
        // le comportement peut être imprévisible sans vérification de sa valeur de retour.
        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            viderBufferClavier();
            choix = -1; // Réinitialise le choix pour rester dans la boucle do-while.
            continue;
        }
        viderBufferClavier(); // Vide le buffer du clavier après la lecture de l'entier.

        // Utilisation d'une instruction switch pour gérer les différentes options du menu.
        switch (choix) {
            case 1:
                ajouterEtudiant();
                break;
            case 2:
                afficherEtudiants();
                break;
            case 3:
                trierEtudiantsParId();
                break;
            case 4:
                sauvegarderDonnees();
                printf("Données sauvegardées avec succès.\n");
                break;
            case 0:
                sauvegarderDonnees(); // Sauvegarde les données avant de quitter (bonne pratique).
                printf("Merci d'avoir utilisé le gestionnaire. Au revoir !\n");
                break;
            default:
                // Si le choix n'est aucune des options valides.
                printf("Choix invalide. Veuillez réessayer.\n");
                break; 
        }
        printf("\n"); // Affiche une ligne vide pour une meilleure lisibilité.
    } while (choix != 0); // La boucle continue tant que l'utilisateur n'a pas choisi de quitter (0).

    return 0;
}

// --- Implémentation des fonctions ---

// Fonction pour afficher le menu des options.
void afficherMenu() {
    printf("--- Gestionnaire de Dossiers Étudiants ---\n");
    printf("1. Ajouter un étudiant\n");
    printf("2. Afficher tous les étudiants\n");
    printf("3. Trier les étudiants par ID\n");
    printf("4. Sauvegarder les données\n");
    printf("0. Quitter\n");
    printf("-------------------------------------------\n");
}

// Fonction pour ajouter un nouvel étudiant.
void ajouterEtudiant() {
    // Vérifie si le tableau est plein avant d'ajouter un nouvel étudiant.
    if (nombreEtudiants >= MAX_ETUDIANTS) {
        printf("Erreur : Le nombre maximal d'étudiants est atteint (%d).\n", MAX_ETUDIANTS);
        return;
    }

    Etudiant nouvelEtudiant; // Déclare une nouvelle structure Etudiant temporaire.

    printf("--- Ajout d'un nouvel étudiant ---\n");

    // Demande et lit l'ID de l'étudiant.
    printf("ID : ");
    // Vérifie si l'entrée est un entier.
    if (scanf("%d", &nouvelEtudiant.id) != 1) {
        printf("ID invalide. L'ID doit être un nombre.\n");
        viderBufferClavier();
        return;
    }
    viderBufferClavier(); // Vide le buffer après scanf.

    // Vérifie si l'ID existe déjà (pour un ID unique).
    for (int i = 0; i < nombreEtudiants; i++) {
        if (listeEtudiants[i].id == nouvelEtudiant.id) {
            printf("Erreur : Un étudiant avec cet ID existe déjà. Veuillez utiliser un ID unique.\n");
            return;
        }
    }

    // Demande et lit le nom de l'étudiant. fgets est préférable à scanf pour les chaînes avec espaces.
    // fgets lit jusqu'à MAX_NOM_PRENOM-1 caractères ou jusqu'au '\n'.
    // stdin représente l'entrée standard (clavier).
    printf("Nom : ");
    fgets(nouvelEtudiant.nom, MAX_NOM_PRENOM, stdin);
    // Supprime le caractère de nouvelle ligne '\n' qui peut être inclus par fgets.
    nouvelEtudiant.nom[strcspn(nouvelEtudiant.nom, "\n")] = 0;

    // Demande et lit le prénom de l'étudiant.
    printf("Prénom : ");
    fgets(nouvelEtudiant.prenom, MAX_NOM_PRENOM, stdin);
    nouvelEtudiant.prenom[strcspn(nouvelEtudiant.prenom, "\n")] = 0;

    // Demande et lit l'âge de l'étudiant.
    printf("Âge : ");
    if (scanf("%d", &nouvelEtudiant.age) != 1) {
        printf("Âge invalide. L'âge doit être un nombre.\n");
        viderBufferClavier();
        return;
    }
    viderBufferClavier();

    // Demande et lit la moyenne de l'étudiant.
    printf("Moyenne : ");
    if (scanf("%f", &nouvelEtudiant.moyenne) != 1) {
        printf("Moyenne invalide. La moyenne doit être un nombre.\n");
        viderBufferClavier();
        return;
    }
    viderBufferClavier();

    // Demande et lit la filière de l'étudiant.
    printf("Filière : ");
    fgets(nouvelEtudiant.filiere, MAX_FILIERE, stdin);
    nouvelEtudiant.filiere[strcspn(nouvelEtudiant.filiere, "\n")] = 0;

    // Ajoute le nouvel étudiant au tableau.
    listeEtudiants[nombreEtudiants] = nouvelEtudiant;
    // Incrémente le compteur du nombre d'étudiants.
    nombreEtudiants++;
    printf("Étudiant ajouté avec succès !\n");
}

// Fonction pour afficher tous les étudiants.
void afficherEtudiants() {
    // Vérifie s'il y a des étudiants à afficher.
    if (nombreEtudiants == 0) {
        printf("Aucun étudiant à afficher.\n");
        return;
    }

    printf("--- Liste des étudiants (%d) ---\n", nombreEtudiants);
    // Boucle pour parcourir tous les étudiants dans le tableau.
    for (int i = 0; i < nombreEtudiants; i++) {
        // Affiche les détails de chaque étudiant de manière formatée.
        printf("ID: %d\n", listeEtudiants[i].id);
        printf("Nom: %s\n", listeEtudiants[i].nom);
        printf("Prénom: %s\n", listeEtudiants[i].prenom);
        printf("Âge: %d\n", listeEtudiants[i].age);
        // %.2f pour afficher la moyenne avec deux chiffres après la virgule.
        printf("Moyenne: %.2f\n", listeEtudiants[i].moyenne);
        printf("Filière: %s\n", listeEtudiants[i].filiere);
        printf("----------------------------------\n"); // Séparateur pour chaque étudiant.
    }
}

// Fonction pour trier les étudiants par ID en utilisant un tri par sélection.
void trierEtudiantsParId() {
    // Si moins de deux étudiants, le tri n'est pas nécessaire.
    if (nombreEtudiants < 2) {
        printf("Pas assez d'étudiants pour trier.\n");
        return;
    }

    printf("Tri des étudiants par ID...\n");
    // Algorithme de tri par sélection.
    // Parcourt le tableau du premier élément jusqu'à l'avant-dernier.
    for (int i = 0; i < nombreEtudiants - 1; i++) {
        int min_idx = i; // Suppose que l'élément actuel est le plus petit.
        // Trouve l'index de l'élément le plus petit dans le reste du tableau.
        for (int j = i + 1; j < nombreEtudiants; j++) {
            if (listeEtudiants[j].id < listeEtudiants[min_idx].id) {
                min_idx = j; // Met à jour l'index du plus petit si un plus petit est trouvé.
            }
        }
        // Échange l'élément trouvé (le plus petit) avec l'élément à la position actuelle 'i'.
        // J'utilise une variable temporaire pour l'échange.
        if (min_idx != i) {
            Etudiant temp = listeEtudiants[i];
            listeEtudiants[i] = listeEtudiants[min_idx];
            listeEtudiants[min_idx] = temp;
        }
    }
    printf("Étudiants triés par ID avec succès !\n");
    // Après le tri, il est souvent utile d'afficher la liste triée.
    afficherEtudiants();
}

// Fonction pour sauvegarder les données des étudiants dans un fichier texte.
void sauvegarderDonnees() {
    // Déclare un pointeur de fichier.
    FILE *fichier;
    // Tente d'ouvrir le fichier en mode écriture ("w").
    // Si le fichier n'existe pas, il est créé. S'il existe, son contenu est écrasé.
    fichier = fopen(NOM_FICHIER, "w");

    // Vérifie si l'ouverture du fichier a échoué (par exemple, problème de permissions).
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s pour écriture.\n", NOM_FICHIER);
        return;
    }

    // Boucle pour écrire chaque étudiant dans le fichier.
    for (int i = 0; i < nombreEtudiants; i++) {
        // Écrit les informations de l'étudiant dans le fichier, séparées par des virgules.
        // Chaque étudiant est sur une nouvelle ligne.
        fprintf(fichier, "%d,%s,%s,%d,%.2f,%s\n",
                listeEtudiants[i].id,
                listeEtudiants[i].nom,
                listeEtudiants[i].prenom,
                listeEtudiants[i].age,
                listeEtudiants[i].moyenne,
                listeEtudiants[i].filiere);
    }

    // Ferme le fichier après avoir terminé l'écriture. Très important !
    fclose(fichier);
}

// Fonction pour charger les données des étudiants depuis un fichier texte.
void chargerDonnees() {
    FILE *fichier; // Déclare un pointeur de fichier.
    // Tente d'ouvrir le fichier en mode lecture ("r").
    fichier = fopen(NOM_FICHIER, "r");

    // Si le fichier n'existe pas ou ne peut pas être ouvert en lecture,
    // on considère que c'est le premier lancement ou qu'il n'y a pas de données.
    if (fichier == NULL) {
        printf("Aucun fichier de données existant trouvé (%s). Démarrage avec une liste vide.\n", NOM_FICHIER);
        return;
    }

    // Réinitialise le compteur d'étudiants avant de charger de nouvelles données.
    nombreEtudiants = 0;

    // Boucle pour lire chaque ligne du fichier tant qu'on n'atteint pas la fin du fichier (EOF).
    // fscanf lit les données du fichier selon le format spécifié.
    
    // Elle doit lire 6 éléments (un entier, 4 chaînes, un flottant) pour chaque étudiant.
    while (fscanf(fichier, "%d,%49[^,],%49[^,],%d,%f,%29[^\n]\n", // Notez les spécificateurs de format pour les chaînes et le '\n' final.
                  &listeEtudiants[nombreEtudiants].id,
                  listeEtudiants[nombreEtudiants].nom,
                  listeEtudiants[nombreEtudiants].prenom,
                  &listeEtudiants[nombreEtudiants].age,
                  &listeEtudiants[nombreEtudiants].moyenne,
                  listeEtudiants[nombreEtudiants].filiere) == 6 &&
           nombreEtudiants < MAX_ETUDIANTS) {
        // Incrémente le compteur d'étudiants après avoir lu une ligne avec succès.
        nombreEtudiants++;
    }

    // Ferme le fichier après avoir terminé la lecture.
    fclose(fichier);
    printf("Données chargées depuis %s. (%d étudiants trouvés).\n", NOM_FICHIER, nombreEtudiants);
}

// Fonction utilitaire pour vider le buffer du clavier.
// Nécessaire après scanf pour les nombres quand on enchaîne avec fgets (qui lit le '\n' résiduel).
void viderBufferClavier() {
    int c;
    // Lit les caractères restants dans le buffer jusqu'à la fin de ligne ou la fin du fichier.
    while ((c = getchar()) != '\n' && c != EOF);
}