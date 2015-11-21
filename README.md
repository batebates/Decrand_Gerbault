
###Projet Ruzzle TP Algo avance

##Contenu
		+un repertoire bin contenant l'executable et les fichiers .txt
		+un repertoire src contenant les sources .c
		+un repertoire include contenant les fichiers entetes .h
		+un repertoire doc contenant les ressources doxygen
		+un repertoire /src/tests contenant les sources .c des tests unitaires
		+un repertoire tests contenant les executables des tests unitaires

##Compilation
	Executer la commande make depuis le dossier dans une console (mingw32-make pour windows)
	->Le programme est compatible actuellement sur mac,linux et windows

##Execution
	Pour executer le programme,placer vous dans le fichier bin et executer le fichier ruzzle.exe depuis une invite de commande

##Etat des fonctions
#dico.c
	+push()->Fonctionne
	+depush()->Fonctionne
	+initpile();->Fonctionne
	+sommetpile();->Fonctionne
	+search_redondance();->Fonctionne
	+chemin()->Fonctionne
	+recherche_mot_grille();->Fonctionne
	+liste_mots_trouve();->Fonctionne
	+trier_score_decroissant();->Fonctionne
	
	
#grille.c
	+creation_grille();->Fonctionne
	+underscore();->Fonctionne
	+affichage_grille();->Fonctionne
	
	
