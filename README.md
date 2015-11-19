# Decrand_Gerbault
Projet Ruzzle TP Algo avance
/*******RUZZLE*******/
Le dossier contient:
		-un repertoire bin contenant l'executable et les fichiers .txt
		-un repertoire src contenant les sources .c
		-un repertoire include contenant les fichiers entetes .h
		-un repertoire doc contenant les ressources doxygen
		-un repertoire /src/tests contenant les sources .c des tests unitaires
		-un repertoire tests contenant les executables des tests unitaires

/***Utilisation du makefile***/
Executer la commande make depuis le dossier dans une console (mingw32-make pour windows)
->Le programme est compatible actuellement sur mac,linux et windows

/*****Etat des fonctions*****/
	/***dico.c***/
	void push(int x,int y,t_coord pile[t_max],int *sommet);->Fonctionne
	void depush(int *sommet);->Fonctionne
	void initpile(int *sommet);->Fonctionne
	int sommetpile_x(t_coord pile[t_max],int *sommet);->Fonctionne
	int sommetpile_y(t_coord pile[t_max],int *sommet);->Fonctionne
	int search_redondance(int x,int y,t_coord pile[t_max],int *sommet);->Fonctionne
	void chemin(t_lettre grille[N][M],char lettre,int *k,t_coord chemin_mot_pile[t_max],t_coord redondance_lettre_pile[t_max],int *adr_chemin_mot_sommet,int *redondance_lettre_sommet)->Fonctionne
	int recherche_mot_grille(t_valeurmot *mot_dico,t_lettre grille[N][M]);->Fonctionne
	liste_mots_trouve(t_lettre grille[N][M]);->Fonctionne
	void trier_score_decroissant(void);->Fonctionne
	
	
	/***grille.c***/
	void creation_grille(t_lettre grille[N][M]);->Fonctionne
	void underscore();->Fonctionne
	void affichage_grille(t_lettre grille[N][M]);->Fonctionne
	
	
	/***tests***/
	void push(int x,int y,t_coord pile[t_max],int *sommet);->Fonctionne/\tests non effectue
	void depush(int *sommet);->Fonctionne/\tests non effectue
	void initpile(int *sommet);->Fonctionne/\tests non effectue
	int sommetpile_x(t_coord pile[t_max],int *sommet);->Fonctionne/\tests non effectue
	int sommetpile_y(t_coord pile[t_max],int *sommet);->Fonctionne/\tests non effectue
	int search_redondance(int x,int y,t_coord pile[t_max],int *sommet);
	void chemin(t_lettre grille[N][M],char lettre,int *k,t_coord chemin_mot_pile[t_max],t_coord redondance_lettre_pile[t_max],int *adr_chemin_mot_sommet,int *redondance_lettre_sommet)->Fonctionne
	int recherche_mot_grille(t_valeurmot *mot_dico,t_lettre grille[N][M]);->Fonctionne/\tests non effectue
	liste_mots_trouve(t_lettre grille[N][M]);->Fonctionne/\tests non effectue
	void trier_score_decroissant(void);->Fonctionne/\tests non effectue
	void creation_grille(t_lettre grille[N][M]);->Fonctionne/\tests non effectue
	void underscore();->Fonctionne/\tests non effectue
	void affichage_grille(t_lettre grille[N][M]);->Fonctionne/\tests non effectue