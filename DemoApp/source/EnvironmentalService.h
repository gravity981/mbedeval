#ifndef __BLE_ENVIRONMENTAL_SERVICE_H__
#define __BLE_ENVIRONMENTAL_SERVICE_H__

#include "ble/BLE.h"

class EnvironmentalService {
private:
    BLE& m_ble;
    int16_t m_temperature;
    uint16_t m_humidity;
    uint32_t m_pressure;

    ReadOnlyGattCharacteristic<int16_t> m_temperatureCharacteristic;
    ReadOnlyGattCharacteristic<uint16_t> m_humidityCharacteristic;
    ReadOnlyGattCharacteristic<uint32_t> m_pressureCharacteristic;
public:
    EnvironmentalService(BLE &ble);
    ~EnvironmentalService();

    void updateTemperature(int16_t temperature);
    void updateHumidity(uint16_t humidity);
    void updatePressure(uint32_t pressure);
};

#endif /* #ifndef __BLE_ENVIRONMENTAL_SERVICE_H__*/
