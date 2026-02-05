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

ClassImp(pueo::daqhsk::Hsk); 
ClassImp(pueo::daqhsk::Sensor); 

#ifdef HAVE_PUEORAWDATA

pueo::hsk::Hsk::Hsk(const pueo_sensors_telem_t *hsk) :
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
        thisSensor.val_fval = rawSensor.val.fval;
        thisSensor.val_ival = rawSensor.val.ival;
        thisSensor.val_uval = rawSensor.val.uval;
       sensors.push_back(thisSensor);    // Populate sensor data
    } // woah is this right?????
}


#endif
