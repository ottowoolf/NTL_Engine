#pragma once

#include <nlohmann/json.hpp>
#include <string_view>

class SaveManager
{
private:
    // Private member variables and methods for managing save data
    nlohmann::json values_;

public:
    // Public methods for saving and loading game data
    SaveManager();
    ~SaveManager();

    void Set(std::string_view key, const auto &value)
    {
        values_[key] = value;
    }

    auto Get(std::string_view key, auto defaultValue = {}) const
    {
        return values_.value(key, defaultValue);
    }

    bool Has(std::string_view key) const;
    void Erase(std::string_view key);
    void Clear();
};