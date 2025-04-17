#include <iostream>
#include <behaviortree_cpp_v3/bt_factory.h>

using namespace BT;

class MoveTowards : public SyncActionNode
{
public:
    MoveTowards(const std::string& name, const NodeConfiguration& config)
        : SyncActionNode(name, config)
    {
    }

    static PortsList providedPorts()
    {
        return { InputPort<std::string>("target") };
    }

    NodeStatus tick() override
    {
        auto target = getInput<std::string>("target");
        if (!target)
        {
            std::cout << "MoveTowards: Missing target" << std::endl;
            return NodeStatus::FAILURE;
        }

        std::cout << "Moving towards " << target.value() << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class IsDoorOpen : public ConditionNode
{
public:
    IsDoorOpen(const std::string& name, const NodeConfiguration& config)
        : ConditionNode(name, config)
    {
    }

    static PortsList providedPorts()
    {
        return { InputPort<std::string>("door") };
    }

    NodeStatus tick() override
    {
        auto door = getInput<std::string>("door");
        if (!door)
        {
            std::cout << "IsDoorOpen: Missing door parameter" << std::endl;
            return NodeStatus::FAILURE;
        }

        std::cout << "Checking if " << door.value() << " is open" << std::endl;
        return NodeStatus::FAILURE; // Always assume door is closed for simplicity
    }
};

class OpenDoor : public SyncActionNode
{
public:
    OpenDoor(const std::string& name, const NodeConfiguration& config)
        : SyncActionNode(name, config)
    {
    }

    static PortsList providedPorts()
    {
        return { InputPort<std::string>("door") };
    }

    NodeStatus tick() override
    {
        auto door = getInput<std::string>("door");
        if (!door)
        {
            std::cout << "OpenDoor: Missing door parameter" << std::endl;
            return NodeStatus::FAILURE;
        }

        std::cout << "Opening " << door.value() << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class CloseDoor : public SyncActionNode
{
public:
    CloseDoor(const std::string& name, const NodeConfiguration& config)
        : SyncActionNode(name, config)
    {
    }

    static PortsList providedPorts()
    {
        return { InputPort<std::string>("door") };
    }

    NodeStatus tick() override
    {
        auto door = getInput<std::string>("door");
        if (!door)
        {
            std::cout << "CloseDoor: Missing door parameter" << std::endl;
            return NodeStatus::FAILURE;
        }

        std::cout << "Closing " << door.value() << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class EnterRoom : public SyncActionNode
{
public:
    EnterRoom(const std::string& name, const NodeConfiguration& config)
        : SyncActionNode(name, config)
    {
    }

    static PortsList providedPorts()
    {
        return {};
    }

    NodeStatus tick() override
    {
        std::cout << "Entering the room" << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class ExitRoom : public SyncActionNode
{
public:
    ExitRoom(const std::string& name, const NodeConfiguration& config)
        : SyncActionNode(name, config)
    {
    }

    static PortsList providedPorts()
    {
        return {};
    }

    NodeStatus tick() override
    {
        std::cout << "Exiting the room" << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class FindApple : public SyncActionNode
{
public:
    FindApple(const std::string& name, const NodeConfiguration& config)
        : SyncActionNode(name, config)
    {
    }

    static PortsList providedPorts()
    {
        return {};
    }

    NodeStatus tick() override
    {
        std::cout << "Finding an apple in the fridge" << std::endl;
        return NodeStatus::SUCCESS;
    }
};

class PickApple : public SyncActionNode
{
public:
    PickApple(const std::string& name, const NodeConfiguration& config)
        : SyncActionNode(name, config)
    {
    }

    static PortsList providedPorts()
    {
        return {};
    }

    NodeStatus tick() override
    {
        std::cout << "Picking the apple" << std::endl;
        return NodeStatus::SUCCESS;
    }
};


int main() {
    BehaviorTreeFactory factory;

    factory.registerNodeType<MoveTowards>("MoveTowards");
    factory.registerNodeType<IsDoorOpen>("IsDoorOpen");
    factory.registerNodeType<OpenDoor>("OpenDoor");
    factory.registerNodeType<CloseDoor>("CloseDoor");
    factory.registerNodeType<EnterRoom>("EnterRoom");
    factory.registerNodeType<ExitRoom>("ExitRoom");
    factory.registerNodeType<FindApple>("FindApple");
    factory.registerNodeType<PickApple>("PickApple");

    auto tree = factory.createTreeFromFile("./../tree.xml");
    
    std::cout << "\n--- Starting Robot Task ---\n" << std::endl;
    tree.tickRoot();
    
    return 0;
}