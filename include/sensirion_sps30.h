
extern void sps30_init();

extern void sps30_update();

struct SPS30_Data
{
    struct 
    {
        float PM_1_0;
        float PM_2_5;
        float PM_4_0;
        float PM_10_0;
    } mass_concentration;

    struct 
    {
        float PM_0_5;
        float PM_1_0;
        float PM_2_5;
        float PM_4_0;
        float PM_10_0;
    } number_concentration;
};

extern SPS30_Data current_SPS30_data;
