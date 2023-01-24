/*
 * MModuleDepthCalibrationLinearStrip.h
 *
 * Copyright (C) 2008-2008 by Mark Bandstra.
 * All rights reserved.
 *
 * Please see the source-file for the copyright-notice.
 *
 */


#ifndef __MModuleDepthCalibrationLinearStrip__
#define __MModuleDepthCalibrationLinearStrip__


////////////////////////////////////////////////////////////////////////////////


// Standard libs:

// ROOT libs:

// MEGAlib libs:
#include "MGlobal.h"
#include "MModule.h"

// Forward declarations:


////////////////////////////////////////////////////////////////////////////////


class MModuleDepthCalibrationLinearStrip : public MModule
{
  // public interface:
 public:
  //! Default constructor
  MModuleDepthCalibrationLinearStrip();
  //! Default destructor
  virtual ~MModuleDepthCalibrationLinearStrip();
  
  //! Create a new object of this class 
  virtual MModuleDepthCalibrationLinearStrip* Clone() { return new MModuleDepthCalibrationLinearStrip(); }

  //! Initialize the module
  virtual bool Initialize();

  //! Main data analysis routine, which updates the event to a new level 
  virtual bool AnalyzeEvent(MReadOutAssembly* Event);

  //! Show the options GUI
  virtual void ShowOptionsGUI();


  // protected methods:
 protected:

  // private methods:
 private:



  // protected members:
 protected:


  // private members:
 private:
  bool m_IsCalibrationLoaded[10];
  bool m_IsCalibrationLoadedStrip[10][2][37];
  double m_StripTiming_Front[10][2][37];
  double m_StripTiming_Back[10][2][37];
  double m_StripTimingFWHM_Front[10][2][37];
  double m_StripTimingFWHM_Back[10][2][37];
  double m_DefaultTiming_Low;
  double m_DefaultTiming_High;
  double m_DefaultTimingFWHM;




#ifdef ___CLING___
 public:
  ClassDef(MModuleDepthCalibrationLinearStrip, 0) // no description
#endif

};

#endif


////////////////////////////////////////////////////////////////////////////////