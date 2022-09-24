#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ndnSIM-module.h"


namespace ns3 {

int
main(int argc, char* argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);

  AnnotatedTopologyReader topologyReader("", 23);
  topologyReader.SetFileName("/home/bertopeng17/ndnSIM/ns-3/src/ndnSIM/examples/topologies/topo-palaparing.txt");
  topologyReader.Read();

  /****************************************************************************/
  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetOldContentStore("ns3::ndn::cs::Lru", "MaxSize", "1000");
  ndnHelper.InstallAll();



 // Set BestRoute strategy
  ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/multicast");



  /****************************************************************************/
  // Installing global routing interface on all nodes
  ndn::GlobalRoutingHelper ndnGlobalRoutingHelper;
  ndnGlobalRoutingHelper.InstallAll();
  /****************************************************************************/
  // Getting containers for the consumer/producer
  Ptr<Node> consumer1 = Names::Find<Node>("palembang");
  Ptr<Node> consumer2 = Names::Find<Node>("surabaya");
  Ptr<Node> consumer3 = Names::Find<Node>("ambon");
  Ptr<Node> consumer4 = Names::Find<Node>("manado");
  Ptr<Node> consumer5 = Names::Find<Node>("jayapura");
  Ptr<Node> consumer6 = Names::Find<Node>("mentawai");
  Ptr<Node> consumer7 = Names::Find<Node>("malang");
  Ptr<Node> consumer8 = Names::Find<Node>("wakatobi");


  Ptr<Node> producer1 = Names::Find<Node>("aceh");
  Ptr<Node> producer2 = Names::Find<Node>("jakarta");
  Ptr<Node> producer3 = Names::Find<Node>("pontianak");
  Ptr<Node> producer4 = Names::Find<Node>("makasar");
  Ptr<Node> producer5 = Names::Find<Node>("nabire");
  Ptr<Node> producer6 = Names::Find<Node>("natuna");
  Ptr<Node> producer7 = Names::Find<Node>("nunukan");
  Ptr<Node> producer8 = Names::Find<Node>("tebangan");





  /****************************************************************************/
  ndn::AppHelper consumerHelper("ns3::ndn::ConsumerCbr");
  consumerHelper.SetAttribute("Frequency", StringValue("100")); // interests per Second
  consumerHelper.SetAttribute("Randomize", StringValue("uniform"));
  /****************************************************************************/
  // on the first to ninth consumer node install a Consumer application
  // that will express interests in /dst1 to /dst9 namespace
 
  consumerHelper.SetPrefix("/aceh");
  consumerHelper.Install(consumer1);  

  consumerHelper.SetPrefix("/jakarta");
  consumerHelper.Install(consumer2);

  consumerHelper.SetPrefix("/pontianak");
  consumerHelper.Install(consumer3);

  consumerHelper.SetPrefix("/makasar");
  consumerHelper.Install(consumer4);

  consumerHelper.SetPrefix("/nabire");
  consumerHelper.Install(consumer5);

  consumerHelper.SetPrefix("/natuna");
  consumerHelper.Install(consumer6);

  consumerHelper.SetPrefix("/nunukan");
  consumerHelper.Install(consumer7);

  consumerHelper.SetPrefix("/tebangan");
  consumerHelper.Install(consumer8);


  /****************************************************************************/
  ndn::AppHelper producerHelper("ns3::ndn::Producer");
  producerHelper.SetAttribute("PayloadSize", StringValue("1024"));
  /****************************************************************************/
  // Register /dst1 to /dst9 prefix with global routing controller and
  // install producer that will satisfy Interests in /dst1 to /dst9 namespace
  ndnGlobalRoutingHelper.AddOrigins("/aceh", producer1);
  producerHelper.SetPrefix("/aceh");
  producerHelper.Install(producer1);

  ndnGlobalRoutingHelper.AddOrigins("/jakarta", producer2);
  producerHelper.SetPrefix("/jakarta");
  producerHelper.Install(producer2);

  ndnGlobalRoutingHelper.AddOrigins("/pontianak", producer3);
  producerHelper.SetPrefix("/pontianak");
  producerHelper.Install(producer3);

  ndnGlobalRoutingHelper.AddOrigins("/makasar", producer4);
  producerHelper.SetPrefix("/makasar");
  producerHelper.Install(producer4);

  ndnGlobalRoutingHelper.AddOrigins("/nabire", producer5);
  producerHelper.SetPrefix("/nabire");
  producerHelper.Install(producer5);

  ndnGlobalRoutingHelper.AddOrigins("/natuna", producer6);
  producerHelper.SetPrefix("/natuna");
  producerHelper.Install(producer6);

  ndnGlobalRoutingHelper.AddOrigins("/nunukan", producer7);
  producerHelper.SetPrefix("/nunukan");
  producerHelper.Install(producer7);

  ndnGlobalRoutingHelper.AddOrigins("/tebangan", producer8);
  producerHelper.SetPrefix("/tebangan");
  producerHelper.Install(producer8);

  /*****************************************************************************/
  // Calculate and install FIBs
  ndn::GlobalRoutingHelper::CalculateRoutes();

  Simulator::Stop(Seconds(20.0));


  

  /****************************************************************************/
  // Tracer:

 // L2RateTracer::InstallAll("/home/bertopeng17/ndnSIM/ns-3/data-tracer-inherent/drop-trace-all.txt", Seconds(0.5));


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
