PROJECT( LiverTumorSegmentation )

#
#  Define the list of source files
#
INCLUDE_DIRECTORIES(
${InsightApplications_SOURCE_DIR}/Auxiliary/FltkImageViewer
${InsightApplications_SOURCE_DIR}/Auxiliary/VtkFltk
${InsightApplications_SOURCE_DIR}/Auxiliary/vtk
${InsightApplications_BINARY_DIR}/Auxiliary/FltkImageViewer
${InsightApplications_BINARY_DIR}/Auxiliary/VtkFltk
${LiverTumorSegmentation_SOURCE_DIR}
${LiverTumorSegmentation_BINARY_DIR}
)

SET(LIVER_TUMOR_SEGMENTATION_LIBRARY_SRCS
  ConfidenceConnectedModule.cxx
  ConnectedThresholdModule.cxx
  ThresholdLevelSetSegmentationModule.cxx
)

SET(LIVER_TUMOR_SEGMENTATION_LIBRARY_HEADS
  macros.h
  ConfidenceConnectedModule.h
  ConnectedThresholdModule.h
  ThresholdLevelSetSegmentationModule.h
)


SET(LIVER_TUMOR_SEGMENTATION_EXAMPLE_SRCS
  DicomImageReaderBase.cxx
  ImageSliceViewer.cxx
  InteractorObserver.cxx
  LiverTumorSegmentation.cxx
  LiverTumorSegmentationBase.cxx
  )


SET(LIVER_TUMOR_SEGMENTATION_EXAMPLE_HEADS
  ClickedPointEvent.h
  DicomImageReader.h
  DicomImageReaderBase.h
  ImageSliceViewer.h
  InteractorObserver.h
  LiverTumorSegmentation.h
  LiverTumorSegmentationBase.h
  )

ADD_LIBRARY(LiverTumorSegmentationLibrary 
		${LIVER_TUMOR_SEGMENTATION_LIBRARY_HEADS} 
		${LIVER_TUMOR_SEGMENTATION_LIBRARY_SRCS} )


ADD_EXECUTABLE(LiverTumorSegmentationExample 
		main.cxx 
		${LIVER_TUMOR_SEGMENTATION_EXAMPLE_HEADS} 
		${LIVER_TUMOR_SEGMENTATION_EXAMPLE_SRCS})

FLTK_WRAP_UI(LiverTumorSegmentationExample 
  DicomImageReaderGUI.fl 
  LiverTumorSegmentationGUI.fl 
  )

TARGET_LINK_LIBRARIES( LiverTumorSegmentationExample 
	LiverTumorSegmentationLibrary 
	ITKAlgorithms ITKBasicFilters ITKCommon ITKIO ITKNumerics ITKIO 
	ITKFltkImageViewer ITKVtkFltk
	vtkRendering vtkGraphics vtkHybrid vtkImaging vtkIO vtkFiltering vtkCommon 
	${FLTK_LIBRARIES})

ADD_EXECUTABLE(ResampleVolumes ResampleVolumes.cxx )

TARGET_LINK_LIBRARIES(ResampleVolumes ITKIO ITKCommon ITKNumerics)
