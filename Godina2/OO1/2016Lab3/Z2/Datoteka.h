#ifndef _datoteka_h_
#define _datoteka_h_

#include <string>

using namespace std;

class Datoteka {
private:
	string ime_;
	int velicina_;
	Datoteka *roditelj_ = nullptr;

protected:
	virtual string naziv() const {
		if (roditelj_) {
			return roditelj_->naziv() + "/" + ime_;
		}
		else {
			return ime_;
		}
	}

	void povecajVelicinu(int razlika) {
		velicina_ += razlika;
	}

	virtual void pisi(ostream &os) const {
		os << naziv();
	}

public:
	Datoteka(string ime, int velicina): ime_(ime), velicina_(velicina) {}

	int velicina() const {
		return velicina_;
	}

	void roditelj(Datoteka *roditelj) {
		roditelj_ = roditelj;
	}

	virtual Datoteka *kopiraj() const {
		return new Datoteka(*this);
	}

	friend ostream &operator<<(ostream &os, const Datoteka &d) {
		d.pisi(os);
		return os;
	}

	string ime() const {
		return ime_;
	}

	virtual ~Datoteka() {}
};

#endif
