#pragma once
#include <cstdint>
#include <string>
#include <dinput.h>
#include <memory>
#include <map>
namespace RS21::direct_input{
class Device;
extern unsigned int DI_MSECONDS;
/**
 * @if english
 * @brief Effect Abstract Class
 * 1. Provide API for effect start and end
 * 2. Provide interfaces for obtaining and modifying general parameters
 * @else
 * @brief The Effect class 效果抽象类
 * 1. 提供效果开始、结束API
 * 2. 提供通用参数的获取、修改接口
 * @endif
 */
class Effect
{
public:
    /**
     * @if english
     * @brief start Force effect
     * @else
     * @brief 力效果启动
     * @endif
     */
    void start();
    /**
     * @if english
     * @brief stop Force effect
     * @else
     * @brief stop 停止力效果
     * @endif
     */
    void stop();

    /**
     * @if english
     * @brief Set the power level
     * @param newAttackLevel Power level
     * @else
     * @brief 设置发力级别
     * @param newAttackLevel 发力级别
     * @endif
     */
    void setAttackLevel(const unsigned long newAttackLevel = 0);
    /**
     * @if english
     * @brief Obtain Power Level
     * @return Power level
     * @else
     * @brief 获取发力级别
     * @return 发力级别
     * @endif
     */
    unsigned long attackLevel() const;

    /**
     * @if english
     * @brief Obtain Power time
     * @return Power time,Unit: ms
     * @else
     * @brief 获取发力时间
     * @return 发力时间，单位：ms
     * @endif
     */
    unsigned long attackTime() const;
    /**
     * @if english
     * @brief set Power time
     * @param newAttackTime Power time,Unit: ms
     * @else
     * @brief 设置发力时间
     * @param newAttackTime 发力时间，单位：ms
     * @endif
     */
    void setAttackTime(const unsigned long newAttackTime = 500);//单位：s

    /**
     * @if english
     * @brief Obtain attenuation level
     * @return attenuation level
     * @else
     * @brief fadeLevel 获取衰减级别
     * @return 衰减级别
     * @endif
     */
    unsigned long fadeLevel() const;
    /**
     * @if english
     * @brief Set attenuation level
     * @param newFadeLevel attenuation level
     * @else
     * @brief 设置衰减级别
     * @param newFadeLevel 衰减级别
     * @endif
     */
    void setFadeLevel(const unsigned long newFadeLevel = 0);

    /**
     * @if english
     * @brief Obtain attenuation time
     * @return attenuation time,Unit: ms
     * @else
     * @brief fadeTime 获取衰减时间，单位：ms
     * @return 衰减时间
     * @endif
     */
    unsigned long fadeTime()const;
    /**
     * @if english
     * @brief Set attenuation time
     * @param newFadeLevel attenuation time,Unit: ms
     * @else
     * @brief setFadeTime 设置衰减时间
     * @param newFadeTime 衰减时间，单位：ms
     * @endif
     */
    void setFadeTime(const unsigned long newFadeTime = 1000 );//

    /**
     * @if english
     * @brief Obtain attenuation duration
     * @return attenuation duration,Unit: ms
     * @else
     * @brief duration 获取效果持续时间
     * @return 效果持续时间，单位：ms
     * @endif
     */
    unsigned long duration() const;
    /**
     * @if english
     * @brief set attenuation duration
     * @param newDuration attenuation duration,Unit: ms
     * @else
     * @brief setDuration 设置效果持续时间
     * @param newDuration 效果持续时间，单位：ms
     * @endif
     */
    void setDuration(const unsigned long newDuration = 2000);

    /**
     * @if english
     * @brief Obtain sampling period
     * @return sampling period,Unit: ms
     * @else
     * @brief 获取采样周期
     * @return 采样周期，单位：ms
     * @endif
     */
    unsigned long samplePeriod() const;
    /**
     * @if english
     * @brief set sampling period
     * @param newSamplePeriod sampling period,Unit: ms
     * @else
     * @brief setSamplePeriod 设置采样周期
     * @param newSamplePeriod 采样周期值，单位：ms
     * @endif
     */
    void setSamplePeriod(const unsigned long newSamplePeriod = 0);

    /**
     * @if english
     * @brief Obtain Gain
     * @return Gain value (according to report descriptor: 0-10000)
     * @else
     * @brief 获取增益
     * @return 增益值（根据报告描述符：0~10000）
     * @endif
     */
    unsigned long gain() const;
    /**
     * @if english
     * @brief set Gain
     * @return newGain Gain value (according to report descriptor: 0-10000)
     * @else
     * @brief 设置增益值
     * @param newGain 增益值（根据报告描述符：0~10000）
     */
    void setGain(const unsigned long newGain = DI_FFNOMINALMAX);

    /**
     * @if english
     * @brief Obtain departure effect button
     * @return departure effect button
     * @else
     * @brief 获取出发效果按钮
     * @return 效果按钮
     * @endif
     */
    unsigned long triggerButton() const;
    /**
     * @if english
     * @brief set departure effect button
     * @param newButtonIndex departure effect button
     * @else
     * @brief 设置触发效果按钮
     * @param newButtonIndex 触发效果按钮
     * @endif
     */
    void setTriggerButton(const unsigned long newButtonIndex = DIEB_NOTRIGGER);

    /**
     * @if english
     * @brief Obtain trigger effect repetition interval
     * @return Trigger effect repetition interval
     * @else
     * @brief 获取触发效果重复间隔
     * @return 触发效果重复间隔
     * @endif
     */
    unsigned long triggerRepeatInterval() const;
    /**
     * @if english
     * @brief Set trigger effect repetition interval
     * @param newRepeatInterval Trigger effect interval
     * @else
     * @brief 设置触发效果间隔
     * @param newRepeatInterval 触发效果间隔
     * @endif
     */
    void setTriggerRepeatInterval(const unsigned long newRepeatInterval = 0);

//    void setCAxes(const unsigned long newCAxes = 2);
    /**
     * @if english
     * @brief Number of effect related axes
     * @return number of axles
     * @else
     * @brief 效果相关轴数
     * @return 轴数
     * @endif
     */
    unsigned long rgdAxesCount();
    /**
     * @if english
     * @brief Obtain relevant axis array
     * @return Related Axis Array
     * @else
     * @brief 获取相关轴数组
     * @return 相关轴数组
     * @endif
     */
    unsigned long* rgdAxes();
    /**
     * @if english
     * @brief Set related axes
     * @param axes Related axis array pointer
     * @param size Length of related axis array
     * @else
     * @brief 设置相关轴
     * @param axes 相关轴数组指针
     * @param size 相关轴数组长度
     * @endif
     */
    void setRgdAxes(unsigned long* axes, unsigned long size);//设置轴，运行时不能修改，不建议修改，使用默认

    /**
     * @if english
     * @brief Obtain the angle of the effect in the x-axis
     * @return The angle of the effect on the x-axis
     * @else
     * @brief 获取effect在x轴向的角度
     * @return effect在x轴的角度
     * @endif
     */
    long xDirection();
    /**
     * @if english
     * @brief Set the angle of the effect in the x-axis
     * @param newDegree The angle of the effect on the x-axis
     * @else
     * @brief 设置effect在x轴向的角度
     * @param newDegree x轴向的角度
     * @endif
     */
    void setXDirection(long newDegree = 1 );//设置x轴方向,单位：度
//    void setEnvelope();//设置封装
//    void virtual setCbTypeSpecificParams() = 0;//设置特殊参数长度
//    void virtual setTypeSpecificParams() = 0;//设置特殊参数长度

    /**
     * @if english
     * @brief Obtain the name of the current effect
     * @return The name of the current effect
     * @else
     * @brief 获取当前effect的名称
     * @return 当前effect的名称
     * @endif
     */
    std::string effectName() const;

    /**
     * @if english
     * @brief set the name of the current effect
     * @param newEffectName The name of the effect
     * @else
     * @brief 设置effect别名
     * @param newEffectName effect的别名
     * @endif
     */
    void setEffectName(const std::string &newEffectName);


    /**
     * @if english
     * @brief Obtain the index of the current effect
     * @return The index of the current effect
     * @else
     * @brief 获取当前effect的index
     * @return 当前effect的index
     * @endif
     */
    int index() const;

    /**
     * @if english
     * @brief set the index of the current effect
     * @param The index of the current effect，index >= 0
     * @else
     * @brief 设置当前effect的index
     * @param newIndex 当前effect的index，index >= 0
     * @endif
     */
    void setIndex( unsigned int newIndex);

    bool m_isRunning = false;
protected:
    Effect(Device* device);//抽象类，但是没有虚函数
    ~Effect();//生命周期由device管理
    virtual void downloadToDevice(LPDIRECTINPUTDEVICE8 device) = 0;
    std::map<std::string, std::string> allGeneralEffectInfo();
protected:
    uint16_t m_effectId;
    std::string m_effectName;
    LPDIRECTINPUTEFFECT m_effect = NULL;
    DIEFFECT m_diEffect;      //effect_info
    DIENVELOPE m_diEnvelope;  //effect_instance
    LONG* m_lDirection = nullptr;
    DWORD *m_dwAxes = nullptr;
    Device* m_device = nullptr;//parent
    unsigned int m_index = 0;
};
}//RS21::directInput
