typedef struct nodoMun {
	char nomMun[25];
	float egMun;
	float pobMun;
	float dpMun;
	struct nodoMun* sigMun;
} * MUN;
typedef struct nodoEdo {
	char nomEdo[25];
	float egEdo;
	float pobEdo;
	float dpEdo;
	float promEg;
	MUN cabMun;
	struct nodoEdo* sigEdo;
} * EDO;

void calcEgProm (EDO estado)
{
	MUN municipio;
	int muns;
	float egT;
	if (estado) {
		municipio = estado->cabMun;
		muns = 0;
		for (; municipio; municipio = municipio->sigMun) {
			muns++;
			egT += municipio->egMun;
		}
		estado->promEg = egT / muns;
		calcEgProm (estado->sigEdo);
	}
}
