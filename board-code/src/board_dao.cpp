#include "board_dao.h"
#include "board_controller_log.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>
#include <regex>
#include <chrono>

namespace rededa
{
RBoardFileDao::RBoardFileDao() : mPath(std::string{}), mName(std::string{}), mMode(BoardMode::PKG)
{
}

bool RBoardFileDao::load(std::function<void(const BoardData&, const std::string&)> callback)
{
    auto &logger = getRBoardLogger();
    if(mPath.empty() || mName.empty())
    {
        return false;
    }
    if(!pathCheck(mPath) || !extensionCheck(mPath))
    {
        std::cout << "27 path" << mPath << std::endl;
        return false;
    }
    std::filesystem::path sysTempDir = std::filesystem::temp_directory_path();
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    std::stringstream time;
    time << duration.count();
    std::string tempFileName = mName + time.str();
    std::filesystem::path tempDir = sysTempDir / tempFileName;
    // 创建临时文件
    if(std::filesystem::create_directory(tempDir))
    {
        // logger.info(std::string{std::string{"create temp file:"} + tempDir.string()}.c_str());
    }
    else
    {
        logger.error("create temp file failed");
        return false;
    }
    std::filesystem::path zipFile = mPath;
    // 复制压缩包到临时文件夹
    std::filesystem::path tempZipFile = tempDir / zipFile.filename();
    std::filesystem::copy(zipFile, tempZipFile);
    if(std::filesystem::exists(tempZipFile))
    {
        // logger.info(std::string{std::string{"zip copy success:"} + tempZipFile.string()}.c_str());
    }
    else
    {
        logger.error("zip copy failed");
        return false;
    }
    // 更改后缀
    auto convertedPath = zipConvert(tempZipFile.string());
    if(convertedPath == std::nullopt)
    {
        logger.error("zip convert failed");
        return false;
    }
    // 使用系统命令解压压缩包
    std::string command = "powershell Expand-Archive -Path " + (*convertedPath).string() + " -DestinationPath " + removeFileName((*convertedPath).string());
    if(std::system(command.c_str()) != 0)
    {
        logger.error("unzip failed");
        return false;
    }
    // logger.info(std::string{std::string{"zip file unzip to:"} + removeFileName((*convertedPath).string())}.c_str());
    int dirCount = 0;
    std::filesystem::path unzipDir;
    for (const auto& entry : std::filesystem::directory_iterator(tempDir))
    {
        if(std::filesystem::is_directory(entry.path()))
        {
            unzipDir = entry.path();
            dirCount++;
        }
    }
    if(dirCount != 1)
    {
        logger.error("file format error");
        return false;
    }
    // logger.info(unzipDir.string().c_str());
    auto itemHolderPath = findFile(unzipDir.string(), ".tproto");
    if(itemHolderPath.empty())
    {
        logger.error("cannot find itemholderfile");
        // return false;
    }
    else
    {
        // logger.info(std::string{std::string{"itemholderfile:"} + itemHolderPath}.c_str());
    }
    auto boardDataPath = findFile(unzipDir.string(), ".json");
    if(boardDataPath.empty())
    {
        logger.error("cannot find boarddatafile");
        return false;
    }
    else
    {
        // logger.info(std::string{std::string{"boarddatafile:"} + boardDataPath}.c_str());
    }
    auto data = readBoardDataJson(boardDataPath);
    if(data == std::nullopt)
    {
        logger.error("json prase failed");
        return false;
    }
    callback(*data, itemHolderPath);
    // 删除临时文件夹
    std::filesystem::remove_all(tempDir);
    logger.info("delete temp dir");
    return true;
}

bool RBoardFileDao::save(std::function<void(const std::string&)> callback)
{
    auto &logger = getRBoardLogger();
    if(mPath.empty() || mName.empty())
    {
        return false;
    }
    // if(!pathCheck(mPath) || !extensionCheck(mPath))
    // {
    //     std::cout << "27 path" << mPath << std::endl;
    //     return false;
    // }
    std::filesystem::path sysTempDir = std::filesystem::temp_directory_path();
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    std::stringstream time;
    time << duration.count();
    std::string tempFileName = mName + time.str();
    std::filesystem::path tempDir = sysTempDir / tempFileName;
    // 创建临时文件
    if(std::filesystem::create_directory(tempDir))
    {
        // logger.info(std::string{std::string{"create temp file:"} + tempDir.string()}.c_str());
    }
    else
    {
        logger.info("create temp file failed");
        return false;
    }
    // 保存board data
    auto jsonName = mName + ".json";
    auto jsonPath = tempDir / jsonName;
    if(!saveBoardDataJson(mBoardData, jsonPath.string()))
    {
        logger.error("boarddata save failed");
    }
    auto itemHolderName = mName + ".tproto";
    // auto itemHolderPath = tempDir.string() + "\\c.tproto";
    auto itemHolderPath = tempDir / itemHolderName;
    // 回调保存item holder
    callback(itemHolderPath.string());
    // 压缩保存的内容
    std::string zipCommand = "powershell Compress-Archive -Path " + tempDir.string() + " -DestinationPath " + tempDir.string() + ".zip";
    if(std::system(zipCommand.c_str()) != 0)
    {
        logger.info("zip failed");
        return false;
    }
    else
    {
        // logger.info(std::string{std::string{"zip success:"} + tempDir.string()}.c_str());
    }
    std::filesystem::path targetDir = removeFileName(mPath);
    std::filesystem::path zipFile = tempDir.string() + ".zip";
    std::filesystem::path targetPath = targetDir / (zipFile.stem().string() + std::filesystem::path(mPath).extension().string());
    std::filesystem::path targetZipPath = removeTimeStamp(targetPath.string(), time.str());
    // 存在同名文件则删除
    if(std::filesystem::exists(targetZipPath))
    {
        std::filesystem::remove(targetZipPath);
    }
    // 移动到指定路径下
    std::filesystem::rename(zipFile, targetZipPath);
    if(std::filesystem::exists(targetZipPath))
    {
        // logger.info(std::string{std::string{"zip move success:"} + targetZipPath.string()}.c_str());
    }
    else
    {
        logger.error("zip move failed");
        return false;
    }
    std::filesystem::remove_all(tempDir);
    // std::cout << "conver:" << targetZipPath <<std::endl;
    // zipConvert(targetZipPath.string());
    return true;
}

std::string RBoardFileDao::removeFileName(const std::string &aPath)
{
    std::regex re(R"((.*[\\/]))");
    std::smatch match;
    if(std::regex_search(aPath, match, re))
    {
        return match[1].str();
    }
    else
    {
        return aPath;
    }
}

std::string RBoardFileDao::removeTimeStamp(
    const std::string &aPath, const std::string &aTimeStamp)
{
    auto result = aPath;
    size_t pos = result.rfind(aTimeStamp);
    if(pos != std::string::npos)
    {
        result.erase(pos, aTimeStamp.length());
    }
    return result;
}



std::optional<std::filesystem::path> RBoardFileDao::zipConvert(const std::string &aPath)
{
    std::filesystem::path newFilePath = aPath;
    newFilePath.replace_extension("zip");
    std::filesystem::rename(aPath, newFilePath);
    if(!std::filesystem::exists(newFilePath))
    {
        return std::nullopt;
    }
    return newFilePath;
}

void RBoardFileDao::setPath(const std::string &aPath)
{
    mPath = aPath;
}

void RBoardFileDao::setName(const std::string &aName)
{
    mName = aName;
}

void RBoardFileDao::setBoardData(const BoardData &aBoardData)
{
    mBoardData = aBoardData;
}

void RBoardFileDao::setMode(const BoardMode &aBoardMode)
{
    mMode = aBoardMode;
}

std::string RBoardFileDao::findFile(const std::string& aPath, const std::string &aExtension)
{
    std::filesystem::path targetFile;
    for(const auto& entry : std::filesystem::recursive_directory_iterator(aPath))
    {
        if(entry.path().extension() == aExtension)
        {
            targetFile = entry.path();
            break;
        }
    }
    return targetFile.string();
}

bool RBoardFileDao::extensionCheck(const std::string &aPath)
{
    std::regex pattern(R"(\.([^/\\]+)$)");
    std::smatch match;
    if(std::regex_search(aPath, match, pattern))
    {
        auto extension = match[1].str();
        if(extension.compare("redpcb") == 0 && mMode == BoardMode::PCB)
        {
            return true;
        }
        if(extension.compare("redpkg") == 0 && mMode == BoardMode::PKG)
        {
            return true;
        }
        std::cout << "extension:" << extension;
    }
    return false;
}

bool RBoardFileDao::pathCheck(const std::string &aPath)
{
    std::filesystem::path path(aPath);
    std::regex illegalPattern(R"([<>\"/\\|?*])");
    // for(const auto& node : path)
    // {
    //     std::cout << "node302:" << node << std::endl;
    // }
    for(const auto& node : path)
    {
        if(node.string().compare("\\") !=0 && node.string().compare("/") !=0 && std::regex_search(node.string(), illegalPattern))
        {
            // std::cout << "node308:" << node << std::endl;
            return false;
        }
    }
    return true;
}

std::optional<BoardData> rededa::RBoardFileDao::readBoardDataJson(const std::string &aPath)
{
    auto &logger = getRBoardLogger();
    nlohmann::json jsonData;
    try{
        std::ifstream dataFile(aPath);
        if(!dataFile.is_open())
        {
            logger.error("jsonfile open failed");
            return std::nullopt;
        }
        dataFile >> jsonData;
    }
    catch(const std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
        return std::nullopt;
    }
    if(!jsonData.contains("BoardData") || !jsonData["BoardData"].is_array() || jsonData["BoardData"].empty())
    {
        logger.error("json format error");
        return std::nullopt;
    }
    BoardData boardData;
    const nlohmann::json& boardDataJson = jsonData["BoardData"][0];
    boardData.accuracy = boardDataJson["accuracy"].get<unsigned>();
    boardData.height = boardDataJson["height"].get<double>();
    boardData.originX = boardDataJson["originX"].get<double>();
    boardData.originY = boardDataJson["originY"].get<double>();
    boardData.path = boardDataJson["path"].get<std::string>();
    boardData.unitName = boardDataJson["unitName"].get<std::string>();
    boardData.width = boardDataJson["width"].get<double>();
    return boardData;
}

bool rededa::RBoardFileDao::saveBoardDataJson(const BoardData& aData, const std::string &aPath)
{
    auto &logger = getRBoardLogger();
    nlohmann::json boardMember;
    nlohmann::json boardData = nlohmann::json::array();
    boardMember["width"] = aData.width;
    boardMember["height"] = aData.height;
    boardMember["accuracy"] = aData.accuracy;
    boardMember["originX"] = aData.originX;
    boardMember["originY"] = aData.originY;
    boardMember["unitName"] = aData.unitName.c_str();
    boardMember["path"] = mPath.c_str();
    boardData.push_back(boardMember);
    nlohmann::json jsonSave;
    jsonSave["BoardData"] = boardData;
    // if(mName.empty())
    // { 
    //     return false;
    // }
    try
    {
        std::ofstream saveFile{aPath, std::ios_base::trunc | std::ios_base::out};
        if(!saveFile.is_open())
        {
            logger.error("jsonfile open failed");
            return false;
        }
        saveFile << jsonSave.dump(4);
        saveFile.close();
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;;
        return false;
    }
    return true;
}
} // namespace rededa