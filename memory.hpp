#ifndef POCKET_DROPPER_MEMORY_HPP
#define POCKET_DROPPER_MEMORY_HPP
#include <json-develop/single_include/nlohmann/json.hpp>
using json = nlohmann::json;

namespace JSON {
    json loadData();
    json AmendScoreJson(int score);
}


#endif //POCKET_DROPPER_MEMORY_HPP