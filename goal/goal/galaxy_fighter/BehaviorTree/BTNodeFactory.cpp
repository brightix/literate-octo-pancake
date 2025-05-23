#include "pch.h"
#include "BTNodeFactory.h"

shared_ptr<BTNode> createNodeFromJson(const json& nodeConfig, shared_ptr<Context> context) {
     //定义节点类型与创建函数的映射
    static const std::unordered_map<std::string, std::function<shared_ptr<BTNode>(const json&, shared_ptr<Context>)>> nodeFactoryMap = {
        {"display_background", [](const json&, shared_ptr<Context> context) { return make_shared<BTAction_image::display_background>(context); }},
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

    // 获取节点类型
    string type = nodeConfig["type"];

    // 检查类型是否存在
    auto it = nodeFactoryMap.find(type);
    if (it != nodeFactoryMap.end()) {
        return it->second(nodeConfig, context);  // 调用对应的构造函数并返回
    }

    // 类型未匹配时返回空指针或处理错误
    cout << "没有类型为 \"" << type << "\" 的行为节点" << endl;
    return nullptr;
}