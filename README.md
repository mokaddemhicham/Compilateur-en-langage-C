# Compilateur en langage C

## Définition
Un compilateur est un programme qui transforme un code source en un code objet2. Généralement, le code source est écrit dans un langage de programmation (le langage source), il est de haut niveau d'abstraction, et facilement compréhensible par l'humain. Le code objet est généralement écrit en langage de plus bas niveau (appelé langage cible), par exemple un langage d'assemblage ou langage machine, afin de créer un programme exécutable par une machine.[Wikipedia](https://fr.wikipedia.org/wiki/Compilateur)

## Fonctionnement
Un compilateur effectue les opérations suivantes : analyse lexicale, pré-traitement (préprocesseur), analyse syntaxique (parsing), analyse sémantique, et génération de code optimisé. La compilation est souvent suivie d'une étape d’édition des liens, pour générer un fichier exécutable.

## Les étapes principales de la compilation

- <b>l'analyse lexicale</b>: qui découpe le code source en petits morceaux appelés jetons (tokens).
Chaque jeton est une unité atomique unique de la langue (unités lexicales ou lexèmes), par exemple un mot-clé, un identifiant ou un symbole. La syntaxe de jeton est généralement un langage régulier, donc reconnaissable par un automate à états finis.
Cette phase est aussi appelée à balayage ou lexing ; le logiciel qui effectue une analyse lexicale est appelé un analyseur lexical ou un scanner. Un analyseur lexical pour un langage régulier peut être généré par un programme informatique, à partir d'une description du langage par des expressions régulières. Deux générateurs classiques sont lex et flex.
- <b>l'analyse syntaxique</b>: implique l'analyse de la séquence jeton pour identifier la structure syntaxique du programme.
Cette phase s'appuie généralement sur la construction d'un arbre d'analyse ; on remplace la séquence linéaire des jetons par une structure en arbre construite selon la grammaire formelle qui définit la syntaxe du langage. Par exemple, une condition est toujours suivie d'un test logique (égalité, comparaison…). L'arbre d'analyse est souvent modifié et amélioré au fur et à mesure de la compilation. Yacc et GNU Bison sont les analyseurs syntaxiques les plus utilisés.
- <b>l'analyse sémantique</b>: est la phase durant laquelle le compilateur ajoute des informations sémantiques à l'arbre d'analyse et construit la table des symboles.
Cette phase vérifie le type (vérification des erreurs de type), ou l'objet de liaison (associant variables et références de fonction avec leurs définitions), ou une tâche définie (toutes les variables locales doivent être initialisées avant utilisation), peut émettre des avertissements, ou rejeter des programmes incorrects.<br/><br/>
![](https://upload.wikimedia.org/wikipedia/commons/e/e5/Cha%C3%AEne_de_compilation.svg)
<br/>

## Le Concept de ce Projet
Le concept de ce projet est de réaliser un programme qui vérifie l'analyse Lexicale puis l'analyse syntaxique d'un algorithme.
### Exemle d'un algorithme
> Variable A   Entier ; <br/>
> var B : Entier ; <br/>
> Lire ( A ) ; <br/>
> Lir (  B ) ; <br/>
> Si ( A  B ) Alors <br/>
> &nbsp;&nbsp;&nbsp;Ecrire ( A ) ; <br/>
> Sinon <br/>
> &nbsp;&nbsp;&nbsp;Ecrire ( B ) ; <br/>
> FinSi ; <br/>
> Fin . 
### Lexique
> a b c d e f g h i j k l m n o p q r s t u v w x y z <br/>
> A B C D E F G H I J K L M N O P Q R S T U V W X Y Z <br/>
> 0 1 2 3 4 5 6 7 8 9 <br/>
> = == != > >= < <= <br/>
> Entier Reel <br/>
> Variable <br/>
> Entier <br/>
> debut <br/>
> Lire <br/>
> Ecrire <br/>
> Si <br/>
> Alors <br/>
> Sinon <br/>
> FinSi <br/>
> ( <br/>
> ) <br/>
> ; <br/>
> : <br/>
> Fin <br/>
> . <br/>

## Collaboration et Contribution

Je vous encourage vivement à collaborer et à contribuer à ce projet. Si vous souhaitez vous impliquer, voici comment vous pouvez participer :

- **Améliorations et Corrections :** Si vous avez des idées d'améliorations, de fonctionnalités supplémentaires ou si vous avez repéré des erreurs, n'hésitez pas à ouvrir des issues sur le dépôt GitHub. Je suis ouvert aux discussions et aux suggestions de la communauté.

- **Contributions de Code :** Si vous êtes intéressé par le développement de code, je vous invite à proposer des pull requests. Vos contributions seront examinées attentivement et peuvent être intégrées au projet.

- **Rapports de Problèmes :** Si vous rencontrez des problèmes lors de l'utilisation de ce projet, veuillez les signaler en ouvrant des rapports de problèmes sur GitHub. Cela m'aidera à identifier et à résoudre rapidement les problèmes.

- **Documentation :** Une documentation claire et précise est essentielle. Si vous pouvez contribuer à améliorer la documentation en fournissant des exemples d'utilisation, des guides d'installation ou toute autre information utile, cela serait grandement apprécié.

- **Test et Retours d'Expérience :** Si vous avez testé ce projet dans différents environnements ou configurations, partagez vos retours d'expérience. Cela peut être précieux pour d'autres utilisateurs.

Pour collaborer avec moi, rendez-vous sur le dépôt GitHub [[lien vers le dépôt](https://github.com/mokaddemhicham/Compilateur-en-langage-C)] et explorez les options de contribution. Votre engagement et vos contributions sont essentiels pour faire de ce projet une ressource de qualité pour la communauté. Je vous remercie pour votre intérêt et votre soutien continu.

## Copyright
© 2023 [Hicham Mokaddem](https://mokaddemhicham.tech). Tous droits réservés.
