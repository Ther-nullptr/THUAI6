#pragma once

#ifndef LOGIC_H
#define LOGIC_H

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Message2Server.pb.h"
#include "Message2Clients.pb.h"
#include "MessageType.pb.h"
#include "Services.grpc.pb.h"
#include "Services.pb.h"
#include "API.h"
#include "AI.h"
#include "structures.h"
#include "state.h"
#include "Communication.h"

// 封装了通信组件和对AI对象进行操作
class Logic : public ILogic
{
private:
    // 日志组件
    std::unique_ptr<spdlog::logger> logger;

    // 通信组件
    std::unique_ptr<Communication> pComm;

    // ID、阵营记录
    int64_t playerID;
    THUAI6::PlayerType playerType;

    // 类型记录
    THUAI6::HumanType humanType;
    THUAI6::ButcherType butcherType;

    // GUID信息
    std::vector<int64_t> playerGUIDs;

    std::unique_ptr<IGameTimer> timer;

    std::thread tAI;  // 用于运行AI的线程

    mutable std::mutex mtxAI;
    mutable std::mutex mtxState;
    mutable std::mutex mtxBuffer;

    std::condition_variable cvBuffer;
    std::condition_variable cvAI;

    // 信息队列
    std::queue<std::pair<int64_t, std::string>> messageQueue;

    // 存储状态，分别是现在的状态和缓冲区的状态。
    State state[2];
    State* currentState;
    State* bufferState;

    // 保存缓冲区数
    int counterState = 0;
    int counterBuffer = 0;

    THUAI6::GameState gameState = THUAI6::GameState::NullGameState;

    // 是否应该执行player()
    std::atomic_bool AILoop = true;

    // buffer是否更新完毕
    bool bufferUpdated = true;

    // 是否应当启动AI
    bool AIStart = false;

    // asynchronous = true 时控制内容更新的变量
    std::atomic_bool freshed = false;

    // 提供给API使用的函数

    std::vector<std::shared_ptr<const THUAI6::Butcher>> GetButchers() const override;
    std::vector<std::shared_ptr<const THUAI6::Human>> GetHumans() const override;
    std::vector<std::shared_ptr<const THUAI6::Prop>> GetProps() const override;
    std::shared_ptr<const THUAI6::Human> HumanGetSelfInfo() const override;
    std::shared_ptr<const THUAI6::Butcher> ButcherGetSelfInfo() const override;

    std::vector<std::vector<THUAI6::PlaceType>> GetFullMap() const override;
    THUAI6::PlaceType GetPlaceType(int32_t CellX, int32_t CellY) const override;

    // 供IAPI使用的操作相关的部分
    bool Move(int64_t time, double angle) override;
    bool PickProp(THUAI6::PropType prop) override;
    bool UseProp() override;
    bool UseSkill() override;

    bool SendMessage(int64_t toID, std::string message) override;
    bool HaveMessage() override;
    std::optional<std::pair<int64_t, std::string>> GetMessage() override;

    bool Escape() override;

    bool StartFixMachine() override;
    bool EndFixMachine() override;

    bool StartSaveHuman() override;
    bool EndSaveHuman() override;

    bool Attack(double angle) override;
    bool CarryHuman() override;
    bool ReleaseHuman() override;
    bool HangHuman() override;

    bool WaitThread() override;

    int GetCounter() const override;

    const std::vector<int64_t> GetPlayerGUIDs() const override;

    bool TryConnection();

    void ProcessMessage();

    // 将信息加载到buffer
    void LoadBuffer(protobuf::MessageToClient&);

    // 解锁状态更新线程
    void UnBlockBuffer();

    // 解锁AI线程
    void UnBlockAI();

    // 更新状态
    void Update() noexcept;

    // 等待
    void Wait() noexcept;

public:
    // 构造函数还需要传更多参数，有待补充
    Logic(THUAI6::PlayerType type, int64_t ID, THUAI6::ButcherType butcher, THUAI6::HumanType human);

    ~Logic()
    {
    }

    // Main函数同上
    void Main(CreateAIFunc createAI, std::string IP, std::string port, bool file, bool print, bool warnOnly);
};

#endif
