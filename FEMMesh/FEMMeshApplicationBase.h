/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    FEMMeshApplicationBase.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef FEMMeshApplicationBase_H
#define FEMMeshApplicationBase_H


#include "itkMacro.h"
#include "vtkRenderWindow.h"
#include "itkFEMHeatConduction2D.h"



// This is the base classe for the Application

class FEMMeshApplicationBase 
{

public:

  typedef itk::fem::FEMHeatConduction2D        HeatSolverType;
  typedef HeatSolverType::FEMMeshType          HeatMeshType;

public:

  FEMMeshApplicationBase();

  virtual ~FEMMeshApplicationBase();
  
  virtual void CreateFEMMesh(void);
  virtual void DisplayFEMMesh(void);
  virtual void DisplayAxes(void) const;
  virtual void ComputeArea(void) const;

protected:
 
  vtkRenderWindow     * m_RenderWindow;
  vtkRenderer         * m_Renderer;


  HeatSolverType::Pointer m_HeatSolver;

};


#endif
