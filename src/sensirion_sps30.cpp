
#include "sensirion_sps30.h"
#include "globals.h"
#include <Wire.h>

#include <SPS30.h>

SPS30 Sensor;

SPS30_Data current_SPS30_data;

// Local logging tag
static const char TAG[] = __FILE__;

static Ticker cycler;

static void cycle() { xTaskNotify(irqHandlerTask, SPS30_IRQ, eSetBits); }

void sps30_init()
{
#ifdef HAS_SPS30
    ESP_LOGI(TAG, "sps30 init");

    if (I2C_MUTEX_LOCK()) {
        Wire.begin(HAS_SPS30, 100000);

        Sensor.begin();

        // Set the SPS30 to clean itself every 302,400 seconds (3.5 days, 84 hours)
        Sensor.setCleaningInterval(302400);

        Wire.begin(HAS_SPS30);
        I2C_MUTEX_UNLOCK(); // release i2c bus access
    }

    cycler.attach(1, cycle);
#endif
}

void sps30_update()
{
#ifdef HAS_SPS30
    if (I2C_MUTEX_LOCK()) {
        Wire.begin(HAS_SPS30, 100000);
        if (Sensor.dataAvailable())
        {
            float mass_concen[4];
            Sensor.getMass(mass_concen);

            float num_concen[5];
            Sensor.getNum(num_concen);

            current_SPS30_data.mass_concentration.PM_1_0  = mass_concen[0];
            current_SPS30_data.mass_concentration.PM_2_5  = mass_concen[1];
            current_SPS30_data.mass_concentration.PM_4_0  = mass_concen[2];
            current_SPS30_data.mass_concentration.PM_10_0 = mass_concen[3];

            current_SPS30_data.number_concentration.PM_0_5 = num_concen[0];
            current_SPS30_data.number_concentration.PM_1_0 = num_concen[1];
            current_SPS30_data.number_concentration.PM_2_5 = num_concen[2];
            current_SPS30_data.number_concentration.PM_4_0 = num_concen[3];
            current_SPS30_data.number_concentration.PM_10_0 = num_concen[4];

            char *pm[5] = {"PM0.5", "PM1.0", "PM2.5", "PM4.0", "PM10"};

            ESP_LOGI(TAG, "--- Mass Concentration ---");

            for (int i = 0; i < 4; i++)
            {
                ESP_LOGI(TAG, "%s: %.2f", pm[i + 1], mass_concen[i]);
            }

            ESP_LOGI(TAG, "--- Number Concentration ---");

            for (int i = 0; i < 5; i++)
            {
                ESP_LOGI(TAG, "%s: %.2f", pm[i], num_concen[i]);
            }
        }

        Wire.begin(HAS_SPS30);
        I2C_MUTEX_UNLOCK(); // release i2c bus access
    }
#endif
}
