#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure Instruction : contient le mot de l'instruction + la ligne ou il se trouve.
typedef struct Instruction{
    char *mot;
    int ligne;
    struct Instruction *next;
} Instruction;
// fonction qui permet de supprimer le premier element d'une liste chainee.
Instruction *supprimerDebut(Instruction *head){
    Instruction *tmp = head;
    if(head != NULL){
        head = head->next;
        free(tmp);
    }else{
        return NULL;
    }
    return head;
}
// fonction pour detruire une liste chainne (vider une liste)
Instruction *detruire_Liste(Instruction *node) {
  Instruction *p = node;
  while (p != NULL) {
    p = supprimerDebut(p);
  }
  return p;
}

// La fonction "ajouterFin" est utilisée pour ajouter un élément à la fin de la liste de chaînes
Instruction *ajouterFin(Instruction *debut,char *chaine,int ligne)
{
    Instruction *nouveau,*temp;
    nouveau =(Instruction*)malloc(sizeof(Instruction));
    nouveau->mot = (char*)malloc(sizeof(char));
    strcpy(nouveau->mot,chaine);
    nouveau->ligne = ligne;
    nouveau->next=NULL;
    if(debut == NULL)
    {
        debut= nouveau;
    }
    else
    {
        temp=debut;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next = nouveau;
    }
    return debut;

}

// La fonction "Analyse_syntaxique" permet d'analyser la syntaxe du code. Instruction par instruction.
int Analyse_syntaxique(Instruction *instruction, int si){
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
            return;
        }else{
            printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez ';'\n",p->ligne);
            return;
        }
    }else if(si != 1 && strcmp(p->mot, "FinSi") == 0){
        printf("Erreur Syntaxique | Ligne %d | 'FinSi' sans 'Si' precedent\n",p->ligne);
        return;
    }else if(si == 1 && strcmp(p->mot, "FinSi") != 0 && strcmp(p->mot, "Sinon") != 0){
        // cette condition permet de vérifier, vaut 'FinSi' est précédée de 'Si' ou 'Sinon'
        printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez 'FinSi'\n",p->ligne);
        return;
    }

    LireEcrire: // l'analyse syntaxique des instructions 'Lire' et 'Ecrire'
    if(strcmp(p->mot, "Lire") == 0 || strcmp(p->mot, "Ecrire") == 0){
        p = p->next;
        if(strcmp(p->mot, "(") == 0){
            p = p->next;
        }else{
            printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez '('\n", p->ligne);
        }

        if(strcmp(p->mot, "A") >= 0 && strcmp(p->mot, "Z") <= 0 || strcmp(p->mot, "a") >= 0 && strcmp(p->mot, "z") <= 0){
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
                return;
            }
        }else{
            printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez ';'\n", p->ligne);
            if(si == 1){
                return si;
            }else{
                return;
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
                return;
            }else{
                printf("Erreur Syntaxique | Ligne %d | Vous avez oubliez ';'\n",p->ligne);
                return;
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
}

// La fonction "Afficher" permet d'afficher une liste chainnee.
void Afficher(Instruction *liste){
    Instruction *p = liste;
    if(p != NULL){
        while(p != NULL){
            printf("%s", p->mot);
            if(p->next != NULL){
                printf(" ");
            }
            p = p->next;
    }
    }else{
        printf("Liste Vide.\n");
    }
}

/* cette fonction permet de:
1 - lire le fichier caractere par caractere jusqu'il a construire un mot, sachant un mot se termine par une espace.
2 - passer chaque mot d'instruction a une autre fonction "ajouterFin" qui va l'inserer dans une liste chainnes, sachant que chaque instruction se termine par une point virgule ";"
3 - Passer chaque instruction a une autre fonction "Analyse_syntaxique", qui va faire l'anayse syntaxique pour cette instruction.
*/
void FichierToListeChainee(char *filePath){
    FILE* file  = fopen(filePath, "r");
    Instruction *p = NULL;
    char *mot = (char*)malloc(sizeof(char)*40); // mot : est un tableau de caractères, je vais le remplir d'apres le fichier du programme.
    int i = 0;
    int siExist = 0; // Variable "siExist" pour indiquer si 'Si' ou 'Sinon' ont été introduits dans le code.
    char c;
    int ligne = 1;
    while(!feof(file))
    {
        c = fgetc(file);
        if(c!= ' ' && c!= '\n')
        {
            *(mot+i) = c; // inserer chaque caractere dans un tableau pour construire un mot.
            i++;
        }
        else
        {
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
            free(mot); // vider le tableau des caracteres (mot).
            mot = (char*)malloc(sizeof(char)*40); // réinitialisation du tableau.
            }
        }
        fclose(file); // fermet le fichier du code.
}

/* cette fonction faire l'analyse lexicale pour chaque mot.
cette derniere prend en parametre le mot + la ligne ou il se trouve dans le fichier + le chemin du dictionnaire.
*/
void Analyse_lix(char* str, char* dict, int ligne)
{
    FILE* dictionnaire = fopen(dict, "r");
    char *lexique = (char*)malloc(sizeof(char)*40); // lexique : est un tableau de caractères, je vais le remplir d'apres le fichier du lexique.
    int i = 0;
    char c;
    int trouve = 0; // trouve une variable qui prend 2  valeur '1' : si le mot exist dans le dictionnaire '0' sinon.
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
            free(lexique);
            lexique = (char*)malloc(sizeof(char)*40);
        }
    }
    fclose(dictionnaire);
    /* si trouve = 0, donc le mot n'exist pas dans le dictionnaire. alors je vais afficher une erreur dans
    dans la console et dans un fichier 'logs.txt', qui va contient toutes les erreurs lexicales du code (Programme).
    */
    if(trouve == 0)
    {
        FILE* errors = fopen("fichiers/logs.txt", "a+");
        fprintf(errors,"Erreur Lexicale en ligne %d : '%s' n'exist pas dans le dictionnaire de la langue.\n",ligne,str);
        fprintf(errors,"---------------------------------------------------------------------------------\n");
        fclose(errors);
        printf("Erreur Lexicale en ligne %d : '%s' n'exist pas dans le dictionnaire de la langue.\n",ligne,str);
    }

}

/* cette fonction permet de:
1 - lire le fichier caractere par caractere jusqu'il a construit un mot, sachant qu'un mot se termine par une espace.
2 - Passer chaque mot a une autre fonction "Analyse_lix", qui va faire l'anayse Lexicale pour ce mot.
*/

void MotToAnalyseLexicale(char* filePath, char* dict)
{
    FILE* file = fopen(filePath, "r");
    char *mot = (char*)malloc(sizeof(char)*40);
    Instruction *fileToListe = NULL;
    int message = 0;
    int i = 0;
    char c;
    int ligne = 1;
    while(!feof(file))
    {
        c = fgetc(file);
        if(c!= ' ' && c!='\n')
        {
            *(mot+i) = c;
            i++;
        }
        else
        {
            if(c == '\n')
            {
                ligne++;
            }
            *(mot+i) = '\0';
            Analyse_lix(mot, dict, ligne); // dict : chemin du dictionnaire + ligne : ligne ou il se trouve le mot

            free(mot);
            i = 0;
            free(mot);
            mot = (char*)malloc(sizeof(char)*40);
        }
    }
    fclose(file);
}

int main()
{
    char* cheminDuCode  = "fichiers/programme.txt"; // chemin du code.
    char* dictionnaire = "fichiers/lexique.txt"; // chemin du lexique (dictionnaire).

    printf("\n----------------- Analyse Lexicale -------------------\n\n");

    MotToAnalyseLexicale(cheminDuCode,dictionnaire);

    printf("\n----------------- Analyse Syntaxique -------------------\n\n");

    FichierToListeChainee(cheminDuCode);

    return 0;
}
