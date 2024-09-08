
#pragma once
#include "Effect.h"


namespace RS21::direct_input {

/**
 * @if english
 * @brief Inertia effect class
 * @else
 * @brief The ETDamper class 惯量效果类
 * @endif
 */
class ETInertia: public Effect
{
public:
    ETInertia(Device* device);
    //查看参数
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
 * @brief Obtain coefficient constant on the positive side of the offset
 * @return coefficient constant on the positive side of the offset, in the range from - 10,000 through 10,000.
 * @else
 * @brief 获取偏移正侧的系数常数
 * @return 偏移正侧的系数常数，范围从-10000到10000
 * @endif
 */
    long positiveCoefficient();
    /**
 * @if english
 * @brief Obtain Coefficient constant on the negative side of the offset
 * @return Coefficient constant on the negative side of the offset, in the range from - 10,000 through 10,000
 * If the device does not support separate positive and negative coefficients, the value of lNegativeCoefficient is ignored,
 * and the value of lPositiveCoefficient is used as both the positive and negative coefficients
 * @else
 * @brief 获取偏移负侧的系数常数
 * @return 偏移负侧的系数常数，范围从-10000到10000。
 * 如果设备不支持单独的正系数和负系数，则忽略lNegativeCoefficient的值，并将lPositiveCoefficiency的值用作正系数和负值
 * @endif
 */
    long negativeCoefficient();
    /**
 * @if english
 * @brief Obtain maximum force output on the positive side of the offset
 * @return Maximum force output on the positive side of the offset, in the range from 0 through 10,000.
 * If the device does not support force saturation, the value of this member is ignored.
 * @else
 * @brief 获得偏移正侧的最大力输出
 * @return 偏移正侧的最大力输出，范围从0到10000。如果设备不支持力饱和，则忽略此成员的值。
 * @endif
 */
    unsigned long positiveSaturation();
    /**
 * @if english
 * @brief Obtain maximum force output on the negative side of the offset
 * @return Maximum force output on the negative side of the offset, in the range from 0 through 10,000.
 * If the device does not support force saturation, the value of this member is ignored.
 * If the device does not support separate positive and negative saturation, the value of dwNegativeSaturation is ignored, and the value of dwPositiveSaturation is used as both the positive and negative saturation.
 * @else
 * @brief 获取偏移负侧的最大力输出
 * @return 偏移负侧的最大力输出，范围从0到10000。
 * 如果设备不支持力饱和，则忽略此成员的值。
 * 如果设备不支持单独的正饱和和负饱和，则忽略dwNegativeSaturation的值，并使用dwPositiveSaturation值作为正饱和和负饱和。
 * @endif
 */
    unsigned long negativeSaturation();
    /**
 * @if english
 * @brief Obtain region around lOffset in which the condition is not active
 * @return Region around lOffset in which the condition is not active, in the range from 0 through 10,000. In other words,
 * the condition is not active between lOffset minus lDeadBand and lOffset plus lDeadBand.
 * @else
 * @brief 获取lOffset周围条件未激活的区域
 * @return lOffset周围条件未激活的区域，范围从0到10000。换句话说，在lOffset减去lDeadBand和lOffset加上lDeadBnd之间，条件不活动。
 * @endif
 */
    long deadBand();

    /**
 * @if english
 * @brief set offset for the condition
 * @param offset Offset for the condition, in the range from - 10,000 through 10,000.
 * @else
 * @brief 设置条件的偏移量
 * @param offset 条件的偏移量，范围从-10000到10000
 * @endif
 */
    void setOffset(long offset);
    /**
 * @if english
 * @brief set coefficient constant on the positive side of the offset
 * @param newPositiveCoefficient coefficient constant on the positive side of the offset, in the range from - 10,000 through 10,000.
 * @else
 * @brief 设置偏移正侧的系数常数
 * @param newPositiveCoefficient 偏移正侧的系数常数，范围从-10000到10000
 * @endif
 */
    void setPositiveCoefficient(long newPositiveCoefficient);
    /**
 * @if english
 * @brief set Coefficient constant on the negative side of the offset
 * @param newNegativeCoefficient Coefficient constant on the negative side of the offset, in the range from - 10,000 through 10,000
 * If the device does not support separate positive and negative coefficients, the value of lNegativeCoefficient is ignored,
 * and the value of lPositiveCoefficient is used as both the positive and negative coefficients
 * @else
 * @brief 设置偏移负侧的系数常数
 * @param newNegativeCoefficient 偏移负侧的系数常数，范围从-10000到10000。
 * 如果设备不支持单独的正系数和负系数，则忽略lNegativeCoefficient的值，并将lPositiveCoefficiency的值用作正系数和负值
 * @endif
 */
    void setNegativeCoefficient(long newNegativeCoefficient);
    /**
 * @if english
 * @brief set maximum force output on the positive side of the offset
 * @param newPositiveSaturation Maximum force output on the positive side of the offset, in the range from 0 through 10,000.
 * If the device does not support force saturation, the value of this member is ignored.
 * @else
 * @brief 设置偏移正侧的最大力输出
 * @param newPositiveSaturation 偏移正侧的最大力输出，范围从0到10000。如果设备不支持力饱和，则忽略此成员的值。
 * @endif
 */
    void setPositiveSaturation(unsigned long newPositiveSaturation);
    /**
 * @if english
 * @brief set maximum force output on the negative side of the offset
 * @param newNegativeSaturation Maximum force output on the negative side of the offset, in the range from 0 through 10,000.
 * If the device does not support force saturation, the value of this member is ignored.
 * If the device does not support separate positive and negative saturation, the value of dwNegativeSaturation is ignored, and the value of dwPositiveSaturation is used as both the positive and negative saturation.
 * @else
 * @brief 设置偏移负侧的最大力输出
 * @param newNegativeSaturation 偏移负侧的最大力输出，范围从0到10000。
 * 如果设备不支持力饱和，则忽略此成员的值。
 * 如果设备不支持单独的正饱和和负饱和，则忽略dwNegativeSaturation的值，并使用dwPositiveSaturation值作为正饱和和负饱和。
 * @endif
 */
    void setNegativeSaturation(unsigned long newNegativeSaturation);
    /**
 * @if english
 * @brief set region around lOffset in which the condition is not active
 * @param newDeadBand Region around lOffset in which the condition is not active, in the range from 0 through 10,000. In other words,
 * the condition is not active between lOffset minus lDeadBand and lOffset plus lDeadBand.
 * @else
 * @brief 设置lOffset周围条件未激活的区域
 * @param newDeadBand lOffset周围条件未激活的区域，范围从0到10000。换句话说，在lOffset减去lDeadBand和lOffset加上lDeadBnd之间，条件不活动。
 * @endif
 */
    void setDeadBand(long newDeadBand);
protected:
    virtual void downloadToDevice(LPDIRECTINPUTDEVICE8 device) override;
    DICONDITION m_diPeriodic;
};
}//rs21::direct_input

