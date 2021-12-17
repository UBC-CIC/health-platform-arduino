/* Adapted from the code provided by 
 * https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor 
 * and https://github.com/DFRobot/DFRobot_CCS811/blob/master/examples/readData/readData.ino 
 */

#include <DFRobot_CCS811.h>

// time between readings (ms)
int interval = 5000;

struct CCS811_reading {
    int CO2;
    int TVOC;
};

DFRobot_CCS811 sensor;

void setup(void)
{
    Serial.begin(115200);
    /*Wait for the chip to be initialized completely, and then exit*/
    while(sensor.begin() != 0){
        Serial.println("failed to init chip, please check if the chip connection is fine");
        delay(1000);
    }
}

void loop() {
    if(sensor.checkDataReady() == true){
        CCS811_reading reading = CCS811_reading();
        reading.CO2 = sensor.getCO2PPM();
        reading.TVOC = sensor.getTVOCPPB();
        // TODO: replace serial output with POST to iot endpoint
        Serial.print("CO2: ");
        Serial.print(reading.CO2);
        Serial.print("ppm, TVOC: ");
        Serial.print(reading.TVOC);
        Serial.println("ppb");
    } else {
        Serial.println("Data is not ready!");
    }
    /*!
     * @brief Set baseline
     * @param get from getBaseline.ino
     */
    sensor.writeBaseLine(0x847B);
    //delay cannot be less than measurement cycle
    delay(interval);
}
