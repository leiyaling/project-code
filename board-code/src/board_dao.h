#ifndef INCLUDE_BOARD_DAO
#define INCLUDE_BOARD_DAO
#include <string>
#include <functional>
#include <optional>
#include <filesystem>

#include "board_data.h"
#include "rededa/board/common/common.h"

namespace rededa
{
class RBoardFileDao
{
public:
    RBoardFileDao();
    bool load(std::function<void(const BoardData&, const std::string&)> callback);
    bool save(std::function<void(const std::string&)> callback);
    void setPath(const std::string &aPath);
    void setName(const std::string &aName);
    void setBoardData(const BoardData& aBoardData);
    void setMode(const BoardMode &aBoardMode);

private:
    std::string removeFileName(const std::string& aPath);
    std::string removeTimeStamp(const std::string& aPath, const std::string& aTimeStamp);
    std::optional<std::filesystem::path> zipConvert(const std::string& aPath);
    std::string findFile(const std::string& aPath, const std::string& aExtension);
    std::optional<BoardData> readBoardDataJson(const std::string& aPath);
    bool extensionCheck(const std::string& aPath);
    bool pathCheck(const std::string& aPath);
    bool saveBoardDataJson(const BoardData& aData, const std::string& aPath);

  private:
    std::string mPath;
    std::string mName;
    BoardData mBoardData;
    BoardMode mMode;
};
}
#endif /* INCLUDE_BOARD_DAO */