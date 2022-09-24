// ndn-simple.cpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"

using ns3::ndn::StackHelper;
using ns3::ndn::AppHelper;
using ns3::ndn::GlobalRoutingHelper;
using ns3::ndn::StrategyChoiceHelper;
namespace ns3 {

int
main(int argc, char* argv[])
{
  // setting default parameters for PointToPoint links and channels
  Config::SetDefault("ns3::PointToPointNetDevice::DataRate", StringValue("100Mbps"));
  Config::SetDefault("ns3::PointToPointChannel::Delay", StringValue("1ms"));
  Config::SetDefault("ns3::DropTailQueue::MaxPackets", StringValue("1024"));

  // Read optional command-line parameters (e.g., enable visualizer with ./waf --run=<> --visualize
  CommandLine cmd;
  cmd.Parse(argc, argv);

  // Creating nodes
  NodeContainer nodes;
  nodes.Create(32);

  // Connecting nodes using two links
  PointToPointHelper p2p;

  p2p.Install(nodes.Get(0), nodes.Get(1)); //aceh > medan
  p2p.Install(nodes.Get(1), nodes.Get(2)); //medan > padang
  p2p.Install(nodes.Get(1), nodes.Get(4)); //medan > pekanbaru
  p2p.Install(nodes.Get(2), nodes.Get(3)); //padang>jambi
  p2p.Install(nodes.Get(3), nodes.Get(7)); //jambi>bandarlampung
  p2p.Install(nodes.Get(4), nodes.Get(6)); //pekanbar>palembang
  p2p.Install(nodes.Get(4), nodes.Get(7)); //pekanbaru-bandarlampung
  p2p.Install(nodes.Get(6), nodes.Get(5)); //palembang-bengkulu
  p2p.Install(nodes.Get(7), nodes.Get(8)); //bandarlampung-serang
  p2p.Install(nodes.Get(8), nodes.Get(9)); //serang-jkt-ui
  p2p.Install(nodes.Get(9), nodes.Get(10)); //jkt-ui-jkt-dikti
  p2p.Install(nodes.Get(9), nodes.Get(11)); //jkt-ui-bandung
  p2p.Install(nodes.Get(10), nodes.Get(12)); //jkt-dikti-semarang
  p2p.Install(nodes.Get(11), nodes.Get(13)); //bandung-jogjakarta
  p2p.Install(nodes.Get(13), nodes.Get(12)); //jogjakarta-semarang
  p2p.Install(nodes.Get(12), nodes.Get(14)); //semarang-surabaya
  p2p.Install(nodes.Get(13), nodes.Get(15)); //jogjakarta-malang
  p2p.Install(nodes.Get(15), nodes.Get(14)); //malang-surabaya
  p2p.Install(nodes.Get(14), nodes.Get(25)); //surabaya-denpasar
  p2p.Install(nodes.Get(14), nodes.Get(26)); //surabaya-mataram
  p2p.Install(nodes.Get(26), nodes.Get(5)); //surabaya-bengkulu
  p2p.Install(nodes.Get(14), nodes.Get(18)); //surabaya-banjarmasin
  p2p.Install(nodes.Get(14), nodes.Get(23)); //surabaya-makasar
  p2p.Install(nodes.Get(25), nodes.Get(26)); //denpasar-mataram
  p2p.Install(nodes.Get(25), nodes.Get(27)); //denpasar-kupang
  p2p.Install(nodes.Get(27), nodes.Get(24)); //denpasar-kendari
  p2p.Install(nodes.Get(24), nodes.Get(23)); //kendari-makasar
  p2p.Install(nodes.Get(23), nodes.Get(22)); //makasar-palu
  p2p.Install(nodes.Get(22), nodes.Get(20)); //palu-gorontalo
  p2p.Install(nodes.Get(20), nodes.Get(21)); //gorontalo-manado
  p2p.Install(nodes.Get(21), nodes.Get(19)); //manado-samarinda
  p2p.Install(nodes.Get(19), nodes.Get(18)); //samarinda-banjarmasin
  p2p.Install(nodes.Get(18), nodes.Get(17)); //banjarmasin-palangkaraya
  p2p.Install(nodes.Get(17), nodes.Get(16)); //palangkaraya-pontianak
  p2p.Install(nodes.Get(16), nodes.Get(0)); //pontianak-banda-aceh


  //p2p.Install(nodes.Get(0), nodes.Get(2));
  //p2p.Install(nodes.Get(0), nodes.Get(3));
  //p2p.Install(nodes.Get(0), nodes.Get(4));
  //p2p.Install(nodes.Get(0), nodes.Get(5));

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetDefaultRoutes(true);
  ndnHelper.InstallAll();

  // Choosing forwarding strategy
  ndn::StrategyChoiceHelper::InstallAll("/prefix1", "/localhost/nfd/strategy/multicast");
  ndn::StrategyChoiceHelper::InstallAll("/prefix2", "/localhost/nfd/strategy/multicast");
  ndn::StrategyChoiceHelper::InstallAll("/prefix3", "/localhost/nfd/strategy/multicast");
  // Installing applications

  // Consumer
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  
   // Consumer will request /prefix/0, /prefix/1, ...
  consumerHelper.SetPrefix("/prefix1");
  consumerHelper.SetAttribute("Frequency", StringValue("100")); // 10 interests a second
  consumerHelper.Install(nodes.Get(7));                        // bandarlampung
 
  consumerHelper.SetPrefix("/prefix2");
  consumerHelper.SetAttribute("Frequency", StringValue("100")); // 10 interests a second
  consumerHelper.Install(nodes.Get(27));                        // kupang

  consumerHelper.SetPrefix("/prefix3");
  consumerHelper.SetAttribute("Frequency", StringValue("100")); // 10 interests a second
  consumerHelper.Install(nodes.Get(21));                        // kupang




  // Producer
  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  // Producer will reply to all requests starting with /prefix
  producerHelper.SetPrefix("/prefix1");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(nodes.Get(14)); // surabaya
 
 // Producer will reply to all requests starting with /prefix
  producerHelper.SetPrefix("/prefix2");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper.Install(nodes.Get(17)); // palangkaraya


 // Producer will reply to all requests starting with /prefix
  //producerHelper.SetPrefix("/prefix3");
  //producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  //producerHelper.Install(nodes.Get(0)); // aceh

// Calculate and install FIBs
  GlobalRoutingHelper::CalculateRoutes();

  ndn::AppDelayTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/Delay-differentstrategy-ncc.txt");
  L2RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/L2-differentstrategy-ncc.txt");
  ndn::L3RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/L3-differentstrategy-ncc.txt");

  Simulator::Stop(Seconds(60.0));

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
