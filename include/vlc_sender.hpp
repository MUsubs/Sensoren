#ifndef R2D2_VLC_SENDER_HPP
#define R2D2_VLC_SENDER_HPP

#include <Arduino.h>

#include <deque>

#include "FreeRTOS.h"
#include "queue.h"

namespace sen {

class VLCSender {
public:
    VLCSender( int led_pin, unsigned int frequency = 60 );

    // sendBytes method with frequency parameter takes frequency from parameter,
    // doesn't overwrite private variable by default, set update_freq to true to
    // overwrite
    void sendBytes( std::deque<uint8_t>& bytes, unsigned int freq,
                    bool update_freq = false, bool overwrite_org = true);

    // sendBytes method without frequency parameter
    // takes frequency from private variable
    void sendBytes( std::deque<uint8_t>& bytes, bool overwrite_org = true);

    void setFrequency( unsigned int new_frequency );
    unsigned int getFrequency();
    void run();

private:
    unsigned int frequency;
    double bit_delay;
    int led_pin;
    std::deque<uint8_t>* bytes;
    xQueueHandle bytes_queue;
    PinStatus pin_state;

    uint8_t generateChecksum( std::deque<uint8_t>& bytes );

    enum class state_t { IDLE, SENDSYNC, SENDBYTE, SENDEND, SENDBIT };

    state_t state = state_t::IDLE;
    state_t return_state = state_t::IDLE;
};

}  // namespace sen

#endif  // R2D2_VLC_SENDER_HPP