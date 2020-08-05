#include <glvf.h>
#include <iostream>
#include <vector>
int main()
{
    GLVFInstance instance;
    GLVFResult result = glvfCreateInstance(&instance);
    if (result != GLVF_OK)
    {
        std::cout << "Instance creation failed with result " << result;
        return result;
    }

    GLVFFeatureFlags supportedFeatures;
    result = glvfQueryInstanceFeatureSupport(instance, &supportedFeatures);
    if (result != GLVF_OK)
    {
        std::cout << "Getting feature support failed with result " << result;
        return result;
    }

    GLVFViewCreateInfo info;
    info.api.kind = GLVF_API_KIND_OPENGL;
    info.api.version[0] = 3;
    info.api.version[1] = 3;
    info.enabledFeatures = supportedFeatures;
    
    int pos[2] = { 50, 50 };
    int size[2] = { 1280, 720 };
    std::vector<const GLVFPropertyFeatureConfig*> configs;
    GLVFPropertyFeatureConfig posConfig;
    posConfig.kind = GLVF_FEATURE_CONFIG_KIND_PROPERTY;
    posConfig.key = GLVF_VIEW_PNAME_VEC2I_POSITION;
    posConfig.value = &pos;
    if ((supportedFeatures & GLVF_FEATURE_CONTROLLABLE_POSITION) != 0)
    {
        configs.push_back(&posConfig);
    }

    GLVFPropertyFeatureConfig sizeConfig;
    sizeConfig.kind = GLVF_FEATURE_CONFIG_KIND_PROPERTY;
    sizeConfig.key = GLVF_VIEW_PNAME_VEC2I_SIZE;
    sizeConfig.value = &size;
    if ((supportedFeatures & GLVF_FEATURE_CONTROLLABLE_SIZE) != 0)
    {
        configs.push_back(&sizeConfig);
    }

    info.numFeatureConfigs = configs.size();
    info.featureConfigs = reinterpret_cast<const GLVFEmptyFeatureConfig**>(&configs[0]);
    info.numBufferBitPreferences = 0;

    GLVFView view;
    result = glvfCreateView(instance, &info, &view);
    if (result != GLVF_OK)
    {
        std::cout << "View creation failed with result " << result;
        return result;
    }

    GLVFEventPumpCreateInfo eventPumpCreateInfo;
    eventPumpCreateInfo.isEventDriven = false;
    GLVFEventPump eventPump;
    result = glvfCreateEventPump(view, &eventPumpCreateInfo, &eventPump);
    if (result != GLVF_OK)
    {
        std::cout << "Event pump creation failed with result " << result;
        return result;
    }

    GLVFEvent events[8]; // process 8 events per frame. can be any number, i just picked 8.
    while (true)
    {
        GLVFViewStatus status;
        result = glvfQueryViewStatus(view, &status);
        if (result != GLVF_OK || status != GLVF_VIEW_STATE_ACTIVE)
        {
            std::cout << "Closing view due to status query. Result: " << result << "Status: " << status;
            break;
        }

        uint32_t count = 8;
        result = glvfEnumerateEvents(eventPump, &count, &events[0]);
        if (result != GLVF_OK && result != GLVF_INCOMPLETE)
        {
            std::cout << "Closing view due to event pump failure with result " << result;
            break;
        }

        for (size_t i = 0; i < count; i++)
        {
            // TODO proper event handling
            std::cout << "Got event " << events[i].kind << " \n";
        }

        glvfSwapBuffers(view);
    }

    glvfDestroyEventPump(eventPump);
    glvfDestroyView(view);
    glvfDestroyInstance(instance);
}