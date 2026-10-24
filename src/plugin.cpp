#include "DistrhoPlugin.hpp"
#include <cmath>

START_NAMESPACE_DISTRHO

class SidechainReceiverPlugin : public Plugin
{
public:
    enum PortGroups
    {
        kPortGroupMain = 0,
        kPortGroupSidechain,
        kPortGroupCount
    };

    enum Parameters
    {
        kParamSidechainGain = 0,
        kParamCount
    };

    SidechainReceiverPlugin() :
        Plugin(kParamCount, 0, 0), // kParamCount parameters, 0 programs, 0 states
        fSidechainGainDB{0.0f},
        fSidechainGainLinear{1.0f}
    { }

protected:
    const char* getLabel()          const override { return "Sidechain Receiver"; }
    const char* getDescription()    const override { return "output == stereo main input + stereo sidechain input * gain"; }
    const char* getMaker()          const override { return "stygian-phrygian"; }
    const char* getLicense()        const override { return "GPLv3"; }
    uint32_t    getVersion()        const override { return d_version(1, 0, 0); }
    long        getUniqueId()       const override { return d_cconst('S', 'R', 'c', 'v'); }

    // Group Definitions
    void initPortGroup(uint32_t groupId, PortGroup& portGroup) override
    {
        switch (groupId)
        {
            case kPortGroupMain:
                portGroup.name   = "Main";
                portGroup.symbol = "main";
                break;
            case kPortGroupSidechain:
                portGroup.name   = "Sidechain";
                portGroup.symbol = "sidechain";
                break;
        }
    }

    // Port Definitions
    void initAudioPort(bool input, uint32_t index, AudioPort& port) override
    {
        if (input)
        {
            switch (index)
            {
                case 0:
                    port.name     = "Main Left";
                    port.symbol   = "main_left";
                    port.groupId  = kPortGroupMain;
                    break;
                case 1:
                    port.name     = "Main Right";
                    port.symbol   = "main_right";
                    port.groupId  = kPortGroupMain;
                    break;
                case 2:
                    port.name     = "Sidechain Left";
                    port.symbol   = "sidechain_left";
                    port.groupId  = kPortGroupSidechain;
                    port.hints    = kAudioPortIsSidechain;
                    break;
                case 3:
                    port.name     = "Sidechain Right";
                    port.symbol   = "sidechain_right";
                    port.groupId  = kPortGroupSidechain;
                    port.hints    = kAudioPortIsSidechain;
                    break;
            }
        }
        else
        {
            port.groupId = kPortGroupMain;
            return;
        }
    }

    // Parameters Control
    void initParameter(uint32_t index, Parameter& parameter) override
    {
        if (index != kParamSidechainGain) { return; }

        parameter.hints = kParameterIsAutomatable;
        parameter.name = "Sidechain Gain";
        parameter.symbol = "sidechain_gain";
        parameter.unit = "dB";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = -60.0f;
        parameter.ranges.max = 6.0f;
    }

    float getParameterValue(uint32_t index) const override
    {
        if (index == kParamSidechainGain) { return fSidechainGainDB; }
        return 0.0f;
    }

    void setParameterValue(uint32_t index, float value) override
    {
        if (index == kParamSidechainGain)
        {
            fSidechainGainDB = value;
            if (value <= -59.5f) { fSidechainGainLinear = 0.0f; }
            else                 { fSidechainGainLinear = std::pow(10.0f, value / 20.0f); }
        }
    }

    // Audio DSP Process Loop
    void run(const float** inputs, float** outputs, uint32_t frames) override
    {
        const float* mainLeft  = inputs[0];
        const float* mainRight = inputs[1];
        const float* sideLeft  = inputs[2];
        const float* sideRight = inputs[3];

        float* outLeft  = outputs[0];
        float* outRight = outputs[1];

        const float gain = fSidechainGainLinear;

        for (uint32_t i = 0; i < frames; ++i)
        {
            outLeft[i]  = mainLeft[i]  + (sideLeft[i]  * gain);
            outRight[i] = mainRight[i] + (sideRight[i] * gain);
        }
    }

private:
    float fSidechainGainDB;
    float fSidechainGainLinear;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SidechainReceiverPlugin)
};

Plugin* createPlugin()
{
    return new SidechainReceiverPlugin();
}

END_NAMESPACE_DISTRHO
