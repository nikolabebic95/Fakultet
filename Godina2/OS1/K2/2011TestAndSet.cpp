/*
 * U klasi Semaphore postoji privatni podatak član isLocked tipa int koji služi da obezbedi međusobno isključenje
 * pristupa strukturi semafora u višeprocesorskom operativnom sistemu. Ako je njegova vrednost 1, kod koji se 
 * izvršava na nekom procesoru je zaključao semafor za svoj isključivi pristup; ako je vrednost 0, pristup 
 * semaforu je slobodan. Korišćenjem operacije test_and_set() koja je implementirana korišćenjem odgovarajuće 
 * atomične instrukcije procesora, realozovati operaciju Semaphore::lock() koja treba da obezbedi međusobno 
 * isključenje pristupa strukturi semafora u višeprocesorskom operativnom sistemu, ali tako da bude efikasnija 
 * od dole date implementacije tako što ne poziva operaciju test_and_set ako je semafor već zaključan od strane 
 * drugog procesora, pošto ta operacija ima veće režijske troškove na magistrali računara.
 */

int test_and_set(int &value);

void Semaphore::oldLock() {
    while(test_and_set(this->isLocked));
}

void Semaphore::lock() {
    while(true){
        while(isLocked);
        if(!test_and_set(isLocked)) break;
    }
}
