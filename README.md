# Travaux pratique complexité
Algorithmes de sous-séquence maximale<br>
Pour un tableau T[1,...,n], on note S(k,l) = ⅀(l, j=k) T[j] pour 1 ≤ k ≤ l ≤ n<br>
On détermine k<sub>max</sub> et l<sub>max</sub> tels que S(k<sub>max</sub>, l<sub>max</sub>) = max S(k,l) / k ≤ l

auteurs : GILETA Michael & BERNARDINI Mickaël

# Sommaire
* Structure
* Compilation
* Exécution

# Structure
**src :**
Répertoire contenant le code source du projet, dont le fichier contenant la fonction main : main.c

**inc :**
Répertoire contenant les fichiers headers des différents algorithme utilisé.

# Compilation
Le projet comporte un *Makefile* qui facilite la compilation en utilisant la
commande *make*.

    make

# Exécution
Pour exécuter le projet il suffit d'exécuter le fichier *main*, précédemment compiler, suivi de l'option désirée puis le tableau à tester. A noté que sans option l'algorithme d en O(n) sera utilisé.

    ./main [OPTION] TABLEAU

##Options
**-a**
Algorithme naïf: examination de toutes les sous-séquences possibles.

**-b**
Optimisation de *-a* en observant que S(k,l) = S(k,l - 1) + T[l]

**-c**
Diviser pour régner: diviser la séquence en deux. calculer une sous-séquence de somme maximale de chaque moitié. Calculer une sous-séquence de somme maximale qui contient l'élément du milieu. Finalement prendre le maximum des trois.

**-d**
Supposer le probleme résolu pour T[1,...,i]. Observer que la solution pour T[1,..., i + 1] est soit la solution précédente doit la sous-sequence de somme maximale qui se termine par T[i + 1].

**-t**
Batterie de test des divers algorithmes sur des tailles d'entrées différentes.
