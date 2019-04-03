#ifndef RENDERER_SETTINGS_HPP
#define RENDERER_SETTINGS_HPP

enum AntialiasingTypes {
    None = 0,
    MultiSampling = 1
};

class Settings {
public:
    static const AntialiasingTypes AntialiasingType = None;
};

#endif //RENDERER_SETTINGS_HPP
