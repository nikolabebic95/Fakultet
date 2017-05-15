#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

// Mora da vraca void * jer tako je definisano u pthread
// Mora da prima void * jer tako je definisano u pthread
// Ako ti ovo sto prima treba za nesto, prosledi pointer
// na bilo sta, pa kastuj posle u ono sto si prosledila
//
// A ako nit treba da vrati vrednost, moze ili da je upise u neku
// globalnu promenljivu (sto bih ja uradio), ali moze i da vrati
// pa da se u join-u procita.
//
// Evo ti i primer vracanja, tako sto u pthread_exit prosledis void*
void *f(void *unused) {
	sem_wait(&mutex);
	std::cout << "Output 1" << std::endl;
	sem_post(&mutex);
	char *ret = (char*)"End";
	pthread_exit(ret);
}

void *g(void *output) {
	sem_wait(&mutex);
	char *ispis = (char*) ono_sto_treba_da_ispise;
	std::cout << ispis << std::endl;
	sem_post(&mutex);
	pthread_exit(NULL);
}

int main() {
	sem_init(&mutex, 0, 1);

	pthread_t first;
	pthread_t second;

	pthread_create(&first, NULL, &f, NULL);

	char *param = (char*)"Output 2";

	pthread_create(&second, NULL, &g, param);

	char *ret;

	// Onda se ovde taj pointer primi tako sto
	// se prosledi adresa pointera koji zelimo da primimo
	// Mora da se kastuje na void**
	pthread_join(first,(void**)&ret);
	pthread_join(second,NULL);

	std::cout << ret << std::endl;

	sem_destroy(&mutex);

	pthread_exit(NULL);
}


