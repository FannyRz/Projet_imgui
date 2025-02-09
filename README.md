# imgui-template

organisation / tâches : 

Pièces 2
-> pour chaque pièce coder ses déplacements 
-> 

Autres 1
-> pouvoir sélectionner une pièce et mettre en évidence la case -> ok
-> pouvoir déplacer les pièces

PROCHAINEMENT : 
1)  selected a case -> ok
2)  deselected a case -> ok
3)  pareil mais que pour les cases avec pièces ->>>>> coder une struct selected Piece ->>>>>>>> FANNYYYYYYYYY

4) création des types des pièces avec héritage ->>>>> JUSTIIIIIIIIIINE -> ok
5) positionPossible.hpp -> move():permet juste de bouger ton pion en lui donnant une case + bouge le tableau      position_piece
                        -> fonction qui prend en entrée une pièce et qui donne un tableau avec les positions possibles
                        -> fonction qui dit si un ennemi sur le chemin, on le mange
                        -> fonction qui dit si un ami est sur le chemin, on agit en conséquence ->> OU on fait juste une fonction: si il y a une piece on fait....
                        -> fonction qui dit la position est en dehors du tableau 

Pour le cavalier : on peut noter les chemins possibles exemples {-2,-1} et après on part de là

CHANGEMENT : 

il faut refaire notre initialisation de plateau avec un enum pour pouvoir gérer la suite, en disant c'est ce type alors ... sinon pour l'instant c'est trop galère