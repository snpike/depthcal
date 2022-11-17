/*
 * MNCTDepthCalibrator.h
 *
 * Copyright (C) by Alex Lowell.
 * All rights reserved.
 *
 * Please see the source-file for the copyright-notice.
 *
 */


#ifndef __MNCTDepthCalibrator__
#define __MNCTDepthCalibrator__


////////////////////////////////////////////////////////////////////////////////


// Standard libs:
#include <unordered_map>
#include <vector>

// ROOT libs:
#include "TMultiGraph.h"
#include "TSpline.h"

// MEGAlib libs:
#include "MGlobal.h"
#include "MString.h"
#include "MFile.h"

// Forward declarations:


////////////////////////////////////////////////////////////////////////////////


class MNCTDepthCalibrator
{
	public:
    //! Default constructor
    MNCTDepthCalibrator();
    //! Default destructor
    virtual ~MNCTDepthCalibrator() {};
		//! Load the coefficients file (i.e. fit parameters for each pixel)
		bool LoadCoeffsFile(MString FName);
		//! Return the coefficients for a pixel
		std::vector<double>* GetPixelCoeffs(int pixel_code);
		//! Load the splines file
		bool LoadSplinesFile(MString FName);
		//! Return a pointer to a spline
		TSpline3* GetSpline(int Det, bool Depth2CTD);
		//! Return detector thickness
		double GetThickness(int DetID);
		//! Get spline relating depth to anode timing
		TSpline3* GetAnodeSpline(int Det);
		//! Get spline relating depth to cathode timing
		TSpline3* GetCathodeSpline(int Det);


	private:
		//! Generate the spline from the data and add it to the internal spline map
		void AddSpline(vector<double> xvec, vector<double> yvec, int DetID, std::unordered_map<int,TSpline3*>& SplineMap, bool invert);


	private:
		std::unordered_map<int,std::vector<double>*> m_Coeffs;
		std::unordered_map<int,TSpline3*> m_SplineMap_Depth2CTD;
		std::unordered_map<int,TSpline3*> m_SplineMap_CTD2Depth;
		std::unordered_map<int,TSpline3*> m_SplineMap_Depth2AnoTiming;
		std::unordered_map<int,TSpline3*> m_SplineMap_Depth2CatTiming;
		bool m_SplinesFileIsLoaded;
		bool m_CoeffsFileIsLoaded;
		std::vector<double> m_Thicknesses;



#ifdef ___CLING___
 public:
  ClassDef(MNCTDepthCalibrator, 0) // no description
#endif

};

#endif