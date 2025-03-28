#pragma once
#include <format>
#include <string>

#define TO_STRING_2(x) std::format("{:.2f}",x)
#define TO_STRING_3(x) std::format("{:.3f}",x)


//���
constexpr int swidth = 1920;
constexpr int sheight = 1080;

//����
constexpr int MAX_ENEMY_LEVEL_1 = 8;//���ȼ�1�ĵл�����


constexpr int MIN_ATTACK_INTERVAL = 8;//��СӢ�۷���Ƶ��


constexpr int ENEMY_TYPE_CNT = 3;//�л���������

//��׼֡��
constexpr double BASE_FRAME_TIME = 1000/60;

constexpr double globalSpeed = 1.0f;

//��־��ӡʱ��
constexpr double LOG_TIME_INTERVAL = 1;

