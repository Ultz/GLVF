#include <glvf.h>
#include "../Platform.h"

class GlfwPlatform : public Platform {
public:
	bool isMultiInstance();
	Instance* createInstance();
};