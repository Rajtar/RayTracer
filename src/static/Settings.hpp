#ifndef RENDERER_SETTINGS_HPP
#define RENDERER_SETTINGS_HPP

enum AntiAliasingTypes {
    None = 0,
    MultiSampling = 1
};

class Settings {
public:
    static const AntiAliasingTypes AntiAliasingType = None;
};

#endif //RENDERER_SETTINGS_HPP
