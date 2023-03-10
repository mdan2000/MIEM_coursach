#pragma once

#include <string>
#include <map>

#include "./Genetic/GeneticParameters.h"

class CNNFromTruthTableParameters
{
public:
  bool getCNFF() { return d_CNFF; }
  bool getCNFT() { return d_CNFT; }

private:
  bool d_generateLimitations = false;
  bool d_CNFF = false;
  bool d_CNFT = false;
};

class GeneratorRandLevelParameters
{
public:
  int getMaxLevel() const
  {
    return d_maxLevel;
  }

  void setMaxLevel(int i_maxLevel)
  {
    d_maxLevel = i_maxLevel;
  }

  int getMaxElements() const
  {
    return d_maxElements;
  }

  void setMaxElements(int i_maxElements)
  {
    d_maxElements = i_maxElements;
  }

private:
  int d_maxLevel = 0;
  int d_maxElements = 0;
};

class GeneratorNumOperationParameters
{
public:
  int getLogicOper(const std::string& i_op) const
  {
    if (d_logicOper.find(i_op) != d_logicOper.end())
      return d_logicOper.at(i_op);
    return -1;
  }

  std::map<std::string, int> getLogicOpers() const
  {
    return d_logicOper;
  }

  void setLogicOper(const std::pair<std::string, int>& i_p)
  {
    d_logicOper[i_p.first] = i_p.second;
  }

  void setLogicOper(const std::map<std::string, int>& i_p)
  {
    d_logicOper = i_p;
  }

  bool getLeaveEmptyOut() const
  {
    return d_leaveEmptyOut;
  }

  void setLeaveEmptyOut(bool i_leo)
  {
    d_leaveEmptyOut = i_leo;
  }

private:
  std::map<std::string, int> d_logicOper;
  bool d_leaveEmptyOut = true;
};

class GenerationParameters
{
public:

  GenerationParameters(
    const std::string& i_name,
    int i_inputs,
    int i_outputs,
    int i_iteration) :
    d_name(i_name),
    d_inputs(i_inputs),
    d_outputs(i_outputs),
    d_iteration(i_iteration),
    d_geneticParameters(GeneticParameters(d_inputs, d_outputs))
  {};

  std::string getName() const
  {
    return d_name;
  }

  void setName(const std::string& i_name)
  {
    d_name = i_name;
  }

  int getInputs() const
  {
    return d_inputs;
  }

  void setInputs(int i_inputs)
  {
    d_inputs = i_inputs;
  }

  int getOutputs() const
  {
    return d_outputs;
  }

  void setOutputs(int i_outputs)
  {
    d_outputs = i_outputs;
  }

  int getIteration() const
  {
    return d_iteration;
  }

  void setIteration(int i_iteration)
  {
    d_iteration = i_iteration;
  }

  CNNFromTruthTableParameters getCNF() const { return d_cnfFromTruthTableParameters; }
  GeneratorRandLevelParameters getRandLevel() const { return d_generatorRandLevelParameters; }
  GeneratorNumOperationParameters getNumOperations() const { return d_generatorNumOperationParameters; }
  GeneticParameters& getGenetic() { return d_geneticParameters; }

private:
  std::string d_name = "";
  int d_inputs = 0;
  int d_outputs = 0;
  int d_iteration = 0;

  CNNFromTruthTableParameters d_cnfFromTruthTableParameters;
  GeneratorRandLevelParameters d_generatorRandLevelParameters;
  GeneratorNumOperationParameters d_generatorNumOperationParameters;

  GeneticParameters d_geneticParameters = GeneticParameters(2, 3);
};
