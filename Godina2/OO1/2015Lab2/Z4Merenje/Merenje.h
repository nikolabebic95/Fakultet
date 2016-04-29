#ifndef _merenje_h_
#define _merenje_h_

class Merenje {
private:
	double temperatura_;
	int vreme_;


public:
	Merenje(double temperatura, int vreme) : temperatura_(temperatura), vreme_(vreme) {}

	double getTemperatura() const { return temperatura_; }
	int getVreme() const { return vreme_; }
};

#endif