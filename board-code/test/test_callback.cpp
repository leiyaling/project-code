#include "common.h"
#include "rededa/board/common/common.h"
#include "board_controller.h"
#include "rededa/board/board_c.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(test_callback, callback_get_path)
{
    auto callback =  [](int handle){
        auto path = board_get_current_file_path(handle);
        std::cout << "path: " << path << std::endl;
        EXPECT_STREQ(path, "aa\\bb");
        return 0;
    };
    board_regist_callback(callback);
    board_new("aa", "bb", BoardMode::PCB);
}

TEST(test_callback, callback_exit_notify)
{
    auto callback = [](bool aResult){
        if(aResult)
        {
            std::cout << "exit" << std::endl;
        }
        else
        {
            std::cout << "file not saved" << std::endl;
        }
    };
    board_regist_close_callback(callback);
    auto handle = board_new("aa", "bb", BoardMode::PCB);
    auto &controller = rededa::RBoardController::instance();
    auto board = controller.get(handle);
    board -> close();
}