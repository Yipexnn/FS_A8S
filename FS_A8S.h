/**
 * @file FS_A8S.h
 * @brief Class for reading and decoding FlySky FS-A8S receiver data over serial.
 *
 * This class implements a simple serial protocol parser for the FlySky FS-A8S RC receiver.
 * It reads raw serial bytes from the receiver, validates frame headers, extracts channel
 * values, and maps them to a user-defined range. The implementation assumes that the FS-A8S
 * outputs data frames beginning with 0x20 0x40, followed by channel data in little-endian order.
 *
 * Typical use:
 * @code
 * #include "FS_A8S.h"
 *
 * FS_A8S receiver;
 *
 * void setup() {
 *   receiver.begin();  // Initialize serial and receiver communication
 * }
 *
 * void loop() {
 *   receiver.readRx();  // Continuously read and decode channel data
 *   // Access channels via receiver.ch[i] or receiver.rawCh[i]
 * }
 * @endcode
 *
 * @note The serial baud rate is set to 115200 by default.
 * @note This implementation currently supports up to 6 channels (configurable).
 */

#ifndef FS_A8S_H
#define FS_A8S_H

#include <stdint.h>
#include <Arduino.h>

#ifndef MAX_CHANNELS
#define MAX_CHANNELS 6   ///< Maximum number of RC channels to decode
#endif

#ifndef BUFFSIZE
#define BUFFSIZE 32      ///< Size of the serial data buffer
#endif

/**
 * @class FS_A8S
 * @brief Handles FlySky FS-A8S receiver communication and channel decoding.
 *
 * The FS_A8S class reads serial data from an FS-A8S receiver and extracts
 * normalized channel values. Each valid data frame starts with 0x20 0x40
 * and contains a sequence of channel values in low-byte–high-byte order.
 */
class FS_A8S
{
  private:
    uint8_t index = 0;           ///< Current index position in the input buffer
    uint8_t bus[BUFFSIZE];       ///< Raw byte buffer for incoming serial data

  public:
    /**
     * @brief Constructs an FS_A8S object.
     *
     * The constructor initializes internal buffers but does not start serial communication.
     * Call `begin()` in `setup()` to initialize the serial interface.
     */
    FS_A8S();

    /**
     * @brief Initializes serial communication for the receiver.
     *
     * Sets up the serial port at 115200 baud and prints a startup message.
     * Should be called once during setup.
     */
    void begin();

    /**
     * @brief Reads and processes incoming serial data from the receiver.
     *
     * This function should be called frequently (e.g. in the main loop). It checks
     * for new bytes from the serial port, validates frame headers, and extracts channel
     * values when a full frame is received. Channel values are automatically scaled
     * to the 0–255 range.
     */
    void readRx();

    int rawCh[MAX_CHANNELS];     ///< Unscaled raw channel values from the receiver
    int ch[MAX_CHANNELS];        ///< Scaled channel values mapped to 0–255 range
};

#endif // FS_A8S_H
