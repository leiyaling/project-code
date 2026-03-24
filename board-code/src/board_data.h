#ifndef INCLUDE_BOARD_DATA_BOARD_DATA
#define INCLUDE_BOARD_DATA_BOARD_DATA
#include <string>
namespace rededa{
struct BoardData
{
    double width;
    double height;
    unsigned accuracy;
    double originX;
    double originY;
    std::string unitName;
    std::string path;
};

struct RenderPointer
{
    void *mScene;
    void *mContext;
    void *mTransform;
    void *msurface;
    void *mRender;
};
}
#endif /* INCLUDE_BOARD_DATA_BOARD_DATA */