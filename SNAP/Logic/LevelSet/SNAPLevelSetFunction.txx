/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    SNAPLevelSetFunction.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$
  Copyright (c) 2003 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.
=========================================================================*/
#include "itkGradientImageFilter.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkNumericTraits.h"

template<class TImageType>
SNAPLevelSetFunction<TImageType>
::SNAPLevelSetFunction()
{
  m_TimeStep = 1.0f;
  
  m_CurvatureSpeedExponent = 0;
  m_AdvectionSpeedExponent = 0;
  m_PropagationSpeedExponent = 0;
  m_LaplacianSmoothingSpeedExponent = 0;

  m_PropagationSpeedInterpolator = ImageInterpolatorType::New();
  m_CurvatureSpeedInterpolator = ImageInterpolatorType::New();
  m_LaplacianSmoothingSpeedInterpolator = ImageInterpolatorType::New();

  m_AdvectionFieldInterpolator = VectorInterpolatorType::New();
}

template<class TImageType>
SNAPLevelSetFunction<TImageType>
::~SNAPLevelSetFunction()
{

}

template<class TImageType>
void
SNAPLevelSetFunction<TImageType>
::CalculateInternalImages()
{
  // Create a map of integers to image pointers.  This map will cache the 
  // different powers of g() that must be computed (hopefully none!)
  typedef std::map<int,ImagePointer> PowerMapType;
  PowerMapType powerMap;

  // Initialize the map for the default powers
  powerMap[0] = NULL;
  powerMap[1] = m_SpeedImage;

  // Create a list of the required powers
  int powers[4] = {
    this->GetPropagationSpeedExponent(),
    this->GetAdvectionSpeedExponent(),
    this->GetCurvatureSpeedExponent(),
    this->GetLaplacianSmoothingSpeedExponent()
  };

  // Create an image for each of these powers, if needed
  for(unsigned int iPower=0; iPower < 4; iPower++)
    {
    // For powers of 0 and 1, which are by far the most common, there is
    // nothing to compute
    if(powers[iPower] == 0 && powers[iPower] == 1) 
      {
      continue;
      }
    
    // For power 2, we square the speed image.  Since pow() is a dog, 
    // let's handle this case explicitly
    else if(powers[iPower] == 2)
      {
      // Create a filter that will square the image
      typedef itk::UnaryFunctorImageFilter<ImageType,ImageType,SquareFunctor>
        ExponentFilterType;

      // Run the filter
      typename ExponentFilterType::Pointer filter = 
        ExponentFilterType::New();
      filter->SetInput(m_SpeedImage);
      filter->Update();
      
      // Stick the filter's output into the map
      powerMap[2] = filter->GetOutput();
      }

    // For powers other than 3, let the user suffer through the pow()!
    else
      {
      // Create a filter that will square the image
      typedef itk::UnaryFunctorImageFilter<ImageType,ImageType,PowFunctor>
        ExponentFilterType;

      typename ExponentFilterType::Pointer filter = 
        ExponentFilterType::New();
      filter->SetInput(m_SpeedImage);
      
      // Create a functor with specified power
      PowFunctor functor;
      functor.power = powers[iPower];
      filter->SetFunctor(functor);

      // Run the filter
      filter->Update();
      
      // Stick the filter's output into the map
      powerMap[powers[iPower]] = filter->GetOutput();
      }
    } // For all powers

  // Now that we have the powers, we can assign the speed images
  m_PropagationSpeedImage = powerMap[m_PropagationSpeedExponent];
  m_CurvatureSpeedImage = powerMap[m_CurvatureSpeedExponent];
  m_LaplacianSmoothingSpeedImage = powerMap[m_LaplacianSmoothingSpeedExponent];
  
  // There is still the business of the advection image to attend to
  // Create a gradient filter to compute \f$ \nabla g() \f$.
  typedef itk::GradientImageFilter<ImageType> GradientFilterType;
  typename GradientFilterType::Pointer fltGradient = 
    GradientFilterType::New();
  fltGradient->SetInput(m_SpeedImage);
  fltGradient->Update();

  // Allocate the advection image
  m_AdvectionField = VectorImageType::New();
  m_AdvectionField->SetRequestedRegion(m_SpeedImage->GetRequestedRegion());
  m_AdvectionField->SetBufferedRegion(m_SpeedImage->GetBufferedRegion());
  m_AdvectionField->SetLargestPossibleRegion(m_SpeedImage->GetLargestPossibleRegion());
  m_AdvectionField->Allocate();

  itk::ImageRegionIterator<GradientFilterType::OutputImageType> 
    git( fltGradient->GetOutput(), 
         m_AdvectionField->GetRequestedRegion());

  itk::ImageRegionIterator<VectorImageType> 
    ait( m_AdvectionField, 
         m_AdvectionField->GetRequestedRegion());

  // Multiply the gradient image by the speed image if necessary
  if(m_AdvectionSpeedExponent != 0)
    {
    // The image to multiply by
    itk::ImageRegionIterator<ImageType> 
      sit( powerMap[m_AdvectionSpeedExponent], 
           m_AdvectionField->GetRequestedRegion());

    for( git.GoToBegin(), ait.GoToBegin(), sit.GoToBegin(); 
         !git.IsAtEnd(); 
         ++git, ++ait, ++sit )
      {
      // ait.Value() = static_cast<VectorType>(git.Value() * sit.Value());
      ait.Value() = git.Value() * sit.Value();
      }
    }
  else
    {
    // Just copy the gradient
    for( git.GoToBegin(), ait.GoToBegin(); !git.IsAtEnd(); ++git, ++ait)
      {
      ait.Value() = git.Value();
      }
    }

  // Set up the image interpolators
  if(m_PropagationSpeedExponent != 0)
    m_PropagationSpeedInterpolator->SetInputImage(m_PropagationSpeedImage);
  if(m_CurvatureSpeedExponent != 0)
    m_CurvatureSpeedInterpolator->SetInputImage(m_CurvatureSpeedImage);
  if(m_LaplacianSmoothingSpeedExponent != 0)
    m_LaplacianSmoothingSpeedInterpolator->SetInputImage(
      m_LaplacianSmoothingSpeedImage);

  // Set up the advection interpolator
  if(m_AdvectionSpeedExponent != 0)
    m_AdvectionFieldInterpolator->SetInputImage(m_AdvectionField);
}


template<class TImageType>
typename SNAPLevelSetFunction<TImageType>::ScalarValueType
SNAPLevelSetFunction<TImageType>
::CurvatureSpeed(const NeighborhoodType &neighborhood, 
                 const FloatOffsetType &offset) const 
{
  // If the exponent is zero, there is nothing to return
  if(m_CurvatureSpeedExponent == 0)
    return itk::NumericTraits<ScalarValueType>::One; 
  
  // Otherwise, perform interpolation on the image
  IndexType idx = neighborhood.GetIndex();
  ContinuousIndexType cdx;
  for (unsigned i = 0; i < ImageDimension; ++i)
    {
    cdx[i] = static_cast<double>(idx[i]) - offset[i];
    }
  if ( m_CurvatureSpeedInterpolator->IsInsideBuffer(cdx) )
    {
    return (static_cast<ScalarValueType>(
        m_CurvatureSpeedInterpolator->EvaluateAtContinuousIndex(cdx)));
    }
  else return ( static_cast<ScalarValueType>(m_CurvatureSpeedImage->GetPixel(idx)) );
}

template<class TImageType>
typename SNAPLevelSetFunction<TImageType>::ScalarValueType
SNAPLevelSetFunction<TImageType>
::PropagationSpeed(const NeighborhoodType &neighborhood, 
                 const FloatOffsetType &offset) const 
{
  // If the exponent is zero, there is nothing to return
  if(m_PropagationSpeedExponent == 0)
    return itk::NumericTraits<ScalarValueType>::One; 
  
  // Otherwise, perform interpolation on the image
  IndexType idx = neighborhood.GetIndex();
  ContinuousIndexType cdx;
  for (unsigned i = 0; i < ImageDimension; ++i)
    {
    cdx[i] = static_cast<double>(idx[i]) - offset[i];
    }
  if ( m_PropagationSpeedInterpolator->IsInsideBuffer(cdx) )
    {
    return (static_cast<ScalarValueType>(
        m_PropagationSpeedInterpolator->EvaluateAtContinuousIndex(cdx)));
    }
  else return ( static_cast<ScalarValueType>(m_PropagationSpeedImage->GetPixel(idx)) );
}

template<class TImageType>
typename SNAPLevelSetFunction<TImageType>::ScalarValueType
SNAPLevelSetFunction<TImageType>
::LaplacianSmoothingSpeed(const NeighborhoodType &neighborhood, 
                 const FloatOffsetType &offset) const 
{
  // If the exponent is zero, there is nothing to return
  if(m_LaplacianSmoothingSpeedExponent == 0)
    return itk::NumericTraits<ScalarValueType>::One; 
  
  // Otherwise, perform interpolation on the image
  IndexType idx = neighborhood.GetIndex();
  ContinuousIndexType cdx;
  for (unsigned i = 0; i < ImageDimension; ++i)
    {
    cdx[i] = static_cast<double>(idx[i]) - offset[i];
    }
  if ( m_LaplacianSmoothingSpeedInterpolator->IsInsideBuffer(cdx) )
    {
    return (static_cast<ScalarValueType>(
        m_LaplacianSmoothingSpeedInterpolator->EvaluateAtContinuousIndex(cdx)));
    }
  else return ( static_cast<ScalarValueType>(m_LaplacianSmoothingSpeedImage->GetPixel(idx)) );
}

template <class TImageType>
typename SNAPLevelSetFunction<TImageType>::VectorType
SNAPLevelSetFunction<TImageType>
::AdvectionField(const NeighborhoodType &neighborhood,
                 const FloatOffsetType &offset)  const
{
  IndexType idx = neighborhood.GetIndex();
  ContinuousIndexType cdx;
  for (unsigned i = 0; i < ImageDimension; ++i)
    {
    cdx[i] = static_cast<double>(idx[i]) - offset[i];
    }
  if ( m_AdvectionFieldInterpolator->IsInsideBuffer(cdx) )
    {
    return ( 
      m_VectorCast(
       m_AdvectionFieldInterpolator->EvaluateAtContinuousIndex(cdx)));
    }
  else return ( m_AdvectionField->GetPixel(idx) );
}

template <class TImageType>
void
SNAPLevelSetFunction<TImageType>
::PrintSelf(std::ostream &os, itk::Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}