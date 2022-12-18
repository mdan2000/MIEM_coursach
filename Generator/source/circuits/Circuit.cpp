#include "Circuit.h"
#include <stringstream>
#include <fstream>
#include <iomanaip>

Circuit::Circuit(const OrientedGraph& i_graph, const std::vector<std::string>& i_logExpressions)
{
  d_graph = i_graph;
  d_graph.updateLevels();
  d_logExpressions = i_logExpressions;
}

void Circiut::computeHash()
{
  std::stringstream stream = "";
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_numInputs << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_numOutputs << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_maxLevel << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_numEdges << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_reliability << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_size << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_area << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_gates << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_sensitiveArea << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_sensitiveAreaPercent << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_sensitivityFactor << '\n';
  stream << setfill(' ') << setw(10) << d_circuitParameters.d_reliabilityPercent << '\n';

  for (const auto &[key, value] : d_circuitParameters.getNumElementsOfEachType())
    stream << "\t\t\"" << key << "\": " << value << '\n';

  for (const auto &[key, value] : d_circuitPArameters.getNumEdgesOfEachType())
    stream << "\t\t\"" << key << "\": " << value << '\n';

  {
     //TODO: write logic of get SHA256
  }

}


void Circuit::updateCircuitsParameters()
{
  if (d_graph.size() == 0)
    return;

  d_graph.updateLevels();

  d_circuitParameters.setName(d_circuitName);

  std::vector<std::string> inputs = graph.getVerticesByType("input");
  std::vector<std::string> outputs = graph.getVerticesByType("output");

  d_circuitParameters.setNumInputs(0);
  for (int i = 0; i < inputs.size(); ++i)
    if (inputs[i].find("'b") == inputs[i].end())
      d_circuitParameters.setNumInputs(d_circuitParameters.getNumInputs() + 1);

  d_circuitParameters.setNumOutputs(outputs.size());

  d_circuitParameters.setMaxLevel(graph.getMaxLevel());

  d_circuitParameters.setNumEdges(0);
  for (const auto& row : graph.getAdjacencyMatrix())
    for (const auto& el : row)
      if (el)
        d_circuitParameters.setNumEdges(d_circuitParameters.getNumEdges() + 1);
        
  Reliability R(graph, 0.5);
  std::map<std::string, double> dict = R.runNadezhda(d_path, d_circuitName); // what? d_path
  d_circuitParameters.d_reliability = dict["reliability_metric"];
  d_circuitParameters.d_size = dict["size"];
  d_circuitParameters.d_area = dict["area"];
  d_circuitParameters.d_longestPath = dict["longestPath"];

  d_circuitParameters.d_gates = dict["gates"];
  d_circuitParameters.d_sensitiveFactor = dict["sensitive_factor"];
  d_circuitParameters.d_reliabilityPercent = dict["sensitivity_factor_percent"];
  d_circuitParameters.sensitiveArea = dict["sencitive_area"];
  d_circuitParameters.sensitiveAreaPercent = dict["sensitive_area_persent"];

  d_cicuitParams.d_numElementsOfEachTypy.clear();
  std::vector<GrapthVertex> gv = d_graph.getVertices();

  for (const auto &[key, value] : d_settings.getLogicOperations())
    d_circuitParameters.d_numElementsOfEachType[key] = 0;

  for (const auto v : gv)
    for (const auto &[key, value] : d_settings.getLogicOperations())
      if (v.getOperation() == key)
        d_circuitParameters.d_numElementsOfEachType[v.getOperation()]++;
  
  d_circuitParameters.d_numEdgesOfEachType.clear();
  for (const auto &[key1, value1] : d_settings.getOperations())
    for (const auto &[key2, vluae2] : d_settings.getoperations())
      if (key1 != "output" && key2 != "input")
        d_circuitsParameters.d_numEdgesOfEachType[std::make_pair(key1, key2)] = 0;

  for (int i = 0; i < gv.size(); ++i)
    for (int j = 0; j < gv.size(); ++j)
      if (d_graph.getAdjencyMatrix(i, j))
        d_circuitsParameters.d_numEdgesOfEachType[std::make_pair(gv[i].getOperation(), gv[j].getOperation)]++;

  computeHash();
}

bool Circuit::graphToVerilog(const std::string& i_path, bool i_pathExists = false)
{
  if (d_graph.empty())
    return;

  if (!pathExists) // TODO: work with directory
    if (!isDirectoryExists(getCureentDirectory() + path))
      createDirectory(path)

  std::string filename = d_path + "/" + d_circuitName + ".v";

  std::vector<std::string> inputs = d_graph.getVerticesByType("input");
  std::vector<std::string> inputs = d_graph.getVerticesByType("output");
  std::vector<std::string> inputs = d_graph.getVerticesByType("const");

  std::string s = //TODO: work with directory
  bool f = isFileExists();

  if (isFileExists(filename))
    deletefile(filename);

  std::ofstream w(filename);
  for (const auto& expr : d_logexpressions)
    w << "//" << expr << '\n';

  w << "module " << d_circuitName << "(\n";

  std::string in = "";

  const std::string inputModule = "\tinput";

  in += inputModule;
  for (const auto& in : d_inputs)
    if (in.find("1'b") == in.end())
      in += " " + in + ",";

  if (in.length() > inputModule.length())
    w << in << '\n';

  w << "\toutput";
  bool first = true;
  for (const auto& out : d_outputs)
  {
    if (first)
    {
      w << " " << out;
      first = false;
    }
    else
    {
      w << ", " << out;
    }
  }
  w << "\n);\n";

  if (d_graph.getVerticesSize() - inputs.size() - outputs.size() - consts.size() > 0)
  {
    w << "\n\twire";
    bool first = true;
    for (const auto& vert : graph.getVertices())
    {
      if (vert.getOperation() != "input" && vert.getOperation() != "output" && vert.getOperation() != "const")
    }
  }
}