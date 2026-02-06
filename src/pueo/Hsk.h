/****************************************************************************************
*  pueo/Nav.h             PUEO Nav Storage
*  
*  Navigation storage classes
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


#ifndef PUEO_DAQHSK_H
#define PUEO_DAQHSK_H

//Includes
#include <TObject.h>

#include <array>
#ifdef HAVE_PUEORAWDATA
#include "pueo/rawdata.h"
#endif
namespace pueo 
{



  namespace hsk 
  {



    /** @defgroup rootclasses The ROOT Classes
     * These are the ROOT clases that make up the event reader
     */
    // per class there will be a surf array that has the surf information and beam array inside it

    // then totally different class for the trigger information and l2 readout time, etc
    class Sensor: public TObject
    {
     public:
       Sensor() {;}
       virtual ~Sensor() {;}
       UShort_t sensor_id=0;
       UShort_t time_ms=0;
       UInt_t time_secs=0;
       //union { // expanded to 32 bits 
       Float_t fval;
       Int_t ival;
       UInt_t uval;
       //} val;
       ClassDef(Sensor,1);
    };
    class Hsk: public TObject
    {
     public:
       Hsk() {;}
#ifdef HAVE_PUEORAWDATA
       //Hsk(const pueo_sensors_telem_t *hsk);
       Hsk(const pueo_sensors_disk_t *hsk,int numsensors);
#endif
      virtual ~Hsk(){;}
      UShort_t sensor_id_magic=0;
      UShort_t num_packets=0;
      std::vector<Sensor> sensors;
      ClassDef(Hsk,1);
    };
  }
}


#endif //ADU5PAT_H
