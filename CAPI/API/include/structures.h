#pragma once
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <cstdint>
#include <array>
#include <map>

namespace THUAI6
{

    // 游戏状态
    enum class GameState : unsigned char
    {
        NullGameState = 0,
        GameStart = 1,
        GameRunning = 2,
        GameEnd = 3,
    };
    // 所有NullXXXType均为错误类型，其余为可能出现的正常类型

    // 位置标志
    enum class PlaceType : unsigned char
    {
        NullPlaceType = 0,
        Land = 1,
        Wall = 2,
        Grass = 3,
        Machine = 4,
        Gate = 5,
        HiddenGate = 6,
    };

    // 形状标志
    enum class ShapeType : unsigned char
    {
        NullShapeType = 0,
        Circle = 1,
        Square = 2,
    };

    // 道具类型
    enum class PropType : unsigned char
    {
        NullPropType = 0,
        PropType1 = 1,
        PropType2 = 2,
        PropType3 = 3,
        PropType4 = 4,
    };

    // 玩家类型
    enum class PlayerType : unsigned char
    {
        NullPlayerType = 0,
        HumanPlayer = 1,
        ButcherPlayer = 2,
    };

    // 人类类型
    enum class HumanType : unsigned char
    {
        NullHumanType = 0,
        HumanType1 = 1,
        HumanType2 = 2,
        HumanType3 = 3,
        HumanType4 = 4,
    };

    // 屠夫类型
    enum class ButcherType : unsigned char
    {
        NullButcherType = 0,
        ButcherType1 = 1,
        ButcherType2 = 2,
        ButcherType3 = 3,
        ButcherType4 = 4,
    };

    // 人类Buff类型
    enum class HumanBuffType : unsigned char
    {
        NullHumanBuffType = 0,
        HumanBuffType1 = 1,
        HumanBuffType2 = 2,
        HumanBuffType3 = 3,
        HumanBuffType4 = 4,
    };

    enum class ButcherBuffType : unsigned char
    {
        NullButcherBuffType = 0,
        ButcherBuffType1 = 1,
        ButcherBuffType2 = 2,
        ButcherBuffType3 = 3,
        ButcherBuffType4 = 4,
    };

    // 人类状态枚举
    enum class HumanState : unsigned char
    {
        NullHumanState = 0,
        Idle = 1,
        Fixing = 2,
        Dying = 3,
        OnChair = 4,
        Dead = 5,
    };

    // 玩家类
    struct Player
    {
        int32_t x;          // x坐标
        int32_t y;          // y坐标
        int32_t speed;      // 移动速度
        int32_t viewRange;  // 视野范围
        int64_t playerID;   // 玩家ID
        int64_t guid;       // 全局唯一ID
        int16_t radius;     // 圆形物体的半径或正方形物体的内切圆半径

        double timeUntilSkillAvailable;  // 技能冷却时间

        PlayerType playerType;  // 玩家类型
        PropType prop;          // 手上的道具类型
        PlaceType place;        // 所处格子的类型
    };

    struct Human : public Player
    {
        HumanState state;    // 人类状态
        int32_t life;        // 剩余生命（本次倒地之前还能承受的伤害）
        int32_t hangedTime;  // 被挂的次数

        HumanType humanType;              // 人类类型
        std::vector<HumanBuffType> buff;  // buff
    };

    struct Butcher : public Player
    {
        int32_t damage;  // 攻击伤害
        bool movable;    // 是否处在攻击后摇中

        ButcherType butcherType;            // 屠夫类型
        std::vector<ButcherBuffType> buff;  // buff
    };

    struct Prop
    {
        int32_t x;
        int32_t y;
        int32_t size;
        int64_t guid;
        PropType type;
        PlaceType place;
        double facingDirection;  // 朝向
        bool isMoving;
    };

    // 仅供DEBUG使用，名称可改动
    // 还没写完，后面待续

    inline std::map<GameState, std::string> gameStateDict{
        {GameState::NullGameState, "NullGameState"},
        {GameState::GameStart, "GameStart"},
        {GameState::GameRunning, "GameRunning"},
        {GameState::GameEnd, "GameEnd"},
    };

    inline std::map<HumanState, std::string> humanStateDict{
        {HumanState::NullHumanState, "NullHumanState"},
        {HumanState::Idle, "Idle"},
        {HumanState::Fixing, "Fixing"},
        {HumanState::Dying, "Dying"},
        {HumanState::OnChair, "OnChair"},
        {HumanState::Dead, "Dead"},
    };

    inline std::map<PlayerType, std::string> playerTypeDict{
        {PlayerType::NullPlayerType, "NullPlayerType"},
        {PlayerType::HumanPlayer, "HumanPlayer"},
        {PlayerType::ButcherPlayer, "ButcherPlayer"},
    };

    inline std::map<PlaceType, std::string> placeTypeDict{
        {PlaceType::NullPlaceType, "NullPlaceType"},
        {PlaceType::Land, "Land"},
        {PlaceType::Wall, "Wall"},
        {PlaceType::Grass, "Grass"},
        {PlaceType::Machine, "Machine"},
        {PlaceType::Gate, "Gate"},
        {PlaceType::HiddenGate, "HiddenGate"},
    };

    inline std::map<PropType, std::string> propTypeDict{
        {PropType::NullPropType, "NullPropType"},

    };

    inline std::map<HumanBuffType, std::string> humanBuffDict{
        {HumanBuffType::NullHumanBuffType, "NullHumanBuffType"},

    };

    inline std::map<ButcherBuffType, std::string> butcherBuffDict{
        {ButcherBuffType::NullButcherBuffType, "NullButcherBuffType"},

    };

}  // namespace THUAI6

#endif
