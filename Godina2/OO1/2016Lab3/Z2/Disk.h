#ifndef _disk_h_
#define _disk_h_

#include "Imenik.h"

class Disk {
private:
	Imenik i = Imenik("");

public:
	Imenik &imenik() {
		return i;
	}
};

#endif
