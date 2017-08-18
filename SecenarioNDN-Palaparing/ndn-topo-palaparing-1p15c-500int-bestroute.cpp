// ndn-congestion-topo-plugin.cpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"


using namespace ns3;
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

  AnnotatedTopologyReader topologyReader("", 23);
  topologyReader.SetFileName("src/ndnSIM/examples/topologies/topo-palaparingv2.txt");
  topologyReader.Read();

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize", "100");
  ndnHelper.InstallAll();
  ndnHelper.SetDefaultRoutes(true);



  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();

  // Getting containers for the consumer/producer
  Ptr<Node> producer = Names::Find<Node>("medan");
  NodeContainer consumerNodes;
  consumerNodes.Add(Names::Find<Node>("pekanbaru"));
  consumerNodes.Add(Names::Find<Node>("bengkulu"));
  consumerNodes.Add(Names::Find<Node>("surabaya"));
  consumerNodes.Add(Names::Find<Node>("kutaibarat"));
  consumerNodes.Add(Names::Find<Node>("wakatobi"));
  consumerNodes.Add(Names::Find<Node>("palamea"));
  consumerNodes.Add(Names::Find<Node>("wamena"));
  consumerNodes.Add(Names::Find<Node>("talaud"));
  consumerNodes.Add(Names::Find<Node>("pulaurote"));
  consumerNodes.Add(Names::Find<Node>("timika"));
  consumerNodes.Add(Names::Find<Node>("gorontalo"));
  consumerNodes.Add(Names::Find<Node>("denpasar"));
  consumerNodes.Add(Names::Find<Node>("bunyu"));
  consumerNodes.Add(Names::Find<Node>("sabang"));
  consumerNodes.Add(Names::Find<Node>("natuna"));
 
  

// Define 30 name prefixes
  std::string prefix = "/prefix";
  

// Install different forwarding strategies for prefix1, prefix2
  ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/best-route");
 
  //ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  consumerHelper.SetPrefix(prefix);
  consumerHelper.SetAttribute("Frequency", StringValue("500")); // 500 interests a second
  consumerHelper.Install(consumerNodes);


  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetPrefix(prefix);
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(producer);

   // Add /prefix origins to ndn::GlobalRouter
  ndnGlobalRoutingHelper.AddOrigins(prefix, producer);
  
  
  // Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes();


  ndn::AppDelayTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-thesis/Delay-bestroute-5s-500interest.txt");
  L2RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-thesis/L2-bestroute-5s-500interest.txt");
  ndn::L3RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-thesis/L3-bestroute-5s-500interest.txt");

  Simulator::Stop(Seconds(5.0));
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
