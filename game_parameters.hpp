#pragma once

struct Parameters{
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr float time_step = 0.017f;
    static constexpr int sprite_size = 32;
    static constexpr int spacing = 18;
    static constexpr int rows = 5;
    static constexpr int columns = 12;
    static constexpr int down = 24;
    static constexpr float acc = 10.f;
    static constexpr float player_speed = 100.f;
    static constexpr float bullet_speed = 200.f;
};