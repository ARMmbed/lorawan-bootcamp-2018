#ifndef _LORA_CONFIG_H_
#define _LORA_CONFIG_H_

#include "mbed.h"
#include "dot_util.h"
#include "RadioEvent.h"

// Replace this with your AppEUI and AppKey
static uint8_t appEUI[] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x00, 0xAA, 0xDF };
static uint8_t appKey[] = { 0xC4, 0x18, 0xF2, 0x99, 0xCC, 0x33, 0x1B, 0xDA, 0x4E, 0x0A, 0xAA, 0x81, 0xB1, 0x7F, 0x29, 0xFE };

static std::string network_name = "MTS-DEMO";
static std::string network_passphrase = "MTS-DEMO";
static lora::NetworkType network_type = lora::PUBLIC_LORAWAN;


#define CHANNEL_PLAN CP_US915

// Other configuration options
static uint8_t frequency_sub_band = 0;  // frequency sub band
static uint8_t ack = 0;                 // acknowledgements
static bool adr = true;                // adaptive data rating
static uint8_t join_delay = 5;

// this is dirty
extern mDot* dot;

static void connect_to_lora(RadioEvent *events) {
    lora::ChannelPlan* plan = NULL;

    mts::MTSLog::setLogLevel(mts::MTSLog::TRACE_LEVEL);
    
#if CHANNEL_PLAN == CP_US915
    plan = new lora::ChannelPlan_US915();
#elif CHANNEL_PLAN == CP_AU915
    plan = new lora::ChannelPlan_AU915();
#elif CHANNEL_PLAN == CP_EU868
    plan = new lora::ChannelPlan_EU868();
#elif CHANNEL_PLAN == CP_KR920
    plan = new lora::ChannelPlan_KR920();
#elif CHANNEL_PLAN == CP_AS923
    plan = new lora::ChannelPlan_AS923();
#elif CHANNEL_PLAN == CP_AS923_JAPAN
    plan = new lora::ChannelPlan_AS923_Japan();
#elif CHANNEL_PLAN == CP_IN865
    plan = new lora::ChannelPlan_IN865();
#endif
    assert(plan);
 
    dot = mDot::getInstance(plan);
    assert(dot);
 
    // attach the custom events handler
    dot->setEvents(events);
 
    if (!dot->getStandbyFlag()) {

        // start from a well-known state
        logInfo("defaulting Dot configuration");
        dot->resetConfig();
        dot->resetNetworkSession();
 
        // make sure library logging is turned on
        dot->setLogLevel(mts::MTSLog::INFO_LEVEL);
 
        // update configuration if necessary
        if (dot->getJoinMode() != mDot::OTA) {
            logInfo("changing network join mode to OTA");
            if (dot->setJoinMode(mDot::OTA) != mDot::MDOT_OK) {
                logError("failed to set network join mode to OTA");
            }
        }
        // in OTA and AUTO_OTA join modes, the credentials can be passed to the library as a name and passphrase or an ID and KEY
        // only one method or the other should be used!
        // network ID = crc64(network name)
        // network KEY = cmac(network passphrase)
        update_ota_config_name_phrase(network_name, network_passphrase, frequency_sub_band, network_type, ack);
        //update_ota_config_id_key(network_id, network_key, frequency_sub_band, network_type, ack);
 
        // configure network link checks
        // network link checks are a good alternative to requiring the gateway to ACK every packet and should allow a single gateway to handle more Dots
        // check the link every count packets
        // declare the Dot disconnected after threshold failed link checks
        // for count = 3 and threshold = 5, the Dot will ask for a link check response every 5 packets and will consider the connection lost if it fails to receive 3 responses in a row
        update_network_link_check_config(3, 5);
 
        // enable or disable Adaptive Data Rate
        dot->setAdr(adr);
 
        // Configure the join delay
        dot->setJoinDelay(join_delay);
 
        // save changes to configuration
        logInfo("saving configuration");
        if (!dot->saveConfig()) {
            logError("failed to save configuration");
        }
 
        // display configuration
        display_config();
    }
}


#endif // _LORA_CONFIG_H_
