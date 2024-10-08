/*
 * MGUIOptionsLoaderMeasurementsBinary.cxx
 *
 *
 * Copyright (C) by Andreas Zoglauer.
 * All rights reserved.
 *
 *
 * This code implementation is the intellectual property of
 * Andreas Zoglauer.
 *
 * By copying, distributing or modifying the Program (or any work
 * based on the Program) you indicate your acceptance of this statement,
 * and all its terms.
 *
 */


// Include the header:
#include "MGUIOptionsLoaderMeasurementsBinary.h"

// Standard libs:

// ROOT libs:
#include <TSystem.h>
#include <MString.h>
#include <TGLabel.h>
#include <TGResourcePool.h>

// MEGAlib libs:
#include "MStreams.h"
#include "MModule.h"
#include "MModuleLoaderMeasurementsBinary.h"


////////////////////////////////////////////////////////////////////////////////


#ifdef ___CLING___
ClassImp(MGUIOptionsLoaderMeasurementsBinary)
#endif


////////////////////////////////////////////////////////////////////////////////


MGUIOptionsLoaderMeasurementsBinary::MGUIOptionsLoaderMeasurementsBinary(MModule* Module) 
  : MGUIOptions(Module)
{
  // standard constructor
}


////////////////////////////////////////////////////////////////////////////////


MGUIOptionsLoaderMeasurementsBinary::~MGUIOptionsLoaderMeasurementsBinary()
{
  // kDeepCleanup is activated 
}


////////////////////////////////////////////////////////////////////////////////


void MGUIOptionsLoaderMeasurementsBinary::Create()
{
  PreCreate();

  m_FileSelector = new MGUIEFileSelector(m_OptionsFrame, "Please select a data file:",
    dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->GetFileName());
  m_FileSelector->SetFileType("Bin file", "*.dat");
  m_FileSelector->SetFileType("Bin file", "*.bin");
  TGLayoutHints* LabelLayout = new TGLayoutHints(kLHintsTop | kLHintsCenterX | kLHintsExpandX, 10, 10, 10, 10);
  m_OptionsFrame->AddFrame(m_FileSelector, LabelLayout);

  m_DataMode = new MGUIERBList(m_OptionsFrame, "Choose the data to look at: ");
  m_DataMode->Add("Raw mode");
  m_DataMode->Add("Compton mode");
  m_DataMode->SetSelected((int) dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->GetDataSelectionMode());
  m_DataMode->Create();
  m_OptionsFrame->AddFrame(m_DataMode, LabelLayout);

  m_AspectMode = new MGUIERBList(m_OptionsFrame, "Choose the aspect mode");
  m_AspectMode->Add("GPS");
  m_AspectMode->Add("Magnetometer");
  m_AspectMode->Add("Interpolated GPS");
  m_AspectMode->Add("None");
  m_AspectMode->SetSelected((int) dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->GetAspectMode());
  m_AspectMode->Create();
  m_OptionsFrame->AddFrame(m_AspectMode, LabelLayout);

  m_CoincidenceMode = new MGUIERBList(m_OptionsFrame, "Enable/Disable merging of coincident events");
  m_CoincidenceMode->Add("Disable");
  m_CoincidenceMode->Add("Enable");
  m_CoincidenceMode->SetSelected((int) dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->GetCoincidenceMerging());
  m_CoincidenceMode->Create();
  m_OptionsFrame->AddFrame(m_CoincidenceMode, LabelLayout);



  PostCreate();
}


////////////////////////////////////////////////////////////////////////////////


bool MGUIOptionsLoaderMeasurementsBinary::ProcessMessage(long Message, long Parameter1, long Parameter2)
{
  // Modify here if you have more buttons

	bool Status = true;
	
  switch (GET_MSG(Message)) {
  case kC_COMMAND:
    switch (GET_SUBMSG(Message)) {
    case kCM_BUTTON:
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
  
  if (Status == false) {
    return false;
  }

  // Call also base class
  return MGUIOptions::ProcessMessage(Message, Parameter1, Parameter2);
}


////////////////////////////////////////////////////////////////////////////////


bool MGUIOptionsLoaderMeasurementsBinary::OnApply()
{
	// Modify this to store the data in the module!

  dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->SetFileName(m_FileSelector->GetFileName());
	
  if (m_DataMode->GetSelected() == 0) {
    dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->SetDataSelectionMode(MBinaryFlightDataParserDataModes::c_Raw);     
  } else if (m_DataMode->GetSelected() == 1) {
    dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->SetDataSelectionMode(MBinaryFlightDataParserDataModes::c_Compton);     
  } else if (m_DataMode->GetSelected() == 2) {
    dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->SetDataSelectionMode(MBinaryFlightDataParserDataModes::c_All);     
  }

  if (m_AspectMode->GetSelected() == 0) {
    dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->SetAspectMode(MBinaryFlightDataParserAspectModes::c_GPS);     
  } else if (m_AspectMode->GetSelected() == 1) {
    dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->SetAspectMode(MBinaryFlightDataParserAspectModes::c_Magnetometer);
  } else if (m_AspectMode->GetSelected() == 2) {
    dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->SetAspectMode(MBinaryFlightDataParserAspectModes::c_Interpolate);
  } else if (m_AspectMode->GetSelected() == 3) {
    dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->SetAspectMode(MBinaryFlightDataParserAspectModes::c_Neither);     
  }

  if( m_CoincidenceMode->GetSelected() == 0 ){
	  //false -> 0
	  dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->EnableCoincidenceMerging(false);
  } else if( m_CoincidenceMode->GetSelected() == 1 ){
	  //true -> 1
	  dynamic_cast<MModuleLoaderMeasurementsBinary*>(m_Module)->EnableCoincidenceMerging(true);
  }


	return true;
}


// MGUIOptionsLoaderMeasurementsBinary: the end...
////////////////////////////////////////////////////////////////////////////////
