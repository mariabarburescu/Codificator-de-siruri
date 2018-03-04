#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//FUNCTIE PENTRU CITIRE

int citire(char *sir[])
{
	unsigned int i, nr = 0;
	char x[50];

	for (i = 0; i < 5; i++)
	{
		nr++;
		scanf("%s", x);
		printf("%s\n", x);
		sir[i] = malloc((strlen(x)+1) * sizeof(char));
		strcpy(sir[i],x);

		if (strcmp(x, "END") == 0)
			break;
	}

	return nr;
}

//FUNCTIE PENTRU A INDENTIFICA CE TIP DE TERMEN ESTE

int identificare(char *x)
{
	int i=0;

//Daca lungimea sa este de 1, verificam daca este caracter sau numar
	if (strlen(x) == 1)
	{
		if ( x[0] < '1' || x[0] > '9' )
//Daca este caracter returneaza 2
			return 2;
		else
//Daca este numar returneaza 3
			return 3;
	}

	else
	{
//Verificam daca este numar
		if (x[i]=='-')
			i++;
		for (; i < strlen(x); i++)
			if (x[i] < '1' || x[i] > '9')
//Daca nu este numar, inseamna ca este cuvant si returneaza 1
				return 1;
	}
//Daca este numar returneaza 3
	return 3;
}

//FUNCTII PENTRU CUVINTE

//Functie pentru aflarea celui mai mare divizor comun
int cmmd(int a)
{
	int i;

	for (i=a/2; i>=1; i--)
		if (a%i == 0)
			return i;
}

//Functie care verifica daca exista macar un numar in cuvant

int existanr(char *x) 
{
	int i;

	for (i=0; i < strlen(x); i++)
		if (x[i] >= '0' && x[i] <= '9')
			return 1;
	return 0;
}

//Functie care prelucreaza cuvantul

char * modifcuv(char *x) 
{
	char cop[50], aux;
	int n, i;

	memset(cop, '\0', 50); //initializare
	n=cmmd(strlen(x));
	strncpy(cop,x,n); //copiem primele n caractere din x in cop
	strcpy(x,x+n); //stergem primele n caractere din x

	if (existanr(x) == 1 || existanr(cop) == 1) //verificam daca exista numere in cuvant
		for (i=0; i<strlen(x)/2; i++) //inversam ordinea caracterelor
		{
			aux=x[i];
			x[i]=x[strlen(x)-1-i];
			x[strlen(x)-1-i]=aux;
		}

	strcat(x,cop); //adaugam la sfarsitul cuvantului primele sale n caractere
	return x;
}

//FUNCTII PENTRU CARACTERE

//Functie care returneaza caracterul cu cele mai putine aparitii

char cmpa(char *a) 
{
	int i, fr[95], min = 95;

	for (i = 0; i <= 94; i++) //Initializam vectorul de frecventa cu 0
		fr[i] = 0;

	for (i = 0; i < strlen(a); i++) //Monitorizam aparitiile caracterelor cu ajutorul vectorului de frecventa
		fr[a[i] - 32]++;

	for (i = 0; i < strlen(a); i++) //Aflam frecventa minima
		if ( fr[a[i] - 32] < min )
			min = fr[a[i] - 32];

	for (i = 0; i < strlen(a); i++) //Returnam caracterul cu aparitia minima
		if ( fr[a[i] - 32] == min )
			return a[i];
}

//Functie care returneaza caracterul cu cele mai multe aparitii 

char cmma(char *a) 
{
	int i, fr[95], Max = 0;
	
	for (i = 0; i <= 94; i++) //Initializam vectorul de frecventa cu 0
		fr[i] = 0;

	for (i = 0; i < strlen(a); i++) //Monitorizam aparitiile caracterelor cu ajutorul vectorului de frecventa
		fr[a[i] - 32]++;

	for (i = 0; i < strlen(a); i++) //Aflam frecventa maxima
		if ( fr[a[i] - 32] > Max )
			Max = fr[a[i] - 32];

	for (i = 0; i < strlen(a); i++) //Returnam caracterul cu aparitia maxima
		if ( fr[a[i] - 32] == Max )
			return a[i];	
}

//FUNCTII PENTRU NUMERE

//Functie pentru codificarea numerelor pozitive

char * nrpoz(char *x)
{
	char *cop = malloc(50 * sizeof(char));
	char aux;
	int i, j, k;

	strcpy(cop, x); //Facem o copie a lui x

	for (i = 0; i < strlen(x)-1; i++) //Acest for ne monitorizeaza numarul de rotiri
	{
		for (j = 0; j < strlen(x)-1; j++) //Cu acest for rotim numarul
		{
			aux = cop[j];
			cop[j] = cop[j+1];
			cop[j+1] = aux;
		}

		k = 0; //ne indica pozitia in vector

		while (x[k] == cop[k]) //Crestem variabila in cazul in care noul numar incepe cu aceleasi caractere ca si cel initial
			k++;

		if (cop[k] > x[k]) //Comparam noul numar obtinut cu cel initial si il memoram in x pe cel mai mare
			strcpy(x, cop);
	}
	return x;
}

//Functie pentru codificarea numerelor negative

char * nrneg(char *x)
{
	char *cop = malloc(50 * sizeof(char));
	char aux;
	int i, j, k;

	strcpy(x, x+1); //Stergem caracterul '-' din numar
	strcpy(cop, x); //Facem o copie a lui x

	for (i = 0; i < strlen(x); i++) //Acest for ne monitorizeaza numarul de rotiri
	{
		for (j = 0; j < strlen(x)-1; j++) //Cu acest for rotim numarul
		{
			aux = cop[j];
			cop[j] = cop[j+1];
			cop[j+1] = aux;
		}

		k = 0; //ne indica pozitia in vector

		while (x[k] == cop[k]) //Crestem variabila in cazul in care noul numar incepe cu aceleasi caractere ca si cel initial
			k++;

		if (cop[k] < x[k]) //Comparam noul numar obtinut cu cel initial si il memoram in x pe cel mai mare
			strcpy(x, cop);

	}
	return x;
}

//Functie pentru a putea identifica daca numarul este pozitiv sau negativ

char * identif_numar(char *x)
{
	if (x[0] == '-')
		return nrneg(x);

	return nrpoz(x);
}

//Declaram noua noastra structura

struct rearanjare{
	char *part;
	double complex;
};

//Functie pentru sortare in functie de complexitate

void sort(struct rearanjare *v, int l)
{
	int i, j, aux;
	char auxi[50];

	for (i = 0; i < (l-1); i++)
	{
		for (j = i+1; j < l; j++)
			if ((v+i) -> complex < (v+j) -> complex) //Comparam complexitatea si le interschimbam valorile
			{
				aux = (v+i) -> complex;
				(v+i) -> complex = (v+j) -> complex;
				(v+j) -> complex = aux;
				strcpy(auxi, (v+i) -> part);
				strcpy((v+i) -> part, (v+j) -> part);
				strcpy((v+j) -> part, auxi);
			}
	}
	return;
}

//Functie pentru sortarea lexicografica

void sort_lex(struct rearanjare *v, int l)
{
	int i, j, aux;
	char auxi[50];
	for (i = 0; i < (l-1); i++)
	{
		for (j = 0; j < l; j++)
			if ((v+i) -> complex == (v+j) -> complex) //Daca complexitatile sunt egale le vom ordona lexicografic
				if (strcmp((v+i) -> part, (v+j) -> part) > 0)
				{
					aux = (v+i) -> complex;
					(v+i) -> complex = (v+j) -> complex;
					(v+j) -> complex = aux;
					strcpy(auxi, (v+i) -> part);
					strcpy((v+i) -> part, (v+j) -> part);
					strcpy((v+j) -> part, auxi);
				}
	}
	return;
}

int main()
{
	int i=0, j, nrcar=0, procent=0, totalcar=0, bucati=0, nrtermeni=0, cuvinte=0, caractere=0, numere=0;
	char *s=calloc(5000, sizeof(char)); //Sirul in care memoram termenii prelucrati
	char *s2=calloc(5000, sizeof(char)); //Sirul in care memoram termenii impartiti in n parti si sortati dupa complexitate si lexicografic cand este cazul
	char **sir=malloc(100 * sizeof(char *)); //Sirul in care citim termenii
	char x[50], n[2], apmax, apmin;
	struct rearanjare *v; //Structura in care il impartim pe s in n bucati si memoram complexitatea fiecarei bucati

	do{
		nrtermeni++; //Crestem numarul de termeni cititi
		scanf("%s", x); //Citim un termen
		sir[i] = malloc((strlen(x)+1) * sizeof(char)); //Alocam memorie
		strcpy(sir[i],x); //Il copiem pe x

		if (strcmp(x, "END") == 0) //Daca am citit "END" ne vom opri din citit
		{
			numere--; //Scadem numarul de termeni care sunt numere, deoarece acesta a crescut si in momentul in care l-am citit pe n
			strcpy(n,sir[i-1]); //Il memoram pe n intr-o alta variabila
			
			break; //Iesim din structura repetitiva
		}

		if (identificare(sir[i]) == 1) //Monitorizam cate cuvinte am citit
			cuvinte++;
		else
			if (identificare(sir[i]) == 2) //Monitorizam cate caractere am citit
				caractere++;
			else
				numere++; //Monitorizam cate numere am citit
		i++;

	}while (strcmp(x, "END") != 0);

	for (i = 0; i < nrtermeni-2; i++) //In aceasta structura repetitiva vom prelucra termenii si ii vom copia in s
	{
		if (identificare(sir[i]) == 1) //Verificam daca e cuvant
		{
			strcat(s,modifcuv(sir[i])); //Concatenam cuvantul prelucrat
		}
		else
		{
			if (identificare(sir[i]) == 2) //Verificam daca e caracter
			{
				if (strlen(s) > 0)
				{
					apmax=cmma(s); //Aflam caracterul cu numarul maxim de aparitii din s
					apmin=cmpa(s); //Aflam caracterul cu numarul minim de aparitii din s
					strncat(s, &apmax, 1); //Concatenam caracterul cu numarul maxim de aparitii din s
					strcat(s, sir[i]); //Concatenam caracterul
					strncat(s, &apmin, 1); //Concatenam caracterul cu numarul minim de aparitii din s
				}
				else
					strcat(s, sir[i]); // Daca nu avem nici un termen in sir, concatenam doar caracterul
			}
			else //Daca merge pe aceasta ramura, inseamna ca este numar
				strcat(s,identif_numar(sir[i])); //Concatenam numarul prelucrat
		}
	}

	printf("%d %d %d\n%s\n", cuvinte, caractere, numere, s); //Afisam numarul de cuvinte, caractere, numere si sirul s care contine termenii codificati

	bucati = atoi(n); //Convertim stringul n in int
	v = calloc(bucati, sizeof(struct rearanjare)); //Alocam memorie structurii
	totalcar = strlen(s); //Aflam numarul total de caractere din s
	nrcar = totalcar/bucati; //Aflam numarul de caractere dintr-o componenta
	procent = totalcar % bucati; //Aflam numarul de caractere ramase si care trebuiesc adaugate la ultima componenta

	for (i = 0; i < (bucati-1); i++) //Impartim sirul in componente (pana la penultima componenta)
	{
		(v+i) -> part = calloc((nrcar+1), sizeof(char)); //Alocam memorie pentru o componenta
		strncpy((v+i) -> part, s, nrcar); //Adaugam o componenta in structura
		strcpy(s, s+nrcar); //Stergem din s componenta pe care am adaugat-o in structura
	}

	(v+i) -> part = calloc((procent+nrcar+1), sizeof(char)); //Alocam memorie ultimei componenta
	strcpy((v+i) -> part, s); //Adaugam ultima componenta
	
	for (i = 0; i < bucati; i++) //Aflam complexitatea fiecarei componente
	{
		(v+i) -> complex = 0; //Initializam

		for (j = 0; j < strlen((v+i) -> part); j++)

			(v+i) -> complex = (v+i) -> complex + ((v+i) -> part)[j];

		(v+i) -> complex = (v+i) -> complex / strlen((v+i) -> part);
	}
	sort(v, bucati); //Facem sortarea dupa complexitate
	sort_lex(v, bucati); //Facem sortarea lexicografica

	for (i = 0; i < (bucati/2); i++) //Concatenam componentele intr-un alt sir (s2)
	{
		strcat(s2, (v+i) -> part);
		strcat(s2, (v+bucati-i-1) -> part);
	}

	if (bucati%2 != 0) //Daca numarul de componente este impar, concatenam si componenta din mijloc
		strcat(s2, (v+i) -> part);

	printf("%s\n", s2); //Afisam sirul s2
	return 0;
}
