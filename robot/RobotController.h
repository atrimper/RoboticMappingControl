#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "globals.h"
#include "Motor.h"
#include "Encoder.h"
#include "LSM9DS1.h"

#define COUNTPERCM 29.538 ///< Encoder counts 192 every 65 mm of wheel rotation
#define ROTERRI 0.730 ///< 90 commanded rotation overshoot compensation
#define ROTERRII 0.770 ///< 180 commanded rotation overshoot compensation
#define ROTERRIII 0.810 ///< 270, 360 commanded rotation overshoot compensation
#define MMTOIN 0.0393701 ///< Metric to emperical length conversion

/**
 * Robot Controller class.
 */
class RobotController {
    public:
        /**
         * Robot Controller constructor.
         * @param leftWheelPwm mbed pin transmitting speed to left motor driver
         * @param leftWheelFwd mbed pin transmitting forward direction to left motor driver
         * @param leftWheelRev mbed pin transmitting reverse direction to left motor driver
         * @param rightWheelPwm mbed pin transmitting speed to right motor driver
         * @param rightWheelFwd mbed pin transmitting forward direction to right motor driver
         * @param rightWheelRev mbed pin transmitting reverse direction to right motor driver
         * @param leftEncoder mbed pin receiving rotation count from left encoder
         * @param rightEncoder mbed pin receiving rotation count from right encoder
         * @param imuSda mbed pin for imu I2C data line
         * @param imuScl mbed pin for imu I2C clock line
         */
        RobotController(PinName leftWheelPwm, PinName leftWheelFwd,
            PinName leftWheelRev, PinName rightWheelPwm, PinName rightWheelFwd,
            PinName rightWheelRev, PinName leftEncoder, PinName rightEncoder,
            PinName imuSda, PinName imuScl);

        /**
         * Robot Controller destructor.
         */
         ~RobotController();

        /**
         * Detect obstacles in 360-degree field of view around the robot.
         */
        void detectObstacles();

        /**
         * Follow trajectory set by user in C# GUI.
         */
        void followTrajectory();

    private:
        Motor leftWheel;
        Motor rightWheel;
        Encoder _leftEncoder;
        Encoder _rightEncoder;
        LSM9DS1 imu;
        Timer t;
        float yaw;
        float w1;
        float w2;
        float t1;
        float t2;
};

#endif /* ROBOT_CONTROLLER_H */