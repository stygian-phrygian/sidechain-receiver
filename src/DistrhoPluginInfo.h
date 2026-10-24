#ifndef DISTRHO_PLUGIN_INFO_H_INCLUDED
#define DISTRHO_PLUGIN_INFO_H_INCLUDED

#define DISTRHO_PLUGIN_NAME     "Sidechain Receiver"
#define DISTRHO_PLUGIN_URI      "https://github.com/stygian-phrygian/sidechain-receiver"
#define DISTRHO_PLUGIN_IS_SYNTH  0

// 4 Inputs = 2 Main Track + 2 Sidechain (Aux) Inputs
#define DISTRHO_PLUGIN_NUM_INPUTS   4
#define DISTRHO_PLUGIN_NUM_OUTPUTS  2

// Important for VST3/CLAP sidechain mapping protocols
#define DISTRHO_PLUGIN_WANT_TIMEPOS 0
#define DISTRHO_PLUGIN_WANT_PROGRAMS 0

#endif // DISTRHO_PLUGIN_INFO_H_INCLUDED
