#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"


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
  StackHelper ndnHelper;
  ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize", "50");
  ndnHelper.InstallAll();

  // Installing global routing interface on all nodes
  GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();

  // Getting containers for the consumer/producer
  Ptr<Node> producer1 = Names::Find<Node>("palembang");
  Ptr<Node> producer2 = Names::Find<Node>("bandung");
  Ptr<Node> producer3 = Names::Find<Node>("manado");
  
  Ptr<Node> consumer1 = Names::Find<Node>("jayapura");
  Ptr<Node> consumer2 = Names::Find<Node>("manokwari");
  Ptr<Node> consumer3 = Names::Find<Node>("kupang");

 

  // Define name prefixes
  std::string prefix1 = "ndn/palembang/makanan/pempek";
  std::string prefix2 = "ndn/bandung/makanan/cireng";
  std::string prefix3 = "ndn/manado/wisata/bunaken";
  
 
  // Install different forwarding strategies for prefix1, prefix2
  StrategyChoiceHelper::InstallAll ("prefix1", "/localhost/nfd/strategy/multicast");
  StrategyChoiceHelper::InstallAll ("prefix2", "/localhost/nfd/strategy/multicast");
  StrategyChoiceHelper::InstallAll ("prefix3", "/localhost/nfd/strategy/multicast");
 
  // Install NDN applications
  AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  consumerHelper.SetPrefix("/prefix1");
  consumerHelper.SetAttribute("Frequency", StringValue("500")); // 1000 interests a second
  consumerHelper.Install(consumer1);
  consumerHelper.SetPrefix("/prefix2");
  consumerHelper.SetAttribute("Frequency", StringValue("500")); // 1000 interests a second
  consumerHelper.Install(consumer2);
  consumerHelper.SetPrefix("/prefix3");
  consumerHelper.SetAttribute("Frequency", StringValue("500")); // 1000 interests a second
  consumerHelper.Install(consumer3);


  AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetPrefix("/prefix1");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(producer1);

  producerHelper.SetPrefix("/prefix2");
  producerHelper.Install(producer2);

  producerHelper.SetPrefix("/prefix3");
  producerHelper.Install(producer3);


  // Add /prefix1 and /prefix2 origins to ndn::GlobalRouter
  ndnGlobalRoutingHelper.AddOrigins("/prefix1", producer1);
  ndnGlobalRoutingHelper.AddOrigins("/prefix2", producer2);
  ndnGlobalRoutingHelper.AddOrigins("/prefix3", producer3);
  // Calculate and install FIBs
  GlobalRoutingHelper::CalculateRoutes();

  ndn::AppDelayTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/Delay-differentstrategy-clientcontrol.txt");
  L2RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/L2-differentstrategy-clientcontrol.txt");
  ndn::L3RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/L3-differentstrategy-clientcontrol.txtt");
  Simulator::Stop(Seconds(300));
  
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

