PROJECT( vtkITK )


IF( BUILD_OUTSIDE_INSIGHT_APPLICATIONS )

  FIND_PACKAGE(ITK)
  IF(ITK_FOUND)
    INCLUDE(${ITK_USE_FILE})
  ELSE(ITK_FOUND)
    MESSAGE(FATAL_ERROR
            "Cannot build ITKApps without ITK.  Please set ITK_DIR.")
  ENDIF(ITK_FOUND)

  FIND_PACKAGE(VTK)
  IF (VTK_FOUND)
      INCLUDE (${VTK_USE_FILE})
  ENDIF (VTK_FOUND)

ENDIF( BUILD_OUTSIDE_INSIGHT_APPLICATIONS )


INCLUDE_REGULAR_EXPRESSION("^.*$")

INCLUDE_DIRECTORIES ( ${vtkITK_SOURCE_DIR}/Common)

IF (VTK_WRAP_TCL)
  INCLUDE_DIRECTORIES ( ${TCL_INCLUDE_PATH})
ENDIF()

IF (VTK_WRAP_PYTHON)
  FIND_PACKAGE(PythonLibs)
  INCLUDE_DIRECTORIES ( ${PYTHON_INCLUDE_PATH})
ENDIF()

# Add the common directory
SUBDIRS ( Common )
SUBDIRS ( Wrapping )
