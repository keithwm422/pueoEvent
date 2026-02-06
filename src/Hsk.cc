/****************************************************************************************
*  GeomTool.cc            Implementation of the PUEO Navigation classes
* 
*  Cosmin Deaconu <cozzyd@kicp.uchicago.edu>
*
*  (C) 2023-, The Payload for Ultrahigh Energy Observations (PUEO) Collaboration
* 
*  This file is part of pueoEvent, the ROOT I/O library for PUEO. 
* 
*  pueoEvent is free software: you can redistribute it and/or modify it under the
*  terms of the GNU General Public License as published by the Free Software
*  Foundation, either version 2 of the License, or (at your option) any later
*  version.
* 
*  Foobar is distributed in the hope that it will be useful, but WITHOUT ANY
*  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
*  A PARTICULAR PURPOSE. See the GNU General Public License for more details.
* 
*  You should have received a copy of the GNU General Public License along with
*  Foobar. If not, see <https://www.gnu.org/licenses/
*
****************************************************************************************/ 



#include "pueo/Hsk.h" 

ClassImp(pueo::hsk::Sensor); 
ClassImp(pueo::hsk::Hsk); 

#ifdef HAVE_PUEORAWDATA

/*pueo::hsk::Hsk::Hsk(const pueo_sensors_telem_t *hsk) :
  timeref_secs(hsk->timeref_secs),
  sensor_id_magic(hsk->sensor_id_magic),
  num_packets(hsk->num_packets)
{
    // Implementation to initialize Hsk from pueo_sensors_telem_t
    for(int i=0; i < hsk->num_packets; ++i)
    {
        pueo::hsk::Sensor thisSensor;
        const pueo_sensor_telem_t &rawSensor = hsk->sensors[i];
        thisSensor.sensor_id = rawSensor.sensor_id;
        thisSensor.relsecs = rawSensor.relsecs;
        thisSensor.val.fval = rawSensor.val.fval;
        thisSensor.val.ival = rawSensor.val.ival;
        thisSensor.val.uval = rawSensor.val.uval;
       sensors.push_back(thisSensor);    // Populate sensor data
    } // woah is this right?????
}*/
pueo::hsk::Hsk::Hsk(const pueo_sensors_disk_t *hsk, int numsensors) :
  sensor_id_magic(hsk->sensor_id_magic),
  num_packets(hsk->num_packets)
{
    // Implementation to initialize Hsk from pueo_sensors_telem_t
    for(int i=0; i < numsensors; ++i)
    {
        pueo::hsk::Sensor thisSensor;
        const pueo_sensor_disk_t &rawSensor = hsk->sensors[i];
        thisSensor.sensor_id = rawSensor.sensor_id;
        thisSensor.time_ms = rawSensor.time_ms;
        thisSensor.time_secs = rawSensor.time_secs;
        //thisSensor.val = rawSensor.val;
        //thisSensor.val.fval = (Float_t) rawSensor.val.fval;
        //thisSensor.val.ival = (Int_t) rawSensor.val.ival;
        //thisSensor.val.uval = (UInt_t) rawSensor.val.uval;
        thisSensor.fval = (Float_t) rawSensor.val.fval;
        thisSensor.ival = (Int_t) rawSensor.val.ival;
        thisSensor.uval = (UInt_t) rawSensor.val.uval;
       sensors.push_back(thisSensor);    // Populate sensor data
    } // woah is this right?????
}


#endif
