#include "Managers/SaveManager.h"
#include "Utils/Log.h"

#include <fstream>

SaveManager::SaveManager()
{

    if (std::ifstream file{"Content/Saves/SaveData.json"})
    {
        values_ = nlohmann::json::parse(file);
        LOG_INFO("Save data loaded successfully!");
    }
    else
    {
        values_ = nlohmann::json::object();
        LOG_INFO("No existing save data found. Initialized with an empty JSON object.");
    }
}

SaveManager::~SaveManager()
{
    if (!values_.empty())
    {
        std::ofstream file{"Content/Saves/SaveData.json"};
        file << values_.dump(4);
        LOG_INFO("Data saved successfully!");
    }
}

bool SaveManager::Has(std::string_view key) const
{
    return values_.contains(key);
}

void SaveManager::Erase(std::string_view key)
{
    values_.erase(key);
}

void SaveManager::Clear()
{
    values_.clear();
}
