/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "ComputeAxisymmetricRZIncrementalStrain.h"
#include "Assembly.h"

template<>
InputParameters validParams<ComputeAxisymmetricRZIncrementalStrain>()
{
  InputParameters params = validParams<Compute2DIncrementalStrain>();
  params.addClassDescription("Compute a strain increment and rotation increment for finite strains under axisymmetric assumptions.");
  return params;
}

ComputeAxisymmetricRZIncrementalStrain::ComputeAxisymmetricRZIncrementalStrain(const InputParameters & parameters) :
    Compute2DIncrementalStrain(parameters),
    _disp_old_0(coupledValueOld("displacements", 0))
{
}

void
ComputeAxisymmetricRZIncrementalStrain::initialSetup()
{
  if (_assembly.coordSystem() != Moose::COORD_RZ)
    mooseError("The coordinate system must be set to RZ for Axisymmetric simulations.");
}

Real
ComputeAxisymmetricRZIncrementalStrain::computeDeformGradZZ()
{
  if (!MooseUtils::relativeFuzzyEqual(_q_point[_qp](0), 0.0))
    return (*_disp[0])[_qp] / _q_point[_qp](0);
  else
    return 0.0;
}

Real
ComputeAxisymmetricRZIncrementalStrain::computeDeformGradZZold()
{
  if (!MooseUtils::relativeFuzzyEqual(_q_point[_qp](0), 0.0))
    return _disp_old_0[_qp] / _q_point[_qp](0);
  else
    return 0.0;
}