/*Program oblicza liczbe PI metoda Monte Carlo  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double LosujWsp();
long LiczbaPktWKole(long wylosowanePkt);
float PoliczPi (long pktWKole,  long wylosowanePkt);
void ZapiszDoPliku (int *iloscLiczb, float *Pi, int Roz);
long IloscWylosowanychLiczb();
int IleLiczbZapisac();

int main()
{
	srand(time(NULL));
	long wylosowanePkt = IloscWylosowanychLiczb();
	long pktWKole = LiczbaPktWKole(wylosowanePkt);
	float pi = PoliczPi (pktWKole, wylosowanePkt);
	printf("\nPi = %f", pi);

	return 0;
}

long IloscWylosowanychLiczb()
{
	long iloscWylosowanychLiczb;
	printf("Ile liczb chcesz wylosowac? ");
	int czyLiczba = scanf("%li", &iloscWylosowanychLiczb);
	if(czyLiczba != 1)
	{
		printf("Nieprawidlowe dane");
		exit(EXIT_FAILURE);
	}
	putchar('\n');
	return iloscWylosowanychLiczb;
}

int IleLiczbZapisac()
{
	int iloscZapisanychLiczb;
	printf("Co ile liczb program ma zapisywac dane do pliku? ");
	int czyLiczba = scanf("%d", &iloscZapisanychLiczb);
	if(czyLiczba != 1)
	{
		printf("Nieprawidlowe dane");
		exit(EXIT_FAILURE);
	}
	putchar('\n');

	return iloscZapisanychLiczb;
}

double LosujWsp()
{
	return ((double)rand() / (RAND_MAX));
}

long LiczbaPktWKole(long wylosowanePkt)
{
	long i;
	long pktWKole = 0;
	int iloscLiczbWPliku = IleLiczbZapisac();
	long Roz = wylosowanePkt/(long)iloscLiczbWPliku;
	int iloscLiczb[Roz];
	float Pi[Roz];
	long j = 0;
	for(i = 1; i <= wylosowanePkt; i++)
	{
		double x = LosujWsp();
		double y = LosujWsp();
		if((x*x + y*y) <= 1) pktWKole++;
		if(i%iloscLiczbWPliku == 0 )
		{
			iloscLiczb[j] = i;
			Pi[j] = 4*(float)pktWKole/i;
			j++;
		}
	}

	printf("N1 = %li", pktWKole);

	ZapiszDoPliku (iloscLiczb, Pi, Roz);

	return pktWKole;

}

float PoliczPi (long pktWKole, long wylosowanePkt)
{
	float pi = ((float)(4*pktWKole)/(wylosowanePkt));

	return pi;
}

void ZapiszDoPliku (int *iloscLiczb, float *Pi, int Roz)
{
	FILE * fp;
	if((fp = fopen("wyniki.txt", "w")) == NULL)
	{
		printf("Nie moge otworzyc pliku");
		exit(EXIT_FAILURE);
	}
	int i;
	for(i = 0; i < Roz; i++)
	{
		fprintf(fp, "N = %d, ", iloscLiczb[i]);
		fprintf(fp, "Pi = %f\n", Pi[i]);
	}
	fclose(fp);
}

