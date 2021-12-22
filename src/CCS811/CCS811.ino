/* Adapted from the code provided by 
 * https://wiki.keyestudio.com/KS0457_keyestudio_CCS811_Carbon_Dioxide_Air_Quality_Sensor 
 * and https://github.com/DFRobot/DFRobot_CCS811/blob/master/examples/readData/readData.ino 
 */

#include <DFRobot_CCS811.h>

// time between readings (ms)
int interval = 5000;

// TODO: CHANGE THIS! Needs to be generated elsewhere to prevent duplicates and map to a patient
// unique id for the sensor
char sensorId[3] = "152";

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
        // TODO: replace serial output with POST to iot endpoint
        

        Serial.print("CO2: ");
        Serial.print(sensor.getCO2PPM());
        Serial.print("ppm, TVOC: ");
        Serial.print(sensor.getTVOCPPB());
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
