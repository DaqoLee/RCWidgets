
#pragma once
#include "Effect.h"
#include <dinput.h>
#include <iostream>
namespace RS21::direct_input{

/**
 * @if english
 * @brief Sinusoidal force effect class
 * @else
 * @brief The ETSine class 正弦力效果类
 * @endif
 */
class ETSine : public Effect
{
public:
    ETSine(Device* device);

    /**
     * @if english
     * @brief Obtain the strength of the current ETSine
     * @return The strength of the current ETSine
     * @else
     * @brief magnitude 获取当前ETSine的强度
     * @return 当前ETSine的强度
     * @endif
     */
    unsigned long magnitude();

    /**
     * @if english
     * @brief set the strength of the current ETSine
     * @param newMagnitude The strength of the current ETSine
     * @else
     * @brief setMagnitude 设置当前ETSine的强度
     * @param newMagnitude 设置的ETSine的强度值
     * @endif
     */
    void setMagnitude(unsigned long newMagnitude);

    /**
     * @if english
     * @brief Obtain offset for the condition
     * @return Offset for the condition, in the range from - 10,000 through 10,000.
     * @else
     * @brief 获取条件的偏移量
     * @return 条件的偏移量，范围从-10000到10000
     * @endif
     */
    long offset();

    /**
     * @if english
     * @brief set offset for the condition
     * @param offset Offset for the condition, in the range from - 10,000 through 10,000.
     * @else
     * @brief 设置条件的偏移量
     * @param offset 条件的偏移量，范围从-10000到10000
     * @endif
     */
    void setOffset(long newOffset);

    /**
     * @if english
     * @brief Obtain the current phase of ETSine
     * @return Current phase of ETSine
     * @else
     * @brief phase 获取当前ETSine相位
     * @return  当前ETSine的相位
     * @endif
     */
    unsigned long phase();

    /**
     * @if english
     * @brief set the current phase of ETSine
     * @param newPhase current phase of ETSine
     * @else
     * @brief 设置当前ETSine的相位
     * @param newPhase 设置的ETSine的相位
     * @endif
     */
    void setPhase(unsigned long newPhase);

    /**
     * @if english
     * @brief Obtain the cycle of the current ETSine
     * @return cycle of the current ETSine
     * @else
     * @brief 获取当前ETSine的周期
     * @return  当前ETSine的周期
     * @endif
     */
    unsigned long period();

    /**
     * @if english
     * @brief set the cycle of the current ETSine
     * @param newPhase cycle of the current ETSine
     * @else
     * @brief 设置当前ETSine的周期
     * @param newPeriod 设置的周期
     * @endif
     */
    void setPeriod(unsigned long newPeriod);


protected:
    virtual void downloadToDevice(LPDIRECTINPUTDEVICE8 device) override;
    DIPERIODIC m_diPeriodic;
};
}//RS21::directInput
