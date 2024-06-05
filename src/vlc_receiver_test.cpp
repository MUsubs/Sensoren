#include "vlc_receiver_test.hpp"

namespace rec {

VLCReceiverTest::VLCReceiverTest( VLCReceiver &vlc_receiver ) :
    vlc_receiver{ vlc_receiver },
    byte_queue{ xQueueCreate( 32, sizeof( uint8_t ) ) },
    this_task_handle{} {

        vlc_receiver.addListener(this);
}

void VLCReceiverTest::byteReceived( uint8_t &byte ) {
    Serial.printf("Byte received: %d\n", byte);
    uint8_t value = byte;
    xQueueSend( byte_queue, &value, 0 );
}

void VLCReceiverTest::printResults( uint32_t &result ) {
    // Create a mask with the highest bit set
    uint32_t mask = 1UL << 31;
    Serial.print( "Test Results : " );

    // Iterate through each bit
    for ( int i = 0; i < 32; i++ ) {
        // Check if the current bit is set and print '1' or '0'
        if ( result & mask ) {
            Serial.print( '1' );
        } else {
            Serial.print( '0' );
        }
        // Shift the mask to the right for the next bit
        mask >>= 1;
    }

    Serial.print( ".\n" );
}


void printbyte( uint8_t &result ) {
    // Create a mask with the highest bit set
    uint8_t mask = 1UL << 7;
    Serial.print( "byte : " );

    // Iterate through each bit
    for ( int i = 0; i < 8; i++ ) {
        // Check if the current bit is set and print '1' or '0'
        if ( result & mask ) {
            Serial.print( '1' );
        } else {
            Serial.print( '0' );
        }
        // Shift the mask to the right for the next bit
        mask >>= 1;
    }

    Serial.print( ".\n" );
}

void VLCReceiverTest::run() {
    uint8_t received_byte = 0;
    unsigned int index = 0;
    for ( ;; ) {
        switch ( state ) {
            case IDLE:
                if ( byte_queue != NULL ) {
                    if ( xQueueReceive( byte_queue, &received_byte, 0 ) ) {
                        state = BYTE;
                    }
                }
                break;

            case BYTE:
                // if ( index >= 0 && index < 32 ) {
                //     if ( received_byte == sen::test_bytes[index] ) {
                //         result |= 1;
                //         result <<= 1;
                //     } else {
                //         result <<= 1;
                //     }
                //     index++;
                //     state = IDLE;
                // }
                // if ( index >= 32 ) {
                //     state = RESULTS;
                // }

                printbyte(received_byte);
                state = IDLE;

                break;

            case RESULTS:
                index = 0;
                printResults( result );
                result = 0;
                state = IDLE;

                break;

            default:
                break;
        }
    }
}

}  // namespace rec