#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"

#include "ndn-load-balancer/random-load-balancer-strategy.hpp"

using namespace ns3;




using ns3::ndn::StackHelper;
using ns3::ndn::AppHelper;
using ns3::ndn::GlobalRoutingHelper;
using ns3::ndn::StrategyChoiceHelper;
using ns3::AnnotatedTopologyReader;

int
main(int argc, char* argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);

  AnnotatedTopologyReader topologyReader("", 25);
  //topologyReader.SetFileName("src/ndnSIM/examples/topologies/topo-load-balancer.txt");
  topologyReader.SetFileName("src/ndnSIM/examples/topologies/topo-uin.txt");
  topologyReader.Read();

  // Install NDN stack on all nodes
  StackHelper ndnHelper;
  ndnHelper.InstallAll();

  // Installing global routing interface on all nodes
  GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();

  // Getting containers for the consumer/producer
  Ptr<Node> producer1 = Names::Find<Node>("uin-surabaya");
  Ptr<Node> producer2 = Names::Find<Node>("uin-jember");
  NodeContainer consumerNodes;
  consumerNodes.Add(Names::Find<Node>("uin-surakarta"));

  // Install NDN applications
  std::string prefix = "/surabaya/hello";

  // Install random-load-balancer forwarding strategy in
  // node UCLA-HUB
  StrategyChoiceHelper::Install<nfd::fw::RandomLoadBalancerStrategy>(Names::Find<Node>("uin-malang"),
                                                                     prefix);

  AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  consumerHelper.SetPrefix(prefix);
  consumerHelper.SetAttribute("Frequency", StringValue("1500")); // 100 interests a second
  consumerHelper.Install(consumerNodes);

  AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetPrefix(prefix);
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(producer1);
  producerHelper.Install(producer2);

  // Add /prefix origins to ndn::GlobalRouter
  ndnGlobalRoutingHelper.AddOrigins(prefix, producer1);
  ndnGlobalRoutingHelper.AddOrigins(prefix, producer2);

  // Calculate and install FIBs
  GlobalRoutingHelper::CalculateRoutes();

  L2RateTracer::InstallAll("/home/eki/Datatracer/load-balancer-l2trace-uin.txt-5s", Seconds(5.0));
  ns3::ndn::L3RateTracer::InstallAll("/home/eki/Datatracer/load-balancer-l3trace-uin-5s.txt",Seconds(5.0));
  ns3::ndn::AppDelayTracer::InstallAll("/home/eki/Datatracer/load-balancer-appdelay-uin-5s.txt");
  

Simulator::Stop(Seconds(5.0));

  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
