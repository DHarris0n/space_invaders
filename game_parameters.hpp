//game_parameters.hpp
#pragma once //insure that this header file is included only once and there will no multiple definition of the same thing

struct Parameters {
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr int sprite_size = 32;
    static constexpr float time_step = 0.017f;
};
