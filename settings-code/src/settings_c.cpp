#include "rededa/settings/settings_c.h"
#include "settings_system.h"
#include "settings_system_general.h"
#include "settings_system_library.h"
#include "settings_general.h"
#include "settings_display.h"
#include "settings_text.h"
#include "rededa/settings/error.h"
#include "rededa/settings/settings_controller.h"
#include "rededa/settings/settings_data.h"
#include "settings_file_dao_factory.h"
#include "settings.h"
#include <iostream>
#include <fstream>
using namespace rededa;

int red_settings_create_id(SettingsProduct setting_product)
{
  if (setting_product == 1)
  {
    std::string name = "UserPreferences";
    // auto systemNode = std::make_shared<RSettingsSystem>();
    // auto systemLibrary = std::make_shared<RSettingsSystemLibrary>();
    // auto systemGeneral = std::make_shared<RSettingsSystemGeneral>();

    // systemNode->addChild(systemLibrary);
    // systemNode->addChild(systemGeneral);

    auto settings = std::make_shared<RSettings>(setting_product, name);
    // settings->registerNode(systemNode);
    settings->initSettings(setting_product);
    return RSettingsController::instance().registerRSetting(settings);
  }
  else if (setting_product == 2)
  {
    std::string name = "RedSCH";

    auto settings = std::make_shared<RSettings>(setting_product, name);
    return RSettingsController::instance().registerRSetting(settings);
  }
  else if (setting_product == 3)
  {
    std::string name = "RedPCB";
    // auto generalNode = std::make_shared<RSettingsGeneral>("General", jsonGeneral);
    // auto displayNode = std::make_shared<RSettingsDisplay>("Display", jsonDisplay);
    // auto textNode = std::make_shared<RSettingsText>("Text", jsonText);

    auto settings = std::make_shared<RSettings>(setting_product, name);
    // settings->registerNode(generalNode);
    // settings->registerNode(displayNode);
    // settings->registerNode(textNode);
    settings->initSettings(setting_product);
    return RSettingsController::instance().registerRSetting(settings);
  }
  else
  {
    std::string name = "RedPKG";
    auto settings = std::make_shared<RSettings>(setting_product, name);
    // auto generalNode = std::make_shared<RSettingsGeneral>("General", jsonGeneral);
    // auto displayNode = std::make_shared<RSettingsDisplay>("Display", jsonDisplay);
    // auto textNode = std::make_shared<RSettingsText>("Text", jsonText);

    // std::cout << "JSON General: " << jsonGeneral.dump(4) << std::endl;
    // std::cout << "JSON Display: " << jsonDisplay.dump(4) << std::endl;
    // std::cout << "JSON Text: " << jsonText.dump(4) << std::endl;

    // settings->registerNode(generalNode);
    // settings->registerNode(displayNode);
    // settings->registerNode(textNode);

    settings->initSettings(setting_product);
    return RSettingsController::instance().registerRSetting(settings);
  }
}

int red_settings_set_all_data(int id, const char *data)
{
  auto settings = RSettingsController::instance().getRSettings(id);
  if (!settings)
  {
    return -1;
  }
  return settings->setAllData(data);
}

int red_settings_set_item(int id, const char *key, const char *value)
{
  auto settings = RSettingsController::instance().getRSettings(id);
  if (!settings)
  {
    return -1;
  }
  try
  {
    nlohmann::json j = nlohmann::json::parse(value);
    settings->updateValue(key, j);
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << "\n";
    return -1;
  }
}

int red_settings_get_item(int id, const char *key, str_copy_call_back call_back)
{
  auto settings = RSettingsController::instance().getRSettings(id);
  if (!settings)
  {
    return -1;
  }
  try
  {
    auto data = settings->getValue(key);
    call_back(data.data(), data.size());
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << "\n";
    return -1;
  }
}

// int red_settings_save(int id, const char *path)
// {
//   auto settings = RSettingsController::instance().getRSettings(id);
//   if (!settings)
//   {
//     return -1;
//   }
//   RFileDAOFactory factory(path);
//   auto settingsDao = factory.createDAO();
//   settings->setISettingsDAO(std::move(settingsDao));

//   return settings->save();
// }

int red_settings_save(int id, const char *path)
{
  auto settings = RSettingsController::instance().getRSettings(id);
  if (!settings)
  {
    return -1;
  }
  std::string filePathStr = path;
  std::filesystem::path filePath(filePathStr);

  if (!std::filesystem::exists(filePath.parent_path()) &&
      !std::filesystem::create_directories(filePath.parent_path()))
  {
    std::cerr << "Failed to create directory: " << filePath.parent_path() << std::endl;
    return -1;
  }

  // 检查文件是否存在，如果不存在则创建它
  if (!std::filesystem::exists(filePath))
  {
    std::ofstream outFile(filePath);
    if (!outFile)
    {
      std::cerr << "Failed to create file: " << filePath << std::endl;
      return -1;
    }
    outFile.close();
  }

  RFileDAOFactory factory(filePath.string());
  auto settingsDao = factory.createDAO();
  settings->setISettingsDAO(std::move(settingsDao));

  int saveResult = settings->save();
  if (saveResult != 0)
  {
    std::cerr << "Failed to save settings." << std::endl;
    return saveResult;
  }

  return 0;
}

int red_settings_load(int id, const char *path)
{
  auto settings = RSettingsController::instance().getRSettings(id);
  if (!settings)
  {
    return -1;
  }
  RFileDAOFactory factory(path);
  auto settingsDao = factory.createDAO();
  settings->setISettingsDAO(std::move(settingsDao));
  return settings->load();
}

int red_settings_get_all_data(int id, str_copy_call_back call_back)
{
  auto settings = RSettingsController::instance().getRSettings(id);
  if (!settings)
  {
    return -1;
  }
  try
  {
    auto data = settings->getAllData();
    call_back(data.data(), data.size());
    return 0;
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << "\n";
    return -1;
  }
}

int red_settings_set_data_change(int id, data_change_call_back call_back)
{
  auto settings = RSettingsController::instance().getRSettings(id);
  if (settings)
  {
    settings->setChangeCallBack(call_back);
    return 0;
  }
  return -1;
}
