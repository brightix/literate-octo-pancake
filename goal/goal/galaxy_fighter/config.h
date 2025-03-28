#pragma once
#include <format>
#include <string>

#define TO_STRING_2(x) std::format("{:.2f}",x)
#define TO_STRING_3(x) std::format("{:.3f}",x)


//宽高
constexpr int swidth = 1920;
constexpr int sheight = 1080;

//常量
constexpr int MAX_ENEMY_LEVEL_1 = 8;//最大等级1的敌机数量


constexpr int MIN_ATTACK_INTERVAL = 8;//最小英雄发射频率


constexpr int ENEMY_TYPE_CNT = 3;//敌机种类数量

//基准帧数
constexpr double BASE_FRAME_TIME = 1000/60;

constexpr double globalSpeed = 1.0f;

//日志打印时间
constexpr double LOG_TIME_INTERVAL = 1;

