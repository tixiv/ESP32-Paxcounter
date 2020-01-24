
#include "sensirion_sps30.h"
#include "globals.h"
#include <Wire.h>


// Local logging tag
static const char TAG[] = __FILE__;

static Ticker cycler;

static void cycle() { xTaskNotify(irqHandlerTask, SPS30_IRQ, eSetBits); }

void sps30_init()
{
    ESP_LOGI(TAG, "sps30 init");
    cycler.attach(1, cycle);
}

void sps30_update()
{
    ESP_LOGI(TAG, "test");
}
