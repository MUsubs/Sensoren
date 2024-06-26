#ifndef R2D2_PACKET_ENUMS_HPP
#define R2D2_PACKET_ENUMS_HPP

#include <Arduino.h>

#include <array>
#include <map>

namespace sen {

enum class packet_t { INST = 0b01, UPDATE = 0b10, SENS = 0b11, NONE = 0b0 };
enum class inst_t { NEW_POS = 0b001, ARRIVED = 0b010, STOP = 0b100, ACK = 0b111, NONE = 0b0 };
enum class data_t { CURR = 0b001, NONE = 0b0 };
enum class sens_t { TEMP = 0b01, GYRO = 0b10, NONE = 0b0 };

extern std::map<String, uint8_t> _single_byte_commands;

struct InstPacket_t {
    inst_t inst_type;
    std::array<uint8_t, 3> data_bytes;

    InstPacket_t( inst_t inst_type, std::array<uint8_t, 3>& data ) :
        inst_type{ inst_type }, data_bytes{ data } {
    }

    InstPacket_t() : inst_type{}, data_bytes{} {
    }
};

struct UpdatePacket_t {
    data_t data_type;
    std::array<uint8_t, 3> data_bytes;

    UpdatePacket_t( data_t data_type, std::array<uint8_t, 3>& data ) :
        data_type{ data_type }, data_bytes{ data } {
    }

    UpdatePacket_t() : data_type{}, data_bytes{} {
    }
};

}  // namespace sen

#endif  // R2D2_PACKET_ENUMS_HPP