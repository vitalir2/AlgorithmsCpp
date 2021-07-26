#include <iostream>
#include <sstream>
#include <string>

#include "flow_graph.h"

void testGraphResidual() {
  int e1_from = 0;
  int e1_to = 1;
  FlowEdge e1 {e1_from, e1_to, 5};
  std::ostringstream os;
  e1.flow = 4;
  os << e1.residualCapacityTo(e1_from) << " " << e1.residualCapacityTo(e1_to);
  std::string result = "4 1";
  if (os.str() == result) {
    std::cerr << "Residual capacity is ok" << std::endl;
  } else {
    std::cerr << "Error: expected " << result << ", got: " << os.str() << std::endl;
  }
}

void testGraphChangeFlow() {
  int e1_from = 0;
  int e1_to = 1;
  FlowEdge e1 {e1_from, e1_to, 5};
  std::ostringstream os;
  e1.changeFlowTo(e1_to, 5);
  os << e1.flow;
  std::string result = "5";
  if (os.str() == result) {
    std::cerr << "Flow to is ok" << std::endl;
  } else {
    std::cerr << "Error: expected " << result << ", got: " << os.str() << std::endl;
  }
  e1.changeFlowTo(e1_from, 2);
  std::string got = std::to_string(static_cast<int>(e1.flow));
  std::string result_from = "3";
  if (got == result_from) {
    std::cerr << "Flow from is ok" << std::endl;
  } else {
    std::cerr << "Error: expected " << result << ", got: " << got << std::endl;
  }
}

int main() {
  testGraphResidual();
  testGraphChangeFlow();
  return 0;
}
