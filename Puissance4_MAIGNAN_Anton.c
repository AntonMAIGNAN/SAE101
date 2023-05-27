/**
* \page Général 
* \author Anton MAIGNAN 1D1
* \version 1.1
* \date 13 novembre 2022
*
* Ce programme propose une partie de jeu de Puissance 4.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * \def couleur(param)
 * \brief Prend comme valeur une modification de printf() pour lui donner une couleur.
 * (exemple: couleur("31") changera les printf(" ") en printf("...",31) qui donne la couleur rouge.)
 */
#define couleur(param) printf("\033[%sm",param)
/**
 * \brief  Correspond à la valeur du pion du 1er joueur, qui est 'X'.
 */
const char PION_A = 'X';
/**
 * \brief  Correspond à la valeur du pion du 2ème joueur, qui est 'O'.
 */
const char PION_B = 'O';
/**
 * \brief Constante permettant l'initialisation de la grille avec le caractère VIDE qui est ' '.
 */
const char VIDE = ' ' ;
/**
 * \brief  Constante qui nous permet de comparer s'il y'a un vainqueur où non. Elle vaut ' '.
 */
const char INCONNU = ' ';
/**
* \def NBLIG
* \brief Taille maximale de la 1ère dimension d'un tableau.
* Nombre maximale de ligne de la grille.
*/
#define NBLIG  6
/**
* \def NBCOL
* \brief Taille maximale de la 2ème dimension d'un tableau.
* Nombre maximale de colonne de la grille.
*/
#define NBCOL  7
/**
 * \brief  Permet de définir où le sélecteur est affiché en premier. ici, cela vaut, NBCOL/2.
 * \see NBCOL
 */
const int COLONNE_DEBUT = NBCOL/2;

/**
* \typedef t_grille
* \brief Le type chaine permet de déclarer un tableau pour une grille de jeu de puissance4 de bonnes dimensions.
*/
typedef char t_grille[NBLIG][NBCOL];

bool appuyerTouche();
void initGrille(t_grille g);
void afficher(t_grille g, char pion, int colonne);
bool grillePleine(t_grille g);
void jouer(t_grille g, char pion, int *ligne, int *colonne);
int choisirColonne(t_grille g, char pion, int colonne);
int trouverLigne(t_grille g, int colonne);
bool estVainqueur(t_grille grille, int ligne, int colonne);
void finDePartie(char pion);

/**
 * \fn int main()
 * \brief Le programme principal lance la partie de jeu et attribut aux fonctions/procédures, le pion de joueur correspondant. 
 * \return 0 
 */
int main(void){
    char vainqueur = INCONNU;
    bool AP= false;
    int ligne, colonne;
    t_grille g;
    
    while(AP==false){
        AP= appuyerTouche();
    }

    initGrille(g);
    afficher(g, PION_A, COLONNE_DEBUT);
    while((vainqueur==INCONNU)&&(grillePleine(g)!=true)){
        colonne=COLONNE_DEBUT;
        jouer(g, PION_A, &ligne, &colonne);
        afficher(g, PION_B, COLONNE_DEBUT);
        if (estVainqueur(g, ligne, colonne)){
            vainqueur= PION_A;
        }
        else if (grillePleine(g)==false){
            colonne=COLONNE_DEBUT;
            jouer(g, PION_B, &ligne, &colonne);
            afficher(g, PION_A, COLONNE_DEBUT);
            if (estVainqueur(g, ligne, colonne)){
                vainqueur= PION_B;
            }
        }
    }
    finDePartie(vainqueur);

    return EXIT_SUCCESS;
}

/*------------------------------------------------------------------------------------*/

/**
 * \fn appuyerTouche()
 * \brief Tant que la touche 'c' n'est pas entrée, affiche le menu.
 * \return fin : true si la touche 'c' est pressée et false si une autre touche est pressée.
 */
bool appuyerTouche(){
    system("cls");
    printf("Appuyer sur la touche c pour commencer votre partie.\n(joueur 1: 'X' ; joueur 2: 'O')\n");
    bool fin= false;
    char c;
    if((c=getchar()) == 'c')
        fin = true;
    return fin;
}

/**
 * \fn void initGrille(t_grille g)
 * \brief Initialise la grille en affectant la constante VIDE à chacun de ses éléments. Parcourt le tableau case par case et attribut la cosntante VIDE à chaque case du tableau.
 * \param g : Grille, représente la grille de jeu
 */
void initGrille(t_grille g){
    int i,j;
    for (i=0; i<6; i++){
        for (j=0; j<7; j++){
            g[i][j]=VIDE;
        }
    }
}

/**
 * \fn void afficher(t_grille g, char pion, int colonne)
 * \brief Réalise l’affichage à l’écran du contenu de la grille avec les pions déjà joués. Cette procédure affiche aussi, au-dessus de la grille, 
 * le prochain pion à tomber (avec un switch) : il sera affiché au-dessus de la colonne dont le numéro est donné en paramètre. 
 * Cette procédure commencera par effacer l’écran, puis Parcourt tout le tableau et l'affiche case par case.
 * \param g : Grille, représente la grille de jeu
 * \param pion : caractère, représente le pion à afficher au-dessus de la grille
 * \param colonne : entier, représente l’indice de la colonne au-dessus de laquelle le pion doit être affiché
 * 
 
 */
void afficher(t_grille g, char pion, int colonne){
    int i,j;
    system("cls");
    switch(colonne){
        case 0:printf("->%c<-                        \n", pion);
                break;
        case 1:printf("    ->%c<-                    \n", pion);
                break;
        case 2:printf("        ->%c<-                \n", pion);
                break;
        case 3: printf("            ->%c<-           \n", pion);
                break;
        case 4:printf("                ->%c<-        \n", pion);
                break;
        case 5:printf("                    ->%c<-    \n", pion);
                break;
        case 6:printf("                        ->%c<-\n", pion);
                break;
        default:couleur("31"); 
                printf("ERROR\n");
                couleur("0");
                break;
    }
    for (i=0; i<6; i++){
        for (j=0; j<7; j++){
            printf("| %c ", g[i][j]); 
        }
        printf("|\n");
    }
    printf("--0---1---2---3---4---5---6--\n\n");
    printf ("Au joueur '%c' de jouer    |   votre caractère : \n", pion);
}

/**
 * \fn grillePleine(t_grille g)
 * \brief Teste si toutes les cases de la grille sont occupées ou non. Parcourt les cases de la 1ère ligne et vérifie si toutes les cases ne sont pas remplies.
 * \param g : Grille, représente la grille de jeu
 * \return true : VRAI si toutes les cases de la grille sont occupées par les pions
 * \return false : FAUX si la grille n'est pas pleine.
 */
bool grillePleine(t_grille g){
    int colonne= 0;
    int compteur= 0;
    while (g[0][colonne]!=' '){
        compteur++;
        colonne++;
        if (compteur==7){
            return true;
        }
    }
    return false;    
}

/**
 * \fn jouer(t_grille g, char pion, int *ligne, int *colonne)
 * \brief Permet à un joueur de jouer son pion. La procédure fait appel à choisirColonne, afin que le joueur indique la colonne dans laquelle il veut jouer ; 
 * puis fait appel à trouverLigne pour définir la case où ajouter le pion.
 * \param g : Grille, représente la grille de jeu
 * \param pion : caractère, correspond au pion à jouer
 * \param ligne : entier, correspond à la ligne où est tombé le pion
 * \param colonne : entier, correspond à la colonne où est tombé le pion
 */
void jouer(t_grille g, char pion, int *ligne, int *colonne){
    int temp = 0;

    *colonne= choisirColonne(g, pion, *colonne);
    temp= trouverLigne(g, *colonne);

    while(temp==-1){
        *colonne= choisirColonne(g, pion, *colonne);
        temp= trouverLigne(g, *colonne);
    }

    *ligne = temp;
    g[*ligne][*colonne]= pion;
}

/**
 * \fn choisirColonne(t_grille g, char pion, int colonne)
 * \brief Un joueur voit son pion au-dessus de la grille et cette fonction doit lui permettre de "déplacer" son pion d’une colonne vers la gauche (par la touche ‘q’) ou 
 * d’une colonne vers la droite (par la touche ‘d’).  Après chaque déplacement, la grille est réaffichée. 
 * Le joueur peut finalement choisir la colonne où il souhaite faire tomber son pion (par la touche ESPACE).
 * \param g : Grille, représente la grille de jeu 
 * \param pion : caractère, représente le pion à tester
 * \param colonne : colonne de départ (celle au-dessus de laquelle se trouve le pion initialement)
 * \return int : indice de la colonne choisie par le joueur 
 */
int choisirColonne(t_grille g, char pion, int colonne){
    char lettreBuffer;
    lettreBuffer = getchar();
    while(lettreBuffer != ' '){
        if ((lettreBuffer =='q')||(lettreBuffer =='Q')){
            if (colonne!=0){
                colonne--;
                afficher(g, pion, colonne);
            }
        }        
        else if ((lettreBuffer =='d')||(lettreBuffer =='D')){
            if (colonne!=6){
                colonne++;
                afficher(g, pion, colonne);
            }
        }
        else{
            afficher(g, pion, colonne);
        }
        lettreBuffer=getchar();
    }

    return colonne;
    
    
}

/**
 * \fn trouverLigne(t_grille grille, int colonne)
 * \brief Consiste à trouver la première case non occupée de la colonne. Si la colonne est pleine, la fonction retourne -1. 
 * Prend en indice le bas(5) de la colonne et verifie case par case s'il y'a un jeton et dès qu'il n'y a pas de jeton, cela retourne l'indice de la ligne.
 * \param grille : Grille, représente la grille de jeu
 * \param colonne : entier, indice de la colonne dans laquelle le pion doit tomber
 * \return int : indice de la ligne où le pion devra être ajouté ou -1 si la colonne est pleine
 * 
 
 */
int trouverLigne(t_grille grille, int colonne){
    const int LIMITE = 0;
    int bas = 5;

    if (grille[0][colonne]!=' '){
        return -1 ;
    }
    while(grille[bas][colonne]!=' '){
        if(bas >=LIMITE){
            bas--;
        }
    }
    return bas;
}

/**
 * \fn estVainqueur(t_grille grille, int ligne, int colonne)
 * \brief Indique si le pion situé dans la case repérée par les paramètres ligne et colonne a gagné la partie. Elle vérifie verticalement, puis horizontalement, puis en diagonale si le pion est aligné.
 * \param grille : Grille, représente la grille de jeu
 * \param ligne : entiers représentant la case à partir de laquelle rechercher une série de 4 successifs identiques
 * \param colonne : entiers représentant la case à partir de laquelle rechercher une série de 4 successifs identiques
 * \return true : VRAI s’il y a 4 jetons alignés
 * \return false : FAUX si il n'y as pas 4 jetons alignés
 */
bool estVainqueur(t_grille grille, int ligne, int colonne){
    const int FIN = 4;

    int compteur = 0;
    char jeton= grille[ligne][colonne];
    int i = ligne;
    int j = colonne;
    
    // Vérification Verticale
    while(grille[i][colonne]==jeton){
        if (grille[i][colonne]==jeton){
            compteur++;
        }
        i++;
    }
    
    i = ligne - 1;

    while(grille[i][colonne]==jeton){
        if (grille[i][colonne]==jeton){
            compteur++;
        }
        i--; 
    }

    if (compteur >= FIN){
        return true;
    }
    compteur = 0;
    i = ligne;
    
    // Vérification Horizontale
    while(grille[ligne][j]==jeton){
        if (grille[ligne][j]==jeton){
            compteur++;
        }
        j++;
    }

    j = colonne - 1;

    while(grille[ligne][j]==jeton){
        if (grille[ligne][j]==jeton){
            compteur++;
        }
        j--;
    }

    if (compteur >= FIN){
        return true;
    }
    compteur = 0;
    j = colonne;

    // Vérification Diagonale (gauche vers droite)
    while(grille[i][j]==jeton){
        if (grille[i][j]==jeton){
            compteur++;
        }
        j++;
        i++;
    }

    i = ligne - 1;
    j = colonne - 1;

    while(grille[i][j]==jeton){
            if (grille[i][j]==jeton){
                compteur++;
            }
            j--;
            i--;
    }

    if (compteur >= FIN){
        return true;
    }
    compteur = 0;
    i = ligne;
    j = colonne;

    // Vérification Diagonale (droite vers gauche)
    while(grille[i][j]==jeton){
        if (grille[i][j]==jeton){
            compteur++;
        }
        j++;
        i--;
            
    }

    i = ligne + 1;
    j = colonne - 1;

    while(grille[i][j]==jeton){
        if (grille[i][j]==jeton){
            compteur++;
        }
        j--;
        i++;
    }

    if (compteur >= FIN){
        return true;
    }

    return false;
}

/**
 * \fn void finDePartie(char pion)
 * \brief Affiche le résultat d’une partie lorsqu’elle est terminée.
 * \param pion : caractère qui représente le pion gagnant (PION_A ou PION_B) ou bien VIDE si match nul.
 */
void finDePartie(char pion){
    couleur("31");
    printf("\n*** FIN DE PARTIE ***\n");
    printf("JOUEUR '%c' A GAGNE\n", pion);
    couleur("0");
}
