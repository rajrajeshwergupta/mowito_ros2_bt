#include <iostream>
#include <behaviortree_cpp_v3/bt_factory.h>

using namespace BT;

// Action node for moving towards a target
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

// Condition node for checking if a door is open
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

// Action node for opening a door
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

// Action node for closing a door
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

// Action node for entering a room
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

// Action node for exiting a room
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

// Action node for finding an apple
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

// Action node for picking an apple
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

// // The XML string defining our behavior tree
// static const char* xml_text = R"(
// <root main_tree_to_execute="RobotTask">
//     <BehaviorTree ID="RobotTask">
//         <Sequence name="MainSequence">
//             <!-- First approach and enter the room -->
//             <Sequence name="EnterRoomSequence">
//                 <Action ID="MoveTowards" target="room_door"/>
//                 <Fallback name="HandleRoomDoor">
//                     <Condition ID="IsDoorOpen" door="room_door"/>
//                     <Action ID="OpenDoor" door="room_door"/>
//                 </Fallback>
//                 <Action ID="EnterRoom"/>
//             </Sequence>
            
//             <!-- Then approach and open the fridge -->
//             <Sequence name="FridgeInteractionSequence">
//                 <Action ID="MoveTowards" target="fridge_door"/>
//                 <Fallback name="HandleFridgeDoor">
//                     <Condition ID="IsDoorOpen" door="fridge_door"/>
//                     <Action ID="OpenDoor" door="fridge_door"/>
//                 </Fallback>
//                 <!-- Find and pick the apple -->
//                 <Action ID="FindApple"/>
//                 <Action ID="PickApple"/>
//                 <!-- Close the fridge -->
//                 <Action ID="CloseDoor" door="fridge_door"/>
//             </Sequence>
            
//             <!-- Exit the room -->
//             <Sequence name="ExitRoomSequence">
//                 <Action ID="MoveTowards" target="room_door"/>
//                 <Action ID="ExitRoom"/>
//             </Sequence>
//         </Sequence>
//     </BehaviorTree>
// </root>
// )";

int main() {
    // Create a BehaviorTree factory
    BehaviorTreeFactory factory;

    // Register all node types
    factory.registerNodeType<MoveTowards>("MoveTowards");
    factory.registerNodeType<IsDoorOpen>("IsDoorOpen");
    factory.registerNodeType<OpenDoor>("OpenDoor");
    factory.registerNodeType<CloseDoor>("CloseDoor");
    factory.registerNodeType<EnterRoom>("EnterRoom");
    factory.registerNodeType<ExitRoom>("ExitRoom");
    factory.registerNodeType<FindApple>("FindApple");
    factory.registerNodeType<PickApple>("PickApple");

    // Create the behavior tree
    // auto tree = factory.createTreeFromText(xml_text);
    auto tree = factory.createTreeFromFile("./../tree.xml");
    
    // Execute the behavior tree
    std::cout << "\n--- Starting Robot Task ---\n" << std::endl;
    tree.tickRoot();
    
    return 0;
}