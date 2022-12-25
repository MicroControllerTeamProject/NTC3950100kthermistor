// Arduino code for use with NTC thermistor

#include <math.h>

#define therm_pin A0
float T_approx;

float V_0 = 3.3; // voltage reference

// first resistance value for voltage divider
float R_1 = 200000.0;
// fit coefficients
float a = 283786.2;
float b = 0.06593;
float c = 49886.0;

int avg_size = 10; // averaging size

void setup() {
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    pinMode(therm_pin, INPUT);

    // set analog reference to read AREF pin
    analogReference(EXTERNAL);
}

void loop() {

    // loop over several values to lower noise
    float T_sum = 0.0;
    for (int ii; ii < avg_size; ii++) {
        // read the input on analog pin 0:
        int sensorValue = analogRead(therm_pin);
        // Convert the analog reading (which goes from 0 - 1023) to voltage reference (3.3V or 5V or other):
        float voltage = (sensorValue / 1023.0) * V_0;

        // this is where the thermistor conversion happens based on parameters from fit
        T_sum += (-1.0 / b) * (log(((R_1 * voltage) / (a * (V_0 - voltage))) - (c / a)));
    }

    // averaging values from loop
    T_approx = T_sum / float(avg_size);

    // readout for Celsius and Fahrenheit
    Serial.print("Temperature: ");
    Serial.print(T_approx);
    Serial.print(" (");
    Serial.print((T_approx * (9.0 / 5.0)) + 32.0);
    Serial.println(" F)");

    delay(500);
}
