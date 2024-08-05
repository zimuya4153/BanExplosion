# BanExplosion - 自定义防爆

## 简介

BanExplosion 是一个 Minecraft LeviLamina服务端插件，用于修改爆炸

## 配置文件
```jsonc
{
    "version": 1, // 配置文件版本(勿动)
    "setting": { // 防爆配置,可填实体霍方块的命名空间ID
        // (None:无视 NoBlock:禁止破坏方块 NoExplosion:禁止爆炸)
        "minecraft:tnt": "NoBlock", // TNT
        "minecraft:respawn_anchor": "NoExplosion", // 重生锚
        "minecraft:tnt_minecart": "NoBlock", // TNT矿车
        "minecraft:creeper": "NoBlock", // 苦力怕
        "minecraft:end_crystal": "NoBlock", // 末地水晶
        "minecraft:dragon_fireball": "NoBlock", // 龙火球
        "minecraft:wither_skull": "NoBlock", // 凋灵之首
        "minecraft:fireball": "NoBlock", // 恶魂火球
        "minecraft:bed": "NoBlock",  // 床
        "minecraft:wither": "NoExplosion", // 凋灵
        "minecraft:wither_skull_dangerous": "NoBlock" // 蓝色的凋灵之首
    }
}
```