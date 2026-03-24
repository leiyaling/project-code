# rededa_board

## config environment

- 克隆公共仓库
    `git clone http://192.168.1.231:9000/rededa-plus/rededa_dev_dist.git`
- 配置 REDEDA_PLUS_DEV_DIST 环境变量
  环境变量 REDEDA_PLUS_DEV_DIST 的值为上一步克隆下来的本地仓库中 rededa_dev_dist\win 目录

## build

```shell
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
    cmake --install build
```

编译产物为动态库 `rededa_board` 和可执行程序 `rtest_board`
