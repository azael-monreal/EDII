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
	float promDp;
	MUN cabMun;
	struct nodoEdo* sigEdo;
} * EDO;

void calcDpProm (EDO estados)
{
	MUN municipio;
	int muns;
	float dpT;
	for (;estados;estados = estados->sigEdo) {
		municipio = estados->cabMun;
		muns = 0;
		dpT = 0;
		for (;municipio;municipio = municipio->sigMun) {
			muns++;
			dpT += municipio->dpMun;
		}
		estados->promDp = dpT/muns;
	}
}
