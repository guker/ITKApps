/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    SegmenterConsole.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef SEGMENTERCONSOLE
#define SEGMENTERCONSOLE

#include <SegmenterConsoleGUI.h>
#include "ImageViewer.h"


class SegmenterConsole : public SegmenterConsoleGUI {

public:

  typedef ImageViewer< InputPixelType, WritePixelType > 
                                               InputImageViewerType;
  typedef ImageViewer< InputPixelType, WritePixelType > 
                                               SeedViewerType;
  typedef ImageViewer< InputPixelType, WritePixelType > 
                                               SpeedViewerType;


public:
  SegmenterConsole();
  virtual ~SegmenterConsole();
  virtual void Show(void);
  virtual void Hide(void);
  virtual void Load(void);
  virtual void Quit(void);
  virtual void ShowInputImage(void);
  virtual void InitializeGuessImage(void);
  virtual void SmoothImage();
  virtual void ShowSpeedImage();
  virtual void ShowSegmentedImage(void);
  virtual void SwitchCase(int);
  virtual void LoadSeedImage();
  virtual void ShowSeedImage(void);
  virtual void GetClickPoints(float x, float y);
  virtual void ChangePaintRadius(float);
  virtual void ClearGuess();
  virtual void ClearThresh();
  virtual void UpdateViewerAfterIteration();
  virtual void ToggleThresholdGuess();
  virtual void CalculateThresholds();
  virtual void SaveSegmented();
  virtual void SaveBinaryMask();
  virtual void ChangeMinThresh(float);
  virtual void ChangeMaxThresh(float);
  virtual void SetThresholdFilterToModified();
  virtual void SaveSession();
  virtual void LoadSession();

  static void ClickSelectCallback(float x, float y, float z, float value, void * args );

private:
  InputImageViewerType*      m_InputViewer;
  SeedViewerType*            m_SeedViewer;
  SpeedViewerType*           m_SpeedViewer;
  
  int guessRadius;
  int m_filterCase;
  int m_drawCase;

  int width;
  int height;
  float min;
  float max;
  float prevMinThresh;
  float prevMaxThresh;

  bool loadingSession;
  std::string inputFilename;
  std::string seedFilename;
};



#endif
