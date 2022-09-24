#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/netanim-module.h"

using ns3::ndn::StackHelper;
using ns3::ndn::AppHelper;
using ns3::ndn::GlobalRoutingHelper;
using ns3::ndn::StrategyChoiceHelper;

namespace ns3 {

int
main(int argc, char* argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);

  AnnotatedTopologyReader topologyReader("", 25);
  topologyReader.SetFileName("/home/bertopeng17/ndnSIM/ns-3/src/ndnSIM/examples/topologies/topo-indonesia-inheren.txt");
  topologyReader.Read();

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.InstallAll();

  // Installing global routing interface on all nodes

  GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();


  // Getting containers for the consumer/producer
  Ptr<Node> producer1 = Names::Find<Node>("manado");
  Ptr<Node> producer2 = Names::Find<Node>("samarinda");

  Ptr<Node> consumer1 = Names::Find<Node>("malang");
  Ptr<Node> consumer2 = Names::Find<Node>("semarang");


  // Define name prefixes
  std::string prefix1 = "/prefix1";
  std::string prefix2 = "/prefix2";

 
 
  // Install different forwarding strategies for prefix1, prefix2
  StrategyChoiceHelper::InstallAll("/prefix1", "/localhost/nfd/strategy/multicast");
  StrategyChoiceHelper::InstallAll("/prefix2", "/localhost/nfd/strategy/multicast");


  // Install NDN applications
  AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  consumerHelper.SetPrefix(prefix1);
  consumerHelper.SetAttribute("Frequency", StringValue("500")); // 500 interests a second
  consumerHelper.Install(consumer1);
  consumerHelper.SetPrefix(prefix2);
  consumerHelper.SetAttribute("Frequency", StringValue("500")); // 500 interests a second
  consumerHelper.Install(consumer2);


  AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetPrefix(prefix1);
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(producer1);

  producerHelper.SetPrefix(prefix2);
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(producer2);

   // Add /prefix1 and /prefix2 origins to ndn::GlobalRouter
  ndnGlobalRoutingHelper.AddOrigins(prefix1, producer1);
  ndnGlobalRoutingHelper.AddOrigins(prefix2, producer2);

 
  // Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes();
  
  Simulator::Stop(Seconds(5.0));
  L2RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/paper/L2RateTracer-int500.txt");     

  ndn::L3RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/paper/L3RateTracer-int500.txt");

  ndn::AppDelayTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/paper/Delay-int500.txt");
  
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}

