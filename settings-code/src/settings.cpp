#include "settings.h"
#include "settings_tool.h"
#include "settings_node.h"
#include "settings_system.h"
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

namespace rededa
{
  RSettings::RSettings(SettingsProduct aSettingProduct, std::string aName)
      : mSettingProduct(aSettingProduct), mRoot(std::make_shared<RSettingsNode>(aName, nlohmann::json()))
  {
  }

  SettingsProduct RSettings::getProduct() const
  {
    return mSettingProduct;
  }

  rhandle_t RSettings::getHandle() const
  {
    return mHandle;
  }

void removeLayer(const std::string &layerName) {
    nlohmann::json jsonData = mRoot->getValue();

    std::string keyPath = "grids.grids_parament.layer";

    // 1. 获取现有的 "layer" 数组
    auto &layers = jsonData["grids"]["grids_parament"]["layer"];

    // 2. 遍历数组找到具有指定 "name" 的元素并删除
    auto it = std::remove_if(layers.begin(), layers.end(),
        [&](const nlohmann::json &layer) {
            return layer.contains("name") && layer["name"] == layerName;
        });

    if (it != layers.end()) {
        layers.erase(it, layers.end()); // 删除找到的元素
    }

    // 3. 更新 JSON 数据并通知变动
    if (mDataChangeCallback) {
        nlohmann::json changeData = getValue(keyPath);
        mDataChangeCallback(keyPath.c_str(), changeData.dump().c_str());
    }
    notifyAll(jsonData);
    
    // 4. 更新根节点的值
    mRoot->setValue(jsonData);

    // 5. 保存更改
    save();
}


void insertLayer(const std::string &layerName) {
	nlohmann::json jsonData = mRoot->getValue();
    // 定义要插入的默认值
    nlohmann::json newLayer = {
        {"name", layerName},
        {"value", {{"x", {25.000}}, {"y", {25.000}}}},
        {"offset", {{"x", 0.000}, {"y", 0.000}}}
    };

    std::string keyPath = "grids.grids_parament.layer";

    // 1. 获取现有的 "layer" 数组
    auto &layers = jsonData["grids"]["grids_parament"]["layer"];
      layers.push_back(newLayer);

    // 调用回调函数通知数据变动
    if (mDataChangeCallback)
    {
	nlohmann::json changeData = getValue(keyPath);
      mDataChangeCallback(keyPath.c_str(),changeData.dump().c_str());
    }
    notifyAll(jsonData);
    mRoot->setValue();
   save();

}

  int RSettings::insertValue(const std::string &aKey, const nlohmann::json &aJson)
  {
    std::vector<std::string> keys = split(aKey, ".");
    std::shared_ptr<RSettingsNode> current = mRoot;

    for (const auto &key : keys)
    {
      auto child = current->getChild(key);
      if (!child)
      {
        child = std::make_shared<RSettingsNode>(key, aJson);
        current->addChild(child);
      }
      current = child;
    }

    current->setValue(aJson);
    current->updateParentValue(); // 更新父节点的值

    // 调用回调函数通知数据变动
    if (mDataChangeCallback)
    {
      mDataChangeCallback(aKey.c_str(), aJson.dump().c_str());
    }
    notify(aKey, aJson);
    return 0;
  }


  int RSettings::updateValue(const std::string &aKey, const nlohmann::json &aJson)
  {
    std::vector<std::string> keys = split(aKey, ".");
    std::shared_ptr<RSettingsNode> current = mRoot;

    for (size_t i = 0; i < keys.size(); ++i)
    {
      std::string key = keys[i];
      std::shared_ptr<RSettingsNode> child = current->getChild(key);

      if (!child)
      {
        std::cout << "Node not found: " << key << std::endl;
        return -1;
      }

      current = child;
    }

    current->setValue(aJson); // 设置当前节点的值
    current->updateParentValue(); // 更新父节点的值

    // 调用回调函数通知数据变动
    if (mDataChangeCallback)
    {
      mDataChangeCallback(aKey.c_str(), aJson.dump().c_str());
    }
    notify(aKey, aJson);
    return 0;
  }

  int RSettings::deleteKey(const std::string &aKey)
  {
    std::vector<std::string> keys = split(aKey, ".");
    std::shared_ptr<RSettingsNode> current = mRoot;

    for (size_t i = 0; i < keys.size(); ++i)
    {
      std::string key = keys[i];
      if (i == keys.size() - 1)
      {
        // 删除最后一个键对应的子节点
        auto it = std::remove_if(current->mChildren.begin(), current->mChildren.end(),
                                 [&](const std::shared_ptr<RSettingsNode> &child)
                                 { return child->getName() == key; });

        if (it != current->mChildren.end())
        {
          current->mChildren.erase(it, current->mChildren.end());

          // 更新父节点的值
          // current->updateParentValue();

          notify(aKey, nlohmann::json());
          return 0;
        }
        return -1;
      }
      else
      {
        std::shared_ptr<RSettingsNode> child = current->getChild(key);
        if (!child)
        {
          return -1;
        }
        current = child;
      }
    }
    return -1;
  }

  const std::string RSettings::getValue(const std::string &aKey)
  {
    std::vector<std::string> keys = split(aKey, ".");
    std::shared_ptr<RSettingsNode> current = mRoot;

    for (const std::string &key : keys)
    {
      std::shared_ptr<RSettingsNode> child = current->getChild(key);
      if (!child)
      {
        return "";
      }
      current = child;
    }
    return current->getValue().dump();
  }

  std::string RSettings::getAllData()
  {
    return mRoot->getValue().dump();
  }

  int RSettings::setAllData(const std::string &aData)
  {
    try
    {
      nlohmann::json data = nlohmann::json::parse(aData);
      mRoot->setValue(data);
      notifyAll(data);
      return 0;
    }
    catch (nlohmann::json::parse_error &e)
    {
      std::cerr << "JSON parsing error: " << e.what() << std::endl;
      return -1;
    }
  }

  void RSettings::setISettingsDAO(std::shared_ptr<IRSettingsDAO> aSettingsDAO)
  {
    mSettingsDAO = aSettingsDAO;
  }

  void RSettings::setChangeCallBack(const data_change_call_back aCallBack)
  {
    mDataChangeCallback = aCallBack;
  }

  void RSettings::registerNode(std::shared_ptr<RSettingsNode> aBranch)
  {
    mRoot->addChild(aBranch);
  }

  int RSettings::load()
  {
    if (mSettingsDAO)
    {
      nlohmann::json settingsData = mSettingsDAO->loadSettings();
      mRoot->setValue(settingsData);
      return 0;
    }
    return -1;
  }


  int RSettings::save()
  {
    if (mSettingsDAO)
    {
      nlohmann::json settingsData = nlohmann::json::parse(getAllData());

      // std::cout << "+++getAllData++++  " << ":   "<< getAllData() << std::endl;
      return mSettingsDAO->saveSettings(settingsData);
    }
    return -1;
  }

  int RSettings::initSettings(SettingsProduct aSettingProduct)
  {
    nlohmann::json jsonData;

    std::filesystem::path executablePath = std::filesystem::current_path();
    std::filesystem::path settingsDir = executablePath / "data" / "settings";

    if (!std::filesystem::exists(settingsDir) && !std::filesystem::create_directories(settingsDir))
    {
      std::cerr << "Failed to create settings directory: " << settingsDir << std::endl;
      return -1;
    }

    std::string filePathStr;
    switch (aSettingProduct)
    {
    case 1: // UserPreferences
      filePathStr = (settingsDir / "settings_userpreferences.json").string();
      break;
    case 2: // RedSCH
      filePathStr = (settingsDir / "settings_redsch.json").string();
      break;
    case 3: // RedPCB
      filePathStr = (settingsDir / "settings_redpcb.json").string();
      break;
    case 4: // RedPKG
      filePathStr = (settingsDir / "settings_redpkg.json").string();
      break;
    default:
      std::cerr << "Unknown settings product." << std::endl;
      return -1;
    }

    // 检查文件是否存在
    if (std::filesystem::exists(filePathStr))
    {
      // 文件存在，从文件读取 JSON 数据
      std::ifstream f(filePathStr, std::ios_base::in);
      if (!f.is_open())
      {
        std::cerr << "Failed to open file: " << filePathStr << std::endl;
        return -1;
      }
      f >> jsonData;
      f.close();
    }
    else
    {
      // 文件不存在，设置默认值
      jsonData = {
          {"general", {{"unit", {{"options", {"microns", "millimeter", "nanometer", "centimeter", "mils", "inch"}}, {"value", "microns"}}}, {"accuracy", 2}, {"long_name_size", 50}, {"canvas_size", {{"options", {"other", "a1", "a2", "a3", "a4", "a", "b", "c", "d"}}, {"value", "other"}, {"width", 100000}, {"height", 100000}, {"left_x", -50000}, {"lower_y", -50000}}}, {"move_origin", {{"x", 0.0}, {"y", 0.0}}}}},
          {"display", {{"display_modes", {{"filled_pad", true}, {"filled_track", true}, {"filled_copper", true}, {"plated_hole", false}, {"via_label", false}, {"waived_drc", false}, {"non_plated_hole", false}, {"display_origin", true}}}, {"display_net_name", {{"copper", false}, {"pad", false}, {"track", false}}}, {"drc_marker_size", 300}, {"fly_net_geometry", "jogger"}, {"fly_net_points", "closest endpoint"}}},
          {"grids", {{"grids_parament", {{"grids_type", {{"options", {"off", "dots", "line"}}, {"value", "dots"}}}, {"non_conductor", {{"value", {{"x", {}}, {"y", {}}}}, {"offset", {{"x", 0}, {"y", 0}}}}}, {"all_conductor", {{"value", {{"x", {}}, {"y", {}}}}, {"offset", {{"x", 0}, {"y", 0}}}}}, {"surface", {{"value", {{"x", {25}}, {"y", {25}}}}, {"offset", {{"x", 0}, {"y", 0}}}}}, {"base", {{"value", {{"x", {25}}, {"y", {25}}}}, {"offset", {{"x", 0}, {"y", 0}}}}}}}, {"grids_group", {{"group_list", {{{"value_x", 1}, {"value_y", 1}, {"offset_x", 0}, {"offset_y", 0}}, {{"value_x", 2}, {"value_y", 2}, {"offset_x", 0}, {"offset_y", 0}}, {{"value_x", 10}, {"value_y", 10}, {"offset_x", 0}, {"offset_y", 0}}, {{"value_x", 25}, {"value_y", 25}, {"offset_x", 0}, {"offset_y", 0}}}}, {"grids_current", 3}}}}},
          {"draw", {}},
          {"text", {{"text_data", {{{"char_space", 30.0}, {"height", 80.0}, {"line_space", 0.0}, {"line_width", 200.0}, {"width", 40.0}}, {{"char_space", 50.0}, {"height", 150.0}, {"line_space", 0.0}, {"line_width", 300.0}, {"width", 75.0}}, {{"char_space", 100.0}, {"height", 600.0}, {"line_space", 0.0}, {"line_width", 800.0}, {"width", 400.0}}, {{"char_space", 200.0}, {"height", 1200.0}, {"line_space", 0.0}, {"line_width", 1600.0}, {"width", 800.0}}, {{"char_space", 400.0}, {"height", 1600.0}, {"line_space", 0.0}, {"line_width", 2000.0}, {"width", 1200.0}}, {{"char_space", 500.0}, {"height", 1900.0}, {"line_space", 0.0}, {"line_width", 2400.0}, {"width", 1400.0}}, {{"char_space", 500.0}, {"height", 2100.0}, {"line_space", 0.0}, {"line_width", 2500.0}, {"width", 1500.0}}, {{"char_space", 600.0}, {"height", 2400.0}, {"line_space", 0.0}, {"line_width", 2900.0}, {"width", 1700.0}}, {{"char_space", 650.0}, {"height", 2600.0}, {"line_space", 0.0}, {"line_width", 3200.0}, {"width", 1900.0}}, {{"char_space", 800.0}, {"height", 3200.0}, {"line_space", 0.0}, {"line_width", 3900.0}, {"width", 2400.0}}, {{"char_space", 1500.0}, {"height", 4000.0}, {"line_space", 0.0}, {"line_width", 5000.0}, {"width", 2900.0}}, {{"char_space", 1100.0}, {"height", 4500.0}, {"line_space", 0.0}, {"line_width", 5500.0}, {"width", 3300.0}}, {{"char_space", 1200.0}, {"height", 4775.0}, {"line_space", 0.0}, {"line_width", 6000.0}, {"width", 3500.0}}, {{"char_space", 1250.0}, {"height", 5000.0}, {"line_space", 0.0}, {"line_width", 6500.0}, {"width", 3800.0}}, {{"char_space", 1450.0}, {"height", 5500.0}, {"line_space", 0.0}, {"line_width", 7000.0}, {"width", 4200.0}}, {{"char_space", 1600.0}, {"height", 6000.0}, {"line_space", 0.0}, {"line_width", 8000.0}, {"width", 4800.0}}}}, {"text_block", 1}, {"coordinate_point", "left"}}},
          {"copper", {}},
          {"route", {}},
          {"manufacture", {}}};

      std::ofstream outFile(filePathStr);
      if (!outFile.is_open())
      {
        std::cerr << "Failed to open file to write default settings: " << filePathStr << std::endl;
        return -1;
      }
      outFile << jsonData.dump(4);
      outFile.close();
    }

    mRoot->setValue(jsonData);

    return 0;
  }

  void RSettings::attach(std::shared_ptr<IRSettingsObserver> aObserver)
  {
    mObservers.push_back(aObserver);
  }

  void RSettings::detach(std::shared_ptr<IRSettingsObserver> aObserver)
  {
    auto it = std::find(mObservers.begin(), mObservers.end(), aObserver);
    if (it != mObservers.end())
    {
      mObservers.erase(it);
    }
  }

  void RSettings::notify(const std::string &aKey, const nlohmann::json &aValue)
  {
    for (auto &observer : mObservers)
    {
      observer->onSettingChanged(aKey, aValue);
    }
  }

  void RSettings::notifyAll(const nlohmann::json &aData)
  {
    for (auto &observer : mObservers)
    {
      observer->onSettingsChangedToAllData(aData);
    }
  }

} // namespace rededa