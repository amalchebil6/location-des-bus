#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct DATE {
    int JOUR;
    int MOIS;
    int ANNEE;
} date;
typedef struct PRODUIT{
    int ID; //the unique identifier of a bus must consist of 6 digits between 100000 and 999999
    char NOM[20]; //the name of a produit must not contain any numbers
    float PRIX;//the price of a bus must be positive
    char DESC[30];//the description of a bus is a  string without spaces
    date DE;
} produit;
typedef struct PRODUITRES{
    int ID; //the unique identifier of a bus must consist of 6 digits between 100000 and 999999
    date Dres;
} produitres;

void Ajouter(){
    produit b;
    FILE *f=fopen("stock.txt","a");

    if (f == NULL)  {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    printf("\nAjout d\'un nouveau bus \n\n");

    do{
            printf("Donnez l\'identifiant du bus a ajouter(6 chiffres): ");
            fflush(stdin);
            scanf("%d", &b.ID);
    }while(b.ID<100000 || b.ID>999999);


    do{
            printf("Donnez le nom du bus a ajouter (string without digits) : ");
            fflush(stdin);
            gets(b.NOM);
    }while(chaine_sans_chiffre(b.NOM)==0);

    do {
            printf("Donnez le prix de reservation du bus a ajouter(prix > 0) : ");
            fflush(stdin);
            scanf("%f", &b.PRIX);
    }while(b.PRIX<0);


    do {
        printf("Donnez la description du bus a ajouter (string without spaces) : ");
        fflush(stdin);
        gets(b.DESC);
    }while(sans_epace(b.DESC)==0);

    do {
            printf("Donnez date de fabrication du bus a ajouter (JJ MM AAAA) :");
            scanf("%d%d%d",&b.DE.JOUR,&b.DE.MOIS,&b.DE.ANNEE);
    }while((b.DE.JOUR<0 || b.DE.JOUR>31 || b.DE.MOIS <0 || b.DE.MOIS>12 || b.DE.ANNEE<1000 || b.DE.ANNEE>9999 ) ||((b.DE.MOIS==2)&& b.DE.JOUR>28));
    fprintf(f,"%d %s %f %s %d/%d/%d\n",b.ID,b.NOM,b.PRIX,b.DESC,b.DE.JOUR,b.DE.MOIS,b.DE.ANNEE);
    fclose(f);
    printf("L\' operation d\'ajout effectuee avec succes !\n\n");
    application();
}
void Supprimer(){
    int x,test=1;
    FILE *f;
    FILE *nf;
  	f=fopen("stock.txt","a+");
  	nf=fopen("tmpfile.txt","w");
    if (f == NULL || nf == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
  	do{
            printf("Donner l'identifiant de bus a supprimer (6 chiffres) :");
            scanf("%d",&x);
    }while(x<100000 || x>999999);
    produit b;
  	while (fscanf(f,"%d %s %f %s %d/%d/%d\n",&b.ID,b.NOM,&b.PRIX,&b.DESC,&b.DE.JOUR,&b.DE.MOIS,&b.DE.ANNEE)!=EOF){

		if(b.ID!=x){
            fprintf(nf,"%d %s %f %s %d/%d/%d\n",b.ID,b.NOM,b.PRIX,b.DESC,b.DE.JOUR,b.DE.MOIS,b.DE.ANNEE);
            test=0;
		}
		else {
            test=1;
		}
    }
    if (test==0){
               	printf("Identifiant introuvable !");
    }
	fclose(nf);
	fclose(f);
	f=fopen("stock.txt","w");
	nf=fopen("tmpfile.txt","r");
	while (fscanf(nf,"%d %s %f %s %d/%d/%d\n",&b.ID,b.NOM,&b.PRIX,&b.DESC,&b.DE.JOUR,&b.DE.MOIS,&b.DE.ANNEE)!=EOF){
            fprintf(f,"%d %s %f %s %d/%d/%d\n",b.ID,b.NOM,b.PRIX,b.DESC,b.DE.JOUR,b.DE.MOIS,b.DE.ANNEE);

	}
	fclose(nf);
	fclose(f);
	if(test==1){
            printf("L\' operation de suppression effectuee avec succes !\n\n");

	}
	application();
}


void AfficherDesc(){
    int x;
    int test=0;
    produit bus;
    do {
            printf("Donner l'identifiant de bus pour voir son description (6 chiffres):");
            scanf("%d",&x);
    }while(x<100000 || x>999999);

    FILE *f=fopen("stock.txt","r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(0);
    }
    while (fscanf(f,"%d %s %f %s %d/%d/%d\n",&bus.ID,&bus.NOM,&bus.PRIX,&bus.DESC,&bus.DE.JOUR,&bus.DE.MOIS,&bus.DE.ANNEE)!=EOF){
        if(bus.ID == x){
            printf("\nLa description de bus d\'identifiant %d est : %s\n",x,bus.DESC);
            test=1;
         }
    }
    if(test==0){
        printf("Aucun produit avec cet identifiant !\n\n");
    }
    fclose(f);
    application();
    return 0;
}
void Afficherbus(){
    char line[256];

    printf("\nLes bus actuellement disponibles sont :\n\n");


    FILE *f=fopen("stock.txt","r");
    if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier");
    exit(1) ;
    }
    while (fgets(line, sizeof(line), f) != NULL) {
    printf("%s", line);
    }
    fclose(f);
    application();
  return 0;
}
void modifierbus( ){
    int choix,x,test=0;
  	do{
            printf("Donner l'identifiant de bus a modifier (6 chiffres) :");
            scanf("%d",&x);
    }while(x<100000 || x>999999);
    FILE *f=fopen("stock.txt","r");
    FILE *nf=fopen("tmpfile.txt","w+");
    if (f == NULL  || nf == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    produit bus;

	while (fscanf(f,"%d %s %f %s %d/%d/%d\n",&bus.ID,bus.NOM,&bus.PRIX,&bus.DESC,&bus.DE.JOUR,&bus.DE.MOIS,&bus.DE.ANNEE)!=EOF){
            if(bus.ID==x){
                printf("Produit avant modification :\n");
                printf("(1) nom :%s\n",bus.NOM);
                printf("(2) prix :%f\n",bus.PRIX);
                printf("(3) description :%s\n",bus.DESC);
                printf("(4) date de fabrication de bus :%d/%d/%d\n",bus.DE.JOUR,bus.DE.MOIS,bus.DE.ANNEE);
                test=1;

                do{
                        printf("Merci de choisir le choix de modification: ");
                        scanf("%d",&choix);
                        printf("\n");
                }while(choix<0 || choix >6);
                switch(choix){
                        case 1:
                            do{
                                printf("Saisir le nouveau nom :");
                                fflush(stdin);
                                gets(bus.NOM);
                            }while(chaine_sans_chiffre(bus.NOM)==0);
                            break;
                        case 2:
                            do{
                                printf("Saisir le nouveau prix de location:");
                                fflush(stdin);
                                scanf("%f", &bus.PRIX);
                            }while(bus.PRIX<0);
                            break;
                        case 3:
                            do {
                                    printf("Saisir la nouvelle description (string without spaces) : ");
                                    fflush(stdin);
                                    gets(bus.DESC);
                            }while(sans_epace(bus.DESC)==0);
                            break;
                        case 4:
                            do{
                                    printf("Saisir la nouvelle date de fabrication (JJ MM AAAA) :");
                                    fflush(stdin);
                                    scanf("%d",&bus.DE.JOUR);
                                    scanf("%d",&bus.DE.MOIS);
                                    scanf("%d",&bus.DE.ANNEE);
                            }while((bus.DE.JOUR<0 || bus.DE.JOUR>31 || bus.DE.MOIS <0 || bus.DE.MOIS>12 || bus.DE.ANNEE<1000 || bus.DE.ANNEE>9999 ) ||((bus.DE.MOIS==2)&& bus.DE.JOUR>28));
                            break;
                        case 0:
                            exit(1);
                        }
            }
            fprintf(nf,"%d %s %f %s %d/%d/%d %d/%d/%d\n",bus.ID,bus.NOM, bus.PRIX,bus.DESC,bus.DE.JOUR,bus.DE.MOIS,bus.DE.ANNEE);
    }
    if(test==0){
        printf("Aucun bus avec ce identifiant !\n\n");
    }

	fclose(nf);
	fclose(f);
    f=fopen("stock.txt","w+");
	nf=fopen("tmpfile.txt","r");
	if(f==NULL || nf ==NULL){
	    printf("Erreur lors de l'ouverture du fichier");
		exit(1);
	}
	while (fscanf(nf,"%d %s %f %s %d/%d/%d\n",&bus.ID,&bus.NOM,&bus.PRIX,bus.DESC,&bus.DE.JOUR,&bus.DE.MOIS,&bus.DE.ANNEE)!=EOF){
            fprintf(f,"%d %s %f %s %d/%d/%d\n",&bus.ID,&bus.NOM,&bus.PRIX,&bus.DESC,&bus.DE.JOUR,&bus.DE.MOIS,&bus.DE.ANNEE);
    }
	fclose(nf);
	fclose(f);
	if(test==1){
            printf("L\' operation de modification effectuee avec succes !\n\n");

	}

	application();
}

void Recherche(){
    int x,test=0;
  	do{
            printf("Donner l'identifiant de bus a chercher (6 chiffres) :");
            scanf("%d",&x);
    }while(x<100000 || x>999999);
    FILE *f=fopen("stock.txt","r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(0);
    }
    produit bus;
    while (fscanf(f,"%d %s %f %s %d/%d/%d\n",&bus.ID,bus.NOM,&bus.PRIX,&bus.DESC,&bus.DE.JOUR,&bus.DE.MOIS,&bus.DE.ANNEE)!=EOF){

			if(bus.ID==x){
                printf("Identifiant : %d\nNom : %s\nPrix : %f\nDescription : %s\nDate de fabrication : %d/%d/%d\n ",bus.ID,bus.NOM,bus.PRIX,bus.DESC,bus.DE.JOUR,bus.DE.MOIS,bus.DE.ANNEE);
                test=1;
	   	   }
    }
    if(test==0){
        printf("Aucun bus avec cet identifiant !\n\n");
    }
	fclose(f);
	application();
}


void reservation(){
    produitres x,bus;
    Afficherbusres();
    int test=1;
    do{
            printf("Donner l'identifiant de bus a reserver (6 chiffres) :");
            scanf("%d",&x.ID);
            printf("Donnez date de reservation du bus (JJ MM AAAA) :");
            scanf("%d%d%d",&x.Dres.JOUR,&x.Dres.MOIS,&x.Dres.ANNEE);
    }while(x.ID<100000 || x.ID>999999 || x.Dres.JOUR<0 || x.Dres.JOUR>31 || x.Dres.MOIS<0 || x.Dres.MOIS>12 || x.Dres.ANNEE<2023 ||(x.Dres.MOIS==2 && x.Dres.JOUR>28)) ;
    FILE *f=fopen("reservation.txt","a+");
    if (f == NULL ) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
  	while (fscanf(f,"%d %d/%d/%d\n",&bus.ID,&bus.Dres.JOUR,&bus.Dres.MOIS,&bus.Dres.ANNEE)!=EOF){

		if(bus.ID == x.ID && bus.Dres.JOUR == x.Dres.JOUR && bus.Dres.MOIS == x.Dres.MOIS && bus.Dres.ANNEE == x.Dres.ANNEE){
            test=0;
		}
    }
    if (test==0){
               	printf("ce bus est reserver a cette date!");
    }
	fclose(f);
	if(test==1){
            FILE *f=fopen("reservation.txt","a+");
            if (f == NULL)  {
                printf("Erreur lors de l'ouverture du fichier");
                exit(1);
            }
            fprintf(f,"%d %d/%d/%d\n",x.ID,x.Dres.JOUR,x.Dres.MOIS,x.Dres.ANNEE);
            fclose(f);
            printf("L\' operation de reservation effectuee avec succes !\n\n");
            }
            printf("%d\n",test);
            application();

        }
void Annulerreservation(){
    produitres x;
    int test=0;
    FILE *f;
    FILE *nf;
    f=fopen("reservation.txt","a+");
  	nf=fopen("tmpfile.txt","w");
    if (f == NULL || nf == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
  	do{
            printf("Donner l'identifiant de bus (6 chiffres) :");
            scanf("%d",&x.ID);
            printf("Donnez date de reservation du bus (JJ MM AAAA) :");
            scanf("%d%d%d",&x.Dres.JOUR,&x.Dres.MOIS,&x.Dres.ANNEE);
    }while(x.ID<100000 || x.ID>999999 || x.Dres.JOUR<0 || x.Dres.JOUR>31 || x.Dres.MOIS<0 || x.Dres.MOIS>12 || x.Dres.ANNEE<2024) ;
    produitres b;
  	while (fscanf(f,"%d %d/%d/%d\n",&b.ID,&b.Dres.JOUR,&b.Dres.MOIS,&b.Dres.ANNEE)!=EOF){

		if(b.ID!=x.ID || b.Dres.JOUR!=x.Dres.JOUR || b.Dres.MOIS!=x.Dres.MOIS || b.Dres.ANNEE!=x.Dres.ANNEE ){
            fprintf(nf,"%d %d/%d/%d\n",b.ID,b.Dres.JOUR,b.Dres.MOIS,b.Dres.ANNEE);
		}
		else {
            test=1;
		}
    }
    if (test==0){
               	printf("Reservation introuvable !");
    }
	fclose(nf);
	fclose(f);
	f=fopen("reservation.txt","w");
	nf=fopen("tmpfile.txt","r");
	while (fscanf(nf,"%d %d/%d/%d\n",&b.ID,&b.Dres.JOUR,&b.Dres.MOIS,&b.Dres.ANNEE)!=EOF){
            fprintf(f,"%d %d/%d/%d\n",b.ID,b.Dres.JOUR,b.Dres.MOIS,b.Dres.ANNEE);
	}
	fclose(nf);
	fclose(f);
	if(test==1){
            printf("L\' operation d'annulation faite avec succes !\n\n");

	}
	application();

}
void Afficherbusres(){
    char line[256];

    printf("\nLes bus actuellement disponibles sont :\n\n");


    FILE *f=fopen("stock.txt","r");
    if (f == NULL) {
    printf("Erreur lors de l'ouverture du fichier");
    exit(1) ;
    }
    while (fgets(line, sizeof(line), f) != NULL) {
    printf("%s", line);
    }
    fclose(f);
  return 0;
}

int main(int argc, char *argv[]) {
    application();
    return 0;

}
void application(){
		printf("\t\t\t\t __________________________________________________\n");
		printf("\t\t\t\t|        -------- Bienvenue --------               | \n");
		printf("\t\t\t\t| 1  : Gestion du bus.                             | \n");
		printf("\t\t\t\t| 2  : Afficher les bus .                          | \n");
		printf("\t\t\t\t| 3  : creer une reservation.                      | \n");
		printf("\t\t\t\t| 4  : annuler une reservation.                    | \n");
		printf("\t\t\t\t| 0  : Quitter .                                   | \n");
		printf("\t\t\t\t|__________________________________________________| \n");
		printf("\n");
        int c;
		do {
                printf("Merci de choisir votre commande : ");
                scanf("%d",&c);
        }while(c<0 || c>4);
        commande(c);

}




void commande(int x){

	switch(x){
			case 1:
				Gestionbus();
				break;
			case 2:
				Afficherbus();
				break;
			case 3:
			    reservation();
				break;
			case 4:
			    Annulerreservation();
				break;
			case 0:
			    exit(1);
            default :
                printf("Erreur");
                return 0;
		}
	}
	void Gestionbus(){
	    int x;
		printf("\t\t\t\t _______________________________________________  \n");
		printf("\t\t\t\t|        -------- Bienvenue --------            | \n");
		printf("\t\t\t\t| 1  : Ajouter un bus.                          | \n");
		printf("\t\t\t\t| 2  : Afficher la description d\'un bus.        | \n");
		printf("\t\t\t\t| 3  : Supprimer un bus.                        | \n");
		printf("\t\t\t\t| 4  : Modifier un bus.                         | \n");
		printf("\t\t\t\t| 5  : Recherche d\'un bus.                      | \n");
		printf("\t\t\t\t| 0  : Retour .                                 | \n");
		printf("\t\t\t\t|_______________________________________________| \n");
		printf("\n");
	    do{
		printf("Merci de choisir votre choix : ");
		scanf("%d",&x);
		}while(x<0 || x>5);
        choix(x);
		return 0;
	}



void choix(int x ){
	switch(x){
			case 1:
				Ajouter();
				break;
			case 2:
				AfficherDesc();
				break;
			case 3:
				Supprimer();
				break;
			case 4:
				modifierbus();
				break;
			case 5:
				Recherche();
				break;
			case 0:
				application();
            default :
                printf("erreur");
                return 0;
		}
		return 0;
}
int sans_epace(char ch[30]){
    int i;
    int l=strlen(ch);
    for (i=0 ;i<l ;i++){
        if (ch[i]==' '){
            return 0;
        }
    }
    return 1;
}
int  chaine_sans_chiffre(char ch[20]){
    if (strpbrk(ch, "0123456789")){
            return 0;
    }
    else{
        return 1;
    }
    return 0;
}
