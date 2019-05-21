#include "Light.h"

Light::Light(LightIntensity commonColor) : diffuseIntensity(commonColor), ambientIntensity(commonColor),
                                                                          specularIntensity(commonColor) {}

Light::Light(const LightIntensity &diffuseIntensity, const LightIntensity &ambientIntensity,
             const LightIntensity &specularIntensity) : diffuseIntensity(diffuseIntensity),
                                                        ambientIntensity(ambientIntensity),
                                                        specularIntensity(specularIntensity) {}

