# Cup Retrieving Robot Car
A project related to Engineering Design and Finite-state Machine.

Here is a demo video of my robot car:

https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/160e5b6c-a0bd-487a-9b8b-83eefa750c16

## Background
A Finite-state machine (FSM) is a mathematical model of computation. Simply speaking, the machine will perform a sequence of actions **depending on different inputs**. When the machine reads an input, it will change from its original state to a different state, the process of changing from one state to another is called a **transition**.

Here is an example of Finite-state machine in daily lives:

**Traffic Light**: A sequence of actions will be triggered depending on the states of other traffic lights
- **States:** RED, RED and YELLOW, YELLOW, GREEN Lights
- **Transitions:**
  - RED &rarr; RED and YELLOW
  - RED and YELLOW &rarr; GREEN
  - GREEN &rarr; YELLOW
  - YELLOW &rarr; RED
- **State Diagram:**
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/4bec3a93-bf9f-4452-a669-cc06ade9c477)


## Objectives
Build a robot car, pick up as many paper cups as possible from a designated arena and drop off the cups at a specific location within a given time limit.

The designated arena is as follows:
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/3aaf10a6-40ef-4025-8ea5-fc0c53554999)


## Specifications
1. Time limit is **3 minutes**
2. Robot car must start at the Start Zone
3. Cups must be collected by the cup grip of the robot car
4. The number of retrievable cups is **12**. Cups will be placed at some specific locations
5. Only cups that are returned to the **End Zone** will be counted
6. A cup will not be replaced if it is collected or knocked off from the stands
7. If cups are fallen outside of the arena during the transportation by the robot car, it will be counted as out-of-bounds and will be removed
8. If cups are not returned to the End Zone by the robot car, it will be counted as out-of-bounds and will not be counted as a returned cup
9. **Unlimited number of trials** can be attempted within the time limit.
10. The robot car can be restarted at the Start Zone if malfunction happens
11. You can pick up **more than one cup** in each trial

## Assessment Criteria
1. **Number of cups** successfully returned to the End Zone
2. **Required time** for returning the last cup into the End Zone within the time limit
