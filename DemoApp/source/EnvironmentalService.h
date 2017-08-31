#ifndef __BLE_ENVIRONMENTAL_SERVICE_H__
#define __BLE_ENVIRONMENTAL_SERVICE_H__

#include "ble/BLE.h"

class EnvironmentalService {
protected:
    BLE& m_ble;
    int16_t m_temperature;
    ReadOnlyGattCharacteristic<int16_t> m_temperatureCharacteristic;
public:
    EnvironmentalService(BLE &ble) :
        m_ble(ble),
        m_temperature(0),
        m_temperatureCharacteristic(
          GattCharacteristic::UUID_TEMPERATURE_CHAR,
          &m_temperature,
          GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY)
    {
        GattCharacteristic *charTable[] = {&m_temperatureCharacteristic};
        GattService environmentalService = GattService(GattService::UUID_ENVIRONMENTAL_SERVICE, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
        m_ble.addService(environmentalService);
    }

    void updateTemperature(int16_t newLevel) {
        m_temperature = newLevel;
        m_ble.gattServer().write(m_temperatureCharacteristic.getValueHandle(), (uint8_t *) &m_temperature, sizeof(int16_t));
    }
};

#endif /* #ifndef __BLE_ENVIRONMENTAL_SERVICE_H__*/
