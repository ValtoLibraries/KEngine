#pragma once

#include "GameObject.hpp"
#include "common/components/LuaComponent.hpp"

namespace kengine {
    class ScriptableObject : public GameObject, public putils::Reflectible<ScriptableObject> {
    public:
        ScriptableObject(std::string_view name, const std::vector<std::string> & scripts = {})
                : GameObject(name) {
            attachComponent<kengine::LuaComponent>(scripts);
        }

        pmeta_get_class_name(ScriptableObject);
    };
}