#include <gtest/gtest.h>
// // #include <gmock/gmock.h>
#include "rededa/settings/settings_data.h"
#include "rededa/settings/settings_c.h"
#include "rededa/settings/settings_controller.h"
#include "rededa/settings/settings_read.h"
#include "settings.h"
#include "settings_concrete_observe.h"
#include <iostream>
#include <fstream>

using namespace rededa;

// class RSettingsTest : public ::testing::Test
// {
// protected:
//     void SetUp() override
//     {
//     }

//     void TearDown() override
//     {
//     }
//     // RSettings logic{1};
// };

// TEST_F(RSettingsTest, smoking)
// {
//     ASSERT_EQ(logic.api(1, nullptr), 0);
// }

TEST(Settings, red_settings_create_id)
{
    int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PKG);
    auto settings = RSettingsController::instance().getRSettings(settings_id);
    std::string ret = settings->getValue("grids.grids_parament.grids_type.value");
    std::cout << "  ++++  " << ret << std::endl;
    std::cout << "  getAllData  " << settings->getAllData() << std::endl;
    ASSERT_EQ(settings_id, 1);
}

// TEST(Settings, red_settings_load)
// {
//     // std::filesystem::path executablePath = std::filesystem::current_path();
//     // std::filesystem::path settingsDir = executablePath / "data" / "settings";

//     std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();
//     std::filesystem::path filePath = currentDir / "test_load.json";

//     std::string filePathStr = filePath.string();
//     const char *path = filePathStr.c_str();

//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PREFERENCES);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);

//     int result = red_settings_load(settings_id, path);
//     ASSERT_EQ(result, 0);

//     std::ifstream file(path);
//     nlohmann::json expected_data;
//     file >> expected_data;
//     file.close();

//     std::string actual_data = settings->getAllData();
//     // std::cout << "1--------" << settings->getAllData() << std::endl;
//     ASSERT_EQ(expected_data.dump(), actual_data);

//     // EXPECT_EQ(red_settings_load(0, ""), -1);
//     // EXPECT_EQ(red_settings_load(-1, ""), -1);
// }

// TEST(Settings, red_settings_set_item)
// {
//     // std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();
//     // std::filesystem::path filePath = currentDir / "test_load.json";

//     // std::string filePathStr = filePath.string();
//     // const char *path = filePathStr.c_str();

//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PREFERENCES);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);

//     // red_settings_load(settings_id, path);

//     std::string key_footprint = "System.Library.footprint";
//     std::string key_data = "grids.grids_parament.grids_type.value";
    
//     std::string value = R"("line")";

//     std::string value_footprint = R"([
//         {
//             "path": "C:\\Users\\Admin\\1111\\footprint",
//             "active": true
//         },
//         {
//             "path": "C:\\Users\\Admin\\1111\\Test\\footprint",
//             "active": false
//         }
//     ])";

//     int result = red_settings_set_item(settings_id, key_footprint.c_str(), value_footprint.c_str());
//     //int result = red_settings_set_item(settings_id, key_data.c_str(), value.c_str());
//     ASSERT_EQ(result, 0);
//     //std::cout << "-----   " << settings->getValue("grids.grids_parament.grids_type.value") << std::endl;

//     std::string data = settings->getValue("System.Library.footprint");
//     nlohmann::json json_data = nlohmann::json::parse(data);
//     ASSERT_EQ(json_data, nlohmann::json::parse(value_footprint));
// }

// std::string captured_data;
// void callback(const char *data, int size)
// {
//     captured_data = std::string(data, size);
// };

// TEST(Settings, red_settings_get_item)
// {
//     // std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();
//     // std::filesystem::path filePath = currentDir / "test_load.json";

//     // std::string filePathStr = filePath.string();
//     // const char *path = filePathStr.c_str();

//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PREFERENCES);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);

//     //red_settings_load(settings_id, path);

//     std::string key = "System.Library";

//     nlohmann::json value = {
//         {"footprint", {{{"path", "C:\\Users\\Admin\\Desktop\\footprint"}, {"active", true}}, {{"path", "C:\\Users\\Admin\\Desktop\\Test\\footprint"}, {"active", false}}}},
//         {"pad", {{{"path", "C:\\Users\\Admin\\Desktop\\pad"}, {"active", true}}, {{"path", "C:\\Users\\Admin\\Desktop\\Test\\pad"}, {"active", false}}}},
//         {"device", {{{"path", "C:\\Users\\Admin\\Desktop\\device"}, {"active", true}}, {{"path", "C:\\Users\\Admin\\Desktop\\Test\\device"}, {"active", false}}}},
//         {"step", {{{"path", "C:\\Users\\Admin\\Desktop\\step"}, {"active", true}}, {{"path", "C:\\Users\\Admin\\Desktop\\Test\\step"}, {"active", false}}}},
//         {"tech", {{{"path", "C:\\Users\\Admin\\Desktop\\tech"}, {"active", true}}, {{"path", "C:\\Users\\Admin\\Desktop\\Test\\tech"}, {"active", false}}}}};

//     int get_item_result = red_settings_get_item(settings_id, key.c_str(), callback);
//     ASSERT_EQ(get_item_result, 0);
//     nlohmann::json jsonLibrary = nlohmann::json::parse(captured_data);

//     ASSERT_EQ(value, jsonLibrary);
// }

// TEST(Settings, red_settings_set_all_data)
// {
//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PREFERENCES);
//     //const char *data = "{\"System\":{\"General\":{\"Theme\":{\"options\":[\"Dark\",\"High\"],\"value\":\"Dark\"},\"Language\":{\"options\":[\"English\",\"中文\"],\"value\":\"English\"},\"auto_save\":false,\"auto_save_time\":10,\"auto_backup\":false,\"maximum_backups\":5,\"auto_backup_time\":10},\"Library\":{\"footprint_lib\":[{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\footprint\",\"active\":true},{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\Test\\\\footprint\",\"active\":false}],\"pad_lib\":[{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\pad\",\"active\":true},{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\Test\\\\pad\",\"active\":false}],\"device_lib\":[{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\device\",\"active\":true},{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\Test\\\\device\",\"active\":false}],\"step_lib\":[{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\step\",\"active\":true},{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\Test\\\\step\",\"active\":false}],\"tech_lib\":[{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\tech\",\"active\":true},{\"path\":\"C:\\\\Users\\\\Admin\\\\Desktop\\\\Test\\\\tech\",\"active\":false}]}},\"Toolbars\":{},\"UI\":{},\"Shortcut\":{}}";
//     std::string data = R"(
//     {
//     "System": {
//         "General": {
//             "Theme": {
//                 "options": [
//                     "Dark",
//                     "Hight"
//                 ],
//                 "value": "Dark"
//             },
//             "Language": {
//                 "options": [
//                     "English",
//                     "中文"
//                 ],
//                 "value": "English"
//             },
//             "auto_save": false,
//             "auto_save_time": 10,
//             "auto_backup": false,
//             "maximum_backups": 5,
//             "auto_backup_time": 10
//         },
//         "Library": {
//             "footprint": [
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\footprint",
//                     "active": true
//                 },
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\Test\\footprint",
//                     "active": false
//                 }
//             ],
//             "pad": [
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\pad",
//                     "active": true
//                 },
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\Test\\pad",
//                     "active": false
//                 }
//             ],
//             "device": [
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\device",
//                     "active": true
//                 },
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\Test\\device",
//                     "active": false
//                 }
//             ],
//             "step": [
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\step",
//                     "active": true
//                 },
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\Test\\step",
//                     "active": false
//                 }
//             ],
//             "tech": [
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\tech",
//                     "active": true
//                 },
//                 {
//                     "path": "C:\\Users\\Admin\\Desktop\\Test\\tech",
//                     "active": false
//                 }
//             ]
//         }
//     },
//     "Toolbars": {},
//     "UI": {},
//     "Shortcut": {}
// })";
    
//     nlohmann::json jsonData = nlohmann::json::parse(data);

//     int result = red_settings_set_all_data(settings_id, data.c_str());
//     ASSERT_EQ(result, 0);
//     auto settings = RSettingsController::instance().getRSettings(settings_id);

//     nlohmann::json jsonAllData = nlohmann::json::parse(settings->getAllData());
//     ASSERT_EQ(jsonData, jsonAllData);
// }

// TEST(Settings, getValue_settings)
// {
//     // std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();
//     // std::filesystem::path filePath = currentDir / "test_load.json";

//     // std::string filePathStr = filePath.string();
//     // const char *path = filePathStr.c_str();

//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PREFERENCES);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);
//    // red_settings_load(settings_id, path);

//     nlohmann::json expected_result1 = "";
//     std::string key1 = "System.Library._holder.Theme"; // 不存在的key
//     std::string ret1 = settings->getValue(key1);
//     ASSERT_EQ(ret1, expected_result1);

//     // value是数组
//     nlohmann::json expected_result2 = {
//         {{"active", true}, {"path", "C:\\Users\\Admin\\Desktop\\footprint"}},
//         {{"active", false}, {"path", "C:\\Users\\Admin\\Desktop\\Test\\footprint"}}};

//     std::string key2 = "System.Library.footprint";
//     std::string ret2 = settings->getValue(key2);

//     nlohmann::json ret2_json = nlohmann::json::parse(ret2);
//     if (ret2_json.is_array() && ret2_json.size() == expected_result2.size())
//     {
//         for (auto it1 = ret2_json.begin(), it2 = expected_result2.begin(); it1 != ret2_json.end(); ++it1, ++it2)
//         {
//             if (*it1 != *it2)
//             {
//                 FAIL() << "JSON arrays do not match at index " << it1 - ret2_json.begin();
//             }
//         }
//         ASSERT_TRUE(true); // 如果所有元素都匹配，则测试通过
//     }
//     else
//     {
//         FAIL() << "JSON arrays do not have the same size or ret2 is not a JSON array.";
//     }

//     nlohmann::json expected_result3 = "Dark";
//     std::string key3 = "System.General.Theme.value";
//     std::string ret3 = settings->getValue(key3);
//     ASSERT_EQ(ret3, expected_result3.dump());
// }

TEST(Settings, red_settings_save)
{
    // std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();

    // std::filesystem::path filePathSave = currentDir / "test_save.json";
    // std::string filePathStrSave = filePathSave.string();
    // const char *path_save = filePathStrSave.c_str();

    int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PKG);

    auto settings = RSettingsController::instance().getRSettings(settings_id);

    //red_settings_load(settings_id, path_load);
    std::string new_key = "grids.grids_parament.L1";

    std::string new_value = R"(
            {
                "value": {
                    "x": [
                        10000,
                        10000
                    
                    ],
                    "y": [
                        10000,
                        10000
                    ]
                },
                "offset": {
                    "x": 0,
                    "y": 0
                }
            }
    )";

    int new_ret = settings->insertValue(new_key,nlohmann::json::parse(new_value));
    std::cout << "grids.grids_parament.L1  " << ":   "<< settings->getValue("grids.grids_parament.L1") << std::endl;

    std::cout << "grids.grids_parament  " << ":   "<< settings->getValue("grids.grids_parament") << std::endl;

    ASSERT_EQ(new_ret, 0);
    // std::cout << "new data  " << new_key<< ":   "<< settings->getAllData() << std::endl;//增加了子节点，父节点没有更新

}

// std::string captured_data1;
// void callback1(const char *data, int size)
// {
//     captured_data1 = std::string(data, size);
// };

// TEST(Settings, red_settings_get_all_data)
// {
//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PREFERENCES);

//     int get_all_data_result = red_settings_get_all_data(settings_id, callback1);
//     ASSERT_EQ(get_all_data_result, 0);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);
//     ASSERT_EQ(captured_data1, settings->getAllData());
// }

// TEST(Settings, updateValue)
// {
//     // std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();
//     // std::filesystem::path filePath = currentDir / "test_load.json";

//     // std::string filePathStr = filePath.string();
//     // const char *path = filePathStr.c_str();

//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PKG);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);

//     //red_settings_load(settings_id, path);
//     std::string key1 = "grids.grids_parament.grids_type.value";
//     nlohmann::json j = "line";

//     int ret1 = settings->updateValue(key1, j);

//     std::cout << "---value  " << settings->getValue("grids.grids_parament.grids_type.value") << std::endl;
//     ASSERT_EQ(ret1, 0);

//     // std::string key2 = "System.Library.device";

//     // nlohmann::json tar = {
//     //     {{"active", false}, {"path", "C:\\Users\\111\\Desktop\\111"}},
//     //     {{"active", false}, {"path", "C:\\Users\\111\\Desktop\\222"}}};

//     // int ret2 = settings->updateValue(key2, tar);
//     // ASSERT_EQ(ret2, 0);

//     // ASSERT_EQ(tar, nlohmann::json::parse(settings->getValue(key2)));
// }

// TEST(Settings, insertValue)
// {
//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PKG);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);


//     std::string key = "grids.grids_parament.surface.value.x";
//     nlohmann::json j = {
//         {{"active", false}, {"path", "C:\\Users\\111\\Desktop\\"}},
//         {{"active", false}, {"path", "C:\\Users\\111\\Desktop\\222"}}};
//     nlohmann::json json_data = {25, 25, 25};
//     int ret = settings->insertValue(key, json_data);

//     std::string ret_data = settings->getValue("grids.grids_parament.surface.value.x");

//     ASSERT_EQ(ret, 0);
//     ASSERT_EQ(json_data,nlohmann::json::parse(ret_data));

//     // nlohmann::json result = {
//     //     {{"active", false}, {"path", "C:\\Users\\111\\Desktop\\"}},
//     //     {{"active", false}, {"path", "C:\\Users\\111\\Desktop\\222"}}};
//     // ASSERT_EQ(result.dump(), settings->getValue(key));

//     // 插入已经存在的key
//     std::string key2 = "text.text_block";
//     nlohmann::json res = 0;

//     int expected_ret = settings->insertValue(key2, res);
//     ASSERT_EQ(expected_ret, 0);
// }

// TEST(Settings, deleteKey)
// {
//     // std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();
//     // std::filesystem::path filePath = currentDir / "test_load.json";

//     // std::string filePathStr = filePath.string();
//     // const char *path = filePathStr.c_str();

//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PREFERENCES);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);
//     //red_settings_load(settings_id, path);

//     std::string key1 = "System.General.Theme";

//     int ret1 = settings->deleteKey(key1);
//     ASSERT_EQ(ret1, 0);

//     std::string key2 = "key3";
//     int ret2 = settings->deleteKey(key2);
//     ASSERT_EQ(ret2, -1); // 删除不存在的key
// }

// TEST(Settings, addRSettings)
// {
//     auto settings = std::make_shared<RSettings>(SettingsProduct::REDEDA_PREFERENCES, "UserPreferences");
//     auto read = std::make_shared<RSettingsRead>();
//     int ret = read->addRSettings(settings);

//     ASSERT_EQ(ret, 1);
// }

// TEST(Settings, removeRSettings)
// {
//     auto settings = std::make_shared<RSettings>(SettingsProduct::REDEDA_PREFERENCES, "UserPreferences");
//     auto read = std::make_shared<RSettingsRead>();
//     int handle = read->addRSettings(settings);

//     int ret1 = read->removeRSettings(handle);
//     ASSERT_EQ(ret1, 0);

//     int ret2 = read->removeRSettings(22); // 没有注册进RSettingsRead
//     ASSERT_EQ(ret2, -1);
// }

// TEST(Settings, Read_getValue)
// {
//     // std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();
//     // std::filesystem::path filePath = currentDir / "test_load.json";

//     // std::string filePathStr = filePath.string();
//     // const char *path = filePathStr.c_str();

//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PREFERENCES);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);
//     //red_settings_load(settings_id, path);

//     auto read = RSettingsController::instance().getRSettingsRead();

//     nlohmann::json expected_result1 = "";
//     std::string key1 = "System.Library._holder.Theme"; // 不存在的key

//     std::string ret1 = read.getValue(key1, settings->getProduct());
//     ASSERT_EQ(ret1, expected_result1);

//     // value是数组
//     nlohmann::json expected_result2 = {
//         {{"active", true}, {"path", "C:\\Users\\Admin\\Desktop\\device"}},
//         {{"active", false}, {"path", "C:\\Users\\Admin\\Desktop\\Test\\device"}}};

//     std::string key2 = "System.Library.device";
//     std::string ret2 = read.getValue(key2, settings->getProduct());

//     nlohmann::json ret2_json = nlohmann::json::parse(ret2);
//     if (ret2_json.is_array() && ret2_json.size() == expected_result2.size())
//     {
//         for (auto it1 = ret2_json.begin(), it2 = expected_result2.begin(); it1 != ret2_json.end(); ++it1, ++it2)
//         {
//             if (*it1 != *it2)
//             {
//                 FAIL() << "JSON arrays do not match at index " << it1 - ret2_json.begin();
//             }
//         }
//         ASSERT_TRUE(true); // 如果所有元素都匹配，则测试通过
//     }
//     else
//     {
//         FAIL() << "JSON arrays do not have the same size or ret2 is not a JSON array.";
//     }

//     nlohmann::json expected_result3 = "Dark";
//     std::string key3 = "System.General.Theme.value";
//     std::string ret3 = read.getValue(key3, settings->getProduct());
//     ASSERT_EQ(ret3, expected_result3.dump());
// }

// TEST(Settings, observer_concrete)
// {
//     std::filesystem::path currentDir = std::filesystem::path(__FILE__).parent_path();
//     std::filesystem::path filePath = currentDir / "test_load.json";

//     std::string filePathStr = filePath.string();
//     const char *path = filePathStr.c_str();

//     int settings_id = red_settings_create_id(SettingsProduct::REDEDA_PREFERENCES);

//     auto settings = RSettingsController::instance().getRSettings(settings_id);

//     red_settings_load(settings_id, path);

//     auto observer = std::make_shared<ConcreteSettingsObserver>();

//     settings->attach(observer);

//     std::string key1 = "System.Library.device";

//     nlohmann::json tar = {
//         {{"active", true}, {"path", "C:\\Users\\111\\Desktop\\111"}},
//         {{"active", false}, {"path", "C:\\Users\\111\\Desktop\\222"}}};

//     int ret1 = settings->updateValue(key1, tar);
//     ASSERT_EQ(ret1, 0);
// }

// TEST(Settings, createByProduct)
// {
//     auto settings = RSettingsController::instance().createByProduct(SettingsProduct::REDEDA_PKG);
//     std::cout << settings->getAllData() << std::endl;
// }