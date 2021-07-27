#include <iostream>
#include <sstream>
#include <string>

#include "flow_graph.h"

void myAssert(const std::string& name, const std::string& got, const std::string& expected) {
  if (got == expected) {
    std::cerr << name << " is ok" << std::endl;
  } else {
    std::cerr << "Error: expected " << expected << ", got: " << got << std::endl;
  }
}

void testEdgeOther() {
  int e_from = 0;
  int e_to = 1;
  FlowEdge fe {e_from, e_to, 5};
  myAssert("Edge to, other", std::to_string(fe.other(e_to)), "0");
  myAssert("Edge from, other", std::to_string(fe.other(e_from)), "1");
}

void testGraphResidual() {
  int e1_from = 0;
  int e1_to = 1;
  FlowEdge e1 {e1_from, e1_to, 5};
  std::ostringstream os;
  e1.flow = 4;
  os << e1.residualCapacityTo(e1_from) << " " << e1.residualCapacityTo(e1_to);
  std::string result = "4 1";
  myAssert("Residual capacity", os.str(), result);
}

void testGraphChangeFlow() {
  int e1_from = 0;
  int e1_to = 1;
  FlowEdge e1 {e1_from, e1_to, 5};
  std::ostringstream os;
  e1.changeFlowTo(e1_to, 5);
  os << e1.flow;
  std::string result = "5";
  myAssert("Flow to", os.str(), result);
  e1.changeFlowTo(e1_from, 2);
  std::string got = std::to_string(static_cast<int>(e1.flow));
  std::string result_from = "3";
  myAssert("Flow from", got, result_from);
}

void testAddAndChangeEdge() {
  FlowGraph fg(2);
  fg.addEdge({0, 1, 10});
  std::string got = std::to_string(static_cast<int>(fg.adj(0)[0].flow));
  std::string result = "0";
  int vertex_to = 1;
  myAssert("Add edge and adjacent: flow", got, result);
  std::string got_rescap = std::to_string(static_cast<int>(fg.adj(0)[0]
        .residualCapacityTo(vertex_to)));
  myAssert("Residual capacity in graph", got_rescap, "10"); 
  fg.adj(0)[0].changeFlowTo(vertex_to, 5);
  std::string got_second = std::to_string(static_cast<int>(fg.adj(0)[0].flow));
  myAssert("Change flow in graph", got_second, "5");
}



int main() {
  testEdgeOther();
  testGraphResidual();
  testGraphChangeFlow();
  testAddAndChangeEdge();
  return 0;
}
