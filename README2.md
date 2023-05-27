## Robot Car Setup

### Components:
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/1dc4e55e-4ead-4e7f-bcea-ad550dbd9832)

### Front View:
![DSC_0440](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/22a7447c-6d47-4d55-81c0-ababef0990b9)

### Explanations:
**1. Clamp** <br>
Grab cups and return to the End Zone

**2. Servo Motor** <br>
Control the rotation angle and facing direction of the clamp

**3. DC Motor & Wheels** <br>
Control the speed and movement of the car

**4. Long Distance Infra-red Sensor** <br>
Detect nearby cups. If a cup is detected by the sensor, the clamp will be opened and ready for catching the cup

**5. State Displayer** <br>
Display the current state of the robot car

**6. Short Distance Infra-red Sensor** <br>
Path tracking <br>
***Remark:*** *There are a total of **6 sensors** (3 at the front and 3 at the back)* <br>
*When the car is moving ***forward***, ***front sensors*** will be used for path tracking* <br>
*When the car is moving ***backward***, ***back sensors*** will be used for path tracking*

## Details on the Movement of the Robot Car:
### 1. Moving Direction <br>
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/a3b55108-a15e-494d-9d1d-37cb932e319b)

### 2. Path Tracking <br>
#### Case 1: Forwards
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/94ed56aa-9c4b-425a-b9b2-f0b554190164)
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/513f8323-2582-45dd-ba4a-5634cac51e4a)
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/c16667a4-e261-497b-8dd7-846ed9ad9ea0)

#### Case 2: Backwards
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/d385a28d-47c7-4962-b7eb-001f4a90a2f9)
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/89d44d33-1ff1-4e94-8372-a14bdd7c3911)
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/9165eac7-15c1-47c0-98a9-d88194622fcc)

### 3. Junction Navigation <br>
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/f764f877-c257-4cda-8526-098c8fa1a3d8)

### How to determine which path the car goes after arriving at the junction?

Here is the proposed path of collecting all cups in the arena: <br>
![image](https://github.com/tommykwok722/Cup-Retrieving-Robot-Car/assets/132838814/5469d935-0931-4443-a8a9-1178b0407a60)
