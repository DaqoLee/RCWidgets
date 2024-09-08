#pragma once
#include <dinput.h>
#include "Effect.h"
namespace RS21::direct_input {
/**
 * @if english
 * @brief Constant force effect class
 * 1.Specialization attribute: magnitude
 * @else
 * @brief The ETConstantForce class 常量力效果类
 * 1. 特化属性：强度，magnitude
 * @endif
 */
class ETConstantForce: public Effect
{
public:
    ETConstantForce(Device* device);

    /**
     * @if english
     * @brief Obtain the strength of the current ETConstantForce
     * @return The strength of the current ETConstantForce
     * @else
     * @brief 获取当前ETConstantForce的强度
     * @return 当前ETConstantForce的强度
     * @endif
     */
    long magnitude();

    /**
     * @if english
     * @brief set the strength of the current ETConstantForce
     * @param newMagnitude The strength of the current ETConstantForce
     * @else
     * @brief 设置当前ETConstantForce的强度
     * @param newMagnitude 设置的ETConstantForce的强度值
     * @endif
     */
    void setMagnitude(long newMagnitude);

protected:
    /**
     * @if english
     * @brief Device creation force (initialization)
     * @param device win Device interface instance
     * @else
     * @brief 设备创建力（初始化）
     * @param device win设备接口实例
     * @endif
     */
    void downloadToDevice(LPDIRECTINPUTDEVICE8 device) override;
    DICONSTANTFORCE m_diPeriodic;


};
}//RS21::directInput
