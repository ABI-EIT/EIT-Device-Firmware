void LOG(char const str[])
{
    Serial.print(str);
}

void LOG(String const & str)
{
    Serial.print(str);
}
void LOG(uint16_t v)
{
    Serial.print(v);
}
void LOG(uint32_t v)
{
    Serial.print(v);
}
void LOG(float v)
{
    Serial.print(v);
}

void LOG(Mode m)
{
    Serial.print(getModeLabels(m));
    Serial.print(" ["); Serial.print(m); Serial.print(']');
}
void LOG(DACMode m)
{
    Serial.print(getDACModeLabel(m));
    Serial.print(" ["); Serial.print(m); Serial.print(']');
}

void SL()
{
    LOG("\r\n# ");
}

template <typename T>
T bound(T value, T min, T max) 
{
  return ( value < min ) ? min : ( ( value > max ) ? max : value ); 
}

void deviceInfo()
{
    SL();
    SL(); LOG(" " DEVICE_NAME " ( v" FIRMWARE_VERSION " )");
    SL(); LOG(" DEBUG BUILD ");
    SL();
}

template <typename Enum, typename Type = typename Enum::Type >
bool getDirectE(String const & name, String const & match, String const & match_to, Type & value)
{
    if (match != match_to) return false;
    SL(); LOG(name); LOG(": "); LOG(value); LOG("\r\n");
    return true;
}

bool getDirect(String const & name, String const & match, String const & match_to, uint16_t & value)
{
    if (match != match_to) return false;
    SL(); LOG(name); LOG(": "); LOG(value); LOG("\r\n");
    return true;
}

bool getDirect(String const & name, String const & match, String const & match_to, uint32_t & value)
{
    if (match != match_to) return false;
    SL(); LOG(name); LOG(": "); LOG(value); LOG("\r\n");
    return true;
}

bool getDirect(String const & name, String const & match, String const & match_to, float & value)
{
    if (match != match_to) return false;
    SL(); LOG(name); LOG(": "); LOG(value); LOG("\r\n");
    return true;
}

bool getDirect(String const & name, String const & match, String const & match_to, bool & value)
{
    if (match != match_to) return false;
    SL(); LOG(name); LOG(": "); LOG(value ? "true" : "false"); LOG("\r\n");
    return true;
}

template <typename Enum, typename Type = typename Enum::Type >
bool setDirectE(String const & name, String const & match, String const & match_to, String const & new_value, Type & value)
{
    if (match != match_to) return false;
    value = (Type) bound<uint32_t>(atoi(new_value.c_str()), (uint32_t) Enum::_MIN, (uint32_t) Enum::_MAX);
    SL(); LOG(name); LOG(": "); LOG(value); LOG("\r\n");
    return true;
}

bool setDirect(String const & name, String const & match, String const & match_to, String const & new_value, uint32_t & value, uint32_t min, uint32_t max)
{
    if (match != match_to) return false;
    value = bound<uint32_t>(atoi(new_value.c_str()), min, max);
    SL(); LOG(name); LOG(": "); LOG(value); LOG("\r\n");
    return true;
}

bool setDirect(String const & name, String const & match, String const & match_to, String const & new_value, bool & value)
{
    if (match != match_to) return false;
    value = ((new_value == "true") || (new_value == "1")) ? true : false;
    SL(); LOG(name); LOG(": "); LOG(value ? "true" : "false"); LOG("\r\n");
    return true;
}


void possibleValues(bool get = true)
{
    LOG("Possible values : ");
    if (get) LOG("all, ");
    LOG("dacMode, ");
    LOG("delay, ");
    LOG("dist, ");
    LOG("electrodes, ");
    LOG("inputGainResistor1, ");
    LOG("inputGainResistor2, ");
    LOG("mode, ");
    LOG("outputGainResistor, ");
    LOG("sampleCycles, ");
    LOG("samplesPerCycle, ");
    LOG("sampleRubbish, ");
    LOG("mapToLines, ");
    LOG("\r\n");
}

bool getUsage() {
    SL(); LOG("Usage : get valueName\r\n");
    possibleValues();
    return true;
}

bool setUsage() {
    SL(); LOG("Usage : set valueName value\r\n");
    possibleValues(false);
    return true;
}

bool unknownValue(String const & val)
{
    SL(); LOG(val); LOG(" not valid!\r\n");
    possibleValues();
    return true;
}


bool possibleCommands()
{
    SL(); LOG("Possible commands : ");
    LOG("stop, start, set, get, help");
    LOG("\r\n");
    return true;
}


bool unknownCommand(String const & cmd)
{
    SL(); LOG("Command '");LOG(cmd); LOG("' not valid!\r\n");
    possibleCommands();
    return true;
}


bool getAll(String const & match_to)
{
    if (match_to != "all") return false;
    SL();
    SL();LOG("mode"             ); LOG(": ");  LOG(g_eMode                   );
    SL();LOG("dacMode"          ); LOG(": ");  LOG(g_eDACMode                );
    SL();
    SL();LOG("delay"             ); LOG(": "); LOG(g_iDelay_ms               ); LOG(" ms");
    SL();LOG("dist"              ); LOG(": "); LOG(g_iDrivingDist                   );
    SL();LOG("electrodes"        ); LOG(": "); LOG(g_iElectrodes             );
    SL();LOG("inputGainResistor1"); LOG(": "); LOG(g_iInputGainResistor1_ohms); LOG(" ohms");
    SL();LOG("inputGainResistor2"); LOG(": "); LOG(g_iInputGainResistor2_ohms); LOG(" ohms");
    SL();LOG("outputGainResistor"); LOG(": "); LOG(g_iOutputGainResistor_ohms); LOG(" ohms");
    SL();LOG("sampleCycles"      ); LOG(": "); LOG(g_iSample_cycles          );
    SL();LOG("samplesPerCycle"   ); LOG(": "); LOG(g_iSamples_per_cycle      );
    SL();LOG("sampleRubbish"     ); LOG(": "); LOG(g_iSample_rubbish         );
    SL();LOG("mapToLines"        ); LOG(": "); LOG(g_bMapElectrodesToLines ? "true" : "false" );
    SL();
    SL();LOG("adcFrequency"      ); LOG(": "); LOG(g_iADC_frequency          ); LOG(" Hz");
    SL();LOG("run"               ); LOG(": "); LOG(g_bRun ? "true" : "false" );
    SL();LOG("samples"           ); LOG(": "); LOG(g_iSamples                );
    SL();LOG("samplesUseful"     ); LOG(": "); LOG(g_iSamples_useful         );
    SL();LOG("targetFrequency"   ); LOG(": "); LOG(g_iTarget_frequency       ); LOG(" Hz");
    SL();LOG("targetPeriod"      ); LOG(": "); LOG(g_iTarget_period_us       ); LOG(" μs");
    SL();
    SL();LOG("dacPoints"         ); LOG(": "); LOG(g_iDAC_points             );
    SL();LOG("pdbCycleLength"    ); LOG(": "); LOG(g_iPDB_cycleLength        );
    SL();LOG("dacTriggerInterval"); LOG(": "); LOG(g_iDAC_trigger_interval   );
    SL();LOG("pdbMod"            ); LOG(": "); LOG(g_iPDB_mod                );

    return true;
}

       

bool getConfigCommand(String const & command, String const & arguments) 
{
    if ( command != "get" ) return false;
    
    if(arguments.length() == 0 ) return getUsage();

    return getAll(arguments)
    || getDirectE<Modes>("mode"      , "mode"              , arguments, g_eMode                   )
    || getDirectE<DACModes>("dacMode", "dacmode"           , arguments, g_eDACMode                )

    || getDirect("delay"             , "delay"             , arguments, g_iDelay_ms               )
    || getDirect("dist"              , "dist"              , arguments, g_iDrivingDist                   )
    || getDirect("electrodes"        , "electrodes"        , arguments, g_iElectrodes             )
    || getDirect("inputGainResistor1", "inputgainresistor1", arguments, g_iInputGainResistor1_ohms)
    || getDirect("inputGainResistor2", "inputgainresistor2", arguments, g_iInputGainResistor2_ohms)
    || getDirect("outputGainResistor", "outputgainresistor", arguments, g_iOutputGainResistor_ohms)
    || getDirect("sampleCycles"      , "samplecycles"      , arguments, g_iSample_cycles          )
    || getDirect("samplesPerCycle"   , "samplespercycle"   , arguments, g_iSamples_per_cycle      )
    || getDirect("sampleRubbish"     , "samplerubbish"     , arguments, g_iSample_rubbish         )
    || getDirect("mapToLines"        , "mapToLines"        , arguments, g_bMapElectrodesToLines            )

    || getDirect("adcFrequency"      , "adcfrequency"      , arguments, g_iADC_frequency          )
    || getDirect("run"               , "run"               , arguments, g_bRun                    )
    || getDirect("samples"           , "samples"           , arguments, g_iSamples                )
    || getDirect("samplesUseful"     , "samplesuseful"     , arguments, g_iSamples_useful         )
    || getDirect("targetFrequency"   , "targetfrequency"   , arguments, g_iTarget_frequency       )
    || getDirect("targetPeriod"      , "targetperiod"      , arguments, g_iTarget_period_us       )


    || getDirect("dacPoints"         , "dacPoints"         , arguments, g_iDAC_points             )
    || getDirect("pdbCycleLength"    , "pdbcyclelength"    , arguments, g_iPDB_cycleLength        )
    || getDirect("dacTriggerInterval", "dactriggerinterval", arguments, g_iDAC_trigger_interval   )
    || getDirect("pdbMod"            , "pdbmod"            , arguments, g_iPDB_mod                )

    || unknownValue(arguments);
}

bool setConfigCommand(String const & command, String const & arguments) 
{
    if ( command != "set" ) return false;

    auto tok = arguments.indexOf(" ");
    
    if(tok == -1) return setUsage();

    auto arg1 = arguments.substring(0, tok);
    auto arg2 = (tok >= arguments.length()) ? "" : arguments.substring(tok+1);

    if((arg1.length() == 0) || (arg2.length() == 0)) return setUsage();
        0
     || setDirectE<Modes>("mode"      , "mode"              , arg1, arg2, g_eMode                   )
     || setDirectE<DACModes>("dacMode", "dacmode"           , arg1, arg2, g_eDACMode                )
     || setDirect("delay"             , "delay"             , arg1, arg2, g_iDelay_ms               , g_iDelay_min_ms               , g_iDelay_max_ms)
     || setDirect("dist"              , "dist"              , arg1, arg2, g_iDrivingDist                   , 1                             , g_iElectrodes/2)
     || setDirect("electrodes"        , "electrodes"        , arg1, arg2, g_iElectrodes             , g_iElectrodes_min             , g_iElectrodes_max)
     || setDirect("inputGainResistor1", "inputgainresistor1", arg1, arg2, g_iInputGainResistor1_ohms, g_iInputGainResistor_min_ohms , g_iInputGainResistor_max_ohms)
     || setDirect("inputGainResistor2", "inputgainresistor2", arg1, arg2, g_iInputGainResistor2_ohms, g_iInputGainResistor_min_ohms , g_iInputGainResistor_max_ohms)
     || setDirect("outputGainResistor", "outputgainresistor", arg1, arg2, g_iOutputGainResistor_ohms, g_iOutputGainResistor_min_ohms, g_iOutputGainResistor_max_ohms)
     || setDirect("sampleCycles"      , "samplecycles"      , arg1, arg2, g_iSample_cycles          , g_iSample_cycles_min          , g_iSample_cycles_max)
     || setDirect("samplesPerCycle"   , "samplespercycle"   , arg1, arg2, g_iSamples_per_cycle      , g_iSamples_per_cycle_min      , g_iSamples_per_cycle_max)
     || setDirect("sampleRubbish"     , "samplerubbish"     , arg1, arg2, g_iSample_rubbish         , g_iSample_rubbish_min         , g_iSample_rubbish_max)
     || setDirect("mapToLines"        , "mapToLines"        , arg1, arg2, g_bMapElectrodesToLines             )
     || unknownValue(arg1);

    recalculateGlobals();
    recalulatePeripherals();

    return true;
}


bool helpCommand(String const & command, String const & arguments) 
{
    if (( command != "help" ) && ( command != "?" )) return false;
    deviceInfo();
    return possibleCommands();
}


bool runCommand(String const & command, String const & arguments) 
{
    if ( ( command == "start" )  || ( command == "run" ) )
    {
        g_bRun = true;
    }
    else if ( command == "stop" )
    {
        g_bRun = false;
    }
    else
    {
        return false;
    }

    return true;
}



bool processCommands()
{
    // Is there anything in the input buffer
    if( Serial.peek() == -1 ) return false;
    
    // TODO: use state machine to manage timeout (infinate time time out until newline is pushed)
    String commandString = Serial.readStringUntil('\n').toLowerCase().trim();

    Serial.print("\r\n");

    // Extract command and arguments
    auto tok = commandString.indexOf(" "); // Everything before the first space is the command, and everything after are the arguments
    auto command = commandString.length() == 0 ? "" : commandString.substring(0, (tok == -1) ? commandString.length() : tok);
    auto arguments = (tok == -1) ? "" : commandString.substring(tok+1);

    // Execute the command
    //  Try each command in order, until we find one that works
    bool res = helpCommand(command, arguments)
            || setConfigCommand(command, arguments)
            || getConfigCommand(command, arguments)
            || runCommand(command, arguments)
            || unknownCommand(command);

    Serial.clear();

    Serial.print("\r\n");

    return res;
}