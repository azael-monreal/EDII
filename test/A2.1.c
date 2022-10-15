// typedef struct {
// 	int num;
// 	int den;
// } Fraction;

//  struct node {
// 	Fraction frac;
// 	struct node* next;
// };

typedef struct {
	int degre;
	float coef;
} Term;

 struct node {
	int degree;
	float coef;
	struct node* next;
} ;

typedef struct {
	int type;
	void* data;
} Generic;

 struct node {
	int type;
	void* data;
	struct node* next;
};

typedef struct nodo* Lista;

int main(void)
{
	struct node n;


	
	return 0;
} 


