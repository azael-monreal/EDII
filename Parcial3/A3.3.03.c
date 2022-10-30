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

float calcDpPromAux (MUN municipios);

void calcDpProm (EDO estados)
{
	for (; estados; estados = estados->sigEdo)
		estados->promDp = calcDpPromAux (estados->cabMun);
}

float calcDpPromAux (MUN municipios)
{
	int muns = 0;
	float dpT = 0;
	for (; municipios; municipios = municipios->sigMun) {
		muns++;
		dpT += municipios->dpMun;
	}
	return dpT / muns;
}
