#include <string>
#include <unordered_map>

enum BanExplosionMode {
    None,        // 无视
    NoBlock,     // 禁止破坏方块
    NoExplosion, // 禁止爆炸
};

namespace BanExplosion {
struct Config {
    int                                               version = 1; // 配置文件版本
    std::unordered_map<std::string, BanExplosionMode> setting = {
        {"minecraft:tnt",                    BanExplosionMode::NoBlock    }, // TNT
        {"minecraft:respawn_anchor",         BanExplosionMode::NoExplosion}, // 重生锚
        {"minecraft:creeper",                BanExplosionMode::NoBlock    }, // 苦力怕
        {"minecraft:end_crystal",            BanExplosionMode::NoBlock    }, // 末地水晶
        {"minecraft:dragon_fireball",        BanExplosionMode::NoBlock    }, // 龙火球
        {"minecraft:fireball",               BanExplosionMode::NoBlock    }, // 火球
        {"minecraft:wither_skull",           BanExplosionMode::NoBlock    }, // 凋零之首
        {"minecraft:tnt_minecart",           BanExplosionMode::NoBlock    }, // TNT矿车
        {"minecraft:bed",                    BanExplosionMode::NoBlock    }, // 床
        {"minecraft:wither",                 BanExplosionMode::NoExplosion}, // 凋零
        {"minecraft:wither_skull",           BanExplosionMode::NoBlock    }, // 凋零之首
        {"minecraft:wither_skull_dangerous", BanExplosionMode::NoBlock    }, // 蓝色凋零之首
    };
};
} // namespace BanExplosion