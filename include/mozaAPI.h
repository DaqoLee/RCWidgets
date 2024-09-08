#include <map>
#include <string>
#include <iostream>
#include "hid_struct.h"
#include "enumCode.h"
#include "effects.h"

#ifdef DLL_EXPORTS
#ifdef MATHLIBRARY_EXPORTS
#define WIN_API __declspec(dllexport)
#else
#define WIN_API __declspec(dllimport)
#endif
#else
#define WIN_API
#endif

namespace  moza {
/**
     * @if english
     * @brief load sdk
     * @else
     * @brief 加载sdk
     * @endif
     */
WIN_API void installMozaSDK();
/**
     * @if english
     * @brief remove sdk
     * @else
     * @brief 卸载sdk
     * @endif
     */
WIN_API void removeMozaSDK();

//力反馈
/**
     * @if english
     * @brief Create a sinusoidal force effector
     * @param id Window id
     * @param err Error code
     * @return Sinusoidal force effector
     * @else
     * @brief 创建正弦力效果器
     * @param id 窗口id
     * @param err 错误码
     * @return 正弦力效果器
     * @endif
     */
WIN_API std::shared_ptr<RS21::direct_input::ETSine> createWheelbaseETSine(HWND id, ERRORCODE& err);
/**
     * @if english
     * @brief Create a constant Force effector
     * @param id Window id
     * @param err Error code
     * @return Constant force effector
     * @else
     * @brief 创建恒定力效果器
     * @param id 窗口id
     * @param err 错误码
     * @return 恒定力效果器
     * @endif
     */
WIN_API std::shared_ptr<RS21::direct_input::ETConstantForce> createWheelbaseETConstantForce(HWND id, ERRORCODE& err);
/**
     * @if english
     * @brief Create a return force effector
     * @param id Window id
     * @param err Error code
     * @return Return force effector
     * @else
     * @brief 创建回中力效果器
     * @param id 窗口id
     * @param err 错误码
     * @return 回中力效果器
     * @endif
     */
WIN_API std::shared_ptr<RS21::direct_input::ETSpring> createWheelbaseETSpring(HWND id, ERRORCODE& err);
/**
     * @if english
     * @brief Create a dampener
     * @param id Window id
     * @param err Error code
     * @return dampener
     * @else
     * @brief 创建阻尼效果器
     * @param id 窗口id
     * @param err 错误码
     * @return 阻尼效果器
     * @endif
     */
WIN_API std::shared_ptr<RS21::direct_input::ETDamper> createWheelbaseETDamper(HWND id, ERRORCODE& err);
/**
     * @if english
     * @brief Create an inertia effector
     * @param id Window id
     * @param err Error code
     * @return Inertia effector
     * @else
     * @brief 创建惯性效果器
     * @param id 窗口id
     * @param err 错误码
     * @return 惯性效果器
     * @endif
     */
WIN_API std::shared_ptr<RS21::direct_input::ETInertia> createWheelbaseETInertia(HWND id, ERRORCODE& err);
/**
     * @if english
     * @brief Create a friction effector
     * @param id Window id
     * @param err Error code
     * @return friction effector
     * @else
     * @brief 创建摩擦力效果器
     * @param id 窗口id
     * @param err 错误码
     * @return 摩擦力效果器
     * @endif
     */
WIN_API std::shared_ptr<RS21::direct_input::ETFriction> createWheelbaseETFriction(HWND id, ERRORCODE &err);

//HID
/**
     * @if english
     * @brief Gets all hid data during the cycle
     * @param err Error code
     * @return hid data
     * @else
     * @brief 获取周期内hid的所有数据
     * @param err 错误码
     * @return hid数据
     * @endif
     */
WIN_API const HIDData* getHIDData(ERRORCODE& err);
/**
     * @if english
     * @brief Gets the enumerated value of the connected device
     * @param dev Device enum
     * @param err Error code
     * @return Device name
     * @else
     * @brief 获取所连接设备的枚举值
     * @param dev 设备枚举值
     * @param err 错误码
     * @return 设备名
     * @endif
     */
WIN_API const char* getDeviceParent(PRODUCTTYPE dev, ERRORCODE& err);

//电机
/**
     * @if english
     * @brief Get the motor limit Angle
     * @param err Error code
     * @return Motor limit Angle, effective range 90-2700
     * @else
     * @brief 获取电机的限位角度
     * @param err 错误码
     * @return 电机的限位角度，有效范围90-2700
     * @endif
     */
WIN_API const std::pair<int, int>* getMotorLimitAngle(ERRORCODE& err);

/**
     * @if english
     * @brief Get the motor limit Angle
     * @param id Window id
     * @param angle target angle,unit deg(degree)
     * @param speed target speed,unit rpm(Revolutions Per Minute)
     * @param err Error code
     * @return success
     * @else
     * @brief 电机转至角度
     * @param id 窗口id
     * @param angle 目标角度，单位：deg(degree)
     * @param speed 目标速度，单位：rpm(Revolutions Per Minute)
     * @param err 错误码
     * @return 是否执行成功
     * @endif
     */
WIN_API void motorMoveTo(HWND id,float angle, float speed, ERRORCODE &err);

WIN_API void motorStopMove();
/**
     * @if english
     * @brief Get the road sensitivity of the motor
     * @param err Error code
     * @return Motor road sensitivity, effective range 0-10
     * @else
     * @brief 获取电机的路感灵敏度
     * @param err 错误码
     * @return 电机的路感灵敏度，有效范围0-10
     * @endif
     */
WIN_API int getMotorRoadSensitivity(ERRORCODE& err);
/**
     * @if english
     * @brief Get the game force feedback intensity of the motor
     * @param err Error code
     * @return The game force feedback intensity of the motor, effective range 0-100
     * @else
     * @brief 获取电机的游戏力回馈强度
     * @param err 错误码
     * @return 电机的游戏力回馈强度，有效范围0-100
     * @endif
     */
WIN_API int getMotorFfbStrength(ERRORCODE& err);
/**
     * @if english
     * @brief Get the maximum steering wheel speed of the motor
     * @param err Error code
     * @return Motor steering wheel maximum speed, effective range 10-100
     * @else
     * @brief 获取电机的方向盘最大转速
     * @param err 错误码
     * @return 电机的方向盘最大转速，有效范围10-100
     * @endif
     */
WIN_API int getMotorLimitWheelSpeed(ERRORCODE& err);
/**
     * @if english
     * @brief Get the mechanical return strength of the motor
     * @param err Error code
     * @return Mechanical return strength of the motor, effective range 0-100
     * @else
     * @brief 获取电机的机械回中强度
     * @param err 错误码
     * @return 电机的机械回中强度，有效范围0-100
     * @endif
     */
WIN_API int getMotorSpringStrength(ERRORCODE& err);
/**
     * @if english
     * @brief Get the mechanical damping of the motor
     * @param err Error code
     * @return Mechanical damping of motor, effective range 0-100
     * @else
     * @brief 获取获取电机的机械阻尼
     * @param err 错误码
     * @return 电机的机械阻尼,有效范围0-100
     * @endif
     */
WIN_API int getMotorNaturalDamper(ERRORCODE& err);
/**
     * @if english
     * @brief Get the mechanical friction of the motor
     * @param err Error code
     * @return Mechanical friction of motor, effective range 0-100
     * @else
     * @brief 获取获取电机的机械摩擦
     * @param err 错误码
     * @return 电机的机械摩擦,有效范围0-100
     * @endif
     */
WIN_API int getMotorNaturalFriction(ERRORCODE& err);
/**
     * @if english
     * @brief Get the velocity damping of the motor
     * @param err Error code
     * @return Motor damping with speed, effective range 0-100
     * @else
     * @brief 获取电机的随速阻尼
     * @param err 错误码
     * @return 电机的随速阻尼,有效范围0-100
     * @endif
     */
WIN_API int getMotorSpeedDamping(ERRORCODE& err);
/**
     * @if english
     * @brief Get the maximum output torque limit of the motor
     * @param err Error code
     * @return Motor maximum output torque limit, effective range 50-100
     * @else
     * @brief 获取电机的最大输出扭矩限制
     * @param err 错误码
     * @return 电机的最大输出扭矩限制,有效范围50-100
     * @endif
     */
WIN_API int getMotorPeakTorque(ERRORCODE& err);
/**
     * @if english
     * @brief Get the actual steering wheel inertia ratio of the motor
     * @param err Error code
     * @return The actual inertia ratio of the steering wheel of the motor, effective range 100-4000
     * @else
     * @brief 获取电机的方向盘实际惯量比
     * @param err 错误码
     * @return 电机的方向盘实际惯量比,有效范围100-4000
     * @endif
     */
WIN_API int getMotorNaturalInertiaRatio(ERRORCODE& err);
/**
     * @if english
     * @brief Get the natural inertia of the motor
     * @param err Error code
     * @return Natural inertia of the motor, effective range 100-500
     * @else
     * @brief 获取电机的自然惯量
     * @param err 错误码
     * @return 电机的自然惯量,有效范围100-500
     * @endif
     */
WIN_API int getMotorNaturalInertia(ERRORCODE& err);
/**
     * @if english
     * @brief Get the velocity damping starting point of the motor
     * @param err Error code
     * @return Velocity damping starting point of the motor, effective range 0-400
     * @else
     * @brief 获取电机的随速阻尼起始点
     * @param err 错误码
     * @return 电机的随速阻尼起始点,有效范围0-400
     * @endif
     */
WIN_API int getMotorSpeedDampingStartPoint(ERRORCODE& err);
/**
     * @if english
     * @brief Get the motor hand off the protective switch
     * @param err Error code
     * @return Motor hand off protection switch, effective range 0-1
     * @else
     * @brief 获取电机的手离开保护开关
     * @param err 错误码
     * @return 电机的手离开保护开关,有效范围0-1
     * @endif
     */
WIN_API int getMotorHandsOffProtection(ERRORCODE& err);
/**
     * @if english
     * @brief Get the motor's game force reverse switch
     * @param err Error code
     * @return Motor game force reverse switch, effective range 0-1
     * @else
     * @brief 获取电机的游戏力反向开关
     * @param err 错误码
     * @return 电机的游戏力反向开关,有效范围0-1
     * @endif
     */
WIN_API int getMotorFfbReverse(ERRORCODE& err);
/**
     * @if english
     * @brief Get the frequency of the motor's road awareness equalizer
     * @param err Error code
     * @return Frequency of road sensing equalizer of motor,EqualizerAmp7_5; EqualizerAmp13 EqualizerAmp22_5, EqualizerAmp39 EqualizerAmp55, [0,500], EqualizerAmp100 [0100]
     * @else
     * @brief 获取电机的路面感知均衡器频点
     * @param err 错误码
     * @return 电机的路面感知均衡器频点,EqualizerAmp7_5;EqualizerAmp13,EqualizerAmp22_5,EqualizerAmp39,EqualizerAmp55,[0,500],EqualizerAmp100[0,100]
     * @endif
     */
WIN_API const std::map<std::string, int>* getMotorEqualizerAmp(ERRORCODE& err);

/**
     * @if english
     * @brief Set the motor limit Angle
     * @param limitAngle Motor limitAngle, effective range 90-2000
     * @param gameMaximumAngle game limitAngle, effective range 90-limitAngle
     * @return Error code
     * @else
     * @brief 设置电机的限位角度
     * @param limitAngle 电机的限位角度，有效范围90-2000
     * @param gameMaximumAngle 游戏限位角度，有效范围90-limitAngle
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorLimitAngle(int limitAngle, int gameMaximumAngle);
/**
     * @if english
     * @brief Set the road sensitivity of the motor
     * @param v Motor road sensitivity, effective range 0-10
     * @return Error code
     * @else
     * @brief 设置电机的路感灵敏度
     * @param v 电机的路感灵敏度，有效范围0-10
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorRoadSensitivity(int v);
/**
     * @if english
     * @brief Set the game force feedback intensity of the motor
     * @param v The game force feedback intensity of the motor, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置电机的游戏力回馈强度
     * @param v 电机的游戏力回馈强度，有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorFfbStrength(int v);
/**
     * @if english
     * @brief Set the maximum steering wheel speed of the motor
     * @param v Motor steering wheel maximum speed, effective range 10-100
     * @return Error code
     * @else
     * @brief 设置电机的方向盘最大转速
     * @param v 电机的方向盘最大转速，有效范围10-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorLimitWheelSpeed(int v);
/**
     * @if english
     * @brief Set the mechanical return strength of the motor
     * @param v Mechanical return strength of the motor, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置电机的机械回中强度
     * @param v 电机的机械回中强度，有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorSpringStrength(int v);
/**
     * @if english
     * @brief Set to get the mechanical damping of the motor
     * @param v Mechanical damping of motor, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置获取电机的机械阻尼
     * @param v 电机的机械阻尼,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorNaturalDamper(int v);
/**
     * @if english
     * @brief Set to get the mechanical friction of the motor
     * @param v Mechanical friction of motor, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置获取电机的机械摩擦
     * @param v 电机的机械摩擦,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorNaturalFriction(int v);
/**
     * @if english
     * @brief Set the speed damping of the motor
     * @param v Motor damping with speed, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置电机的随速阻尼
     * @param v 电机的随速阻尼,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorSpeedDamping(int v);
/**
     * @if english
     * @brief Set the maximum output torque limit of the motor
     * @param v Motor maximum output torque limit, effective range 50-100
     * @return Error code
     * @else
     * @brief 设置电机的最大输出扭矩限制
     * @param v 电机的最大输出扭矩限制,有效范围50-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorPeakTorque(int v);
/**
     * @if english
     * @brief Set the actual steering wheel inertia ratio of the motor
     * @param v The actual inertia ratio of the steering wheel of the motor, effective range 100-4000
     * @return Error code
     * @else
     * @brief 设置电机的方向盘实际惯量比
     * @param v 电机的方向盘实际惯量比,有效范围100-4000
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorNaturalInertiaRatio(int v);
/**
     * @if english
     * @brief Set the natural inertia of the motor
     * @param v Natural inertia of the motor, effective range 100-500
     * @return Error code
     * @else
     * @brief 设置电机的自然惯量
     * @param v 电机的自然惯量,有效范围100-500
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorNaturalInertia(int v);
/**
     * @if english
     * @brief Set the velocity damping starting point of the motor
     * @param v Velocity damping starting point of the motor, effective range 0-400
     * @return Error code
     * @else
     * @brief 设置电机的随速阻尼起始点
     * @param v 电机的随速阻尼起始点,有效范围0-400
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorSpeedDampingStartPoint(int v);
/**
     * @if english
     * @brief Set motor hand off protection switch
     * @param v Motor hand off protection switch, effective range 0-1
     * @return Error code
     * @else
     * @brief 设置电机的手离开保护开关
     * @param v 电机的手离开保护开关,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorHandsOffProtection(int v);
/**
     * @if english
     * @brief Set the game force reverse switch of the motor
     * @param v Motor game force reverse switch, effective range 0-1
     * @return Error code
     * @else
     * @brief 设置电机的游戏力反向开关
     * @param v 电机的游戏力反向开关,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorFfbReverse(int v);
/**
     * @if english
     * @brief Set the frequency of the motor's road awareness equalizer
     * @param v Frequency of the motor's road sense equalizer,EqualizerAmp7_5;EqualizerAmp13,EqualizerAmp22_5,EqualizerAmp39,EqualizerAmp55,[0,500],EqualizerAmp100[0,100]
     * @return Error code
     * @else
     * @brief 设置电机的路面感知均衡器频点
     * @param v 电机的路面感知均衡器频点,EqualizerAmp7_5;EqualizerAmp13,EqualizerAmp22_5,EqualizerAmp39,EqualizerAmp55,[0,500],EqualizerAmp100[0,100]
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setMotorEqualizerAmp(const std::map<std::string, int>& v);
/**
     * @if english
     * @brief Soft restart of motor
     * @return Error code
     * @else
     * @brief 电机软重启
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE SoftReboot();

//方向盘
/**
     * @if english
     * @brief Steering wheel alignment
     * @return Error code
     * @else
     * @brief 方向盘对中
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE CenterWheel();
/**
     * @if english
     * @brief Get steering wheel indicator brightness
     * @param err Error code
     * @return Steering wheel indicator brightness, effective range 0-100
     * @else
     * @brief 获取方向盘的指示灯亮度
     * @param err 错误码
     * @return 方向盘的指示灯亮度,有效范围0-100
     * @endif
     */
WIN_API int getSteeringWheelShiftIndicatorBrightness(ERRORCODE& err);
/**
     * @if english
     * @brief Get the steering wheel's clutch pattern
     * @param err Error code
     * @return Steering wheel clutch mode, effective range 1-3
     * @else
     * @brief 获取方向盘的离合拨片模式
     * @param err 错误码
     * @return 方向盘的离合拨片模式,有效范围1-3
     * @endif
     */
WIN_API int getSteeringWheelClutchPaddleAxisMode(ERRORCODE& err);
/**
     * @if english
     * @brief Get the clutch combination value of the steering wheel
     * @param err Error code
     * @return Steering wheel clutch combination value, effective range 0-100
     * @else
     * @brief 获取方向盘的离合拨片组合值
     * @param err 错误码
     * @return 方向盘的离合拨片组合值,有效范围0-100
     * @endif
     */
WIN_API int getSteeringWheelClutchPaddleCombinePos(ERRORCODE& err);
/**
     * @if english
     * @brief Get the steering wheel's band knob mode
     * @param err Error code
     * @return Steering wheel's band knob mode, effective range 0-1
     * @else
     * @brief 获取方向盘的波段旋钮模式
     * @param err 错误码
     * @return 方向盘的波段旋钮模式,有效范围0-1
     * @endif
     */
WIN_API int getSteeringWheelKnobMode(ERRORCODE& err);
/**
     * @if english
     * @brief Get the joystick pattern for the steering wheel
     * @param err Error code
     * @return Rocker mode for steering wheel, effective range 0-1
     * @else
     * @brief 获取方向盘的摇杆模式
     * @param err 错误码
     * @return 方向盘的摇杆模式,有效范围0-1
     * @endif
     */
WIN_API int getSteeringWheelJoystickHatswitchMode(ERRORCODE& err);
/**
     * @if english
     * @brief Get the steering wheel's indicator switch mode
     * @param err Error code
     * @return Steering wheel indicator switch mode, effective range 1-3
     * @else
     * @brief 获取方向盘的指示灯开关模式
     * @param err 错误码
     * @return 方向盘的指示灯开关模式,有效范围1-3
     * @endif
     */
WIN_API int getSteeringWheelShiftIndicatorSwitch(ERRORCODE& err);
/**
     * @if english
     * @brief Get the steering wheel indicator display mode
     * @param err Error code
     * @return Steering wheel indicator display mode, effective range 0-1
     * @else
     * @brief 获取方向盘的指示灯显示模式
     * @param err 错误码
     * @return 方向盘的指示灯显示模式,有效范围0-1
     * @endif
     */
WIN_API int getSteeringWheelShiftIndicatorMode(ERRORCODE& err);
/**
     * @if english
     * @brief Get the steering wheel indicator color
     * @param err Error code
     * @return Indicator color
     * @else
     * @brief 获取方向盘的指示灯颜色
     * @param err 错误码
     * @return 指示灯颜色
     * @endif
     */
WIN_API const std::vector<std::string>* getSteeringWheelShiftIndicatorColor(ERRORCODE& err);
/**
     * @if english
     * @brief Gets the steering wheel's indicator speed indication percentage
     * @param err Error code
     * @return Steering wheel indicator speed indicates percentage
     * @else
     * @brief 获取方向盘的指示灯转速提示百分比
     * @param err 错误码
     * @return 方向盘的指示灯转速提示百分比
     * @endif
     */
WIN_API const std::vector<int>* getSteeringWheelShiftIndicatorLightRpm(ERRORCODE& err);
/**
     * @if english
     * @brief Gets the speed unit of the display
     * @param err Error code
     * @return The speed unit of the display, effective range 0-1
     * @else
     * @brief 获取显示屏的速度单位
     * @param err 错误码
     * @return 显示屏的速度单位,有效范围0-1
     * @endif
     */
WIN_API int getSteeringWheelSpeedUnit(ERRORCODE& err);
/**
     * @if english
     * @brief Get the temperature unit of the display
     * @param err Error code
     * @return Temperature unit of the display, effective range 0-1
     * @else
     * @brief 获取显示屏的温度单位
     * @param err 错误码
     * @return 显示屏的温度单位,有效范围0-1
     * @endif
     */
WIN_API int getSteeringWheelTemperatureUnit(ERRORCODE& err);
/**
     * @if english
     * @brief Gets the screen brightness of the display
     * @param err Error code
     * @return Display screen brightness, effective range 0-100
     * @else
     * @brief 获取显示屏的屏幕亮度
     * @param err 错误码
     * @return 显示屏的屏幕亮度,有效范围0-100
     * @endif
     */
WIN_API int getSteeringWheelScreenBrightness(ERRORCODE& err);
/**
     * @if english
     * @brief Get UI list
     * @param err Error code
     * @return UI list
     * @else
     * @brief 获取UI列表
     * @param err 错误码
     * @return UI列表
     * @endif
     */
WIN_API const std::map<int, std::string>* getSteeringWheelScreenUIList(ERRORCODE& err);
/**
     * @if english
     * @brief Get the current UI
     * @param err Error code
     * @return current UI
     * @else
     * @brief 获取当前UI
     * @param err 错误码
     * @return 当前UI
     * @endif
     */
WIN_API int getSteeringWheelScreenCurrentUI(ERRORCODE& err);

/**
     * @if english
     * @brief Set steering wheel indicator brightness
     * @param v Steering wheel indicator brightness, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置方向盘的指示灯亮度
     * @param v 方向盘的指示灯亮度,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelShiftIndicatorBrightness(int v);
/**
     * @if english
     * @brief Set the steering wheel's clutch pattern
     * @param v Steering wheel clutch mode, effective range 1-3
     * @return Error code
     * @else
     * @brief 设置方向盘的离合拨片模式
     * @param v 方向盘的离合拨片模式,有效范围1-3
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelClutchPaddleAxisMode(int v);
/**
     * @if english
     * @brief Set the clutch combination value of the steering wheel
     * @param v Steering wheel clutch combination value, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置方向盘的离合拨片组合值
     * @param v 方向盘的离合拨片组合值,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelClutchPaddleCombinePos(int v);
/**
     * @if english
     * @brief Set the steering wheel's band knob mode
     * @param v Steering wheel's band knob mode, effective range 0-1
     * @return Error code
     * @else
     * @brief 设置方向盘的波段旋钮模式
     * @param v 方向盘的波段旋钮模式,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelKnobMode(int v);
/**
     * @if english
     * @brief Set the rocker mode for the steering wheel
     * @param v Rocker mode for steering wheel, effective range 0-1
     * @return Error code
     * @else
     * @brief 设置方向盘的摇杆模式
     * @param v 方向盘的摇杆模式,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelJoystickHatswitchMode(int v);
/**
     * @if english
     * @brief Set the steering wheel indicator switch mode
     * @param v Steering wheel indicator switch mode, effective range 1-3
     * @return Error code
     * @else
     * @brief 设置方向盘的指示灯开关模式
     * @param v 方向盘的指示灯开关模式,有效范围1-3
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelShiftIndicatorSwitch(int v);
/**
     * @if english
     * @brief Set the steering wheel indicator display mode
     * @param v Steering wheel indicator display mode, effective range 0-1
     * @return Error code
     * @else
     * @brief 设置方向盘的指示灯显示模式
     * @param v 方向盘的指示灯显示模式,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelShiftIndicatorMode(int v);
/**
     * @if english
     * @brief Set the steering wheel indicator color
     * @param v Indicator color
     * @return Error code
     * @else
     * @brief 设置方向盘的指示灯颜色
     * @param v 指示灯颜色
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelShiftIndicatorColor(const std::vector<std::string>& v);
/**
     * @if english
     * @brief Set the steering wheel's indicator speed indication percentage
     * @param v Steering wheel indicator speed indication percentage, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置方向盘的指示灯转速提示百分比
     * @param v 方向盘的指示灯转速提示百分比,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelShiftIndicatorLightRpm(const std::vector<int>& v);
/**
     * @if english
     * @brief Set the speed unit of the display
     * @param v The speed unit of the display, effective range 0-1
     * @return Error code
     * @else
     * @brief 设置显示屏的速度单位
     * @param v 显示屏的速度单位,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelSpeedUnit(int v);
/**
     * @if english
     * @brief Set the temperature unit of the display
     * @param v Temperature unit of the display, effective range 0-1
     * @return Error code
     * @else
     * @brief 设置显示屏的温度单位
     * @param v 显示屏的温度单位,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelTemperatureUnit(int v);
/**
     * @if english
     * @brief Set the screen brightness of the display
     * @param v Display screen brightness, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置显示屏的屏幕亮度
     * @param v 显示屏的屏幕亮度,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelScreenBrightness(int v);
/**
     * @if english
     * @brief Set current UI
     * @param v current UI
     * @return Error code
     * @else
     * @brief 设置当前UI
     * @param v 当前UI
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setSteeringWheelScreenCurrentUI(int v);

//显示器
/**
     * @if english
     * @brief Get the speed unit of the display
     * @param err Error code
     * @return The speed unit of the display, effective range 0-1, 0-metric 1-imperial
     * @else
     * @brief 获取显示屏的速度单位
     * @param err 错误码
     * @return 显示屏的速度单位,有效范围0-1,0-公制 1-英制
     * @endif
     */
WIN_API int getDisplayScreenSpeedUnit(ERRORCODE& err);
/**
     * @if english
     * @brief Get the temperature unit of the display
     * @param err Error code
     * @return Temperature unit of the display, effective range 0-1, 0-degrees Celsius, 1-degrees Fahrenheit
     * @else
     * @brief 获取显示屏的温度单位
     * @param err 错误码
     * @return 显示屏的温度单位,有效范围0-1,0-摄氏度 1-华氏度
     * @endif
     */
WIN_API int getDisplayScreenTemperatureUnit(ERRORCODE& err);
/**
     * @if english
     * @brief Get the screen brightness of the display
     * @param err Error code
     * @return Display screen brightness, effective range 0-100
     * @else
     * @brief 获取显示屏的屏幕亮度
     * @param err 错误码
     * @return 显示屏的屏幕亮度,有效范围0-100
     * @endif
     */
WIN_API int getDisplayScreenScreenBrightness(ERRORCODE& err);
/**
     * @if english
     * @brief Get the display UI list
     * @param err Error code
     * @return UI list
     * @else
     * @brief 获取显示屏UI列表
     * @param err 错误码
     * @return UI列表
     * @endif
     */
WIN_API const std::map<int, std::string>* getDisplayScreenScreenUIList(ERRORCODE& err);
/**
     * @if english
     * @brief Get the current UI of the display
     * @param err Error code
     * @return current UI
     * @else
     * @brief 获取显示屏当前UI
     * @param err 错误码
     * @return 当前UI
     * @endif
     */
WIN_API int getDisplayScreenScreenCurrentUI(ERRORCODE& err);

/**
     * @if english
     * @brief Set the speed unit of the display
     * @param v The speed unit of the display, effective range 0-1, 0-metric 1-imperial
     * @return Error code
     * @else
     * @brief 设置显示屏的速度单位
     * @param v 显示屏的速度单位,有效范围0-1,0-公制 1-英制
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setDisplayScreenSpeedUnit(int v);
/**
     * @if english
     * @brief Set the temperature unit of the display
     * @param v Temperature unit of the display, effective range 0-1, 0-degrees Celsius, 1-degrees Fahrenheit
     * @return Error code
     * @else
     * @brief 设置显示屏的温度单位
     * @param v 显示屏的温度单位,有效范围0-1,0-摄氏度 1-华氏度
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setDisplayScreenTemperatureUnit(int v);
/**
     * @if english
     * @brief Set the screen brightness of the display
     * @param v Display screen brightness, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置显示屏的屏幕亮度
     * @param v 显示屏的屏幕亮度,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setDisplayScreenScreenBrightness(int v);
/**
     * @if english
     * @brief Set the current UI of the display
     * @param v UI id
     * @return Error code
     * @else
     * @brief 设置显示屏当前UI
     * @param v UI id
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setDisplayScreenScreenCurrentUI(int v);

//踏板
/**
     * @if english
     * @brief Get the clutch output direction of the pedal
     * @param err Error code
     * @return Pedal clutch output direction, effective range 0-1, 0-forward 1-reverse
     * @else
     * @brief 获取踏板的离合输出方向
     * @param err 错误码
     * @return 踏板的离合输出方向,有效范围0-1,0-正向 1-反向
     * @endif
     */
WIN_API int getPedalClutchOutDir(ERRORCODE& err);
/**
     * @if english
     * @brief Get the brake output direction of the pedal
     * @param err Error code
     * @return Pedal brake output direction, effective range 0-1, 0-forward 1-reverse
     * @else
     * @brief 获取踏板的刹车输出方向
     * @param err 错误码
     * @return 踏板的刹车输出方向,有效范围0-1,0-正向 1-反向
     * @endif
     */
WIN_API int getPedalBrakeOutDir(ERRORCODE& err);
/**
     * @if english
     * @brief Get the throttle output direction of the pedal
     * @param err Error code
     * @return Pedal throttle output direction, effective range 0-1, 0-forward 1-reverse
     * @else
     * @brief 获取踏板的油门输出方向
     * @param err 错误码
     * @return 踏板的油门输出方向,有效范围0-1,0-正向 1-反向
     * @endif
     */
WIN_API int getPedalAccOutDir(ERRORCODE& err);
/**
     * @if english
     * @brief Get the percentage of pressure binding points of the pedal
     * @param err Error code
     * @return Pedal pressure binding percentage, effective range 0-100
     * @else
     * @brief 获取踏板的压力结合点百分比
     * @param err 错误码
     * @return 踏板的压力结合点百分比,有效范围0-100
     * @endif
     */
WIN_API int getPedalBrakePressCombine(ERRORCODE& err);
/**
     * @if english
     * @brief Get the pedal clutch output nonlinear adjustment
     * @param err Error code
     * @return Pedal clutch output nonlinear adjustment
     * @else
     * @brief
     * @param err 错误码
     * @return 踏板离合输出非线性调整
     * @endif
     */
WIN_API const std::vector<int>* getPedalClutchNonLinear(ERRORCODE& err);
/**
     * @if english
     * @brief Get the pedal throttle output nonlinear adjustment
     * @param err Error code
     * @return Pedal throttle output nonlinear adjustment
     * @else
     * @brief 获取踏板油门输出非线性调整
     * @param err 错误码
     * @return 踏板油门输出非线性调整
     * @endif
     */
WIN_API const std::vector<int>* getPedalAccNonLinear(ERRORCODE& err);
/**
     * @if english
     * @brief Get the pedal brake output nonlinear adjustment
     * @param err Error code
     * @return Pedal brake output nonlinear adjustment
     * @else
     * @brief 获取踏板刹车输出非线性调整
     * @param err 错误码
     * @return 踏板刹车输出非线性调整
     * @endif
     */
WIN_API const std::vector<int>* getPedalBrakeNonLinear(ERRORCODE& err);

/**
     * @if english
     * @brief Pedal clutch calibration begins
     * @return Error code
     * @else
     * @brief 踏板离合标定开始
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE ClutchCalibrateStrat();
/**
     * @if english
     * @brief Pedal clutch calibration is complete
     * @return Error code
     * @else
     * @brief 踏板离合标定结束
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE ClutchCalibrateFinish();
/**
     * @if english
     * @brief Pedal throttle calibration begins
     * @return Error code
     * @else
     * @brief 踏板油门标定开始
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE AccCalibrateStrat();
/**
     * @if english
     * @brief Pedal throttle calibration is complete
     * @return Error code
     * @else
     * @brief 踏板油门标定结束
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE AccCalibrateFinish();
/**
     * @if english
     * @brief Pedal brake calibration begins
     * @return Error code
     * @else
     * @brief 踏板刹车标定开始
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE BrakeCalibrateStrat();
/**
     * @if english
     * @brief Pedal brake calibration complete
     * @return Error code
     * @else
     * @brief 踏板刹车标定结束
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE BrakeCalibrateFinish();
/**
     * @if english
     * @brief Set the clutch output direction of the pedal
     * @param v Pedal clutch output direction, effective range 0-1, 0-forward 1-reverse
     * @return Error code
     * @else
     * @brief 设置踏板的离合输出方向
     * @param v 踏板的离合输出方向,有效范围0-1,0-正向 1-反向
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setPedalClutchOutDir(int v);
/**
     * @if english
     * @brief Set the brake output direction of the pedal
     * @param v Pedal brake output direction, effective range 0-1, 0-forward 1-reverse
     * @return Error code
     * @else
     * @brief 设置踏板的刹车输出方向
     * @param v 踏板的刹车输出方向,有效范围0-1,0-正向 1-反向
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setPedalBrakeOutDir(int v);
/**
     * @if english
     * @brief Set the throttle output direction of the pedal
     * @param v Pedal throttle output direction, effective range 0-1, 0-forward 1-reverse
     * @return Error code
     * @else
     * @brief 设置踏板的油门输出方向
     * @param v 踏板的油门输出方向,有效范围0-1,0-正向 1-反向
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setPedalAccOutDir(int v);
/**
     * @if english
     * @brief Set the percentage of pressure binding points for the pedal
     * @param v Pedal pressure binding percentage, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置踏板的压力结合点百分比
     * @param v 踏板的压力结合点百分比,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setPedalBrakePressCombine(int v);
/**
     * @if english
     * @brief Set pedal clutch output nonlinear adjustment
     * @param v Pedal clutch output nonlinear adjustment, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置踏板离合输出非线性调整
     * @param v 踏板离合输出非线性调整，有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setPedalClutchNonLinear(const std::vector<int>& v);
/**
     * @if english
     * @brief Set pedal throttle output nonlinear adjustment
     * @param v Pedal throttle output nonlinear adjustment, effective range 0-100
     * @return Error code
     * @else
     * @brief 设置踏板油门输出非线性调整
     * @param v 踏板油门输出非线性调整，有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setPedalAccNonLinear(const std::vector<int>& v);
/**
     * @if english
     * @brief Set pedal brake output nonlinear adjustment
     * @param v Pedal brake output nonlinear adjustment
     * @return Error code
     * @else
     * @brief 设置踏板刹车输出非线性调整
     * @param v 踏板刹车输出非线性调整
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setPedalBrakeNonLinear(const std::vector<int>& v);

//手刹
/**
     * @if english
     * @brief Get the output direction of the handbrake
     * @param err Error code
     * @return Hand brake output direction, effective range 0-1
     * @else
     * @brief 获取手刹的输出方向
     * @param err 错误码
     * @return 手刹的输出方向,有效范围0-1
     * @endif
     */
WIN_API int getHandbrakeOutDir(ERRORCODE& err);
/**
     * @if english
     * @brief Get the application mode of the handbrake
     * @param err Error code
     * @return Handbrake application mode, effective range 0-1
     * @else
     * @brief 获取手刹的应用模式
     * @param err 错误码
     * @return 手刹的应用模式,有效范围0-1
     * @endif
     */
WIN_API int getHandbrakeApplicationMode(ERRORCODE& err);
/**
     * @if english
     * @brief Get the nonlinear adjustment of handbrake output
     * @param err Error code
     * @return Handbrake output nonlinear adjustment
     * @else
     * @brief 获取手刹输出非线性调整
     * @param err 错误码
     * @return 手刹输出非线性调整
     * @endif
     */
WIN_API const std::vector<int>* getHandbrakeNonLinear(ERRORCODE& err);

/**
     * @if english
     * @brief Handbrake calibration Start
     * @return Error code
     * @else
     * @brief 手刹标定开始
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE HandbrakeCalibrateStart();
/**
     * @if english
     * @brief Handbrake calibration complete
     * @return Error code
     * @else
     * @brief 手刹标定结束
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE HandbrakeCalibrateFinish();
/**
     * @if english
     * @brief Set the output direction of the handbrake
     * @param v Hand brake output direction, effective range 0-1
     * @return Error code
     * @else
     * @brief 设置手刹的输出方向
     * @param v 手刹的输出方向,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setHandbrakeOutDir(int v);
/**
     * @if english
     * @brief Set the application mode of the handbrake
     * @param v Handbrake application mode, effective range 0-1
     * @return Error code
     * @else
     * @brief 设置手刹的应用模式
     * @param v 手刹的应用模式,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setHandbrakeApplicationMode(int v);
/**
     * @if english
     * @brief Set the handbrake output nonlinear adjustment
     * @param v Handbrake output nonlinear adjustment
     * @return Error code
     * @else
     * @brief 设置手刹输出非线性调整
     * @param v 手刹输出非线性调整
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setHandbrakeNonLinear(const std::vector<int>& v);

//换挡器
/**
     * @if english
     * @brief Get the downshift refill output percentage of the shifter
     * @param err Error code
     * @return Downshift oil output percentage of the stopper, effective range 0-100
     * @else
     * @brief 获取换挡器的降档补油输出百分比
     * @param err 错误码
     * @return 挡器的降档补油输出百分比,有效范围0-100
     * @endif
     */
WIN_API int getHandingShifterAutoBlipOutput(ERRORCODE& err);
/**
     * @if english
     * @brief Get the downshift refill duration of the shifter
     * @param err Error code
     * @return Downshift replenishment duration of gear shifter, effective range 0-1000
     * @else
     * @brief 获取换挡器的降档补油持续时间
     * @param err 错误码
     * @return 换挡器的降档补油持续时间,有效范围0-1000
     * @endif
     */
WIN_API int getHandingShifterAutoBlipDuration(ERRORCODE& err);
/**
     * @if english
     * @brief Get the downshift refill switch of the gear shifter
     * @param err Error code
     * @return Downshift oil refill switch of gear shifter, effective range 0-1
     * @else
     * @brief 获取换挡器的降档补油开关
     * @param err 错误码
     * @return 换挡器的降档补油开关,有效范围0-1
     * @endif
     */
WIN_API int getHandingShifterAutoBlipSwitch(ERRORCODE& err);

/**
     * @if english
     * @brief Gear shifter start calibration
     * @return Error code
     * @else
     * @brief 换挡器开始标定
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE ShifterCalibrateStart();
/**
     * @if english
     * @brief Shift end calibration
     * @return Error code
     * @else
     * @brief 换挡器结束标定
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE ShifterCalibrateFinish();
/**
     * @if english
     * @brief Get the downshift refill output percentage of the shifter
     * @param v Downshift oil output percentage of the stopper, effective range 0-100
     * @return Error code
     * @else
     * @brief 获取换挡器的降档补油输出百分比
     * @param v 挡器的降档补油输出百分比,有效范围0-100
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setHandingShifterAutoBlipOutput(int v);
/**
     * @if english
     * @brief Get the downshift refill duration of the shifter
     * @param v Downshift replenishment duration of gear shifter, effective range 0-1000
     * @return Error code
     * @else
     * @brief 获取换挡器的降档补油持续时间
     * @param v 换挡器的降档补油持续时间,有效范围0-1000
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setHandingShifterAutoBlipDuration(int v);
/**
     * @if english
     * @brief Get the downshift refill switch of the gear shifter
     * @param v Downshift oil refill switch of gear shifter, effective range 0-1
     * @return Error code
     * @else
     * @brief 获取换挡器的降档补油开关
     * @param v 换挡器的降档补油开关,有效范围0-1
     * @return 错误码
     * @endif
     */
WIN_API ERRORCODE setHandingShifterAutoBlipSwitch(int v);

}
