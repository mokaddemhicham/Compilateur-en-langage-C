#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure Instruction: contains the instruction word and the line number.
typedef struct Instruction {
    char *mot;
    int ligne;
    struct Instruction *next;
} Instruction;

// Function to delete the first element of a linked list.
Instruction *supprimerDebut(Instruction *head) {
    Instruction *tmp = head;
    if (head != NULL) {
        head = head->next;
        free(tmp);
    } else {
        return NULL;
    }
    return head;
}

// Function to destroy a linked list (empty a list).
Instruction *detruire_Liste(Instruction *node) {
    Instruction *p = node;
    while (p != NULL) {
        p = supprimerDebut(p);
    }
    return p;
}

// Function to add an element to the end of a linked list.
Instruction *ajouterFin(Instruction *debut, char *chaine, int ligne) {
    Instruction *nouveau, *temp;
    nouveau = (Instruction *)malloc(sizeof(Instruction));
    nouveau->mot = strdup(chaine);
    nouveau->ligne = ligne;
    nouveau->next = NULL;
    if (debut == NULL) {
        debut = nouveau;
    } else {
        temp = debut;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nouveau;
    }
    return debut;
}

// Function to display a linked list.
void Afficher(Instruction *liste) {
    Instruction *p = liste;
    if (p != NULL) {
        while (p != NULL) {
            printf("%s", p->mot);
            if (p->next != NULL) {
                printf(" ");
            }
            p = p->next;
        }
    } else {
        printf("Liste Vide.\n");
    }
}

// Function to perform syntactic analysis on the linked list of instructions.
int Analyse_syntaxique(Instruction *instruction, int si) {
    Instruction *p = instruction;
    Afficher(p);
    printf("\n");

    // cette condition permet de vérifier, vaut 'Sinon' est précédée de 'Si'
    if(si == 1 && strcmp(p->mot, "Sinon") == 0){
        p = p->next;
        si = 1;
        goto LireEcrire; // si vrai nous allons vérifier la syntaxe des instructions de sous-bloc de 'Sinon'
    }else if(si != 1 && strcmp(p->mot, "Sinon") == 0){
        printf("Erreur Syntaxique | Ligne %d | 'Sinon' sans 'Si' precedent\n",p->ligne);
    }
    // cette condition permet de vérifier, vaut 'FinSi' est précédée de 'Si'
    if(si == 1 && strcmp(p->mot, "FinSi") == 0){
        p = p->next;
        if(strcmp(p->mot, ";") == 0){
            return 0;
        }else{
            printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez ';'\n",p->ligne);
            return 0;
        }
    }else if(si != 1 && strcmp(p->mot, "FinSi") == 0){
        printf("Erreur Syntaxique | Ligne %d | 'FinSi' sans 'Si' precedent\n",p->ligne);
        return 0;
    }else if(si == 1 && strcmp(p->mot, "FinSi") != 0 && strcmp(p->mot, "Sinon") != 0){
        // cette condition permet de vérifier, vaut 'FinSi' est précédée de 'Si' ou 'Sinon'
        printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez 'FinSi'\n",p->ligne);
        return 0;
    }

    LireEcrire: // l'analyse syntaxique des instructions 'Lire' et 'Ecrire'
    if(strcmp(p->mot, "Lire") == 0 || strcmp(p->mot, "Ecrire") == 0){
        p = p->next;
        if(strcmp(p->mot, "(") == 0){
            p = p->next;
        }else{
            printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez '('\n", p->ligne);
        }

        if((strcmp(p->mot, "A") >= 0 && strcmp(p->mot, "Z") <= 0) || (strcmp(p->mot, "a") >= 0 && strcmp(p->mot, "z") <= 0)){
            p = p->next;
        }else{
            printf("Erreur Syntaxique | Ligne %d | Vous devez entrer une variable de [a-zA-Z]\n", p->ligne);
        }

        if(strcmp(p->mot, ")") == 0){
            p = p->next;
        }else{
            printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez ')'\n",p->ligne);
        }

        if(strcmp(p->mot, ";") == 0){
            if(si == 1){
                return si;
            }else{
                return 0;
            }
        }else{
            printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez ';'\n", p->ligne);
            if(si == 1){
                return si;
            }else{
                return 0;
            }
        }
    }
        // l'analyse syntaxique de l'instruction 'Variable'
        if(strcmp(p->mot, "Variable") == 0){
            p = p->next;
            if((strcmp(p->mot, "A") >= 0 && strcmp(p->mot, "Z") <= 0) || (strcmp(p->mot, "a") >= 0 && strcmp(p->mot, "z") <= 0)){
                p = p->next;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous devez entrer une variable de [a-zA-Z]\n", p->ligne);
            }

            if(strcmp(p->mot, ":") == 0){
                p = p->next;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez ':'\n", p->ligne);
            }

            if(strcmp(p->mot, "Entier") == 0){
                p = p->next;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez le type du variable\n",p->ligne);
            }

            if(strcmp(p->mot, ";") == 0){
                return 0;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez ';'\n",p->ligne);
                return 0;
            }
        }
        // l'analyse syntaxique de l'instruction 'Si'
        if(strcmp(p->mot,"Si")==0)
        {
            si = 1;
            p=p->next;
            if(strcmp(p->mot,"(")==0){
                p= p->next;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oublier '('\n",p->ligne);
            }

            if((strcmp(p->mot, "A") >= 0 && strcmp(p->mot, "Z") <= 0) || (strcmp(p->mot, "a") >= 0 && strcmp(p->mot, "z") <= 0)){
                p = p->next;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oublier le premier comparant\n", p->ligne);
            }

            if(strcmp(p->mot,"==")== 0 || strcmp(p->mot,"<")==0 || strcmp(p->mot,">")==0|| strcmp(p->mot,"<=")==0|| strcmp(p->mot,">=")==0|| strcmp(p->mot,"!=")==0 ){
                p = p->next;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oublier l'operateur\n",p->ligne);
            }

            if((strcmp(p->mot, "A") >= 0 && strcmp(p->mot, "Z") <= 0) || (strcmp(p->mot, "a") >= 0 && strcmp(p->mot, "z") <= 0)){
                    p = p->next;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oublier le deuxieme comparant\n",p->ligne);
            }
            if(strcmp(p->mot,")")==0){
                p = p->next;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oublier ')'\n",p->ligne);
            }
            if(strcmp(p->mot,"Alors")==0){
                p = p->next;
                goto LireEcrire; //
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oublier 'Alors'\n",p->ligne);
            }
        }

    return si;
}

// Function to read a file, extract instructions, and perform syntactic analysis.
void FichierToListeChainee(char *filePath) {
    FILE *file = fopen(filePath, "r");
    Instruction *p = NULL;
    char *mot = (char *)malloc(sizeof(char) * 40);
    int i = 0;
    int siExist = 0;
    char c;
    int ligne = 1;

    while (!feof(file)) {
        c = fgetc(file);
        if (c != ' ' && c != '\n') {
            *(mot + i) = c;
            i++;
        } else {
            if(c == '\n')
            {
                ligne++; // pour savoir la ligne ou se trouve chaque mot.
            }
            *(mot+i) = '\0'; // terminer chaque mot par le caractere '\0'.
            if(strcmp(mot, ";") != 0  && strcmp(mot,"\0") != 0 && strcmp(mot, ".") != 0){
                // cette condition permet d'inserer chaque mot dans la liste tant que le mot != ";" et != '\0' et != '.'
                p = ajouterFin(p,mot,ligne);
            }else if(strcmp(mot,"\0") != 0){ // mot != '\0' pour eviter un mot vide.
                if(strcmp(mot,".") != 0){
                    p = ajouterFin(p,";",ligne);
                }else{
                    p = ajouterFin(p,".",ligne); // pour inserer le dernier point qui indique la fin du code.
                }
                /* cette fonction "Analyse_syntaxique" retourne la valeur '1', si 'Si' ou 'Sinon' exist.
                'p' une liste chainee d'une instruction, 'siExist' : j'ai deja l'expliquer */
                siExist = Analyse_syntaxique(p, siExist);
                // cette fonction permet de detruire la liste chainee apres l'analyse syntaxique de chaque instruction.
                p = detruire_Liste(p);
            }

            i = 0;
            //free(mot);
            mot = (char *)malloc(sizeof(char) * 40);
        }
    }
    fclose(file);
}

// Function to perform lexical analysis on a single word using a provided lexicon (dictionary).
void Analyse_lix(char *str, char *dict, int ligne) {
    FILE *dictionnaire = fopen(dict, "r");
    char *lexique = (char *)malloc(sizeof(char) * 40);
    int i = 0;
    char c;
    int trouve = 0;

    while(!feof(dictionnaire))
    {
        c = fgetc(dictionnaire);
        if(c!= ' ' && c!= '\n')
        {
            *(lexique+i) = c;
            i++;
        }
        else
        {
            *(lexique+i) = '\0';
            if(strcmp(str, lexique) != 0) // comparaison entre le mot 'str' avec chaque mot du lexique.
            {
                trouve = 0;
            }
            else
            {
                trouve = 1;
                break;
            }
            i = 0;
            lexique = (char*)malloc(sizeof(char)*40);
        }
    }

    fclose(dictionnaire);

    if (trouve == 0) {
        FILE *errors = fopen("fichiers/logs.txt", "a+");
        fprintf(errors, "Erreur Lexicale en ligne %d : '%s' n'exist pas dans le dictionnaire de la langue.\n", ligne, str);
        fprintf(errors, "---------------------------------------------------------------------------------\n");
        fclose(errors);
        printf("Erreur Lexicale en ligne %d : '%s' n'exist pas dans le dictionnaire de la langue.\n", ligne, str);
    }
}

// Function to read a file, extract words, and perform lexical analysis on each word.
void MotToAnalyseLexicale(char *filePath, char *dict) {
    FILE *file = fopen(filePath, "r");
    char *mot = (char *)malloc(sizeof(char) * 40);
    int i = 0;
    char c;
    int ligne = 1;

    while (!feof(file)) {
        c = fgetc(file);
        if (c != ' ' && c != '\n') {
            *(mot + i) = c;
            i++;
        } else {
            if(c == '\n')
            {
                ligne++;
            }
            *(mot+i) = '\0';
            Analyse_lix(mot, dict, ligne); // dict : chemin du dictionnaire + ligne : ligne ou il se trouve le mot

            i = 0;
            mot = (char *)malloc(sizeof(char) * 40);
        }
    }
    fclose(file);
}

int main() {
    char *cheminDuCode = "fichiers/programme.txt";
    char *dictionnaire = "fichiers/lexique.txt";

    printf("\n----------------- Analyse Lexicale -------------------\n\n");

    MotToAnalyseLexicale(cheminDuCode, dictionnaire);

    printf("\n----------------- Analyse Syntaxique -------------------\n\n");

    FichierToListeChainee(cheminDuCode);

    return 0;
}
