#pragma once
#ifndef PRECICE_NO_PYTHON

#include "action/Action.hpp"
#include "mesh/SharedPointer.hpp"
#include "logging/Logger.hpp"
#include <string>

struct _object;
using PyObject = _object;


namespace precice {
namespace action {

/// Action whose implementation is given in a Python file.
class PythonAction : public Action
{
public:

  PythonAction (
    Timing               timing,
    const std::string&   modulePath,
    const std::string&   moduleName,
    const mesh::PtrMesh& mesh,
    int                  targetDataID,
    int                  sourceDataID );

  virtual ~PythonAction();

  virtual void performAction (
    double time,
    double dt,
    double computedPartFullDt,
    double fullDt );

private:

  static logging::Logger _log;

  std::string _modulePath;

  std::string _moduleName;

  mesh::PtrData _targetData;

  mesh::PtrData _sourceData;

  int _numberArguments;

  bool _isInitialized;

  PyObject* _moduleNameObject;

  PyObject* _module;

  PyObject* _sourceValues;

  PyObject* _targetValues;

  PyObject* _performAction;

  PyObject* _vertexCallback;

  PyObject* _postAction;

  void initialize();

  int makeNumPyArraysAvailable();
};

}} // namespace precice, action

#endif
