/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include "tcMenuBLERemoteConnector.h"

using namespace tcremote;

BLEDevice tcremote::central;
BLEService tcremote::bleApiService(bleServiceIdentifier);
BLECharacteristic tcremote::toApiCharacteristic(characteristicDeviceToApi, BLERead | BLENotify, 255, false);
BLECharacteristic tcremote::fromApiCharacteristic(characteristicApiToDevice, BLEWrite, 255, false);
BLECharacteristic tcremote::deviceSequenceCharacteristic(characteristicDeviceSeqCounter, BLERead | BLENotify, 4, true);
BLECharacteristic tcremote::apiSequenceCharacteristic(characteristicApiSeqCounter, BLEWrite, 4, true);

inline uint32_t read32From(uint8_t* buf) {
    return (uint32_t)buf[0] << 24 | (uint32_t)buf[1] << 16 | (uint32_t)buf[2] << 8 | (uint32_t)buf[3];
}

inline void writeToBuffer(uint8_t* buffer, uint32_t sequence) {
    buffer[0] = (sequence >> 24);
    buffer[1] = (sequence >> 16) & 0xFF;
    buffer[2] = (sequence >> 8) & 0xFF;
    buffer[3] = sequence & 0xFF;
}

BLETagValTransport::BLETagValTransport() : BaseBufferedRemoteTransport(BUFFER_ONE_MESSAGE, 255, 255) {
    writeBufferPos = 4;
    writeToBuffer(writeBuffer, currDeviceSequence + 1);
}

bool BLETagValTransport::readAvailable() {
    if(readBufferAvail && readBufferPos < readBufferAvail) {
        return true;
    }

    fillReadBuffer(readBuffer, readBufferSize);
    return readBufferPos < readBufferAvail;
}

int BLETagValTransport::fillReadBuffer(uint8_t *dataBuffer, int maxSize) {
    if(!central.connected() || !fromApiCharacteristic.written()) {
        return 0;
    }

    readBufferAvail = fromApiCharacteristic.readValue(readBuffer, readBufferSize);
    if(readBufferAvail <= 4)
    {
        return 0;
    }

    serlogHexDump(SER_NETWORK_DEBUG, "fromApi ", readBuffer, readBufferAvail);

    size_t i=4;
    while(readBuffer[i] != 0 && i < readBufferAvail) {
        i++;
    }
    readBufferAvail = i;
    uint32_t rxSequence = read32From(readBuffer);
    serlogF3(SER_NETWORK_DEBUG, "RxSeq ", rxSequence, readBufferAvail);

    uint8_t buffer[4];
    writeToBuffer(buffer, rxSequence);
    bool writtenSeqOk = deviceSequenceCharacteristic.writeValue(buffer, 4) != 0;
    serlogF2(SER_NETWORK_DEBUG, "RxSeqOK ", writtenSeqOk);

    readBufferPos = 4;
    return readBufferAvail;
}

void BLETagValTransport::flush() {
    if(apiSequenceCharacteristic.written()) {
        uint8_t buffer[4];
        apiSequenceCharacteristic.readValue(buffer, sizeof(buffer));
        currApiSequence = read32From(buffer);
        serlogF3(SER_NETWORK_DEBUG, "ApiSeq rd ", currApiSequence, currDeviceSequence)
    }
    if(central.connected() && currApiSequence == currDeviceSequence) {
        // bump the device sequence
        currDeviceSequence += 1;

        // zero terminate if not full size of buffer
        if((writeBufferSize - writeBufferPos) > 1) {
            writeBuffer[writeBufferPos] = 0;
            writeBufferPos++;
        }

        // write the value out and make sure it all writes.
        int written = toApiCharacteristic.writeValue(writeBuffer, writeBufferPos);
        if(written != 0) {
            serlogF3(SER_NETWORK_DEBUG, "ApiToDevice ", writeBufferPos, currDeviceSequence)
        } else {
            central.disconnect();
        }
        writeBufferPos = 4;
        writeToBuffer(writeBuffer, currDeviceSequence);
    }
}

bool BLETagValTransport::available() {
    return central.connected();
}

bool BLETagValTransport::connected() {
    return central.connected();
}

void BLETagValTransport::connectedClient() {
    currApiSequence = currDeviceSequence = 0;
    uint8_t zeroBuffer[] = {0};
    deviceSequenceCharacteristic.writeValue(zeroBuffer, 4);
}

bool BLEDeviceInitialisation::attemptInitialisation() {
    serlogF(SER_NETWORK_INFO, "BLE Starting");
    if(!initialised && BLE.begin() == 0) return false;
    initialised = true;
    if (!BLE.begin()) {
        serlogF(SER_ERROR, "BLE failed!");
    }

    bleApiService.addCharacteristic(toApiCharacteristic);
    bleApiService.addCharacteristic(fromApiCharacteristic);
    bleApiService.addCharacteristic(apiSequenceCharacteristic);
    bleApiService.addCharacteristic(deviceSequenceCharacteristic);
    uint8_t buffer[4] = {0};
    apiSequenceCharacteristic.writeValue(buffer, 4);
    deviceSequenceCharacteristic.writeValue(buffer, 4);

    BLE.addService(bleApiService);
    BLE.setLocalName(applicationInfo.name);
    BLE.setAdvertisedService(bleApiService);
    BLE.advertise();

    serlogF(SER_NETWORK_INFO, "BLE Up");
    return true;
}

bool BLEDeviceInitialisation::attemptNewConnection(BaseRemoteServerConnection *transport) {
    central = BLE.central();
    if(central.connected()) {
        reinterpret_cast<BLETagValTransport*>(transport)->connectedClient();
        return true;
    }
    return false;
}
