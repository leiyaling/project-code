#include "rededa/settings/settings_controller.h"
#include "settings.h"
#include "rededa/settings/settings_read.h"
#include "settings_system.h"
#include "settings_system_general.h"
#include "settings_system_library.h"
#include "settings_general.h"
#include "settings_display.h"
#include "settings_text.h"

namespace rededa
{
  RSettingsController &RSettingsController::instance()
  {
    static RSettingsController instance;
    return instance;
  }

  std::shared_ptr<IRSettings> RSettingsController::createByProduct(SettingsProduct aSettingProduct)
  {
    if (aSettingProduct == 1)
    {
      std::string name = "UserPreferences";
      //auto systemNode = std::make_shared<RSettingsSystem>();
      // auto systemLibrary = std::make_shared<RSettingsSystemLibrary>();
      // auto systemGeneral = std::make_shared<RSettingsSystemGeneral>();

      // systemNode->addChild(systemLibrary);
      // systemNode->addChild(systemGeneral);

      auto settings = std::make_shared<RSettings>(aSettingProduct, name);
      //settings->registerNode(systemNode);
      settings->initSettings(aSettingProduct);
      return settings;
    }
    else if (aSettingProduct == 2)
    {
      std::string name = "RedSCH";

      auto settings = std::make_shared<RSettings>(aSettingProduct, name);
      return settings;
    }
    else if (aSettingProduct == 3)
    {
      std::string name = "RedPCB";
      auto settings = std::make_shared<RSettings>(aSettingProduct, name);
      // auto generalNode = std::make_shared<RSettingsGeneral>("General", jsonGeneral);
      // auto displayNode = std::make_shared<RSettingsDisplay>("Display", jsonDisplay);
      // auto textNode = std::make_shared<RSettingsText>("Text", jsonText);

      // settings->registerNode(generalNode);
      // settings->registerNode(displayNode);
      // settings->registerNode(textNode);
      settings->initSettings(aSettingProduct);
      return settings;
    }
    else if (aSettingProduct == 4)
    {
      std::string name = "RedPKG";
      auto settings = std::make_shared<RSettings>(aSettingProduct, name);

      // auto generalNode = std::make_shared<RSettingsGeneral>("General", jsonGeneral);
      // auto displayNode = std::make_shared<RSettingsDisplay>("Display", jsonDisplay);
      // auto textNode = std::make_shared<RSettingsText>("Text", jsonText);

      // settings->registerNode(generalNode);
      // settings->registerNode(displayNode);
      // settings->registerNode(textNode);
      settings->initSettings(aSettingProduct);
      return settings;
    }
    return nullptr;
  }

  int RSettingsController::registerRSetting(std::shared_ptr<IRSettings> aSettings)
  {
    return mRead->addRSettings(aSettings); // 返回settings句柄
  }

  std::shared_ptr<IRSettings> RSettingsController::getRSettings(rhandle_t aHandle)
  {
    return mRead->getRSettings(aHandle);
  }

  int RSettingsController::deleteRSettings(rhandle_t aHandle)
  {
    return mRead->removeRSettings(aHandle);
  }

  RSettingsRead &RSettingsController::getRSettingsRead()
  {
    return *mRead;
  }

}