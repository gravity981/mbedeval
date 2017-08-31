/* mbed Microcontroller Library
 * Copyright (c) 2006-2014 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <events/mbed_events.h>
#include <mbed.h>
#include "ble/BLE.h"
#include "ble/Gap.h"
#include "ble/services/BatteryService.h"
#include "XNucleoIKS01A2.h"
#include "EnvironmentalService.h"

// Instantiate the expansion board
static XNucleoIKS01A2 *mems_expansion_board = XNucleoIKS01A2::instance(D14, D15, D4, D5);

// Retrieve the composing elements of the expansion board
static LSM303AGRMagSensor *magnetometer = mems_expansion_board->magnetometer;
static HTS221Sensor *hum_temp = mems_expansion_board->ht_sensor;
static LPS22HBSensor *press_temp = mems_expansion_board->pt_sensor;
static LSM6DSLSensor *acc_gyro = mems_expansion_board->acc_gyro;
static LSM303AGRAccSensor *accelerometer = mems_expansion_board->accelerometer;

DigitalOut led1(LED1, 1);
DigitalOut led2(LED2, 0);

const static char     DEVICE_NAME[] = "CAMP17 DEMO NRF";
static const uint16_t uuid16_list[] = {GattService::UUID_BATTERY_SERVICE,
GattService::UUID_ENVIRONMENTAL_SERVICE};

static uint8_t batteryLevel = 50;
static BatteryService* batteryServicePtr;

static float temperature = 25;
static float pressure = 998;
static float humidity = 31;
static EnvironmentalService* environmentalServicePtr;

static EventQueue eventQueue(/* event count */ 16 * EVENTS_EVENT_SIZE);

void disconnectionCallback(const Gap::DisconnectionCallbackParams_t *params)
{
    BLE::Instance().gap().startAdvertising();
}

int16_t encodeTemperature(float temperature)
{
  return (int16_t) roundf(temperature*100);
}

uint16_t encodeHumidity(float humidity)
{
  return (uint16_t) roundf(humidity*100);
}

uint32_t encodePressure(float pressure)
{
  return (uint32_t) roundf(pressure*1000);
}

void updateSensorValue() {
    batteryLevel++;
    if (batteryLevel > 100) {
        batteryLevel = 20;
    }

    batteryServicePtr->updateBatteryLevel(batteryLevel);

    hum_temp->get_temperature(&temperature);
    hum_temp->get_humidity(&humidity);
    press_temp->get_pressure(&pressure);
    environmentalServicePtr->updateTemperature(encodeTemperature(temperature));
    environmentalServicePtr->updateHumidity(encodeHumidity(humidity));
    environmentalServicePtr->updatePressure(encodePressure(pressure));
}

void blinkCallback(void)
{
    led1 = !led1; /* Do blinky on LED1 while we're waiting for BLE events */
    led2 = !led2;

    BLE &ble = BLE::Instance();
    if (ble.gap().getState().connected) {
        eventQueue.call(updateSensorValue);
    }
}

/**
 * This function is called when the ble initialization process has failled
 */
void onBleInitError(BLE &ble, ble_error_t error)
{
    /* Initialization error handling should go here */
}

/**
 * Callback triggered when the ble initialization process has finished
 */
void bleInitComplete(BLE::InitializationCompleteCallbackContext *params)
{
    BLE&        ble   = params->ble;
    ble_error_t error = params->error;

    if (error != BLE_ERROR_NONE) {
        /* In case of error, forward the error handling to onBleInitError */
        onBleInitError(ble, error);
        return;
    }

    /* Ensure that it is the default instance of BLE */
    if(ble.getInstanceID() != BLE::DEFAULT_INSTANCE) {
        return;
    }

    ble.gap().onDisconnection(disconnectionCallback);

    /* Setup primary service */
    batteryServicePtr = new BatteryService(ble, batteryLevel);
    environmentalServicePtr = new EnvironmentalService(ble);

    /* Setup advertising */
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS, (uint8_t *) uuid16_list, sizeof(uuid16_list));
    ble.gap().accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *) DEVICE_NAME, sizeof(DEVICE_NAME));
    ble.gap().setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    ble.gap().setAdvertisingInterval(1000); /* 1000ms */
    ble.gap().startAdvertising();
}

void scheduleBleEventsProcessing(BLE::OnEventsToProcessCallbackContext* context) {
    BLE &ble = BLE::Instance();
    eventQueue.call(Callback<void()>(&ble, &BLE::processEvents));
}

/* Helper function for printing floats & doubles */
static char *print_double(char* str, double v, int decimalDigits=2)
{
  int i = 1;
  int intPart, fractPart;
  int len;
  char *ptr;

  /* prepare decimal digits multiplicator */
  for (;decimalDigits!=0; i*=10, decimalDigits--);

  /* calculate integer & fractinal parts */
  intPart = (int)v;
  fractPart = (int)((v-(double)(int)v)*i);

  /* fill in integer part */
  sprintf(str, "%i.", intPart);

  /* prepare fill in of fractional part */
  len = strlen(str);
  ptr = &str[len];

  /* fill in leading fractional zeros */
  for (i/=10;i>1; i/=10, ptr++) {
    if (fractPart >= i) {
      break;
    }
    *ptr = '0';
  }

  /* fill in (rest of) fractional part */
  sprintf(ptr, "%i", fractPart);

  return str;
}

void printSensorValues()
{
  float value1, value2;
  char buffer1[32], buffer2[32];
  int32_t axes[3];

  printf("\r\n");

  hum_temp->get_temperature(&value1);
  hum_temp->get_humidity(&value2);
  printf("HTS221: [temp] %7s C,   [hum] %s%%\r\n", print_double(buffer1, value1), print_double(buffer2, value2));

  press_temp->get_temperature(&value1);
  press_temp->get_pressure(&value2);
  printf("LPS22HB: [temp] %7s C, [press] %s mbar\r\n", print_double(buffer1, value1), print_double(buffer2, value2));

  printf("---\r\n");

  magnetometer->get_m_axes(axes);
  printf("LSM303AGR [mag/mgauss]:  %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);

  accelerometer->get_x_axes(axes);
  printf("LSM303AGR [acc/mg]:  %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);

  acc_gyro->get_x_axes(axes);
  printf("LSM6DSL [acc/mg]:      %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);

  acc_gyro->get_g_axes(axes);
  printf("LSM6DSL [gyro/mdps]:   %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
}

void printSensorInfo()
{
  uint8_t id;

  hum_temp->read_id(&id);
  printf("HTS221  humidity & temperature    = 0x%X\r\n", id);
  press_temp->read_id(&id);
  printf("LPS22HB  pressure & temperature   = 0x%X\r\n", id);
  magnetometer->read_id(&id);
  printf("LSM303AGR magnetometer            = 0x%X\r\n", id);
  accelerometer->read_id(&id);
  printf("LSM303AGR accelerometer           = 0x%X\r\n", id);
  acc_gyro->read_id(&id);
  printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);
}

int main()
{
    eventQueue.call_every(500, blinkCallback);

    BLE &ble = BLE::Instance();
    ble.onEventsToProcess(scheduleBleEventsProcessing);
    ble.init(bleInitComplete);

    /* Enable all sensors */
    hum_temp->enable();
    press_temp->enable();
    magnetometer->enable();
    accelerometer->enable();
    acc_gyro->enable_x();
    acc_gyro->enable_g();

    //printSensorInfo();
    //printSensorValues();

    eventQueue.dispatch_forever();

    return 0;
}
