//--------------------------------------------
//
//     Project:   Operating Room
//
//     Author:    Luis Ibanez
//
//     Division of Neurosugery
//     Department of Surgery
//     University of North Carolina
//     Chapel Hill, NC 27599
//
//--------------------------------------------


#include <liShape3D.h>
#include <liCommandTubesGeneratePointSet.h>
#include <FL/Fl.H>

namespace li {


//--------------------------------------------------
//
//    Constructor
//
//--------------------------------------------------
CommandTubesGeneratePointSet::CommandTubesGeneratePointSet(void)  
{
}



//--------------------------------------------------
//
//    Execute
//
//--------------------------------------------------
void
CommandTubesGeneratePointSet::Execute( itk::Object * unit, unsigned long event )
{
  
  if( event == FluoroscopyUnitMovedEvent ||
      event == PatientMovedEvent         ||
      event == TableMovedEvent              )
  {
    if( m_FluoroscopyUnit && m_Tubes )
    {

      itk::Point<double,3>  sourcePosition;
      itk::Point<double,3>  detectorPosition;
      
      sourcePosition   = m_FluoroscopyUnit->GetSourcePosition();
      detectorPosition = m_FluoroscopyUnit->GetDetectorPosition();
      
      itk::Vector<double,3> lineOfSigth = detectorPosition - sourcePosition;

      m_Tubes->GeneratePointSet( lineOfSigth );

    }
  }
}




//--------------------------------------------------
//
//    Execute
//
//--------------------------------------------------
void
CommandTubesGeneratePointSet::Execute(const itk::Object * unit, unsigned long event )
{

  if( event == FluoroscopyUnitMovedEvent   ||
      event == PatientMovedEvent           ||
      event == TableMovedEvent              )
  {
    if( m_FluoroscopyUnit && m_Tubes )
    {

      itk::Point<double,3>  sourcePosition;
      itk::Point<double,3>  detectorPosition;
      
      sourcePosition   = m_FluoroscopyUnit->GetSourcePosition();
      detectorPosition = m_FluoroscopyUnit->GetDetectorPosition();
      
      itk::Vector<double,3> lineOfSigth = detectorPosition - sourcePosition;

      m_Tubes->GeneratePointSet( lineOfSigth );

    }
  }

}




} // end namespace li


