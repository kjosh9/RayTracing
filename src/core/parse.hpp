#ifndef PARSE_HPP
#define PARSE_HPP

#include <vector>
#include <memory>

#include "light.hpp"
#include "shadedObject.hpp"
#include "camera.hpp"
#include "nlohmann/json.hpp"

namespace parser {

bool parse_json(const nlohmann::json & JSonObj,
        Camera & camera,
        std::vector<std::shared_ptr<Light>> & lights,
        std::vector<std::shared_ptr<ShadedObject>> & objects);

bool parse(std::string filename,
           Camera & camera,
           std::vector<std::shared_ptr<Light>> & lights,
           std::vector<std::shared_ptr<ShadedObject>> & objects);

}
#endif // PARSE_HPP
