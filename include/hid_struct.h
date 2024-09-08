#ifndef HID_STRUCT_H
#define HID_STRUCT_H
#include <vector>


enum ROCKERMODE
{
    UNKNOW = 0,
    CROSSKEY,
    KEY,
};
enum KNOBMODE
{
    UNKNOWKNOB = 0,
    KNOB,
    MULTIKEY,
};

enum CLUTCHPICKMODE
{
    UNKNOWCLUTCHPICK = 0,
    COMPOSITEAXIS,
    INDEPENDENTAXIS,
};

enum ROCKEREDIR
{
    UP = 0,
    RIGHTUP,
    RIGHT,
    RIGHTDOWM,
    DOWM,
    LEFTDOWM,
    LEFT,
    LEFTUP,
    NONEDIR
};

//enum ERRORCODE
//{
//    NORMAL = 0,
//    NOINSTALLSDK,
//    NODEVICES,
//    COLLECTIONCYCLEDATALOSS,
//};

struct HIDButton
{
    bool startValue = 0;
    int  changeNum = -1;
    bool isPressed() const{
        if(changeNum == -1)
            return startValue;
        return startValue || changeNum;
    };
    bool lastPressState() const{
        return (changeNum & 1) == 0 || changeNum == -1 ? startValue : !startValue;
    }
    int pressNum(){
        return changeNum == -1 ? 0 : changeNum/2 + changeNum&0x01;
    }
};

//没有操作为空，8同样表示没有操作，但vector第一个数据不会为8
struct HIDRocker
{
    std::vector<ROCKEREDIR> rockerDatas;
    ROCKEREDIR lastDir() const
    {
        return rockerDatas.empty()? NONEDIR : rockerDatas.back();
    }
};

struct HIDKnob
{   
    std::vector<int> knobDatas;
    int getOffset() const{
        int res = 0;
        for(auto var : knobDatas)
            res += var;
        return res;
    }
};

struct HIDMultiSegmentKnob : public HIDKnob
{
    int getLastKey() const
    {
        return knobDatas.empty()? 0 : knobDatas.back();
    }
};

enum GEAR
{
    R = 0,
    GEAR1st,
    GEAR2nd,
    GEAR3rf,
    GEAR4th,
    GEAR5th,
    GEAR6th,
    GEAR7th,
    GEAR0th,
};

struct HIDData
{
    float fSteeringWheelAngle =  NAN;//返回角度
    int16_t       steeringWheelAxle = 0x8001;
    int16_t       clutchSynthesisShaft = 0x8001;

    int16_t       clutchIndependentShaftL = 0x8001;
    int16_t       clutchIndependentShaftR = 0x8001;

    int16_t       throttle = 0x8000;
    int16_t       clutch = 0x8000;
    int16_t       brake = 0x8000;
    int16_t       handbrake = 0x8001;

    HIDButton buttons[128];

    HIDRocker leftRocker5_8;
    HIDRocker rightRocker9_12;  

    HIDKnob knobL45_46;
    HIDKnob knobR47_48;
//    HIDKnob knob2L;
//    HIDKnob knob2R;

    HIDMultiSegmentKnob multiSegmentKnob26_27or53_64;
    HIDMultiSegmentKnob multiSegmentKnob28_29or65_76;
    HIDMultiSegmentKnob multiSegmentKnob30_31or77_88;
    HIDMultiSegmentKnob multiSegmentKnob39_40or89_100;
    HIDMultiSegmentKnob multiSegmentKnob43_44or101_112;

    GEAR shift = GEAR0th;
    bool buttonHandbrake = false;
};

#endif // HID_STRUCT_H
