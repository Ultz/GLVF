#include <glvf.h>
#include "Instance.h"

class Platform {
public:
	virtual bool isMultiInstance() = 0;
	virtual Instance* createInstance() = 0;
};