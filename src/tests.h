
void collect_and_print_samples_analyse(bool printSamples = false);

void TestFixedOutput()
{
    Serial.println("\r\n\r\nFixed Output Drive 1,2, Sense 3,4 : \r\n");
    Serial.flush();

    driveSourceMux.select((ADG732::Channel) transformElectrode(0));
    driveGroundMux.select((ADG732::Channel) transformElectrode(1));
    senseAMux.select((ADG732::Channel) transformElectrode(2));
    senseBMux.select((ADG732::Channel) transformElectrode(3));

    driveSourceMux.enable(true);
    driveGroundMux.enable(true);
    senseAMux.enable(true);
    senseBMux.enable(true);

    collect_and_print_samples_analyse(true);

    eit_iq_demodulation ( const_cast<uint32_t const * >(&g_aiSamples[g_iSample_rubbish]), g_iSamples_useful, g_iSamples_per_cycle, true);
    Serial.flush();
       
}

void TestOutputsToInputs()
{
    Serial.print("\r\nOutput vs Input Matrix");
    Serial.print("\r\nDist: ");Serial.print(g_iDrivingDist);
    Serial.print("\r\nO+,O-,\t");
    for (int i = 0; i < g_iElectrodes; ++i) {
        Serial.print(transformElectrode(i)+1);
        Serial.print(",\t");
    }

    Serial.flush();

    driveSourceMux.enable(false);
    driveGroundMux.enable(false);
    senseAMux.enable(false);
    senseBMux.enable(false);

    // Loop over all driving pairs
    for(
            // Start from the 0th electrode
            unsigned int drivingElectrode = 0, 
                          groundElectrode = g_iDrivingDist;

            // Do all the electrodes pairs
            drivingElectrode < g_iElectrodes;

            // Rotate by g_iDrivingDist each iteration
            groundElectrode  = ( ++drivingElectrode + g_iDrivingDist  ) % g_iElectrodes
        )
    {
        Serial.print("\r\n");
        Serial.print(transformElectrode(drivingElectrode)+1);Serial.print(", ");
        Serial.print(transformElectrode(groundElectrode) +1);Serial.print(",\t");Serial.flush();

        driveSourceMux.select((ADG732::Channel) transformElectrode(drivingElectrode));
        driveGroundMux.select((ADG732::Channel) transformElectrode(groundElectrode));
        driveSourceMux.enable(true); driveGroundMux.enable(true);
        
        // Loop over all sensing pairs
        for (   // Sensing pairs from 0
                unsigned int senseAElectrode = 0, senseBElectrode = 1;

                // Continue until we reach the driving electrode
                senseAElectrode < g_iElectrodes;

                // Rotate by one each iteration
                senseBElectrode = ( ++senseAElectrode + 1 ) % g_iElectrodes 
            )
        {

            senseAMux.select((ADG732::Channel) transformElectrode(senseAElectrode));
            senseBMux.select((ADG732::Channel) transformElectrode(senseBElectrode));
            senseAMux.enable(true); senseBMux.enable(true);

            adc_collect_samples(const_cast<uint32_t * >(g_aiSamples), g_iSamples);

            senseAMux.enable(false); senseBMux.enable(false);

            float magnitude = eit_iq_demodulation ( const_cast<uint32_t const * >(&g_aiSamples[g_iSample_rubbish]), g_iSamples_useful, g_iSamples_per_cycle);

            Serial.print(magnitude, 4); Serial.print(",\t");Serial.flush();
        }
        Serial.flush();
        driveSourceMux.enable(false); driveGroundMux.enable(false);
    }
    Serial.print("\r\n");
    Serial.flush();
}

void TestElectrodeInputRawValues()
{
    Serial.println("\r\nElectrode Inputs Raw Values");
    Serial.flush();

    driveSourceMux.enable(false);
    driveGroundMux.enable(false);
    senseAMux.enable(false);
    senseBMux.enable(false);

        
    // Loop over all sensing pairs
    for (   // Sensing pairs from 0
            unsigned int senseAElectrode = 0, senseBElectrode = 1;

            // Continue until we reach the driving electrode
            senseBElectrode < g_iElectrodes;

            // Rotate by one each iteration
            ++senseBElectrode
        )
    {
        senseAMux.select((ADG732::Channel) transformElectrode(senseAElectrode));
        senseBMux.select((ADG732::Channel) transformElectrode(senseBElectrode));
        senseAMux.enable(true); senseBMux.enable(true);

        volatile uint32_t sample = 0;
        adc_collect_samples(const_cast<uint32_t * >( &sample), 1);

        senseAMux.enable(false); senseBMux.enable(false);

        Serial.print(sample * ( 3.33f / 65536 ) , 4); Serial.print(",\t");Serial.flush();
    }
    Serial.print("\r\n");Serial.flush();
}

void TestInputs()
{
    Serial.println("\r\nInputs");
    Serial.flush();

    driveSourceMux.enable(false);
    driveGroundMux.enable(false);
    senseAMux.enable(false);
    senseBMux.enable(false);

        
    // Loop over all sensing pairs
    for (   // Sensing pairs from 0
            unsigned int senseAElectrode = 0, senseBElectrode = 1;

            // Continue until we reach the driving electrode
            senseBElectrode < g_iElectrodes;

            // Rotate by one each iteration
            ++senseBElectrode
        )
    {
        senseAMux.select((ADG732::Channel) transformElectrode(senseAElectrode));
        senseBMux.select((ADG732::Channel) transformElectrode(senseBElectrode));
        senseAMux.enable(true); senseBMux.enable(true);
        
        adc_collect_samples(const_cast<uint32_t * >(g_aiSamples), g_iSamples);

        senseAMux.enable(false); senseBMux.enable(false);

        float magnitude = eit_iq_demodulation ( const_cast<uint32_t const * >(&g_aiSamples[g_iSample_rubbish]), g_iSamples_useful, g_iSamples_per_cycle);

        Serial.print(magnitude, 4); Serial.print(",\t");Serial.flush();
    }

    Serial.print("\r\n");Serial.flush();

        // Loop over all sensing pairs
    for (   // Sensing pairs from 0
            unsigned int senseAElectrode = 0, senseBElectrode = 1;

            // Continue until we reach the driving electrode
            senseBElectrode < g_iElectrodes;

            // Rotate by one each iteration
            ++senseBElectrode
        )
    {
        senseBMux.select((ADG732::Channel) transformElectrode(senseAElectrode));
        senseAMux.select((ADG732::Channel) transformElectrode(senseBElectrode));
        senseAMux.enable(true); senseBMux.enable(true);
        
        adc_collect_samples(const_cast<uint32_t * >(g_aiSamples), g_iSamples);

        senseAMux.enable(false); senseBMux.enable(false);

        float magnitude = eit_iq_demodulation ( const_cast<uint32_t const * >(&g_aiSamples[g_iSample_rubbish]), g_iSamples_useful, g_iSamples_per_cycle);

        Serial.print(magnitude, 4); Serial.print(",\t");Serial.flush();
    }
    Serial.print("\r\n");Serial.flush();
}


void TestEITRaw()
{
    unsigned int result_counter = 0;
    Serial.print("\r\nEIT Raw data ");
    Serial.print("\r\nO+,O-,\tI+,I-,\tSamples");
    Serial.flush();

    driveSourceMux.enable(false);
    driveGroundMux.enable(false);
    senseAMux.enable(false);
    senseBMux.enable(false);

    // Loop over all driving pairs
    for(
            // Start from the 0th electrode
            unsigned int drivingElectrode = 0, 
                          groundElectrode = ( drivingElectrode + g_iDrivingDist ) % g_iElectrodes;

            // Do all the electrodes pairs
            drivingElectrode < g_iElectrodes;

            // Rotate by 1 each iteration
            groundElectrode  = ( ( ++drivingElectrode ) + g_iDrivingDist ) % g_iElectrodes
        )
    {
        // Drive the selected pair
        driveSourceMux.select((ADG732::Channel) transformElectrode(drivingElectrode));
        driveGroundMux.select((ADG732::Channel) transformElectrode(groundElectrode ));
        driveGroundMux.enable(true); driveSourceMux.enable(true);

        // Loop over all sensing pairs for the current driving arrangement :
        for (   // Sensing pairs start immediately after the driving electrode
                unsigned int senseAElectrode = (drivingElectrode + 1) % g_iElectrodes,
                             senseBElectrode = (senseAElectrode  + 1) % g_iElectrodes;

                // Continue until we reach the driving electrode
                (    ( senseAElectrode != drivingElectrode ) 
                  && ( senseBElectrode != drivingElectrode ) );

                // Rotate by one each iteration
                senseBElectrode = (   ( senseAElectrode = ( senseAElectrode + 1 ) % g_iElectrodes ) 
                                      + 1 ) % g_iElectrodes 
            )
        {
            // Skip measurements involving the driving electrodes
            if (    ( groundElectrode == senseAElectrode )
                 || ( groundElectrode == senseBElectrode ) )
            {
                continue;
            }

            Serial.print("\r\n");
            Serial.print(drivingElectrode + 1);
            Serial.print(',');
            Serial.print(groundElectrode + 1);
            Serial.print(",\t");
            Serial.print(senseAElectrode + 1);
            Serial.print(',');
            Serial.print(senseBElectrode + 1);
            Serial.print(",\t");
            Serial.flush();

            senseAMux.select((ADG732::Channel) transformElectrode(senseAElectrode));
            senseBMux.select((ADG732::Channel) transformElectrode(senseBElectrode));
            senseAMux.enable(true); senseBMux.enable(true);

            adc_collect_samples(const_cast<uint32_t * >(g_aiSamples), g_iSamples);

            senseAMux.enable(false); senseBMux.enable(false);

            for (int i = 0; 
                i < g_iSamples_useful;
                ++i)
            {
                const uint16_t sample = g_aiSamples[g_iSample_rubbish + i];
                Serial.print(sample); Serial.print(", ");
            }

            result_counter++;
            Serial.flush();
        }

        driveSourceMux.enable(false);
        driveGroundMux.enable(false);
        senseAMux.enable(false);
        senseBMux.enable(false);

    }
    Serial.print("\r\n");
}


void collect_and_print_samples_analyse(bool printSamples)
{
    uint16_t smallest = 0xFFFF;
    uint16_t largest = 0x0000;
    uint32_t sum = 0x00000000;

    adc_collect_samples(const_cast<uint32_t * >(g_aiSamples), g_iSamples);

    Serial.print("Sampling : \r\n");
    Serial.print("\tsamples: "); Serial.print(g_iSamples_useful);Serial.print("\r\n");

    for (int i = 0; 
         i < g_iSamples_useful;
         ++i)
    {
        const uint16_t sample = g_aiSamples[g_iSample_rubbish + i];
        sum += sample;
        if (smallest > sample ) smallest = sample;
        if (largest < sample ) largest = sample;
        if(printSamples) { Serial.print(sample); Serial.print(", "); }
    }

    const float mean =  sum / (float) g_iSamples_useful;
    if(printSamples) Serial.print("\r\n");
    Serial.print("\tmin: ");  Serial.print(smallest * ( 3.33f / 65536 ), 4); Serial.print("\r\n");
    Serial.print("\tmax: ");  Serial.print(largest  * ( 3.33f / 65536 ), 4); Serial.print("\r\n");
    Serial.print("\tmean: "); Serial.print(mean     * ( 3.33f / 65536 ), 4); Serial.print("\r\n");

    float mean_squares = 0;

    for (int i = 0; 
         i < g_iSamples_useful;
         ++i)
    {
        const float sample = g_aiSamples[g_iSample_rubbish + i];
        const float mean_f = mean;
        mean_squares += pow(sample - mean_f, 2);
    }
    float variance = (mean_squares / g_iSamples_useful) * pow( 3.33f / 65536, 2 );
    float sigma = sqrt(variance);
    Serial.print("\tsigma: "); Serial.print(sigma, 4); Serial.print("\r\n");
}
