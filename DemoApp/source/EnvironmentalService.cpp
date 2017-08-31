#include "EnvironmentalService.h"

EnvironmentalService::EnvironmentalService(BLE &ble) :
    m_ble(ble),
    m_temperature(0),
    m_humidity(0),
    m_pressure(0),
    m_temperatureCharacteristic(
      GattCharacteristic::UUID_TEMPERATURE_CHAR,
      &m_temperature,
      GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY),
    m_humidityCharacteristic(
      GattCharacteristic::UUID_HUMIDITY_CHAR,
      &m_humidity,
      GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY),
    m_pressureCharacteristic(
      GattCharacteristic::UUID_PRESSURE_CHAR,
      &m_pressure,
      GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY)
{
    GattCharacteristic *charTable[] = {
      &m_temperatureCharacteristic,
      &m_humidityCharacteristic,
      &m_pressureCharacteristic
    };
    GattService environmentalService = GattService(GattService::UUID_ENVIRONMENTAL_SERVICE, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
    m_ble.addService(environmentalService);
}

EnvironmentalService::~EnvironmentalService()
{
}

void EnvironmentalService::updateTemperature(int16_t temperature)
{
    m_temperature = temperature;
    m_ble.gattServer().write(m_temperatureCharacteristic.getValueHandle(), (uint8_t *) &m_temperature, sizeof(int16_t));
}

void EnvironmentalService::updateHumidity(uint16_t humidity)
{
  m_humidity = humidity;
  m_ble.gattServer().write(m_humidityCharacteristic.getValueHandle(), (uint8_t *) &m_humidity, sizeof(uint16_t));
}

void EnvironmentalService::updatePressure(uint32_t pressure)
{
  m_pressure = pressure;
  m_ble.gattServer().write(m_pressureCharacteristic.getValueHandle(), (uint8_t *) &m_pressure, sizeof(uint32_t));
}
