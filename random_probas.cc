#include <iostream>
#include <random>

using namespace std;

static default_random_engine e ;// pour contexte projet

// programme principal sous forme d'une boucle infinie

int main(void)
{ 
	int seq_duration(50);  // petite valeur pour constater que la série est la même
	
	while(true)            // simule la lecture d'un nouveau fichier
	{
		int n;
		cin  >> n ;  // permet de faire une pause et de quitter ce programme de test

		if(n == 0) break;  // fin
		
		e.seed(1);         // reset sequence de nombres aléatoires
		
		double p(0.1);         // probabilité dans [0, 1]
		bernoulli_distribution b(p);
		
		for(int i(0) ; i< seq_duration ; ++i)
			cout << b(e) ; // affiche une suite de 0 et de 1
		
		cout << endl;
	}
	return EXIT_SUCCESS;
}

