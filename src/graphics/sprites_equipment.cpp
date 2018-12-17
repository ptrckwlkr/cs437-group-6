#include <map>
#include "graphics/sprites_equipment.h"

using namespace EquipSprite;

std::string EquipSprite::getEquipSprite(EquipSet set, EquipSlot slot)
{
    static const std::map<std::pair<int, int>, std::string> equipMap {
            {std::make_pair<int, int>(Renegade, Head),            std::string("renegade_head")},
            {std::make_pair<int, int>(Renegade, Chest),           std::string("renegade_armor")},
            {std::make_pair<int, int>(Renegade, Shoulders),       std::string("renegade_shoulders")},
            {std::make_pair<int, int>(Renegade, Legs),            std::string("renegade_pants")},
            {std::make_pair<int, int>(Renegade, Feet),            std::string("renegade_boots")},
            {std::make_pair<int, int>(Renegade, Hands),           std::string("renegade_gloves")},

            {std::make_pair<int, int>(Crimson_Rogue, Head),       std::string("crimson_rogue_head")},
            {std::make_pair<int, int>(Crimson_Rogue, Chest),      std::string("crimson_rogue_armor")},
            {std::make_pair<int, int>(Crimson_Rogue, Shoulders),  std::string("crimson_rogue_shoulders")},
            {std::make_pair<int, int>(Crimson_Rogue, Legs),       std::string("crimson_rogue_pants")},
            {std::make_pair<int, int>(Crimson_Rogue, Feet),       std::string("crimson_rogue_boots")},
            {std::make_pair<int, int>(Crimson_Rogue, Hands),      std::string("crimson_rogue_gloves")},

            {std::make_pair<int, int>(Forest_Priest, Head),       std::string("forest_priest_head")},
            {std::make_pair<int, int>(Forest_Priest, Chest),      std::string("forest_priest_armor")},
            {std::make_pair<int, int>(Forest_Priest, Shoulders),  std::string("forest_priest_shoulders")},
            {std::make_pair<int, int>(Forest_Priest, Legs),       std::string("forest_priest_pants")},
            {std::make_pair<int, int>(Forest_Priest, Feet),       std::string("forest_priest_boots")},
            {std::make_pair<int, int>(Forest_Priest, Hands),      std::string("forest_priest_gloves")},

            {std::make_pair<int, int>(Guard, Head),               std::string("guard_head")},
            {std::make_pair<int, int>(Guard, Chest),              std::string("guard_armor")},
            {std::make_pair<int, int>(Guard, Shoulders),          std::string("guard_shoulders")},
            {std::make_pair<int, int>(Guard, Legs),               std::string("guard_pants")},
            {std::make_pair<int, int>(Guard, Feet),               std::string("guard_boots")},
            {std::make_pair<int, int>(Guard, Hands),              std::string("guard_gloves")},

            {std::make_pair<int, int>(Iron_Hunter, Head),         std::string("iron_hunter_head")},
            {std::make_pair<int, int>(Iron_Hunter, Chest),        std::string("iron_hunter_armor")},
            {std::make_pair<int, int>(Iron_Hunter, Shoulders),    std::string("iron_hunter_shoulders")},
            {std::make_pair<int, int>(Iron_Hunter, Legs),         std::string("iron_hunter_pants")},
            {std::make_pair<int, int>(Iron_Hunter, Feet),         std::string("iron_hunter_boots")},
            {std::make_pair<int, int>(Iron_Hunter, Hands),        std::string("iron_hunter_gloves")},

            {std::make_pair<int, int>(Cultist, Head),             std::string("cultist_head")},
            {std::make_pair<int, int>(Cultist, Chest),            std::string("cultist_armor")},
            {std::make_pair<int, int>(Cultist, Shoulders),        std::string("cultist_shoulders")},
            {std::make_pair<int, int>(Cultist, Legs),             std::string("cultist_pants")},
            {std::make_pair<int, int>(Cultist, Feet),             std::string("cultist_boots")},
            {std::make_pair<int, int>(Cultist, Hands),            std::string("cultist_gloves")},

            {std::make_pair<int, int>(Gatekeeper, Head),          std::string("gatekeeper_head")},
            {std::make_pair<int, int>(Gatekeeper, Chest),         std::string("gatekeeper_armor")},
            {std::make_pair<int, int>(Gatekeeper, Shoulders),     std::string("gatekeeper_shoulders")},
            {std::make_pair<int, int>(Gatekeeper, Legs),          std::string("gatekeeper_pants")},
            {std::make_pair<int, int>(Gatekeeper, Feet),          std::string("gatekeeper_boots")},
            {std::make_pair<int, int>(Gatekeeper, Hands),         std::string("gatekeeper_gloves")},

            {std::make_pair<int, int>(Illusionist, Head),         std::string("illusionist_head")},
            {std::make_pair<int, int>(Illusionist, Chest),        std::string("illusionist_armor")},
            {std::make_pair<int, int>(Illusionist, Shoulders),    std::string("illusionist_shoulders")},
            {std::make_pair<int, int>(Illusionist, Legs),         std::string("illusionist_pants")},
            {std::make_pair<int, int>(Illusionist, Feet),         std::string("illusionist_boots")},
            {std::make_pair<int, int>(Illusionist, Hands),        std::string("illusionist_gloves")},

            {std::make_pair<int, int>(Marauder, Head),            std::string("marauder_head")},
            {std::make_pair<int, int>(Marauder, Chest),           std::string("marauder_armor")},
            {std::make_pair<int, int>(Marauder, Shoulders),       std::string("marauder_shoulders")},
            {std::make_pair<int, int>(Marauder, Legs),            std::string("marauder_pants")},
            {std::make_pair<int, int>(Marauder, Feet),            std::string("marauder_boots")},
            {std::make_pair<int, int>(Marauder, Hands),           std::string("marauder_gloves")},

            {std::make_pair<int, int>(Sharpshooter, Head),        std::string("sharpshooter_head")},
            {std::make_pair<int, int>(Sharpshooter, Chest),       std::string("sharpshooter_armor")},
            {std::make_pair<int, int>(Sharpshooter, Shoulders),   std::string("sharpshooter_shoulders")},
            {std::make_pair<int, int>(Sharpshooter, Legs),        std::string("sharpshooter_pants")},
            {std::make_pair<int, int>(Sharpshooter, Feet),        std::string("sharpshooter_boots")},
            {std::make_pair<int, int>(Sharpshooter, Hands),       std::string("sharpshooter_gloves")},
    };
    auto i = equipMap.find(std::pair<int, int>(set, slot));
    return i->second;
}