


#ifndef __MAspectPacket__
#define __MAspectPacket__


////////////////////////////////////////////////////////////////////////////////


// Standard libs:
#include <deque>
#include <string>
#include <cstdint>
using namespace std;

// ROOT libs:
#include "TROOT.h"

// MEGAlib libs:

// Forward declarations:


////////////////////////////////////////////////////////////////////////////////	


class MAspectPacket{
	public:
    //! Default constructor to initialize the avles with a default value
    MAspectPacket() {
      GPS_or_magnetometer = 2;
      test_or_not = 1;
      date_and_time = "";
      nanoseconds = 0;
      geographic_longitude = 0;
      geographic_latitude = 0;
      elevation = 0;
      heading = 0;
      pitch = 0;
      roll = 0;
      PPSClk = 0;
      CorrectedClk = 0;
      Error = false;
    
      GPSMilliseconds = 0;
      BRMS = 0;
      AttFlag = 0;

      GPSWeek = 0;
		GPSms = 0;
    }
    virtual ~MAspectPacket();
    
		int GPS_or_magnetometer; //0=GPS;1=magnetometer;2=no good data at
		/*specified time (when the GetAspect, GetAspectGPS, and 
		GetAspectMagnetometer search functions fail to find an MAspect
		object at a specified time they return a dummy MAspect object
		with its m_GPS_Or_Magnetometer attribute equal to 2*/
		int test_or_not; //0=Print Statements Shown; 1=Print statements deactivated
		string date_and_time;
		unsigned int nanoseconds;
		double geographic_longitude;
		double geographic_latitude;
		double elevation;
		double heading;
		double pitch;
		double roll;
		uint64_t PPSClk;
		uint64_t CorrectedClk;// approx the clock board value using the GPS milliseconds + PPS latch info
		bool Error;

		//From the GPS
		uint32_t GPSMilliseconds;
		double BRMS;
		uint16_t AttFlag;

		//GPS week computed from packet header
		int GPSWeek;

		//Unix time
		time_t UnixTime;

		//absolute GPS time down to the ms
		uint64_t GPSms;
	
	
  
#ifdef ___CLING___
 public:
   ClassDef(MAspectPacket, 0) 
#endif

};

#endif



////////////////////////////////////////////////////////////////////////////////
	
