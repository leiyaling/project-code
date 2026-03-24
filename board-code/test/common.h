#ifndef TEST_COMMON
#define TEST_COMMON

#include <filesystem>
namespace test_board
{

inline std::filesystem::path getRBoardTestCurrentExistResourcePath(const std::string &aName)
{
    std::filesystem::path currentPath{std::string{__FILE__}};
    std::filesystem::path resourcePath = currentPath.parent_path() / "data/";
    resourcePath /= aName;
    if (std::filesystem::exists(resourcePath))
    {
        return resourcePath.make_preferred();
    }
    return {};
}

inline std::filesystem::path getRBoardTestResourcePath(const std::string &aName)
{
    std::filesystem::path currentPath{std::string{__FILE__}};
    std::filesystem::path resourcePath = currentPath.parent_path() / "data/";
    if (!aName.empty())
    {
        resourcePath /= aName;
        return resourcePath.make_preferred();
    }
    return {};
}
} // namespace test_board

#endif /* TEST_COMMON */