#pragma once

#include <string>
#include <map>
#include <utility>
#include <vector>

enum generationTypes {
  none,
  truthTableToGraphWithoutOptimization,
  truthTableToGraphWithOptimization
};

class Settings {
public:
  Settings();
  void loadSettings();
  std::pair<std::string, int> getLogicOperation(const std::string& i_op);
  std::vector<std::string> getLogicOperationsKeys();
  std::string fromOperationsToName(const std::string& i_op) const;
  std::string getDatasetPath() const;
  std::string getGenerationMethodPrefix(const std::string& i_s) const;
  int getMaxInputs() const;
  int getMaxOutputs() const;
  std::map<std::string, std::pair<std::string, int>> getLogicOperations() const;
  std::string getPathNadezhda() const;
  std::string getNadezhdaVar(const std::string& key) const;
  std::vector<std::string> fromOperationsToHierarchy(int key) const;

private:
  void SaveSettings();

  std::string d_csvdataset = "dataset.csv";
  std::string d_fileName = "settings.dat";
  std::string d_datasetPath = "./database";
  //Settings d_instance;
  std::string d_pathToNadezhda = "./data/Nadezhda";
  std::map<std::string, std::string> d_nadezhda = {
    {"python", "pathtopython"},
    {"resynthesis", "Nadezda/Scripts/resynthesis_local_rewriting.pyc"},
    {"reliability", "Nadezhda/Scripts/check_reliability.pyc"},
    {"liberty", "Nadezda/Test/Nangate.lib"}
  };
  int d_numThreads = 4;
  std::map<std::string, std::pair<std::string, int>> d_logicOperations = 
  {
    {"input",  {"",     10}},
    {"output", {"=",    0}},
    {"const",  {"1'b",  9}},
    {"and",    {"ans",  4}},
    {"nand",   {"nand", 3}},
    {"or",     {"or",   2}},
    {"nor",    {"nor",  1}},
    {"not",    {"not",  7}},
    {"buf",    {"buf",  8}},
    {"xor",    {"xor",  6}},
    {"xnor",   {"xnor", 5}}

  };
  std::map<int, std::vector<std::string>> d_operationsToHierarchy;
  std::map<std::string, std::string> d_operationsToName;
  int d_maxInputs = 50;
  int d_maxOutputs = 50;
};
