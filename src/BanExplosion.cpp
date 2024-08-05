#include "BanExplosion.h"
#include "Config.h"

#include <ll/api/Config.h>
#include <ll/api/memory/Hook.h>
#include <ll/api/mod/RegisterHelper.h>
#include <ll/api/service/Bedrock.h>
#include <mc/world/actor/Actor.h>
#include <mc/world/actor/boss/WitherBoss.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/RespawnAnchorBlock.h>
#include <mc/world/level/dimension/Dimension.h>
#include <memory>


BanExplosion::Config config;

BanExplosionMode checkMode(Actor* entity, std::pair<BlockPos, int> pos) {
    if (entity) {
        return config.setting[entity->getTypeName()];
    }
    if (auto level = ll::service::getLevel()) {
        auto& block = level->getDimension(pos.second)->getBlockSourceFromMainChunkSource().getBlock(pos.first);
        return config.setting[block.getTypeName()];
    }
    return BanExplosionMode::None;
}

LL_AUTO_TYPE_INSTANCE_HOOK(
    ExplodeHook,
    HookPriority::Normal,
    Level,
    &Level::explode,
    bool,
    BlockSource& region,
    Actor*       source,
    Vec3 const&  pos,
    float        explosionRadius,
    bool         fire,
    bool         breaksBlocks,
    float        maxResistance,
    bool         allowUnderwater
) {
    auto result = checkMode(source, std::pair<BlockPos, int>(pos, region.getDimensionId()));
    if (result == BanExplosionMode::NoExplosion) return false;
    if (result == BanExplosionMode::NoBlock) breaksBlocks = false;
    return origin(region, source, pos, explosionRadius, fire, breaksBlocks, maxResistance, allowUnderwater);
}

LL_AUTO_TYPE_STATIC_HOOK(
    RespawnAnchorExplodeHook,
    HookPriority::Normal,
    RespawnAnchorBlock,
    &RespawnAnchorBlock::_explode,
    void,
    Player&         player,
    BlockPos const& pos,
    BlockSource&    region,
    Level&          level
) {
    auto result = checkMode(nullptr, std::pair<BlockPos, int>(pos, region.getDimensionId()));
    if (result == BanExplosionMode::NoExplosion || result == BanExplosionMode::NoBlock) return;
    origin(player, pos, region, level);
}


LL_AUTO_TYPE_INSTANCE_HOOK(
    WitherDestroyHook,
    HookPriority::Normal,
    WitherBoss,
    &WitherBoss::_destroyBlocks,
    void,
    Level&                       level,
    AABB const&                  aabb,
    BlockSource&                 region,
    int                          range,
    WitherBoss::WitherAttackType type
) {
    auto result = checkMode(this, std::pair<BlockPos, int>(getPosition(), region.getDimensionId()));
    if (result == BanExplosionMode::NoExplosion || result == BanExplosionMode::NoBlock) return;
    origin(level, aabb, region, range, type);
}

namespace BanExplosion {

static std::unique_ptr<Entry> instance;

Entry& Entry::getInstance() { return *instance; }

bool Entry::load() {
    auto path = getSelf().getConfigDir() / "config.json";
    try {
        if (!ll::config::loadConfig(config, path)) {
            ll::config::saveConfig(config, path);
        }
    } catch (...) {
        ll::config::saveConfig(config, path);
    }
    return true;
}

bool Entry::enable() { return true; }

bool Entry::disable() { return true; }

bool Entry::unload() {
    ll::memory::HookRegistrar<ExplodeHook, RespawnAnchorExplodeHook, WitherDestroyHook>().unhook();
    return true;
}

} // namespace BanExplosion

LL_REGISTER_MOD(BanExplosion::Entry, BanExplosion::instance);
