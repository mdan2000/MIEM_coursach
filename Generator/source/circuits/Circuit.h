#pragma once

class Circuit
{
public:
  Circuit(const OrientedGraph& i_graph, const std::vector<std::string>& i_logExpressions);
  void updateCircuitsParameters();
  void computeHash();
  bool graphToVerilog(const std::string& i_path, bool i_pathExists = false);
  bool saveParameters(bool i_pathExists = false);
  bool generate(bool i_pathExists);

private:
  OrientedGraph d_graph;
  std::vector<std::string> d_logExpressions;
  TruthTable d_tTable;
  std::string d_path;
  std::string d_circuitName;
  CircuitParameters d_circuitParameters;
  Settings d_settings = Settings::loadSettings();

  bool checkExistingHash();

}