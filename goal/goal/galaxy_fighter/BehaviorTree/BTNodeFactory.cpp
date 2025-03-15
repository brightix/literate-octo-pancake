#include "pch.h"
#include "BTNodeFactory.h"

shared_ptr<BTNode> createNodeFromJson(const json& nodeConfig, shared_ptr<Context> context) {
    // ����ڵ������봴��������ӳ��
    static const std::unordered_map<std::string, std::function<shared_ptr<BTNode>(const json&, shared_ptr<Context>)>> nodeFactoryMap = {
        {"display_background", [](const json&, shared_ptr<Context> context) { return make_shared<BTAction_image::display_background>(context); }},
        {"player_detect_input", [](const json&, shared_ptr<Context> context) { return make_shared<BTAction_player::player_detect_input>(context); }},
        {"player_move_jump", [](const json&, shared_ptr<Context> context) { return make_shared<BTAction_player::player_move_jump>(context); }},
        {"player_move_down", [](const json&, shared_ptr<Context> context) { return make_shared<BTAction_player::player_move_down>(context); }},
        {"player_move_left", [](const json&, shared_ptr<Context> context) { return make_shared<BTAction_player::player_move_left>(context); }},
        {"player_move_right", [](const json&, shared_ptr<Context> context) { return make_shared<BTAction_player::player_move_right>(context); }},
        {"refreshRect", [](const json&, shared_ptr<Context> context) { return make_shared<BTAction_player::refreshRect>(context); }},
        {"display_full", [](const json&, shared_ptr<Context> context) { return make_shared<BTAction_image::display_full>(context); }},
        {"Selector", [](const json& nodeConfig, shared_ptr<Context> context) {
            auto selector = make_shared<Selector>();
            for (auto& child : nodeConfig["children"]) {
                selector->addChild(createNodeFromJson(child, context));
            }
            return selector;
        }},
        {"Sequence", [](const json& nodeConfig, shared_ptr<Context> context) {
            auto sequence = make_shared<Sequence>();
            for (auto& child : nodeConfig["children"]) {
                sequence->addChild(createNodeFromJson(child, context));
            }
            return sequence;
        }},
    };

    // ��ȡ�ڵ�����
    string type = nodeConfig["type"];

    // ��������Ƿ����
    auto it = nodeFactoryMap.find(type);
    if (it != nodeFactoryMap.end()) {
        return it->second(nodeConfig, context);  // ���ö�Ӧ�Ĺ��캯��������
    }

    // ����δƥ��ʱ���ؿ�ָ��������
    return nullptr;
}