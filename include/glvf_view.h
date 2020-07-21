#include "glvf_core.h"
#include "glvf_rendering_api.h"
#include "glvf_features.h"

typedef enum {
	GLVF_BUFFER_KIND_DEPTH,
	GLVF_BUFFER_KIND_STENCIL,
	GLVF_FORCE_32_BIT = 2147483647
} GLVFBufferKind;

typedef enum {
	GLVF_DONT_CARE,
	GLVF_NONE,
	GLVF_COLOR_R8_G8_B8_A8,
	GLVF_COLOR_R5_G6_B5,
	GLVF_DEPTH_R16,
	GLVF_DEPTH_R24,
	GLVF_STENCIL_R8
} GLVFBits;

typedef struct {
	GLVFBufferKind buffer;
	GLVFBits preferredBits;
} GLVFBufferBits;


typedef struct {
	GLVFStructureType sType;
	GLVFRenderingApi api;
	int32_t numBufferBitPreferences;
	const GLVFBufferBits* pBufferBitPreferences;
	GLVFFeatureFlags enabledFeatures;
} GLVFViewCreateInfo;

GLVFResult glvfCreateView(GLVFInstance instance, const GLVFViewCreateInfo* info, GLVFView* result);
GLVFBool glvfIsViewActive(GLVFView view);
void glvfBootstrapView(GLVFMainFunction fn);
GLVFResult glvfDestroyView(GLVFView view);